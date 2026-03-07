# Project Structure

This document describes the complete structure and organization of the C++ Library Collection project.

## Directory Structure

```
Cpp-Library-Collection/
├── CMakeLists.txt              # Main build configuration
├── README.md                   # Project documentation and getting started guide
├── CHANGELOG.md                # Version history and changes
├── LICENSE                     # MIT license file
├── CONTRIBUTING.md             # Contribution guidelines
├── src/                        # Source files
│   └── MyLib.cpp              # Static member variable definitions
├── include/                    # Header files
│   └── MyLib/                 # Library namespace
│       ├── MyString.h         # String manipulation class
│       ├── MyDate.h           # Date handling class
│       ├── MyPeriod.h         # Period operations class
│       └── MyUtil.h           # Utility functions
├── tests/                      # Test suite
│   ├── CMakeLists.txt         # Test build configuration
│   ├── test_main.cpp          # Main test file
│   └── MyLib/                 # Additional test files (if any)
│       ├── test_MyString.cpp
│       ├── test_MyDate.cpp
│       └── test_MyPeriod.cpp
├── examples/                   # Usage examples
│   ├── CMakeLists.txt         # Examples build configuration
│   └── basic_demo.cpp         # Complete demonstration
├── docs/                       # Additional documentation
│   └── PROJECT_STRUCTURE.md   # This file
└── build/                      # Build output directory (generated)
    ├── CMakeCache.txt
    ├── Makefile or build.ninja
    ├── tests/
    │   └── tests.exe
    └── examples/
        └── basic_demo.exe
```

## Component Overview

### Core Library Components

#### MyString Class (`include/MyLib/MyString.h`)
- **Purpose**: Comprehensive string manipulation utilities
- **Key Features**: Word counting, case conversion, splitting/joining, palindrome detection
- **Error Handling**: Validates empty strings and provides meaningful error messages
- **Performance**: Uses move semantics and efficient algorithms

#### MyDate Class (`include/MyLib/MyDate.h`)
- **Purpose**: Modern date handling with validation
- **Key Features**: Multiple constructors, date validation, string conversion, date arithmetic
- **Error Handling**: Validates date format and ranges (DD/MM/YYYY)
- **Dependencies**: Uses MyString for parsing operations

#### MyPeriod Class (`include/MyLib/MyPeriod.h`)
- **Purpose**: Date range operations and calculations
- **Key Features**: Period creation, overlap detection, duration calculation
- **Error Handling**: Validates period logic (start <= end)
- **Dependencies**: Uses MyDate for all date operations

#### MyUtil Class (`include/MyLib/MyUtil.h`)
- **Purpose**: Utility functions and helper methods
- **Key Features**: Common operations shared across the library

### Build System

#### Main CMakeLists.txt
- **Purpose**: Main build configuration
- **Features**: 
  - C++17 standard requirement
  - Library creation from sources and headers
  - Conditional inclusion of tests and examples
  - Installation configuration

#### Test CMakeLists.txt (`tests/CMakeLists.txt`)
- **Purpose**: Test build configuration
- **Features**:
  - Test executable creation
  - Library linking
  - CTest integration
  - Windows-specific settings

#### Examples CMakeLists.txt (`examples/CMakeLists.txt`)
- **Purpose**: Examples build configuration
- **Features**:
  - Demo executable creation
  - Library linking
  - Example-specific settings

### Source Files

#### MyLib.cpp (`src/MyLib.cpp`)
- **Purpose**: Definition of static member variables
- **Contents**: 
  - MyString::_lastError
  - MyDate::_lastError  
  - MyPeriod::_lastError
- **Importance**: Resolves linking errors for static variables

### Test Suite

#### test_main.cpp (`tests/test_main.cpp`)
- **Purpose**: Comprehensive test suite
- **Coverage**:
  - All public APIs tested
  - Error handling validation
  - Edge case testing
  - Integration testing
- **Results**: 100% pass rate

#### Individual Test Files (`tests/MyLib/*.cpp`)
- **Purpose**: Modular test organization (future expansion)
- **Current Status**: Framework ready for individual test files

### Documentation

#### README.md
- **Purpose**: Main project documentation
- **Contents**: Installation, usage, API reference, examples

#### CHANGELOG.md
- **Purpose**: Version history and change tracking
- **Format**: Keep a Changelog standard
- **Versions**: Current 1.1.0 with detailed history

#### PROJECT_STRUCTURE.md
- **Purpose**: Project organization documentation
- **Contents**: This file

## Build Process

### Prerequisites
- CMake 3.16 or higher
- C++17 compatible compiler
- Ninja or Make build system

### Build Steps
1. **Configuration**: `cmake ..`
2. **Build Library**: `ninja` or `make`
3. **Build Tests**: `ninja tests`
4. **Run Tests**: `./tests/tests.exe` or `ctest`
5. **Build Examples**: `ninja basic_demo`

### Installation
```bash
sudo make install  # or ninja install
```

## Development Guidelines

### Code Organization
- All classes in `MyLib` namespace
- Consistent naming conventions
- Header-only design with source file for static variables
- Comprehensive error handling

### Testing Strategy
- Unit tests for each class
- Error handling validation
- Integration testing
- 100% coverage goal

### Documentation Standards
- Clear API documentation
- Usage examples
- Change tracking
- Migration guides

## Dependencies

### External Dependencies
- C++ Standard Library (iostream, string, vector, etc.)
- CMake (build system)
- C++17 compiler

### Internal Dependencies
- MyDate depends on MyString
- MyPeriod depends on MyDate
- All classes share common error handling patterns

## Quality Assurance

### Code Quality
- Modern C++ practices
- Const correctness
- Move semantics
- Exception safety

### Testing
- Comprehensive test suite
- All tests passing
- Error condition testing
- Performance validation

### Build Quality
- Cross-platform compatibility
- Clean builds
- Proper linking
- Installation support

## Future Expansion

The project structure supports:
- Additional utility classes
- Extended test coverage
- More examples
- Advanced documentation
- Performance optimizations
- New features following established patterns
