// Adding features to a class: mixins
// Mixins are a way of reusing a class’s code in multiple class hierarchies.

// To use a mixin, use the with keyword followed by one or more mixin names. The following example shows two classes that use mixins:

mixin Musical {
  bool canPlayPiano = false;
  bool canCompose = false;
  bool canConduct = false;

  void entertainMe() {
    if (canPlayPiano) {
      print('Playing piano');
    } else if (canConduct) {
      print('Waving hands');
    } else {
      print('Humming to self');
    }
  }
}

class Musician with Musical {

  // ···

}

// To specify that only certain types can use the mixin — for example, so your mixin can invoke a method that it doesn’t define — use on to specify the required superclass:
mixin MusicalPerformer on Musician {
  // ···
}