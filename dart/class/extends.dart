class Television {
  void turnOn() {
    // _illuminateDisplay();
    // _activateIrSensor();
  }
  // ···
}

class SmartTelevision extends Television {
  void turnOn() {
    super.turnOn();
    // _bootNetworkInterface();
    // _initializeMemory();
    // _upgradeApps();
  }
  // ···
}

// override
class SmartTelevision1 extends Television {
  @override
  void turnOn() { 
    // ···
  }
}

// Here’s an example of a class that overrides the + and - operators:

class Vector {
  final int x, y;

  Vector(this.x, this.y);

  Vector operator +(Vector v) => Vector(x + v.x, y + v.y);
  Vector operator -(Vector v) => Vector(x - v.x, y - v.y);

  // Operator == and hashCode not shown. For details, see note below.
  // ···
}

void main() {
  final v = Vector(2, 3);
  final w = Vector(2, 2);

  assert(v + w == Vector(4, 5));
  assert(v - w == Vector(0, 1));
}

// noSuchMethod()
// To detect or react whenever code attempts to use a non-existent method or instance variable, you can override noSuchMethod():

class A {
  // Unless you override noSuchMethod, using a
  // non-existent member results in a NoSuchMethodError.
  @override
  void noSuchMethod(Invocation invocation) {
    print('You tried to use a non-existent member: ' +
        '${invocation.memberName}');
  }
}