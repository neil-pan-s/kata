// Using generic methods
// Initially, Dart’s generic support was limited to classes. A newer syntax, called generic methods, allows type arguments on methods and functions:

T first<T>(List<T> ts) {
  // Do some initial work or error checking, then...
  T tmp = ts[0];
  // Do some additional checking or processing...
  return tmp;
}
// Here the generic type parameter on first (<T>) allows you to use the type argument T in several places:

// In the function’s return type (T).
// In the type of an argument (List<T>).
// In the type of a local variable (T tmp).