import 'dart:core';

// An anonymous function looks similar to a named function— zero or more parameters, separated by commas and optional type annotations, between parentheses.

// The code block that follows contains the function’s body:

// ([[Type] param1[, …]]) { 
//   codeBlock; 
// }; 

void main(List<String> args) {
  var list = ['apples', 'bananas', 'oranges'];
  list.forEach((item) {
    print('${list.indexOf(item)}: $item');
  });

  // error syntax
  // list.forEach((item) => {
  //   print('${list.indexOf(item)}: $item');
  // });

  list.forEach((item) => print('${list.indexOf(item)}: $item'));
  
}