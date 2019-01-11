abstract class ObjectCache {
  Object getByKey(String key);
  void setByKey(String key, Object value);
}

abstract class StringCache {
  String getByKey(String key);
  void setByKey(String key, String value);
}

abstract class Cache<T> {
  T getByKey(String key);
  void setByKey(String key, T value);
}


// Restricting the parameterized type
// When implementing a generic type, you might want to limit the types of its parameters. You can do this using extends.

// class Foo<T extends SomeBaseClass> {
//   // Implementation goes here...
//   String toString() => "Instance of 'Foo<$T>'";
// }

// class Extender extends SomeBaseClass {...}