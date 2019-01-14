import 'package:test/test.dart';

import 'hello-person.dart' as hello_person;
import 'hello-world.dart' as hello_world;

void main() {
  group('hello_person ', hello_person.main);
  group('hello_world ', hello_world.main);
}