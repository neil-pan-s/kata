import 'dart:core';

void main() {
  // Check whether a string contains another string.
  assert('Never odd or even'.contains('odd'));

  // Does a string start with another string?
  assert('Never odd or even'.startsWith('Never'));

  // Does a string end with another string?
  assert('Never odd or even'.endsWith('even'));

  // Find the location of a string inside a string.
  assert('Never odd or even'.indexOf('odd') == 6);

  // Grab a substring.
  assert('Never odd or even'.substring(6, 9) == 'odd');

  // Split a string using a string pattern.
  var parts = 'structured web apps'.split(' ');
  assert(parts.length == 3);
  assert(parts[0] == 'structured');

  // Get a UTF-16 code unit (as a string) by index.
  assert('Never odd or even'[0] == 'N');

  // Use split() with an empty string parameter to get
  // a list of all characters (as Strings); good for
  // iterating.
  for (var char in 'hello'.split('')) {
    print(char);
  }

  // Convert to uppercase.
  assert('structured web apps'.toUpperCase() ==
      'STRUCTURED WEB APPS');

  // Convert to lowercase.
  assert('STRUCTURED WEB APPS'.toLowerCase() ==
      'structured web apps');  

  // Trim a string.
  assert('  hello  '.trim() == 'hello');

  // Check whether a string is empty.
  assert(''.isEmpty);

  // Strings with only white space are not empty.
  assert('  '.isNotEmpty);      

  var greetingTemplate = 'Hello, NAME!';
  var greeting =
      greetingTemplate.replaceAll(RegExp('NAME'), 'Bob');

  // greetingTemplate didn't change.
  assert(greeting != greetingTemplate);  

  var sb = StringBuffer();
  sb
    ..write('Use a StringBuffer for ')
    ..writeAll(['efficient', 'string', 'creation'], ' ')
    ..write('.');

  var fullString = sb.toString();

  assert(fullString ==
      'Use a StringBuffer for efficient string creation.');  


  var numbers = RegExp(r'\d+');
  var someDigits = 'llamas live 15 to 20 years';

  // Check whether the reg exp has a match in a string.
  assert(numbers.hasMatch(someDigits));

  // Loop through all matches.
  for (var match in numbers.allMatches(someDigits)) {
    print(match.group(0)); // 15, then 20
  }
  
  print("hello world".hashCode);
}