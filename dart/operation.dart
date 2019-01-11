class Point {
  int x;
  int y; 
}

void main(List<String> args) {
  
  // ~/ 
  assert(5 / 2 == 2.5); // Result is a double
  assert(5 ~/ 2 == 2); // Result is an int

  // ??
  // Assign value to b if b is null; otherwise, b stays the same
  var b = null;
  const value = 1;
  // same to js: b = b || value;
  b ??= value;

  assert(b == 1);

  // expr1 ?? expr2
  // If expr1 is non-null, returns its value; otherwise, evaluates and returns the value of expr2.
  const c = null;
  assert((c ?? 2) == 2);


  // Cascade notation (..)
  // Cascades (..) allow you to make a sequence of operations on the same object. In addition to function calls, you can also access fields on that same object. This often saves you the step of creating a temporary variable and allows you to write more fluid code.
  // Strictly speaking, the “double dot” notation for cascades is not an operator. It’s just part of the Dart syntax.
  var sb = StringBuffer();
  sb
    ..write('Use a StringBuffer for ')
    ..writeAll(['efficient', 'string', 'creation'], ' ')
    ..write('.');

  var fullString = sb.toString();

  assert(fullString ==
      'Use a StringBuffer for efficient string creation.');  


  // ?. Conditional member access


  var p = Point();
  p.y = 2;
  assert(p?.y == 2);
  p = null;
  assert(p?.y == null);
}