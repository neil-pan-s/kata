import 'package:flutter/material.dart';

void main() {
  runApp(new Container(
    child: new Row(
      children: <Widget>[
        const Text('Flutter\'s hot reload helps you quickly and easily experiment, build UIs, add features, and fix bug faster. Experience sub-second reload times, without losing state, on emulators, simulators, and hardware for iOS and Android.', textDirection: TextDirection.ltr),
        const Icon(Icons.sentiment_very_satisfied, textDirection: TextDirection.ltr,),
      ],
  )));
}