#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#endif
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "JioFiber_4G"
#define WIFI_PASSWORD "Playgod@98"

#define API_KEY "AIzaSyCrYg2xcdfuBtgQ7SVCWoP5DD3yonhflsQ"

/* 3. Define the user Email and password that already registerd or added in your project */
#define USER_EMAIL "horizon613pluto@gmail.com"
#define USER_PASSWORD "12345678"

/* 4. If work with RTDB, define the RTDB URL */
#define DATABASE_URL "https://virtualhealth-287-default-rtdb.asia-southeast1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app


// Define Firebase Data object
FirebaseData fbdo;
FirebaseData stream;

FirebaseAuth auth;
FirebaseConfig config;

String uid;
unsigned long sendDataPrevMillis = 0;


String childPath[3] = {"/SensorData"};

#define pushbutton 19


// time period interval in which sensor collects readings
#define REPORTING_PERIOD_MS     500

PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat Detected!");
}
void setup()
{

  Serial.begin(115200); 
   Serial.print("Initializing pulse oximeter..");
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_14_2MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
   
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Or use legacy authenticate method
  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "<database secret>";

  // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);

  // You can use TCP KeepAlive For more reliable stream operation and tracking the server connection status, please read this for detail.
  // https://github.com/mobizt/Firebase-ESP32#enable-tcp-keepalive-for-reliable-http-streaming
  stream.keepAlive(5, 5, 1);

  // The data under the node being stream (parent path) should keep small
  // Large stream payload leads to the parsing error due to memory allocation.

  // The MultiPathStream works as normal stream with the payload parsing function.
  Serial.println("Fetching User ID");
  while ((auth.token.uid) == "") {
    Serial.println('.');
    delay(1000);
  }
  uid = auth.token.uid.c_str();
  Serial.print("User ID: ");
  Serial.println(uid);
}

void loop()
{
   float bpm = pox.getSpO2();

  // Firebase.ready() should be called repeatedly to handle authentication tasks.

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
   String parentPath = "/users/"+uid+"/SensorData";
    Serial.print("\nSet json...");

    FirebaseJson json;

    for (size_t i = 0; i < 10; i++)
    {
      json.set("MAX30100/SpO2",bpm);
      json.set("MAX30100/Heart Rate",pox.getHeartRate());

      // The response is ignored in this async function, it may return true as long as the connection is established.
      // The purpose for this async function is to set, push and update data instantly.
      Firebase.setJSONAsync(fbdo, parentPath, json);
//      count++;
    }

    Serial.println("ok\n");
  }

  // After calling stream.keepAlive, now we can track the server connecting status
  if (!stream.httpConnected())
  {
    // Server was disconnected!
  }
     
      pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
 
        tsLastReport = millis();
    }
}
