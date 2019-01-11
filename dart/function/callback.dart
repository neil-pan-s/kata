import 'dart:core';

typedef dynamic Callback ();

dynamic fnA (Callback cb) {
  return cb();
}

void main(List<String> args) {
  print(fnA(() => 123));
}