class Point {
  num x, y;

  Point(num x, num y) {
    // There's a better way to do this, stay tuned.
    this.x = x;
    this.y = y;
  }
}

class Point1 {
  num x, y;

  // Syntactic sugar for setting x and y
  // before the constructor body runs.
  Point1(this.x, this.y);
}

// Redirecting constructors
// Sometimes a constructor’s only purpose is to redirect to another constructor in the same class. A redirecting constructor’s body is empty, with the constructor call appearing after a colon (:).

class Point2 {
  num x, y;

  // The main constructor for this class.
  Point2(this.x, this.y);

  // Delegates to the main constructor.
  Point2.alongXAxis(num x) : this(x, 0);
}

// Constant constructors
// If your class produces objects that never change, you can make these objects compile-time constants. To do this, define a const constructor and make sure that all instance variables are final.

class ImmutablePoint {
  static final ImmutablePoint origin =
      const ImmutablePoint(0, 0);

  final num x, y;

  const ImmutablePoint(this.x, this.y);
}

var a = const ImmutablePoint(1, 1);
var b = const ImmutablePoint(1, 1);

// assert(identical(a, b)); // They are the same instance!