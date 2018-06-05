# Elma

Elma is an experimental, hobbyist and toy compiler that is being developed primarily as a learning project, research code and for fun.
It is also open source and distributed under the [MIT License](https://opensource.org/licenses/MIT). Feel free to fork, submit a pull request or modify anywhere you like!

## Language Specification

```swift
func greeting(s: String) -> String {
    return "Hello, " + s;
}

print(greeting("world"));
```

## Requirements

Elma is written in C++17 and designed for multi-platform.
To build and test, the following packages are required:

- CMake 3.10 and later
- Visual Studio 2017 and later (for Windows)
- Xcode 9.2 and later (for macOS)
- Clang (for Linux)

Optional:

- Bison 3.0.4
- Flex 2.6.4
- ClangFormat 6.0.0 or later

## Building

To build the project with CMake, run the following from the root directory:

```sh
cd path/to/elma

# Building library and test cases
cmake -Bbuild -H. && make -C build

# Running test application
./build/unittest
```

To generate Xcode project, execute the following command:

```sh
cd path/to/elma

# Generating Xcode projects
mkdir build && cd build
cmake -G Xcode ..

# Opening your project
open elma.xcodeproj

# Building with Xcode
xcodebuild -project elma.xcodeproj -configuration Release

# Running test application
./Release/unittest
```

## Generating Lexer and Parser

To generate lexer and parser, use the following command:

```sh
# Generating lexer using Flex
flex src/Parser/Lexer.l

# Generating parser using Bison
bison src/Parser/Parser.y
```

## Open Source Software used in Elma

All of the dependencies that Elma needs to build or run.

- [Catch2](https://github.com/catchorg/Catch2)
- [Duktape](https://github.com/svaarala/duktape)

To update all third party libraries, execute the following command:

```sh
cd path/to/elma

# Updating Catch2
curl -L https://github.com/catchorg/Catch2/releases/download/v2.2.2/catch.hpp -o thirdparty/catch2/catch.hpp

# Updating Duktape
curl -O -L https://github.com/svaarala/duktape/releases/download/v2.2.1/duktape-2.2.1.tar.xz
tar xpvf duktape-2.2.1.tar.xz
cp -R duktape-2.2.1/src/ thirdparty/duktape
rm duktape-2.2.1.tar.xz
rm -R duktape-2.2.1
```
