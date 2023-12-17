# Nyctous

---

> A Modern C++ Ecosystem Manager.

## Why ... Nyctous?

It is completely based on source code hierarchy for project dependency management and simplifies well-known yet complex workflows.

## How to build itself

```
$ git clone https://github.com/tanpero/nyctous.git # Or SSH path
$ cd nyctous
$ cmake .
```

Then `make` (On *nix) or `start nyctous.sln` (On Windows)

## Basic Usage

### Setup a project

Use `ny init`.

```
$ mkdir hello && cd hello
$ ny init
Project Name (hello): <Enter your answer>
Version (0.1.0): <Enter your answer>
Description: <Enter your answer>
Git Repository: <Enter the url>
Author: <Enter your name>
License: <Enter your choice>

Project is available!

$ ls
CMakeLists.txt  LICENSE  README.md  deps/  docs/  include/  nyctous.json  src/  test/
```

### Install the dependencies

```
$ ny add nlohmann/json
$ ny add fmtlib/fmt
```

### Build the project

For Nyctous, a "project" does not mean an output object, but a collection of interconnected workflows. It will include several targets.

```
$ ny build
```

### Test the project

If you have written code for examples or tests and specified a test script in nyctous.json, then all you need to do is

```
$ ny test
```

### Packaging and release the application

```
$ ny pack
```

Then you will see a beautiful test report (for the test project) or expected application output (for the example project) on the terminal.

## License

Based on MIT license.
