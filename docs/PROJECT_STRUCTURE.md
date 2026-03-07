# Project Structure

This document describes the complete structure and organization of the C++ Library Collection project.

## Directory Structure

```
Cpp-Library-Collection/
├── README.md                   # Quick overview and navigation hub
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
├── docs/                       # Complete documentation
│   ├── README.md              # Main documentation hub
│   ├── INSTALLATION.md        # Build and install instructions
│   ├── API_REFERENCE.md       # Complete API documentation
│   ├── EXAMPLES.md            # Code examples and usage patterns
│   ├── TESTING.md             # Testing information and guidelines
│   ├── CONTRIBUTING.md         # Contribution guidelines
│   ├── LICENSE.md              # MIT License information
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
- **Static Methods**: UpperAllString, LowerAllString, Split, JoinString, IsPalindrome

#### MyDate Class (`include/MyLib/MyDate.h`)
- **Purpose**: Modern date handling with validation
- **Key Features**: Multiple constructors, date validation, string conversion, date arithmetic
- **Error Handling**: Validates date format (DD/MM/YYYY) and ranges
- **Dependencies**: Uses MyString for parsing operations
- **Static Methods**: GetSystemDate, IsValidDate, GetDifferenceInDays

#### MyPeriod Class (`include/MyLib/MyPeriod.h`)
- **Purpose**: Date range operations and calculations
- **Key Features**: Period creation, overlap detection, duration calculation
- **Error Handling**: Validates period logic (start <= end)
- **Dependencies**: Uses MyDate for all date operations
- **Static Methods**: IsOverlapPeriods

#### MyUtil Class (`include/MyLib/MyUtil.h`)
- **Purpose**: Utility functions and helper methods
- **Key Features**: Common operations shared across the library
- **Status**: Framework ready for additional utilities

### Source Files

#### MyLib.cpp (`src/MyLib.cpp`)
- **Purpose**: Definition of static member variables
- **Contents**: 
  - MyString::_lastError
  - MyDate::_lastError  
  - MyPeriod::_lastError
- **Importance**: Resolves linking errors for static variables
- **Build System**: Compiled into the main library

### Build System

#### Main CMakeLists.txt
- **Purpose**: Main build configuration
- **Features**: 
  - C++17 standard requirement
  - Library creation from sources and headers
  - Conditional inclusion of tests and examples
  - Installation configuration
  - Cross-platform compatibility

#### Test CMakeLists.txt (`tests/CMakeLists.txt`)
- **Purpose**: Test build configuration
- **Features**:
  - Test executable creation
  - Library linking
  - CTest integration
  - Windows-specific settings
  - Test registration

#### Examples CMakeLists.txt (`examples/CMakeLists.txt`)
- **Purpose**: Examples build configuration
- **Features**:
  - Demo executable creation
  - Library linking
  - Example-specific settings

### Test Suite

#### test_main.cpp (`tests/test_main.cpp`)
- **Purpose**: Comprehensive test suite
- **Coverage**:
  - All public APIs tested
  - Error handling validation
  - Edge case testing
  - Integration testing
- **Results**: 100% pass rate
- **Structure**: Organized by class and functionality

#### Individual Test Files (`tests/MyLib/*.cpp`)
- **Purpose**: Modular test organization (future expansion)
- **Current Status**: Framework ready for individual test files
- **Benefits**: Easier maintenance and parallel testing

### Documentation

#### docs/README.md
- **Purpose**: Main documentation hub
- **Contents**: Complete project documentation
- **Audience**: Users wanting comprehensive information
- **Features**: Full API reference, installation guide, examples

#### Root README.md
- **Purpose**: Quick overview and navigation
- **Contents**: Project summary and links to detailed docs
- **Audience**: New users and quick reference
- **Features**: Quick start example and navigation table

#### Documentation Files
- **INSTALLATION.md**: Detailed build and install instructions
- **API_REFERENCE.md**: Complete API documentation with examples
- **EXAMPLES.md**: Comprehensive code examples and use cases
- **TESTING.md**: Testing strategies and guidelines
- **CONTRIBUTING.md**: Contribution guidelines and development workflow
- **LICENSE.md**: MIT License information
- **PROJECT_STRUCTURE.md**: This file

### Examples

#### basic_demo.cpp (`examples/basic_demo.cpp`)
- **Purpose**: Complete demonstration of all library features
- **Features**: Shows all classes and major functionality
- **Usage**: Educational and reference implementation
- **Build**: Integrated with CMake build system

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

## Architecture Decisions

### Design Patterns
- **Static Error Handling**: Centralized error management
- **Move Semantics**: Performance optimization
- **Exception Safety**: Robust error handling
- **Header-First Design**: Easy integration

### File Organization
- **Separation of Concerns**: Clear separation between headers, source, tests, and docs
- **Modular Structure**: Each component in its own file
- **Documentation Centralization**: All docs in docs/ folder
- **Build Integration**: CMake handles all build aspects

### Performance Considerations
- **Lazy Evaluation**: Computation only when needed
- **Memory Efficiency**: Move semantics reduce copies
- **Cache-Friendly**: Data structures optimized for access patterns
- **Exception Safety**: No memory leaks even with exceptions

## Future Expansion

The project structure supports:
- Additional utility classes in MyLib namespace
- Extended test coverage with individual test files
- More examples demonstrating specific use cases
- Advanced documentation with tutorials
- Performance optimizations
- New features following established patterns

## Maintenance Guidelines

### Adding New Features
1. Create header in `include/MyLib/`
2. Add source to `src/MyLib.cpp` if needed
3. Create tests in `tests/`
4. Update documentation
5. Update this structure file

### Updating Documentation
- Keep API_REFERENCE.md current
- Update EXAMPLES.md with new use cases
- Maintain cross-references between files
- Update structure file when organization changes

### Build System Maintenance
- Keep CMakeLists.txt files clean
- Test on multiple platforms
- Update build instructions when needed
- Maintain compatibility with older compilers

---

This structure provides a solid foundation for a professional C++ library with excellent maintainability and extensibility.
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
