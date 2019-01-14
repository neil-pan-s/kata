# snapshots

## Script Snapshots

The Dart VM has long supported script snapshots that allow a Dart programmer to package up an application into a single file and reduce startup time.

$ dart --snapshot=hello.dart.snapshot hello.dart
$ dart hello.dart.snapshot arguments-for-use

Hello, world!
These snapshots contain tokenized sources, but lack parsed classes and functions and lack compiled code. This makes them fairly small and portable between CPU architectures. But it also means the Dart VM must still parse and compile all the classes and functions that are used in each run, which can be a substanial portion of run time for large programs that process a small input.

## Application Snapshots

Starting in 1.21, the Dart VM also supports application snapshots, which include all the parsed classes and compiled code generated during a training run of a program.

$ dart --snapshot=hello.dart.snapshot --snapshot-kind=app-jit hello.dart arguments-for-training
Hello, world!
$ dart hello.dart.snapshot arguments-for-use
Hello, world!
When running from an application snapshot, the Dart VM will not need to parse or compile classes and functions that were already used during the training run, so it starts running user code sooner.

These snapshots are CPU architecture specific, so a snapshot created by an x64 VM cannot run on an IA32 VM or vice versa. Also, because different code is generated in production mode and checked mode, an app snapshot created in production mode cannot be run in checked mode or vice versa.

The above are known app-jit snapshots. There is also an app-aot variant that does not use a training run, but compiles the entire program starting from main. App-AOT snapshots are needed to run compiled code on iOS, and they used by Flutter its profile and release modes.

```
https://github.com/dart-lang/sdk/wiki/Snapshots
```