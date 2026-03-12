# C++ Library Collection Documentation

[![Build Status](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/workflows/CI/badge.svg)](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)

A modern C++ educational library providing comprehensive string, date, and period operations with robust error handling and performance optimizations.

## 📚 Table of Contents

- [🚀 Quick Start](docs/QUICK_START.md) - Get started in 5 minutes
- [🔧 Installation](INSTALLATION.md) - Build and install instructions
- [📖 API Reference](API_REFERENCE.md) - Complete API documentation
- [💡 Examples](EXAMPLES.md) - Code examples and usage patterns
- [🧪 Testing](TESTING.md) - Testing information and guidelines
- [🤝 Contributing](CONTRIBUTING.md) - Contribution guidelines
- [📄 License](LICENSE.md) - MIT License information
- [🏗️ Project Structure](PROJECT_STRUCTURE.md) - Project organization

## 🎯 Quick Start

### Prerequisites
- CMake 3.16 or higher
- C++17 compatible compiler
- Ninja or Make build system

### Installation
```bash
# Clone the repository
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection

# Build and install
mkdir build && cd build
cmake ..
ninja
sudo ninja install
```

### Basic Usage
```cpp
#include <iostream>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"

int main() {
    using namespace MyLib;
    
    // 🔤 String operations
    MyString text("Hello World");
    std::cout << "Word count: " << text.CountWords() << std::endl;
    
    // 📅 Date operations
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today is: ";
    today.Print();
    
    // 📅 Period operations
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    MyPeriod year2023(start, end);
    std::cout << "Duration: " << year2023.GetDurationInDays() << " days" << std::endl;
    
    return 0;
}
```

## 📊 Project Status

| Status | Description |
|--------|-------------|
| 🚀 **Development** | Actively developed and ready for use |
| ✅ **Testing** | Comprehensive test suite with 100% pass rate |
| 📚 **Documentation** | Complete documentation in docs/ folder |
| 🌍 **Platform** | Cross-platform (Windows, Linux, macOS) |

## 🚀 Features

- **🔤 String Operations**: Comprehensive string manipulation utilities
- **📅 Date Operations**: Modern date handling with validation
- **📅 Period Operations**: Date range calculations and overlap detection
- **🛡️ Error Handling**: Comprehensive input validation and exception handling
- **⚡ Performance**: Optimized with move semantics and modern C++ practices
- **📦 Modern C++**: C++17 compliant with const correctness

## 📚 Documentation Overview

### 🔧 Installation Guide
- [INSTALLATION.md](INSTALLATION.md) - Complete build and install instructions
  - Prerequisites and requirements
  - Platform-specific instructions
  - Build options and configuration
  - Troubleshooting guide

### 📖 API Reference
- [API_REFERENCE.md](API_REFERENCE.md) - Complete API documentation
  - MyString class methods and examples
  - MyDate class methods and examples
  - MyPeriod class methods and examples
  - Error handling patterns
  - Performance considerations

### 💡 Examples
- [EXAMPLES.md](EXAMPLES.md) - Comprehensive code examples
  - Basic usage examples
  - Advanced use cases
  - Error handling examples
  - Performance examples
  - Real-world applications

### 🧪 Testing
- [TESTING.md](TESTING.md) - Testing information and guidelines
  - Running tests
  - Test structure
  - Writing new tests
  - Debugging tests
  - Performance testing

### 🤝 Contributing
- [CONTRIBUTING.md](CONTRIBUTING.md) - Contribution guidelines
  - Development workflow
  - Code style guidelines
  - Testing requirements
  - Pull request process

### 🏗️ Project Structure
- [PROJECT_STRUCTURE.md](PROJECT_STRUCTURE.md) - Project organization
  - Directory structure
  - Component overview
  - Architecture decisions
  - Build system details
  - Maintenance guidelines

## 🧪 Testing

### Running Tests
```bash
# Build tests
cd build
ninja tests

# Run tests
./tests/tests.exe
# or use ctest
ctest
```

### Test Coverage
- ✅ All MyString functionality
- ✅ All MyDate functionality
- ✅ All MyPeriod functionality
- ✅ Error handling validation
- ✅ Edge case testing

## 🤝 Contributing

Contributions are welcome! Please see the [Contributing Guide](CONTRIBUTING.md) for detailed guidelines.

### How to Contribute
1. 🍴 Fork the repository
2. 🌿 Create a feature branch
3. 💻 Make your changes
4. ✅ Add tests if applicable
5. 📤 Submit a pull request

## 📞 Support

If you encounter any issues or have questions:

| Resource | Link |
|----------|------|
| 🐛 **Bug Reports** | [Open an Issue](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/issues) |
| 📚 **Documentation** | [docs/README.md](README.md) |
| 💡 **Examples** | [docs/EXAMPLES.md](EXAMPLES.md) |
| 🧪 **Testing** | [docs/TESTING.md](TESTING.md) |
| 🏗️ **Architecture** | [docs/PROJECT_STRUCTURE.md](PROJECT_STRUCTURE.md) |

## 📄 License

This project is licensed under the MIT License - see [LICENSE.md](LICENSE.md) for details.

## 🙏 Acknowledgments

- Thanks to all contributors who have helped improve this library
- Built with modern C++ best practices in mind
- Educational focus with comprehensive error handling

---

**⭐ If you find this library helpful, consider giving it a star!**
