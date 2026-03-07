# Quick Start Guide

Welcome to the C++ Library Collection! This guide will get you up and running in minutes.

## 🎯 What This Library Does

The C++ Library Collection provides three main classes:

- **🔤 MyString**: Advanced string manipulation (word counting, case conversion, splitting, etc.)
- **📅 MyDate**: Modern date handling with validation (DD/MM/YYYY format)
- **📅 MyPeriod**: Date range operations (overlap detection, duration calculation)

## ⚡ 5-Minute Quick Start

### Step 1: Install the Library

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

### Step 2: Use It in Your Code

Create a file called `main.cpp`:

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
    std::cout << "Upper case: " << MyString::UpperAllString(text.GetValue()) << std::endl;
    
    // 📅 Date operations
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today: " << today.DateToString() << std::endl;
    
    MyDate birthday("25/12/2023");
    std::cout << "Christmas: " << birthday.DateToString() << std::endl;
    
    // 📅 Period operations
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    MyPeriod year2023(start, end);
    std::cout << "Days in 2023: " << year2023.GetDurationInDays() << std::endl;
    
    return 0;
}
```

### Step 3: Compile and Run

```bash
# Compile
g++ -std=c++17 main.cpp -lMyLib -o main

# Run
./main
```

**Expected output:**
```
Word count: 2
Upper case: HELLO WORLD
Today: DD/MM/YYYY (current date)
Christmas: 25/12/2023
Days in 2023: 365
```

## 🔤 MyString Quick Examples

```cpp
using namespace MyLib;

MyString text("Hello World");

// Basic operations
std::cout << "Words: " << text.CountWords() << std::endl;        // 2
std::cout << "Vowels: " << text.CountVowels() << std::endl;      // 3

// Case conversion
std::cout << "Upper: " << MyString::UpperAllString(text.GetValue()) << std::endl;  // HELLO WORLD
std::cout << "Lower: " << MyString::LowerAllString(text.GetValue()) << std::endl;  // hello world

// String manipulation
std::vector<std::string> words = MyString::Split(text.GetValue(), " ");
std::cout << "First word: " << words[0] << std::endl;              // Hello

// Analysis
std::cout << "Contains 'World': " << (text.Contains("World") ? "Yes" : "No") << std::endl;  // Yes
std::cout << "Is 'racecar' palindrome: " << (MyString::IsPalindrome("racecar") ? "Yes" : "No") << std::endl;  // Yes
```

## 📅 MyDate Quick Examples

```cpp
using namespace MyLib;

// Current date
MyDate today = MyDate::GetSystemDate();
std::cout << "Today: " << today.DateToString() << std::endl;

// Create specific dates
MyDate christmas(25, 12, 2023);
MyDate newYear("01/01/2024");

// Date arithmetic
int daysUntilChristmas = MyDate::GetDifferenceInDays(today, christmas);
std::cout << "Days until Christmas: " << daysUntilChristmas << std::endl;

// Validation
std::cout << "Is Christmas valid: " << (christmas.IsValid() ? "Yes" : "No") << std::endl;
```

## 📅 MyPeriod Quick Examples

```cpp
using namespace MyLib;

// Create a period
MyDate start(1, 1, 2023);
MyDate end(31, 12, 2023);
MyPeriod year2023(start, end);

// Get information
std::cout << "Duration: " << year2023.GetDurationInDays() << " days" << std::endl;

// Check overlap
MyDate vacationStart(15, 6, 2023);
MyDate vacationEnd(30, 6, 2023);
MyPeriod vacation(vacationStart, vacationEnd);

if (year2023.IsOverLapWith(vacation)) {
    std::cout << "Vacation is within 2023" << std::endl;
}
```

## 🛡️ Error Handling

The library provides comprehensive error handling:

```cpp
using namespace MyLib;

try {
    // This will throw an exception
    MyString empty("");
} catch (const std::exception& e) {
    std::cout << "Error: " << MyString::GetLastError() << std::endl;
}

try {
    // Invalid date format
    MyDate invalid("32-13-2024");
} catch (const std::exception& e) {
    std::cout << "Error: " << MyDate::GetLastError() << std::endl;
}

try {
    // Invalid period (start after end)
    MyDate start(31, 12, 2023);
    MyDate end(1, 1, 2023);
    MyPeriod invalid(start, end);
} catch (const std::exception& e) {
    std::cout << "Error: " << MyPeriod::GetLastError() << std::endl;
}
```

## 🔧 Common Use Cases

### Word Counter
```cpp
MyString text("This is a sample text for word counting");
std::cout << "Total words: " << text.CountWords() << std::endl;
```

### Date Calculator
```cpp
MyDate start(1, 1, 2023);
MyDate end(31, 12, 2023);
int daysInYear = MyDate::GetDifferenceInDays(start, end, true);
std::cout << "Days in year: " << daysInYear << std::endl;
```

### Event Planner
```cpp
MyDate eventDate("25/12/2023");
MyDate today = MyDate::GetSystemDate();
int daysUntilEvent = MyDate::GetDifferenceInDays(today, eventDate);
std::cout << "Days until event: " << daysUntilEvent << std::endl;
```

### Text Processor
```cpp
MyString text("  Hello World!  ");
std::string trimmed = text.Trim();
std::string upper = MyString::UpperAllString(trimmed);
std::cout << "Processed: " << upper << std::endl;  // HELLO WORLD!
```

## 📚 Next Steps

Now that you know the basics:

1. **📖 Read the API Reference** - Learn about all available methods
2. **💡 Check Examples** - See more advanced use cases
3. **🧪 Run Tests** - Verify your installation
4. **🤝 Contribute** - Help improve the library

## 🔗 Useful Links

- [Complete API Reference](API_REFERENCE.md)
- [More Examples](EXAMPLES.md)
- [Installation Guide](INSTALLATION.md)
- [Testing Information](TESTING.md)

## 💡 Tips

- **Date Format**: Always use DD/MM/YYYY format (e.g., "25/12/2023")
- **Error Handling**: Always wrap operations in try-catch blocks
- **Static Methods**: Use static methods when you don't need to create an object
- **Performance**: The library uses move semantics for optimal performance

## 🆘 Need Help?

- **🐛 Report Issues**: [GitHub Issues](https://github.com/yusuf-alshalabi/Cpp-Library-Collection/issues)
- **📚 Documentation**: [docs/README.md](README.md)
- **💡 Examples**: [docs/EXAMPLES.md](EXAMPLES.md)

---

**Happy coding! 🚀**
