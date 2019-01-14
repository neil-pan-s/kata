import 'package:hello/hello.dart';
import 'package:test/test.dart';

void main() {
  group('sayHelloWorld group', () {
    test('sayHelloWorld test', () {
      var hello = sayHelloWorld();
      expect(hello, equals('hello world'));
    });
  });
}