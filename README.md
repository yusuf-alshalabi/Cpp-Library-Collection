# C++ Library Collection

[![Build Status](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/workflows/CI/badge.svg)](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)

A modern C++ educational library providing comprehensive string, date, and period operations with robust error handling and performance optimizations.

## 📊 Project Status

| Status | Description |
|--------|-------------|
| 🚀 **Development** | Actively developed and ready for use |
| ✅ **Testing** | Comprehensive test suite with 100% pass rate |
| 📚 **Documentation** | Complete API reference and examples |
| 🌍 **Platform** | Cross-platform (Windows, Linux, macOS) |

## 🚀 Features

- **🔤 String Operations**: Comprehensive string manipulation utilities
- **📅 Date Operations**: Modern date handling with validation
- **📅 Period Operations**: Date range calculations and overlap detection
- **🛡️ Error Handling**: Comprehensive input validation and exception handling
- **⚡ Performance**: Optimized with move semantics and modern C++ practices
- **📦 Modern C++**: C++17 compliant with const correctness

## 📦 Installation

### 🔧 Using CMake

```bash
# Clone the repository
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection

# Build and install
mkdir build && cd build
cmake ..
make
sudo make install
```

### 📦 Using as Header-Only

```bash
# Clone the repository
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git

# Copy headers to your project
cp -r include/MyLib /path/to/your/project/include/
```

## 🎯 Quick Start

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

## 📚 API Reference

### 🔤 MyString Class

#### 🏗️ Constructors
- `MyString()` - Default constructor
- `MyString(const std::string& Value)` - Constructor with validation
- `MyString(std::string&& Value)` - Move constructor

#### ⚙️ String Operations
- `size_t CountWords() const` - Count words in string
- `static std::string UpperAllString(const std::string& S1)` - Convert to uppercase
- `static std::string LowerAllString(const std::string& S1)` - Convert to lowercase
- `std::string UpperFirstLetterOfEachWord() const` - Capitalize first letter of each word
- `std::string LowerFirstLetterOfEachWord() const` - Lowercase first letter of each word
- `std::string InvertAllLettersCase() const` - Invert letter case
- `size_t CountLetters(enWhatToCount WhatToCount)` - Count letters by type
- `size_t CountVowels() const` - Count vowels
- `static std::vector<std::string> Split(const std::string& S1, const std::string& Delim)` - Split string
- `std::string Trim() const` - Trim whitespace
- `static std::string JoinString(const std::vector<std::string>& vString, const std::string& Delim)` - Join strings
- `std::string ReverseWordsInString() const` - Reverse word order
- `std::string ReplaceWord(const std::string& StringToReplace, const std::string& sReplaceTo)` - Replace words
- `std::string RemovePunctuations() const` - Remove punctuation
- `bool Contains(const std::string& S2) const` - Check if contains substring
- `bool StartsWith(const std::string& prefix) const` - Check if starts with prefix
- `bool EndsWith(const std::string& suffix) const` - Check if ends with suffix
- `std::string Repeat(int times) const` - Repeat string
- `static bool IsPalindrome(const std::string& S1)` - Check if palindrome

#### 🛡️ Error Handling
- `static std::string GetLastError()` - Get last error message
- `static void ClearError()` - Clear error state

### 📅 MyDate Class

#### 🏗️ Constructors
- `MyDate()` - Default constructor (current date)
- `MyDate(const std::string& sDate)` - Constructor from string (DD/MM/YYYY)
- `MyDate(short Day, short Month, short Year)` - Constructor with parameters

#### ⚙️ Date Operations
- `static MyDate GetSystemDate()` - Get current system date
- `static bool IsValidDate(const MyDate& Date)` - Validate date
- `bool IsValid() const` - Check if date is valid
- `std::string DateToString() const` - Convert to string
- `static int GetDifferenceInDays(const MyDate& Date1, const MyDate& Date2, bool IncludeEndDate = false)` - Calculate days difference

#### 🛡️ Error Handling
- `static std::string GetLastError()` - Get last error message
- `static void ClearError()` - Clear error state

### 📅 MyPeriod Class

#### 🏗️ Constructors
- `MyPeriod()` - Default constructor
- `MyPeriod(const MyDate& StartDate, const MyDate& EndDate)` - Constructor with validation

#### ⚙️ Period Operations
- `static bool IsOverlapPeriods(const MyPeriod& Period1, const MyPeriod& Period2)` - Check if periods overlap
- `bool IsOverLapWith(const MyPeriod& Period2) const` - Check overlap with another period
- `int GetDurationInDays() const` - Get period duration in days

#### 🛡️ Error Handling
- `static std::string GetLastError()` - Get last error message
- `static void ClearError()` - Clear error state

## 🧪 Testing

```bash
# Build tests
cd build
cmake ..
ninja tests

# Run tests
./tests/tests.exe
# or use ctest if available
ctest
```

**Test Coverage:**
- ✅ All MyString functionality
- ✅ All MyDate functionality
- ✅ All MyPeriod functionality
- ✅ Error handling validation
- ✅ Edge case testing

## 📖 Examples

```bash
# Build examples
cd build
cmake ..
ninja basic_demo

# Run demo
./examples/basic_demo.exe
```

**Available Examples:**
- `basic_demo.cpp` - Complete demonstration of all library features

## 📚 Documentation

| Document | Description |
|----------|-------------|
| 📖 [API Reference](README.md#api-reference) | Detailed API documentation |
| 💡 [Examples](examples/) | Code examples and usage patterns |
| 🏗️ [Project Structure](docs/PROJECT_STRUCTURE.md) | Project organization and architecture |

## 🤝 Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

**How to Contribute:**
1. 🍴 Fork the repository
2. 🌿 Create a feature branch
3. 💻 Make your changes
4. ✅ Add tests if applicable
5. 📤 Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Thanks to all contributors who have helped improve this library
- Built with modern C++ best practices in mind
- Educational focus with comprehensive error handling

## 📞 Support

If you encounter any issues or have questions:

| Resource | Link |
|----------|------|
| 🐛 **Bug Reports** | [Open an Issue](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/issues) |
| 📚 **Documentation** | [API Reference](README.md#api-reference) |
| 💡 **Examples** | [Examples Directory](examples/) |
| 🏗️ **Architecture** | [Project Structure](docs/PROJECT_STRUCTURE.md) |

---

**⭐ If you find this library helpful, consider giving it a star!**
