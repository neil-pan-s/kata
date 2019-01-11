import 'dart:convert';

void main(List<String> args) {
  // NOTE: Be sure to use double quotes ("),
  // not single quotes ('), inside the JSON string.
  // This string is JSON, not Dart.
  var jsonString = '''
    [
      {"score": 40},
      {"score": 80}
    ]
  ''';

  var scores = jsonDecode(jsonString);
  assert(scores is List);

  var firstScore = scores[0];
  assert(firstScore is Map);
  assert(firstScore['score'] == 40);

  var scores1 = [
    {'score': 40},
    {'score': 80},
    {'score': 100, 'overtime': true, 'special_guest': null}
  ];

  var jsonText = jsonEncode(scores1);
  assert(jsonText ==
      '[{"score":40},{"score":80},'
      '{"score":100,"overtime":true,'
      '"special_guest":null}]');
}