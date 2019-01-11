
enum Color { red, green, blue }

void main(List<String> args) {

  // Each value in an enum has an index getter, which returns the zero-based position of the value in the enum declaration. For example, the first value has index 0, and the second value has index 1.
  assert(Color.red.index == 0);
  assert(Color.green.index == 1);
  assert(Color.blue.index == 2);

  // To get a list of all of the values in the enum, use the enum’s values constant.
  List<Color> colors = Color.values;
  assert(colors[2] == Color.blue);
}

