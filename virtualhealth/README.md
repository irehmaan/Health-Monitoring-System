# Smart Health Monitoring System


## Overview

The Smart Health Monitoring System is an IoT-based solution designed to monitor vital health statistics in real-time. This project uses ESP32 with the Max30100 sensor for data collection, Firebase Realtime Database (RTDB) for data storage, and a mobile app developed with Flutter for user-friendly access to health data. Firebase OAuth authentication ensures data security.

## Features

- **Real-time Monitoring**: Continuously tracks vital health data.
- **ESP32 & Max30100**: Utilizes ESP32 microcontroller with Max30100 sensor for accurate measurements.
- **Firebase RTDB**: Stores data in Firebase Realtime Database for easy access.
- **Mobile App (Flutter)**: Offers a user-friendly interface for monitoring health stats.
- **Firebase OAuth**: Ensures data security with secure authentication.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- **ESP32 Setup**: Configure your ESP32 with the Max30100 sensor.
- **Firebase Account**: Create a Firebase account and set up a Realtime Database.
- **Flutter Installation**: Install Flutter for mobile app development.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/SmartHealthMonitoring.git
2. Configure the ESP32 with Max30100 as per the provided documentation.

3. Set up Firebase credentials and configure the database. Update the Firebase configuration in the mobile app code.

4. Build and install the Flutter mobile app.

## Usage
1. Run the ESP32 code to start collecting health data from the Max30100 sensor.

2. Open the Flutter app on your mobile device and log in using Firebase OAuth authentication.

3. Access real-time health data, monitor vitals, and receive alerts as needed.

## Contributing
Contributions are welcome! Please follow these steps to contribute to the project:

Fork the project.
Create a new branch for your feature or bugfix: git checkout -b feature/my-feature or bugfix/issue-description.
Commit your changes: git commit -m 'Add some feature'.
Push to your branch: git push origin feature/my-feature.
Submit a pull request to the main branch.
