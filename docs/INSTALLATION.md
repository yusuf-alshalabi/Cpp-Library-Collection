# 🔧 Installation Guide

This guide covers how to install and set up the C++ Library Collection on your system.

## 📚 Table of Contents

- [📋 Prerequisites](#prerequisites)
  - [✅ Required](#required)
  - [🔧 Optional](#optional)

- [🔧 Installation Methods](#installation-methods)
  - [🏗️ Method 1: CMake Build and Install (Recommended)](#method-1-cmake-build-and-install-recommended)
  - [📦 Method 2: Header-Only Usage](#method-2-header-only-usage)

- [🖥️ Platform-Specific Instructions](#platform-specific-instructions)
  - [🪟 Windows (Visual Studio)](#windows-visual-studio)
  - [🐧 Linux (Ubuntu/Debian)](#linux-ubuntudebian)
  - [🍎 macOS](#macos)

- [🔍 Verification](#verification)
  - [🧪 Test the Installation](#test-the-installation)
  - [✅ Expected Output](#expected-output)

- [🛠️ Build Options](#build-options)
  - [⚙️ CMake Options](#cmake-options)
  - [🔨 Build System Options](#build-system-options)

- [🔧 Integration with Your Project](#integration-with-your-project)
  - [🏗️ CMake Integration](#cmake-integration)
  - [📦 Header-Only Integration](#header-only-integration)

- [🚨 Troubleshooting](#troubleshooting)
  - [⚠️ Common Issues](#common-issues)
  - [🐛 Getting Help](#getting-help)

- [📚 Next Steps](#next-steps)

## 📋 Prerequisites

### Required
- **CMake** 3.16 or higher
- **C++17 compatible compiler**
  - GCC 7.0+ (Linux)
  - Clang 5.0+ (macOS/Linux)
  - MSVC 2017+ (Windows)
- **Build System**
  - Ninja (recommended) or Make

### Optional
- **Git** - For cloning the repository
- **ctest** - For running tests (usually comes with CMake)

## 🔧 Installation Methods

### Method 1: CMake Build and Install (Recommended)

#### Step 1: Clone the Repository
```bash
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection
```

#### Step 2: Configure Build
```bash
mkdir build && cd build
cmake ..
```

#### Step 3: Build the Library
```bash
# Using Ninja (recommended)
ninja

# Or using Make
make
```

#### Step 4: Run Tests (Optional but Recommended)
```bash
# Build tests
ninja tests

# Run tests
./tests/tests.exe

# Or use ctest
ctest
```

#### Step 5: Install the Library
```bash
# Using Ninja
ninja install

# Or using Make
sudo make install
```

### Method 2: Header-Only Usage

#### Step 1: Clone the Repository
```bash
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection
```

#### Step 2: Copy Headers to Your Project
```bash
# Copy the entire include directory
cp -r include/MyLib /path/to/your/project/include/

# Or copy specific headers
cp include/MyLib/*.h /path/to/your/project/include/
```

#### Step 3: Add to Your CMakeLists.txt
```cmake
# Add include directory
target_include_directories(your_target PRIVATE include)

# Or if using copied headers
target_include_directories(your_target PRIVATE /path/to/your/project/include)
```

## 🖥️ Platform-Specific Instructions

### Windows (Visual Studio)

#### Prerequisites
- Visual Studio 2017 or later
- CMake (comes with Visual Studio)
- Git

#### Installation Steps
```powershell
# Clone repository
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection

# Create build directory
mkdir build
cd build

# Configure for Visual Studio
cmake .. -G "Visual Studio 16 2019"

# Build
cmake --build . --config Release

# Run tests
ctest --config Release

# Install (optional)
cmake --install . --config Release
```

### Linux (Ubuntu/Debian)

#### Prerequisites
```bash
# Install required packages
sudo apt update
sudo apt install build-essential cmake git ninja-build

# Or without ninja
sudo apt install build-essential cmake git
```

#### Installation Steps
```bash
# Clone repository
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection

# Build and install
mkdir build && cd build
cmake ..
ninja
sudo ninja install
```

### macOS

#### Prerequisites
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Install Homebrew (if not installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required tools
brew install cmake ninja git
```

#### Installation Steps
```bash
# Clone repository
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection

# Build and install
mkdir build && cd build
cmake ..
ninja
sudo ninja install
```

## 🔍 Verification

### Test the Installation

#### Create a Test File
```cpp
// test_installation.cpp
#include <iostream>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"

int main() {
    using namespace MyLib;
    
    // Test MyString
    MyString text("Hello World");
    std::cout << "Word count: " << text.CountWords() << std::endl;
    
    // Test MyDate
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today: " << today.DateToString() << std::endl;
    
    // Test MyPeriod
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    MyPeriod year2023(start, end);
    std::cout << "Days in 2023: " << year2023.GetDurationInDays() << std::endl;
    
    std::cout << "Installation successful!" << std::endl;
    return 0;
}
```

#### Compile and Run
```bash
# Compile
g++ -std=c++17 test_installation.cpp -lMyLib -o test_installation

# Run
./test_installation
```

### Expected Output
```
Word count: 2
Today: DD/MM/YYYY
Days in 2023: 365
Installation successful!
```

## 🛠️ Build Options

### CMake Options

#### Debug Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

#### Release Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

#### Custom Installation Prefix
```bash
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
```

#### Disable Tests
```bash
cmake .. -DBUILD_TESTS=OFF
```

#### Disable Examples
```bash
cmake .. -DBUILD_EXAMPLES=OFF
```

### Build System Options

#### Using Ninja (Recommended)
```bash
# Configure
cmake .. -GNinja

# Build
ninja

# Install
ninja install
```

#### Using Make
```bash
# Configure
cmake .. -G"Unix Makefiles"

# Build
make

# Install
make install
```

## 🔧 Integration with Your Project

### CMake Integration

#### Basic Integration
```cmake
cmake_minimum_required(VERSION 3.16)
project(YourProject)

# Find the library (if installed)
find_package(MyLib REQUIRED)

# Or add as subdirectory (if using source)
add_subdirectory(path/to/Cpp-Library-Collection)

# Create your executable
add_executable(your_target main.cpp)

# Link with the library
target_link_libraries(your_target PRIVATE MyLib)

# Add include directories
target_include_directories(your_target PRIVATE include)
```

### Header-Only Integration

```cmake
cmake_minimum_required(VERSION 3.16)
project(YourProject)

# Add headers
add_library(MyLib INTERFACE)
target_include_directories(MyLib INTERFACE path/to/Cpp-Library-Collection/include)

# Create your executable
add_executable(your_target main.cpp)

# Link with the library
target_link_libraries(your_target PRIVATE MyLib)
```

## 🚨 Troubleshooting

### Common Issues

#### Issue: CMake cannot find the library
**Solution**: Make sure the library is installed or use add_subdirectory

#### Issue: Compilation errors with missing headers
**Solution**: Check include paths and ensure headers are copied correctly

#### Issue: Linking errors
**Solution**: Verify that the library is built and linked correctly

#### Issue: Tests fail to run
**Solution**: Check that the library is built before running tests

### Getting Help

If you encounter issues:

1. **Check the logs** - Look at CMake output and compiler errors
2. **Verify prerequisites** - Ensure all required tools are installed
3. **Check versions** - Make sure you have compatible versions
4. **Search issues** - Check [GitHub Issues](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/issues)
5. **Ask for help** - Open a new issue with detailed information

## 📚 Next Steps

After successful installation:

- 📖 Read the [API Reference](API_REFERENCE.md)
- 💡 Check out the [Examples](EXAMPLES.md)
- 🧪 Run the [Tests](TESTING.md)
- 🤝 Learn how to [Contribute](CONTRIBUTING.md)
