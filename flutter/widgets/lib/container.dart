import 'package:flutter/material.dart';

void main() {
  runApp(
    new Container(
      alignment: Alignment.center,
      color: Colors.blue,
      margin: EdgeInsets.fromLTRB(10, 50, 10, 50),
      child: new Text(
        'Hello, world!',
        textDirection: TextDirection.ltr,
      ),
    ),
  );
}