import 'package:hello/hello.dart';
import 'package:test/test.dart';

void main() {
  group('sayHelloPerson group', () {
    test('sayHelloPerson test', () {
      var hello = sayHelloPerson('neil');
      expect(hello, equals('hello neil'));
    });
  });
}