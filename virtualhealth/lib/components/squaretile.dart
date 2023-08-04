import 'package:flutter/material.dart';

class SquareTile extends StatelessWidget {
  final String path;
  final Function()? signInWithGoogle;
  const SquareTile(
      {super.key, required this.path, required this.signInWithGoogle});

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: signInWithGoogle,
      child: Container(
        padding: EdgeInsets.all(10),
        decoration: BoxDecoration(
            color: Colors.grey.shade100,
            border: Border.all(color: Colors.white),
            borderRadius: BorderRadius.circular(16)),
        child: Image.asset(
          path,
          height: 45,
        ),
      ),
    );
  }
}
