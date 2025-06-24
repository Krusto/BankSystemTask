# BankSystemTask

> A modern C++ project with CMake and unit testing using GoogleTest.

[![GitHub Issues](https://img.shields.io/github/issues-raw/Krusto/BankSystemTask)](https://github.com/Krusto/BankSystemTask/issues)
[![GitHub Code Size](https://img.shields.io/github/languages/code-size/Krusto/BankSystemTask)](https://github.com/Krusto/BankSystemTask)
[![GitHub Fork](https://img.shields.io/github/forks/Krusto/BankSystemTask?style=social)](https://github.com/Krusto/BankSystemTask)
![GitHub License](https://img.shields.io/github/license/Krusto/BankSystemTask)
![GitHub Release](https://img.shields.io/github/v/release/Krusto/BankSystemTask)			atures

- Modern C++ (C++23)
- Cross-platform with CMake
- Unit tests powered by GoogleTest
- Clean and modular project layout

## Getting Started

### Prerequisites

- [CMake](https://cmake.org/download/) (version 3.15+)
- A C++ compiler (GCC, Clang, MSVC, etc.)
- Git
- llvm-19(for test coverage)

### Clone and Build

Regular build

```bash
git clone https://github.com/Krusto/BankSystemTask.git
cd BankSystemTask
mkdir build && cd build
cmake ..
cmake --build .
```

Generating Coverage Data

```bash
		
cmake --build build --target generate_coverage_report
```

Run Tests

```bash
cmake -S . -B build -DENABLE_TESTS=ON
cmake --build ./build --target run_tests
```

### For Generating Coverage Data

Only works with clang-19 and llvm-19 for the moment

```bash
sudo apt install llvm-19
```
