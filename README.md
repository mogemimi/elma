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

- Visual Studio 2017 and later (for Windows)
- Xcode 9.2 and later (for macOS)

## Open Source Software used in Elma

All of the dependencies that Elma needs to build or run.

- [Catch2](https://github.com/catchorg/Catch2)
- [Duktape](https://github.com/svaarala/duktape)
