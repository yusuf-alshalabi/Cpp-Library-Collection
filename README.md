# C++ Library Collection

[![Build Status](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/workflows/CI/badge.svg)](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)

A modern C++ educational library providing comprehensive string, date, and period operations with robust error handling and performance optimizations.

## 🚀 Features

- **🔤 String Operations**: Comprehensive string manipulation utilities
- **📅 Date Operations**: Modern date handling with validation
- **📅 Period Operations**: Date range calculations and overlap detection
- **🛡️ Error Handling**: Comprehensive input validation and exception handling
- **🚀 Performance**: Optimized with move semantics and modern C++ practices
- **📦 Modern C++**: C++17 compliant with const correctness

## 📦 Installation

### Using CMake

```bash
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
cd Cpp-Library-Collection
mkdir build && cd build
cmake ..
make
sudo make install
```

### Using as Header-Only

```bash
git clone https://github.com/yusuf-alshalabi/Cpp-Library-Collection.git
# Copy include/MyLib to your project
```

## 🎯 Quick Start

```cpp
#include <iostream>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"

int main() {
    using namespace MyLib;
    
    // String operations
    MyString text("Hello World");
    std::cout << "Word count: " << text.CountWords() << std::endl;
    
    // Date operations
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today is: ";
    today.Print();
    
    // Period operations
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    MyPeriod year2023(start, end);
    std::cout << "Duration: " << year2023.GetDurationInDays() << " days" << std::endl;
    
    return 0;
}
```

## 📚 API Reference

### MyString Class

#### Constructors
- `MyString()` - Default constructor
- `MyString(const std::string& Value)` - Constructor with validation
- `MyString(std::string&& Value)` - Move constructor

#### String Operations
- `size_t CountWords() const` - Count words in string
- `std::string UpperFirstLetterOfEachWord() const` - Capitalize first letter of each word
- `std::string LowerFirstLetterOfEachWord() const` - Lowercase first letter of each word
- `std::string UpperAllString() const` - Convert to uppercase
- `std::string LowerAllString() const` - Convert to lowercase
- `std::string InvertAllLettersCase() const` - Invert letter case
- `size_t CountLetters(enWhatToCount WhatToCount)` - Count letters by type
- `size_t CountVowels() const` - Count vowels
- `std::vector<std::string> Split(const std::string& Delim)` - Split string
- `std::string Trim() const` - Trim whitespace
- `std::string JoinString(const std::vector<std::string>& vString, const std::string& Delim)` - Join strings
- `std::string ReverseWordsInString() const` - Reverse word order
- `std::string ReplaceWord(const std::string& StringToReplace, const std::string& sReplaceTo)` - Replace words
- `std::string RemovePunctuations() const` - Remove punctuation
- `bool Contains(const std::string& S2) const` - Check if contains substring
- `bool StartsWith(const std::string& prefix) const` - Check if starts with prefix
- `bool EndsWith(const std::string& suffix) const` - Check if ends with suffix
- `std::string Repeat(int times) const` - Repeat string
- `bool IsPalindrome() const` - Check if palindrome

#### Error Handling
- `static std::string GetLastError()` - Get last error message
- `static void ClearError()` - Clear error state

### MyDate Class

#### Constructors
- `MyDate()` - Default constructor (current date)
- `MyDate(const std::string& sDate)` - Constructor from string (DD/MM/YYYY)
- `MyDate(short Day, short Month, short Year)` - Constructor with parameters

#### Date Operations
- `static MyDate GetSystemDate()` - Get current system date
- `static bool IsValidDate(const MyDate& Date)` - Validate date
- `bool IsValid() const` - Check if date is valid
- `std::string DateToString() const` - Convert to string
- `static int GetDifferenceInDays(const MyDate& Date1, const MyDate& Date2, bool IncludeEndDate = false)` - Calculate days difference

#### Error Handling
- `static std::string GetLastError()` - Get last error message
- `static void ClearError()` - Clear error state

### MyPeriod Class

#### Constructors
- `MyPeriod(const MyDate& StartDate, const MyDate& EndDate)` - Constructor with validation
- `MyPeriod(MyPeriod&& other) noexcept` - Move constructor

#### Period Operations
- `static bool IsOverlapPeriods(const MyPeriod& Period1, const MyPeriod& Period2)` - Check if periods overlap
- `bool IsOverLapWith(const MyPeriod& Period2) const` - Check overlap with another period
- `int GetDurationInDays() const` - Get period duration in days

#### Error Handling
- `static std::string GetLastError()` - Get last error message
- `static void ClearError()` - Clear error state

## 🧪 Testing

```bash
cd build
make basic_demo
./basic_demo
```

## 📖 Examples

See the `examples/` directory for comprehensive usage examples:
- `basic_demo.cpp` - Complete demonstration of all library features

## 📚 Documentation

- [API Reference](README.md#-api-reference) - Detailed API documentation
- [Examples](examples/) - Code examples

## 🤝 Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📈 Changelog

See [CHANGELOG.md](CHANGELOG.md) for a detailed history of changes.

## 🙏 Acknowledgments

- Thanks to all contributors who have helped improve this library
- Built with modern C++ best practices in mind

## 📞 Support

If you encounter any issues or have questions:
- Open an [Issue](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/issues)
- Check the [Documentation](README.md#-api-reference)
- Look at [Examples](examples/)
