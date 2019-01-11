import 'dart:core';

void main(List<String> args) {
  var uri = 'http://example.org/api?foo=some message';

  var encoded = Uri.encodeFull(uri);
  assert(encoded ==
      'http://example.org/api?foo=some%20message');

  var decoded = Uri.decodeFull(encoded);
  assert(uri == decoded);

  var encoded1 = Uri.encodeComponent(uri);
  assert(encoded1 ==
      'http%3A%2F%2Fexample.org%2Fapi%3Ffoo%3Dsome%20message');

  var decoded1 = Uri.decodeComponent(encoded);
  assert(uri == decoded1);  

  var _uri = Uri.parse('http://example.org:8080/foo/bar#frag');

  assert(_uri.scheme == 'http');
  assert(_uri.host == 'example.org');
  assert(_uri.path == '/foo/bar');
  assert(_uri.fragment == 'frag');
  assert(_uri.origin == 'http://example.org:8080');


  var uri1 = Uri(
    scheme: 'http',
    host: 'example.org',
    path: '/foo/bar',
    fragment: 'frag');
assert(
    uri1.toString() == 'http://example.org/foo/bar#frag');
}