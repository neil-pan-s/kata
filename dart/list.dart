import 'dart:core';

void main() {
  // Use a List constructor.
  var vegetables = List();

  // Or simply use a list literal.
  var fruits = ['apples', 'oranges'];

  // Access a list item by index.
  assert(fruits[0] == 'apples');

  // Find an item in a list.
  assert(fruits.indexOf('apples') == 0);  

  // Add to a list.
  fruits.add('kiwis');

  // Add multiple items to a list.
  fruits.addAll(['grapes', 'bananas']);

  // Get the list length.
  assert(fruits.length == 5);

  // Remove a single item.
  var appleIndex = fruits.indexOf('apples');
  fruits.removeAt(appleIndex);
  assert(fruits.length == 4);

  // Remove all elements from a list.
  fruits.clear();
  assert(fruits.length == 0);

}