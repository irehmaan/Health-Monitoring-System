import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:virtualhealth/components/button.dart';
import 'package:virtualhealth/components/squaretile.dart';
import 'package:virtualhealth/components/textfield.dart';
import 'package:virtualhealth/services/oauthservice.dart';

class LoginPage extends StatefulWidget {
  final Function()? onTap;
  const LoginPage({super.key, required this.onTap});

  @override
  State<LoginPage> createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  final TextEditingController usernameController = TextEditingController();
  final TextEditingController passwordController = TextEditingController();

  // sign in function
  void signIn() async {
    showDialog(
        context: context,
        builder: (context) {
          return const Center(
            child: CircularProgressIndicator(),
          );
        });

    try {
      FirebaseAuth.instance.signInWithEmailAndPassword(
          email: usernameController.text, password: passwordController.text);
      Navigator.pop(context);
    } on FirebaseAuthException catch (e) {
      Navigator.pop(context);
      showErrorMessage(e.code);
    }
  }

  void showErrorMessage(String message) {
    showDialog(
        context: context,
        builder: (context) {
          return AlertDialog(
            title: Center(
              child: Text(message),
            ),
          );
        });
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
        child: Scaffold(
      body: Center(
        child: SingleChildScrollView(
          child: Column(
            children: [
              const Icon(
                Icons.monitor_heart_sharp,
                size: 40,
              ),
              const SizedBox(
                height: 8,
              ),
              const Text(
                "Welcome, Let's Get You Healthy !",
                style: TextStyle(fontSize: 20, fontStyle: FontStyle.italic),
              ),
              const SizedBox(
                height: 15,
              ),
              inputTextField(
                  controller: usernameController,
                  hintText: " Enter E-mail",
                  obscureText: false),
              const SizedBox(
                height: 10,
              ),
              inputTextField(
                  controller: passwordController,
                  hintText: " Enter your password",
                  obscureText: true),
              const SizedBox(
                height: 10,
              ),
              Button(onTap: signIn, text: "Sign in"),
              const SizedBox(
                height: 10,
              ),
              Padding(
                padding: const EdgeInsets.all(5.0),
                child: Row(
                  children: const [
                    Expanded(
                      child: Divider(
                        color: Colors.grey,
                        thickness: 0.7,
                        indent: 10,
                        endIndent: 10,
                        height: 20,
                      ),
                    ),
                    Text(
                      "or continue with",
                      style: TextStyle(
                        fontSize: 14,
                      ),
                    ),
                    Expanded(
                      child: Divider(
                        color: Colors.grey,
                        thickness: 0.7,
                        indent: 5,
                        endIndent: 5,
                        height: 20,
                      ),
                    ),
                  ],
                ),
              ),
              Padding(
                padding: const EdgeInsets.all(8.0),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    SquareTile(
                        path: "assets/images/google.png",
                        signInWithGoogle: () => OAuth().signInWithGoogle())
                  ],
                ),
              ),
              SizedBox(
                height: 10,
              ),
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  const Text("Not a member?"),
                  const SizedBox(
                    width: 5,
                  ),
                  GestureDetector(
                    onTap: widget.onTap,
                    child: const Text(
                      "Be a member of Smart Health !",
                      style: TextStyle(
                          color: Colors.green, fontStyle: FontStyle.italic),
                    ),
                  )
                ],
              )
            ],
          ),
        ),
      ),
    ));
  }
}
