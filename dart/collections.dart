import 'dart:core';

void main(List<String> args) {
  var coffees = [];
  var teas = ['green', 'black', 'chamomile', 'earl grey'];
  assert(coffees.isEmpty);
  assert(teas.isNotEmpty);

  teas.forEach((tea) => print('I drink $tea'));

  // var loudTeas = teas.map((tea) => tea.toUpperCase());
  // var loudTeas = teas.map((tea) => tea.toUpperCase()).toList();
  var loudTeas = teas.map((tea) => tea.toUpperCase()).toSet();
  print(loudTeas);
  loudTeas.forEach(print);


  // Chamomile is not caffeinated.
  bool isDecaffeinated(String teaName) => teaName == 'chamomile';

  // Use where() to find only the items that return true
  // from the provided function.
  var decaffeinatedTeas =
      teas.where((tea) => isDecaffeinated(tea));
  // or teas.where(isDecaffeinated)

  // Use any() to check whether at least one item in the
  // collection satisfies a condition.
  assert(teas.any(isDecaffeinated));

  // Use every() to check whether all the items in a
  // collection satisfy a condition.
  assert(!teas.every(isDecaffeinated));
}