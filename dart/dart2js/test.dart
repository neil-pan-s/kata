import 'dart:core';

// List<String> supported
void testList() {
  var list = new List<String>();
  list.add('a');
  list.add('b');
  list.add('c');
  print(list.join('-'));
}

// use below statement will throw error
// maybe js main function have no List<String> args
// void main(List<String> args) {

void main() {
  print('hello world');
  testList(); 
}