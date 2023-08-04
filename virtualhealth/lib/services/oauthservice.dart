import 'package:firebase_auth/firebase_auth.dart';
import 'package:google_sign_in/google_sign_in.dart';

class OAuth {
  signInWithGoogle() async {
    final GoogleSignInAccount? currUser = await GoogleSignIn().signIn();

    final GoogleSignInAuthentication currAuth = await currUser!.authentication;

    final creds = GoogleAuthProvider.credential(
        accessToken: currAuth.accessToken, idToken: currAuth.idToken);

    return await FirebaseAuth.instance.signInWithCredential(creds);
  }
}
