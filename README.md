# Hyper-optimized telemetry kata in C++

[![CI](https://github.com/Coding-Cuddles/hyper-optimized-telemetry-cpp-kata/actions/workflows/main.yml/badge.svg)](https://github.com/Coding-Cuddles/hyper-optimized-telemetry-cpp-kata/actions/workflows/main.yml)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Replit](https://img.shields.io/badge/Try%20with%20Replit-black?logo=replit)](https://replit.com/new/github/Coding-Cuddles/hyper-optimized-telemetry-cpp-kata)

## Overview

This kata complements [Clean Code: Advanced TDD, Ep. 20](https://cleancoders.com/episode/clean-code-episode-20)
and [Clean Code: Advanced TDD, Ep. 21](https://cleancoders.com/episode/clean-code-episode-21).

This repository contains two exercises designed to improve your skills in
test-driven development.

## Instructions

We will work on a telemetry system for a remote control car project. Bandwidth
in the telemetry system is at a premium and you have been asked to implement a
message protocol for communicating telemetry data.

Data is transmitted in a buffer (byte array). When integers are sent, the size
of the buffer is reduced by employing the protocol described below.

Each value should be represented in the smallest possible C integral type
(types of `char` and `unsigned char` are not included as the saving would be
trivial):

| From                       | To                        | Type             |
|:---------------------------|:------------------------- |:-----------------|
| 4,294,967,296              | 9,223,372,036,854,775,807 | `long`           |
| 2,147,483,648              | 4,294,967,295             | `unsigned int`   |
| 65,536                     | 2,147,483,647             | `int`            |
| 0                          | 65,535                    | `unsigned short` |
| -32,768                    | -1                        | `short`          |
| -2,147,483,648             | -32,769                   | `int`            |
| -9,223,372,036,854,775,808 | -2,147,483,649            | `long`           |

The value should be converted to the appropriate number of bytes for its
assigned type. The complete internal 9-byte buffer comprises three parts:
* _prefix byte_: a byte indicating the number of the payload bytes in the
  buffer;
* _payload bytes_: the bytes holding the integer;
* _trailing bytes_: the zero-fill bytes to complete the buffer.

To distinguish between signed and unsigned types, the protocol introduces a
little trick: for signed types, their _prefix byte_ value is `256` minus the
number of _payload bytes_ in the buffer.

### Exercise 1

Implement the static method `TelemetryBuffer.to_buffer()` to encode a buffer
taking an integer value passed to the method.

```cpp
// Type: unsigned short, bytes: 2, signed: no, prefix byte: 2
TelemetryBuffer::to_buffer(5);
// => {0x2, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}

// Type: int, bytes: 4, signed: yes, prefix byte: 256 - 4
TelemetryBuffer::to_buffer(2'147'483'647);
// => {0xfc, 0xff, 0xff, 0xff, 0x7f, 0x0, 0x0, 0x0, 0x0}
```

> [!TIP]
>
> The `BitConverter` class provides a convenient way of converting integer
> types to and from arrays of bytes.

### Exercise 2

Implement the static method `TelemetryBuffer.from_buffer()` to decode the
buffer received, and return the value in the form of an integer.

```cpp
TelemetryBuffer::from_buffer({0xfc, 0xff, 0xff, 0xff, 0x7f, 0x0, 0x0, 0x0, 0x0});
// => 2'147'483'647
```

If the prefix byte is of unexpected value, then return `0`.

## Integral numbers in C

> [!NOTE]
>
> For type sizes, we assume a typical 64-bit system.

The C language provides a number of types that represent integers, each with
its own range of values. The ranges are determined by the storage width of the
type as allocated by the system:

| Type             | Width  | Minimum                    | Maximum                     |
|:-----------------|:-------|:---------------------------|:--------------------------- |
| `char`           | 8 bit  | -128                       | +127                        |
| `short`          | 16 bit | -32,768                    | +32,767                     |
| `int`            | 32 bit | -2,147,483,648             | +2,147,483,647              |
| `long`           | 64 bit | -9,223,372,036,854,775,808 | +9,223,372,036,854,775,807  |
| `unsigned char`  | 8 bit  | 0                          | +255                        |
| `unsigned short` | 16 bit | 0                          | +65,535                     |
| `unsigned int`   | 32 bit | 0                          | +4,294,967,295              |
| `unsigned long`  | 64 bit | 0                          | +18,446,744,073,709,551,615 |

This is a C++17 kata using GoogleTest. Setup is complete when CTest reports
`100% tests passed`.

## Prerequisites

Required:

- [Git](https://git-scm.com/downloads)
- A compiler with C++17 support. Choose one:
  - [GCC](https://gcc.gnu.org/) 10+ on Linux
  - [LLVM Clang](https://llvm.org/) 14+ on Linux
  - [Apple Clang](https://developer.apple.com/xcode/) 17+ on macOS
  - [MSVC](https://visualstudio.microsoft.com/) 2022 on Windows
- [CMake 3.24 or later](https://cmake.org)

Optional:

- [GNU Make](https://www.gnu.org/software/make/), for shorter commands. Every
  required task also has direct CMake and CTest commands. Make may be
  unavailable on Windows.

You do not need to install GoogleTest separately. CMake finds an installed
copy or downloads the pinned release when needed.

## Set up the kata

The tracked Replit configuration and badge are retained. The local setup below
is the validated development path.

1. Clone the repository:

   ```console
   git clone https://github.com/Coding-Cuddles/hyper-optimized-telemetry-cpp-kata.git
   ```

2. Enter the repository directory:

   ```console
   cd hyper-optimized-telemetry-cpp-kata
   ```

3. Build and run the tests. Use Make when it is installed:

   ```console
   make test
   ```

   Otherwise, use CMake and CTest directly:

   ```console
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
   cmake --build build --config Debug
   ctest --test-dir build --build-config Debug --output-on-failure
   ```

The first run may download and build GoogleTest. CTest should report
`100% tests passed`. If a command reports a missing compiler or CMake, install
that prerequisite and run the setup commands again. Setup is complete when
CTest reports `100% tests passed`.

## Work on the kata

Work through the two exercises in order. Add one test at a time, then implement
enough code to make the test pass. Keep the protocol, constraints, and expected
results above as the target behavior.

After each change, use Make when it is installed:

```console
make test
```

Otherwise, use CMake and CTest directly:

```console
cmake --build build --config Debug
ctest --test-dir build --build-config Debug --output-on-failure
```

Continue when CTest reports `100% tests passed`.

## Run the example

Use Make when it is installed:

```console
make run
```

Otherwise, use the CMake run target:

```console
cmake --build build --config Debug --target run
```

The executable prints `Hello World!`.

## Make command reference

Make is optional. Run `make` or `make help` to list these commands in the
terminal.

| Command             | Result                                    |
| ------------------- | ----------------------------------------- |
| `make all`          | Build and run the test suite              |
| `make help`         | List public Make targets                  |
| `make build`        | Configure and build without running tests |
| `make run`          | Build and run the example executable      |
| `make test`         | Build and run the test suite              |
| `make format`       | Format tracked C++ and header files       |
| `make format-check` | Check formatting without changing files   |
| `make clean`        | Remove generated build artifacts          |

## Credits and references

* <https://exercism.org/tracks/csharp/exercises/hyper-optimized-telemetry>
