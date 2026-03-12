# API Reference

This document provides a comprehensive reference for all classes, methods, and functionality in the C++ Library Collection.

## � Table of Contents

- [🔤 MyString Class](#-mystring-class)
  - [🏗️ Constructors](#-constructors)
  - [⚙️ String Operations](#️-string-operations)
    - [🔄 Case Conversion](#-case-conversion)
    - [📝 Word and Letter Operations](#-word-and-letter-operations)
    - [🔧 String Manipulation](#-string-manipulation)
    - [🔍 String Analysis](#-string-analysis)
  - [🛡️ Error Handling](#️-error-handling)
  - [📝 Examples](#-examples)

- [📅 MyDate Class](#-mydate-class)
  - [🏗️ Constructors](#-constructors-1)
  - [⚙️ Date Operations](#️-date-operations)
    - [📅 Date Creation and Access](#-date-creation-and-access)
    - [🔄 Date Validation and Conversion](#-date-validation-and-conversion)
    - [🧮 Date Arithmetic](#-date-arithmetic)
  - [🛡️ Error Handling](#️-error-handling-1)
  - [📝 Examples](#-examples-1)

- [📅 MyPeriod Class](#-myperiod-class)
  - [🏗️ Constructors](#-constructors-2)
  - [⚙️ Period Operations](#️-period-operations)
    - [📅 Date Access and Modification](#-date-access-and-modification)
    - [📊 Period Analysis](#-period-analysis)
  - [🛡️ Error Handling](#️-error-handling-2)
  - [📝 Examples](#-examples-2)

- [🎭 Enums and Types](#-enums-and-types)
  - [enWhatToCount (MyString)](#enwhattocount-mystring)
  - [enDateCompare (MyDate)](#endatecompare-mydate)

- [🚀 Performance Considerations](#-performance-considerations)

- [🛡️ Error Handling Best Practices](#️-error-handling-best-practices)

- [📚 Additional Resources](#-additional-resources)

## 🔤 MyString Class

The `MyString` class provides comprehensive string manipulation utilities with robust error handling.

### 🏗️ Constructors

| Constructor | Description | Example |
|-------------|-------------|---------|
| `MyString()` | Default constructor (creates empty string) | `MyString str;` |
| `MyString(const std::string& Value)` | Constructor with validation | `MyString str("Hello");` |
| `MyString(std::string&& Value)` | Move constructor | `MyString str(std::move(temp));` |

**Exception Handling:**
- Throws `std::invalid_argument` if empty string is provided
- Error message available via `MyString::GetLastError()`

### ⚙️ String Operations

#### Case Conversion
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `static UpperAllString(const std::string& S1)` | `std::string` | Convert to uppercase | `MyString::UpperAllString("hello")` |
| `static LowerAllString(const std::string& S1)` | `std::string` | Convert to lowercase | `MyString::LowerAllString("HELLO")` |
| `UpperFirstLetterOfEachWord() const` | `std::string` | Capitalize first letter of each word | `str.UpperFirstLetterOfEachWord()` |
| `LowerFirstLetterOfEachWord() const` | `std::string` | Lowercase first letter of each word | `str.LowerFirstLetterOfEachWord()` |
| `InvertAllLettersCase() const` | `std::string` | Invert letter case | `str.InvertAllLettersCase()` |

#### Word and Letter Operations
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `CountWords() const` | `size_t` | Count words in string | `str.CountWords()` |
| `CountLetters(enWhatToCount WhatToCount)` | `size_t` | Count letters by type | `str.CountLetters( CAPITAL )` |
| `CountVowels() const` | `size_t` | Count vowels | `str.CountVowels()` |

#### String Manipulation
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `static Split(const std::string& S1, const std::string& Delim)` | `std::vector<std::string>` | Split string by delimiter | `MyString::Split("a,b,c", ",")` |
| `static JoinString(const std::vector<std::string>& vString, const std::string& Delim)` | `std::string` | Join strings with delimiter | `MyString::JoinString(vec, ",")` |
| `Trim() const` | `std::string` | Trim whitespace | `str.Trim()` |
| `ReverseWordsInString() const` | `std::string` | Reverse word order | `str.ReverseWordsInString()` |
| `ReplaceWord(const std::string& StringToReplace, const std::string& sReplaceTo)` | `std::string` | Replace words | `str.ReplaceWord("old", "new")` |
| `RemovePunctuations() const` | `std::string` | Remove punctuation | `str.RemovePunctuations()` |
| `Repeat(int times) const` | `std::string` | Repeat string | `str.Repeat(3)` |

#### String Analysis
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `Contains(const std::string& S2) const` | `bool` | Check if contains substring | `str.Contains("hello")` |
| `StartsWith(const std::string& prefix) const` | `bool` | Check if starts with prefix | `str.StartsWith("Hello")` |
| `EndsWith(const std::string& suffix) const` | `bool` | Check if ends with suffix | `str.EndsWith("World")` |
| `static IsPalindrome(const std::string& S1)` | `bool` | Check if palindrome | `MyString::IsPalindrome("racecar")` |

### 🛡️ Error Handling

| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `static GetLastError()` | `std::string` | Get last error message | `MyString::GetLastError()` |
| `static ClearError()` | `void` | Clear error state | `MyString::ClearError()` |

### 📝 Examples

```cpp
#include "MyLib/MyString.h"
using namespace MyLib;

// Basic usage
MyString text("Hello World");
std::cout << "Word count: " << text.CountWords() << std::endl;

// Static methods
std::string upper = MyString::UpperAllString("hello");
std::vector<std::string> words = MyString::Split("a,b,c", ",");

// Error handling
try {
    MyString empty(""); // Throws exception
} catch (const std::exception& e) {
    std::cout << "Error: " << MyString::GetLastError() << std::endl;
}
```

---

## 📅 MyDate Class

The `MyDate` class provides modern date handling with comprehensive validation and arithmetic operations.

### 🏗️ Constructors

| Constructor | Description | Example |
|-------------|-------------|---------|
| `MyDate()` | Default constructor (current system date) | `MyDate today;` |
| `MyDate(const std::string& sDate)` | Constructor from string (DD/MM/YYYY) | `MyDate date("25/12/2023")` |
| `MyDate(short Day, short Month, short Year)` | Constructor with parameters | `MyDate date(25, 12, 2023)` |

**Exception Handling:**
- Throws `std::invalid_argument` for invalid date format or values
- Error message available via `MyDate::GetLastError()`

### ⚙️ Date Operations

#### Date Creation and Access
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `static GetSystemDate()` | `MyDate` | Get current system date | `MyDate today = MyDate::GetSystemDate();` |
| `GetDay() const` | `short` | Get day of month | `date.GetDay()` |
| `GetMonth() const` | `short` | Get month | `date.GetMonth()` |
| `GetYear() const` | `short` | Get year | `date.GetYear()` |
| `SetDay(short Day)` | `void` | Set day of month | `date.SetDay(15)` |
| `SetMonth(short Month)` | `void` | Set month | `date.SetMonth(6)` |
| `SetYear(short Year)` | `void` | Set year | `date.SetYear(2023)` |

#### Date Validation and Conversion
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `static IsValidDate(const MyDate& Date)` | `bool` | Validate date | `MyDate::IsValidDate(date)` |
| `IsValid() const` | `bool` | Check if date is valid | `date.IsValid()` |
| `DateToString() const` | `std::string` | Convert to string (DD/MM/YYYY) | `date.DateToString()` |

#### Date Arithmetic
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `static GetDifferenceInDays(const MyDate& Date1, const MyDate& Date2, bool IncludeEndDate = false)` | `int` | Calculate days difference | `MyDate::GetDifferenceInDays(date1, date2)` |

### 🛡️ Error Handling

| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `static GetLastError()` | `std::string` | Get last error message | `MyDate::GetLastError()` |
| `static ClearError()` | `void` | Clear error state | `MyDate::ClearError()` |

### 📝 Examples

```cpp
#include "MyLib/MyDate.h"
using namespace MyLib;

// Current date
MyDate today = MyDate::GetSystemDate();
std::cout << "Today: " << today.DateToString() << std::endl;

// Create specific date
MyDate christmas(25, 12, 2023);

// Date from string
MyDate newYear("01/01/2024");

// Date arithmetic
int daysUntilChristmas = MyDate::GetDifferenceInDays(today, christmas);

// Error handling
try {
    MyDate invalid("32/13/2024"); // Throws exception
} catch (const std::exception& e) {
    std::cout << "Error: " << MyDate::GetLastError() << std::endl;
}
```

---

## 📅 MyPeriod Class

The `MyPeriod` class provides date range operations with overlap detection and duration calculations.

### 🏗️ Constructors

| Constructor | Description | Example |
|-------------|-------------|---------|
| `MyPeriod()` | Default constructor (single day period) | `MyPeriod period;` |
| `MyPeriod(const MyDate& StartDate, const MyDate& EndDate)` | Constructor with validation | `MyPeriod period(start, end)` |

**Exception Handling:**
- Throws `std::invalid_argument` if start date is after end date
- Error message available via `MyPeriod::GetLastError()`

### ⚙️ Period Operations

#### Date Access and Modification
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `GetStartDate() const` | `MyDate` | Get start date | `period.GetStartDate()` |
| `GetEndDate() const` | `MyDate` | Get end date | `period.GetEndDate()` |
| `SetStartDate(const MyDate& StartDate)` | `void` | Set start date | `period.SetStartDate(start)` |
| `SetEndDate(const MyDate& EndDate)` | `void` | Set end date | `period.SetEndDate(end)` |

#### Period Analysis
| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `GetDurationInDays() const` | `int` | Get period duration in days | `period.GetDurationInDays()` |
| `static IsOverlapPeriods(const MyPeriod& Period1, const MyPeriod& Period2)` | `bool` | Check if periods overlap | `MyPeriod::IsOverlapPeriods(p1, p2)` |
| `IsOverLapWith(const MyPeriod& Period2) const` | `bool` | Check overlap with another period | `period.IsOverLapWith(other)` |

### 🛡️ Error Handling

| Method | Return Type | Description | Example |
|--------|-------------|-------------|---------|
| `static GetLastError()` | `std::string` | Get last error message | `MyPeriod::GetLastError()` |
| `static ClearError()` | `void` | Clear error state | `MyPeriod::ClearError()` |

### 📝 Examples

```cpp
#include "MyLib/MyPeriod.h"
using namespace MyLib;

// Create a period
MyDate start(1, 1, 2023);
MyDate end(31, 12, 2023);
MyPeriod year2023(start, end);

// Get duration
int daysInYear = year2023.GetDurationInDays();
std::cout << "Days in 2023: " << daysInYear << std::endl;

// Check overlap
MyDate vacationStart(15, 6, 2023);
MyDate vacationEnd(30, 6, 2023);
MyPeriod vacation(vacationStart, vacationEnd);

if (year2023.IsOverLapWith(vacation)) {
    std::cout << "Vacation is within 2023" << std::endl;
}

// Error handling
try {
    MyDate invalidStart(31, 12, 2023);
    MyDate invalidEnd(1, 1, 2023);
    MyPeriod invalidPeriod(invalidStart, invalidEnd); // Throws exception
} catch (const std::exception& e) {
    std::cout << "Error: " << MyPeriod::GetLastError() << std::endl;
}
```

---

## 🎭 Enums and Types

### enWhatToCount (MyString)
Used with `CountLetters()` method to specify what type of letters to count.

| Enum Value | Description |
|------------|-------------|
| `CAPITAL` | Count capital letters |
| `SMALL` | Count small letters |
| `ALL` | Count all letters |
| `VOWELS` | Count vowels only |

### enDateCompare (MyDate)
Used for date comparison operations.

| Enum Value | Description |
|------------|-------------|
| `Before` | First date is before second |
| `Equal` | Dates are equal |
| `After` | First date is after second |

---

## 🚀 Performance Considerations

### String Operations
- **Static methods** are preferred for one-time operations
- **Move semantics** are automatically used where beneficial
- **Memory management** is handled automatically

### Date Operations
- **Validation** is performed once during construction
- **String conversion** creates new strings (consider caching)
- **Arithmetic operations** are optimized for common cases

### Period Operations
- **Overlap detection** uses efficient comparison algorithms
- **Duration calculation** accounts for leap years
- **Date validation** is inherited from MyDate class

---

## 🛡️ Error Handling Best Practices

### General Guidelines
1. **Clear errors** before operations that might fail
2. **Check return values** and error messages after operations
3. **Use try-catch blocks** for operations that might throw exceptions
4. **Handle specific exceptions** rather than catching all exceptions

### Example Error Handling Pattern
```cpp
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"
using namespace MyLib;

// Clear previous errors
MyString::ClearError();
MyDate::ClearError();
MyPeriod::ClearError();

try {
    // Perform operations
    MyString text("Hello World");
    MyDate date("25/12/2023");
    MyPeriod period(start, end);
    
    // Check for errors
    if (!text.GetValue().empty()) {
        std::cout << "String created successfully" << std::endl;
    }
    
} catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
    std::cout << "String Error: " << MyString::GetLastError() << std::endl;
    std::cout << "Date Error: " << MyDate::GetLastError() << std::endl;
    std::cout << "Period Error: " << MyPeriod::GetLastError() << std::endl;
}
```

---

## 📚 Additional Resources

- [Examples](EXAMPLES.md) - Practical usage examples
- [Testing](TESTING.md) - Testing information and guidelines
- [Project Structure](PROJECT_STRUCTURE.md) - Project organization
- [Installation](INSTALLATION.md) - Build and install instructions
