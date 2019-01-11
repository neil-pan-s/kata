
// Exceptions

// Your Dart code can throw and catch exceptions. Exceptions are errors indicating that something unexpected happened. If the exception isn’t caught, the isolate that raised the exception is suspended, and typically the isolate and its program are terminated.
// In contrast to Java, all of Dart’s exceptions are unchecked exceptions. Methods do not declare which exceptions they might throw, and you are not required to catch any exceptions.

// eg.
// throw FormatException('Expected at least 1 section');

// try {
//   breedMoreLlamas();
// } on OutOfLlamasException {
//   buyMoreLlamas();
// }


// try {
//   breedMoreLlamas();
// } on OutOfLlamasException {
//   // A specific exception
//   buyMoreLlamas();
// } on Exception catch (e) {
//   // Anything else that is an exception
//   print('Unknown exception: $e');
// } catch (e) {
//   // No specified type, handles all
//   print('Something really unknown: $e');
// }
// As the preceding code shows, you can use either on or catch or both. Use on when you need to specify the exception type. Use catch when your exception handler needs the exception object.

// You can specify one or two parameters to catch(). The first is the exception that was thrown, and the second is the stack trace (a StackTrace object).

// try {
//   // ···
// } on Exception catch (e) {
//   print('Exception details:\n $e');
// } catch (e, s) {
//   print('Exception details:\n $e');
//   print('Stack trace:\n $s');
// }


// Finally
// To ensure that some code runs whether or not an exception is thrown, use a finally clause. If no catch clause matches the exception, the exception is propagated after the finally clause runs:

// try {
//   breedMoreLlamas();
// } finally {
//   // Always clean up, even if an exception is thrown.
//   cleanLlamaStalls();
// }
// The finally clause runs after any matching catch clauses:

// try {
//   breedMoreLlamas();
// } catch (e) {
//   print('Error: $e'); // Handle the exception first.
// } finally {
//   cleanLlamaStalls(); // Then clean up.
// }

// To partially handle an exception, while allowing it to propagate, use the rethrow keyword.
void misbehave() {
  try {
    dynamic foo = true;
    print(foo++); // Runtime error
  } catch (e) {
    print('misbehave() partially handled ${e.runtimeType}.');
    rethrow; // Allow callers to see the exception.
  }
}

void main() {
  try {
    misbehave();
  } catch (e) {
    print('main() finished handling ${e.runtimeType}.');
  }
}