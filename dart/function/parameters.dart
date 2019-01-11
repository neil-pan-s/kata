import 'dart:core';

// Optional named parameters - 可选具名参数
void testOptionalNamedParameters(int a, { String b = 'bbb', String c }) {
  print("Optional named parameters: $a - $b - $c");
}

// Optional positional parameters - 可选位置参数
void testOptionalPositionalParameters(int a, [ String b = 'bbb' , String c = 'ccc' ]) {
  print("Optional positional parameters: $a - $b - $c");
}

void main(List<String> args) {
  testOptionalNamedParameters(1);
  testOptionalNamedParameters(1, b: 'bbb');
  testOptionalNamedParameters(1, b: 'bbb', c: 'ccc');

  testOptionalPositionalParameters(2, 'bbb', 'ccc');
}