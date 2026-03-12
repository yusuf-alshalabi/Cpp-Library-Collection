# 💡 Examples

This document provides comprehensive examples demonstrating the usage of the C++ Library Collection.

## � Table of Contents

- [� MyString Examples](#-mystring-examples)
  - [🎯 Basic String Operations](#-basic-string-operations)
  - [🔧 String Manipulation](#-string-manipulation)
  - [🔍 String Analysis](#-string-analysis)
  - [🛡️ Error Handling](#️-error-handling)

- [📅 MyDate Examples](#-mydate-examples)
  - [🎯 Basic Date Operations](#-basic-date-operations)
  - [🧮 Date Arithmetic](#-date-arithmetic)
  - [📝 Date Modification](#-date-modification)
  - [🛡️ Error Handling](#️-error-handling-1)

- [📅 MyPeriod Examples](#-myperiod-examples)
  - [🎯 Basic Period Operations](#-basic-period-operations)
  - [🔍 Period Overlap Detection](#-period-overlap-detection)
  - [📝 Period Modification](#-period-modification)
  - [🛡️ Error Handling](#️-error-handling-2)

- [🎯 Combined Examples](#-combined-examples)
  - [📚 Complete Library Demo](#-complete-library-demo)
  - [📅 Practical Application: Event Planner](#-practical-application-event-planner)

- [🧪 Testing Examples](#-testing-examples)
  - [📝 Unit Test Pattern](#-unit-test-pattern)

- [📚 Next Steps](#-next-steps)

## 🔤 MyString Examples

### 🎯 Basic String Operations

```cpp
#include <iostream>
#include "MyLib/MyString.h"
using namespace MyLib;

int main() {
    // Create a string
    MyString text("Hello World");
    std::cout << "Original: " << text.GetValue() << std::endl;
    
    // Count words
    std::cout << "Word count: " << text.CountWords() << std::endl;
    
    // Case conversion
    std::cout << "Upper: " << MyString::UpperAllString(text.GetValue()) << std::endl;
    std::cout << "Lower: " << MyString::LowerAllString(text.GetValue()) << std::endl;
    
    // First letter operations
    std::cout << "Title case: " << text.UpperFirstLetterOfEachWord() << std::endl;
    
    return 0;
}
```

**Output:**
```
Original: Hello World
Word count: 2
Upper: HELLO WORLD
Lower: hello world
Title case: Hello World
```

### 🔧 String Manipulation

```cpp
#include <iostream>
#include <vector>
#include "MyLib/MyString.h"
using namespace MyLib;

int main() {
    MyString sentence("The quick brown fox jumps over the lazy dog");
    
    // Split into words
    std::vector<std::string> words = MyString::Split(sentence.GetValue(), " ");
    std::cout << "Words: ";
    for (const auto& word : words) {
        std::cout << "[" << word << "] ";
    }
    std::cout << std::endl;
    
    // Join words
    std::string joined = MyString::JoinString(words, "-");
    std::cout << "Joined: " << joined << std::endl;
    
    // Reverse words
    std::cout << "Reversed: " << sentence.ReverseWordsInString() << std::endl;
    
    // Replace word
    std::cout << "Replaced: " << sentence.ReplaceWord("fox", "cat") << std::endl;
    
    return 0;
}
```

**Output:**
```
Words: [The] [quick] [brown] [fox] [jumps] [over] [the] [lazy] [dog] 
Joined: The-quick-brown-fox-jumps-over-the-lazy-dog
Reversed: dog lazy the over jumps fox brown quick The
Replaced: The quick brown cat jumps over the lazy dog
```

### String Analysis

```cpp
#include <iostream>
#include "MyLib/MyString.h"
using namespace MyLib;

int main() {
    MyString text("Programming is fun!");
    
    // Letter counting
    std::cout << "Capital letters: " << text.CountLetters(CAPITAL) << std::endl;
    std::cout << "Small letters: " << text.CountLetters(SMALL) << std::endl;
    std::cout << "All letters: " << text.CountLetters(ALL) << std::endl;
    std::cout << "Vowels: " << text.CountVowels() << std::endl;
    
    // String analysis
    std::cout << "Contains 'fun': " << (text.Contains("fun") ? "Yes" : "No") << std::endl;
    std::cout << "Starts with 'Pro': " << (text.StartsWith("Pro") ? "Yes" : "No") << std::endl;
    std::cout << "Ends with '!': " << (text.EndsWith("!") ? "Yes" : "No") << std::endl;
    
    // Palindrome check
    MyString palindrome("racecar");
    std::cout << "Is 'racecar' palindrome: " << (MyString::IsPalindrome("racecar") ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

**Output:**
```
Capital letters: 1
Small letters: 15
All letters: 16
Vowels: 6
Contains 'fun': Yes
Starts with 'Pro': Yes
Ends with '!': Yes
Is 'racecar' palindrome: Yes
```

### Error Handling

```cpp
#include <iostream>
#include "MyLib/MyString.h"
using namespace MyLib;

int main() {
    // Clear any previous errors
    MyString::ClearError();
    
    try {
        // This will throw an exception
        MyString empty("");
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "Error message: " << MyString::GetLastError() << std::endl;
    }
    
    // Normal usage
    try {
        MyString valid("Hello World");
        std::cout << "Valid string created: " << valid.GetValue() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

**Output:**
```
Exception caught: MyString: Cannot create with empty value
Error message: Cannot create MyString with empty value
Valid string created: Hello World
```

---

## 📅 MyDate Examples

### Basic Date Operations

```cpp
#include <iostream>
#include "MyLib/MyDate.h"
using namespace MyLib;

int main() {
    // Current date
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today: " << today.DateToString() << std::endl;
    std::cout << "Day: " << today.GetDay() << std::endl;
    std::cout << "Month: " << today.GetMonth() << std::endl;
    std::cout << "Year: " << today.GetYear() << std::endl;
    
    // Specific date
    MyDate christmas(25, 12, 2023);
    std::cout << "Christmas 2023: " << christmas.DateToString() << std::endl;
    
    // Date from string
    MyDate newYear("01/01/2024");
    std::cout << "New Year 2024: " << newYear.DateToString() << std::endl;
    
    // Date validation
    std::cout << "Is Christmas valid: " << (christmas.IsValid() ? "Yes" : "No") << std::endl;
    std::cout << "Is 32/13/2024 valid: " << (MyDate::IsValidDate(MyDate(32, 13, 2024)) ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

**Output:**
```
Today: DD/MM/YYYY (current date)
Day: DD
Month: MM
Year: YYYY
Christmas 2023: 25/12/2023
New Year 2024: 01/01/2024
Is Christmas valid: Yes
Is 32/13/2024 valid: No
```

### Date Arithmetic

```cpp
#include <iostream>
#include "MyLib/MyDate.h"
using namespace MyLib;

int main() {
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    
    // Calculate difference
    int daysInYear = MyDate::GetDifferenceInDays(start, end, true);
    std::cout << "Days in 2023 (inclusive): " << daysInYear << std::endl;
    
    int daysExclusive = MyDate::GetDifferenceInDays(start, end, false);
    std::cout << "Days in 2023 (exclusive): " << daysExclusive << std::endl;
    
    // Date comparisons
    MyDate date1(15, 6, 2023);
    MyDate date2(20, 6, 2023);
    
    int diff = MyDate::GetDifferenceInDays(date1, date2);
    std::cout << "Days between June 15 and June 20: " << diff << std::endl;
    
    return 0;
}
```

**Output:**
```
Days in 2023 (inclusive): 365
Days in 2023 (exclusive): 364
Days between June 15 and June 20: 5
```

### Date Modification

```cpp
#include <iostream>
#include "MyLib/MyDate.h"
using namespace MyLib;

int main() {
    MyDate date(15, 6, 2023);
    std::cout << "Original date: " << date.DateToString() << std::endl;
    
    // Modify components
    date.SetDay(20);
    std::cout << "After setting day to 20: " << date.DateToString() << std::endl;
    
    date.SetMonth(12);
    std::cout << "After setting month to 12: " << date.DateToString() << std::endl;
    
    date.SetYear(2024);
    std::cout << "After setting year to 2024: " << date.DateToString() << std::endl;
    
    return 0;
}
```

**Output:**
```
Original date: 15/06/2023
After setting day to 20: 20/06/2023
After setting month to 12: 20/12/2023
After setting year to 2024: 20/12/2024
```

### Error Handling

```cpp
#include <iostream>
#include "MyLib/MyDate.h"
using namespace MyLib;

int main() {
    // Clear any previous errors
    MyDate::ClearError();
    
    try {
        // Invalid date format
        MyDate invalid1("32-13-2024");  // Wrong delimiter
    } catch (const std::exception& e) {
        std::cout << "Format error: " << MyDate::GetLastError() << std::endl;
    }
    
    MyDate::ClearError();
    
    try {
        // Invalid date values
        MyDate invalid2(32, 13, 2024);  // Invalid day/month
    } catch (const std::exception& e) {
        std::cout << "Value error: " << MyDate::GetLastError() << std::endl;
    }
    
    // Valid date
    try {
        MyDate valid("25/12/2023");
        std::cout << "Valid date created: " << valid.DateToString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

**Output:**
```
Format error: Invalid date format. Expected DD/MM/YYYY
Value error: Invalid date: Day, month, or year values are out of range
Valid date created: 25/12/2023
```

---

## 📅 MyPeriod Examples

### Basic Period Operations

```cpp
#include <iostream>
#include "MyLib/MyPeriod.h"
#include "MyLib/MyDate.h"
using namespace MyLib;

int main() {
    // Create a period
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    MyPeriod year2023(start, end);
    
    std::cout << "Period: " << start.DateToString() << " to " << end.DateToString() << std::endl;
    std::cout << "Duration: " << year2023.GetDurationInDays() << " days" << std::endl;
    
    // Access dates
    std::cout << "Start date: " << year2023.GetStartDate().DateToString() << std::endl;
    std::cout << "End date: " << year2023.GetEndDate().DateToString() << std::endl;
    
    return 0;
}
```

**Output:**
```
Period: 01/01/2023 to 31/12/2023
Duration: 365 days
Start date: 01/01/2023
End date: 31/12/2023
```

### Period Overlap Detection

```cpp
#include <iostream>
#include "MyLib/MyPeriod.h"
#include "MyLib/MyDate.h"
using namespace MyLib;

int main() {
    // Year 2023
    MyDate yearStart(1, 1, 2023);
    MyDate yearEnd(31, 12, 2023);
    MyPeriod year2023(yearStart, yearEnd);
    
    // Summer vacation
    MyDate vacationStart(15, 6, 2023);
    MyDate vacationEnd(30, 6, 2023);
    MyPeriod vacation(vacationStart, vacationEnd);
    
    // Winter break (next year)
    MyDate winterStart(20, 12, 2023);
    MyDate winterEnd(10, 1, 2024);
    MyPeriod winterBreak(winterStart, winterEnd);
    
    // Check overlaps
    std::cout << "Vacation overlaps with 2023: " << 
        (year2023.IsOverLapWith(vacation) ? "Yes" : "No") << std::endl;
    
    std::cout << "Winter break overlaps with 2023: " << 
        (year2023.IsOverLapWith(winterBreak) ? "Yes" : "No") << std::endl;
    
    // Static method
    std::cout << "Vacation and winter break overlap: " << 
        (MyPeriod::IsOverlapPeriods(vacation, winterBreak) ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

**Output:**
```
Vacation overlaps with 2023: Yes
Winter break overlaps with 2023: Yes
Vacation and winter break overlap: No
```

### Period Modification

```cpp
#include <iostream>
#include "MyLib/MyPeriod.h"
#include "MyLib/MyDate.h"
using namespace MyLib;

int main() {
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    MyPeriod period(start, end);
    
    std::cout << "Original period: " << 
        period.GetStartDate().DateToString() << " to " << 
        period.GetEndDate().DateToString() << std::endl;
    
    // Modify start date
    MyDate newStart(15, 1, 2023);
    period.SetStartDate(newStart);
    std::cout << "After changing start date: " << 
        period.GetStartDate().DateToString() << " to " << 
        period.GetEndDate().DateToString() << std::endl;
    
    // Modify end date
    MyDate newEnd(15, 12, 2023);
    period.SetEndDate(newEnd);
    std::cout << "After changing end date: " << 
        period.GetStartDate().DateToString() << " to " << 
        period.GetEndDate().DateToString() << std::endl;
    
    std::cout << "New duration: " << period.GetDurationInDays() << " days" << std::endl;
    
    return 0;
}
```

**Output:**
```
Original period: 01/01/2023 to 31/12/2023
After changing start date: 15/01/2023 to 31/12/2023
After changing end date: 15/01/2023 to 15/12/2023
New duration: 334 days
```

### Error Handling

```cpp
#include <iostream>
#include "MyLib/MyPeriod.h"
#include "MyLib/MyDate.h"
using namespace MyLib;

int main() {
    // Clear any previous errors
    MyPeriod::ClearError();
    
    try {
        // Invalid period (start after end)
        MyDate start(31, 12, 2023);
        MyDate end(1, 1, 2023);
        MyPeriod invalid(start, end);
    } catch (const std::exception& e) {
        std::cout << "Period error: " << MyPeriod::GetLastError() << std::endl;
    }
    
    // Valid period
    try {
        MyDate start(1, 1, 2023);
        MyDate end(31, 12, 2023);
        MyPeriod valid(start, end);
        std::cout << "Valid period created: " << 
            valid.GetStartDate().DateToString() << " to " << 
            valid.GetEndDate().DateToString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

**Output:**
```
Period error: Invalid period: Start date cannot be after end date
Valid period created: 01/01/2023 to 31/12/2023
```

---

## 🎯 Combined Examples

### Complete Library Demo

```cpp
#include <iostream>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"
using namespace MyLib;

int main() {
    std::cout << "=== C++ Library Collection Demo ===" << std::endl << std::endl;
    
    // === MyString Demo ===
    std::cout << "🔤 MyString Demo:" << std::endl;
    MyString text("Hello C++ Library");
    std::cout << "Original: " << text.GetValue() << std::endl;
    std::cout << "Word count: " << text.CountWords() << std::endl;
    std::cout << "Upper: " << MyString::UpperAllString(text.GetValue()) << std::endl;
    std::cout << "Is palindrome: " << (MyString::IsPalindrome("level") ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
    
    // === MyDate Demo ===
    std::cout << "📅 MyDate Demo:" << std::endl;
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today: " << today.DateToString() << std::endl;
    
    MyDate projectStart(1, 1, 2023);
    MyDate projectEnd(31, 12, 2023);
    std::cout << "Project duration: " << 
        MyDate::GetDifferenceInDays(projectStart, projectEnd) << " days" << std::endl;
    std::cout << std::endl;
    
    // === MyPeriod Demo ===
    std::cout << "📅 MyPeriod Demo:" << std::endl;
    MyPeriod projectPeriod(projectStart, projectEnd);
    std::cout << "Project period: " << 
        projectPeriod.GetStartDate().DateToString() << " to " << 
        projectPeriod.GetEndDate().DateToString() << std::endl;
    
    // Check if today is within project period
    if (projectPeriod.IsOverLapWith(MyPeriod(today, today))) {
        std::cout << "Today is within the project period!" << std::endl;
    }
    std::cout << std::endl;
    
    // === Error Handling Demo ===
    std::cout << "🛡️ Error Handling Demo:" << std::endl;
    try {
        MyString empty("");
    } catch (const std::exception& e) {
        std::cout << "String error caught: " << MyString::GetLastError() << std::endl;
    }
    
    try {
        MyDate invalid("32/13/2024");
    } catch (const std::exception& e) {
        std::cout << "Date error caught: " << MyDate::GetLastError() << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "=== Demo Complete ===" << std::endl;
    
    return 0;
}
```

### Practical Application: Event Planner

```cpp
#include <iostream>
#include <vector>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"
using namespace MyLib;

struct Event {
    MyString name;
    MyDate date;
    MyString description;
    
    Event(const std::string& n, const std::string& d, const std::string& desc)
        : name(n), date(d), description(desc) {}
};

int main() {
    std::cout << "=== Event Planner ===" << std::endl << std::endl;
    
    // Create events
    std::vector<Event> events;
    events.emplace_back("Birthday Party", "15/06/2023", "John's birthday celebration");
    events.emplace_back("Conference", "20/06/2023", "Tech conference 2023");
    events.emplace_back("Vacation", "01/07/2023", "Summer vacation starts");
    
    // Display events
    std::cout << "📅 Upcoming Events:" << std::endl;
    for (const auto& event : events) {
        std::cout << "- " << event.GetValue() 
                  << " on " << event.date.DateToString() 
                  << ": " << event.description.GetValue() << std::endl;
    }
    std::cout << std::endl;
    
    // Create a period for June 2023
    MyDate juneStart(1, 6, 2023);
    MyDate juneEnd(30, 6, 2023);
    MyPeriod junePeriod(juneStart, juneEnd);
    
    std::cout << "🎯 June 2023 Events:" << std::endl;
    for (const auto& event : events) {
        MyPeriod eventDay(event.date, event.date);
        if (junePeriod.IsOverLapWith(eventDay)) {
            std::cout << "- " << event.GetValue() 
                      << " (" << event.date.DateToString() << ")" << std::endl;
        }
    }
    std::cout << std::endl;
    
    // Calculate days until next event
    MyDate today = MyDate::GetSystemDate();
    std::cout << "⏰ Days until events:" << std::endl;
    for (const auto& event : events) {
        int days = MyDate::GetDifferenceInDays(today, event.date);
        if (days >= 0) {
            std::cout << "- " << event.GetValue() << ": " << days << " days" << std::endl;
        }
    }
    
    return 0;
}
```

---

## 🧪 Testing Examples

### Unit Test Pattern

```cpp
#include <iostream>
#include <cassert>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"
using namespace MyLib;

void test_mystring() {
    std::cout << "Testing MyString..." << std::endl;
    
    // Test constructor
    MyString str("Hello World");
    assert(str.GetValue() == "Hello World");
    assert(str.CountWords() == 2);
    
    // Test static methods
    assert(MyString::UpperAllString("hello") == "HELLO");
    assert(MyString::LowerAllString("HELLO") == "hello");
    assert(MyString::IsPalindrome("racecar") == true);
    
    // Test error handling
    MyString::ClearError();
    try {
        MyString empty("");
        assert(false); // Should not reach here
    } catch (const std::exception& e) {
        assert(MyString::GetLastError() == "Cannot create MyString with empty value");
    }
    
    std::cout << "✓ MyString tests passed" << std::endl;
}

void test_mydate() {
    std::cout << "Testing MyDate..." << std::endl;
    
    // Test constructor
    MyDate date(25, 12, 2023);
    assert(date.GetDay() == 25);
    assert(date.GetMonth() == 12);
    assert(date.GetYear() == 2023);
    assert(date.IsValid() == true);
    
    // Test string constructor
    MyDate date2("01/01/2024");
    assert(date2.GetDay() == 1);
    assert(date2.GetMonth() == 1);
    assert(date2.GetYear() == 2024);
    
    // Test error handling
    MyDate::ClearError();
    try {
        MyDate invalid("32/13/2024");
        assert(false); // Should not reach here
    } catch (const std::exception& e) {
        assert(MyDate::GetLastError() == "Invalid date format. Expected DD/MM/YYYY");
    }
    
    std::cout << "✓ MyDate tests passed" << std::endl;
}

void test_myperiod() {
    std::cout << "Testing MyPeriod..." << std::endl;
    
    // Test constructor
    MyDate start(1, 1, 2023);
    MyDate end(31, 12, 2023);
    MyPeriod period(start, end);
    
    assert(period.GetStartDate().GetDay() == 1);
    assert(period.GetEndDate().GetDay() == 31);
    assert(period.GetDurationInDays() == 365);
    
    // Test error handling
    MyPeriod::ClearError();
    try {
        MyDate invalidStart(31, 12, 2023);
        MyDate invalidEnd(1, 1, 2023);
        MyPeriod invalid(invalidStart, invalidEnd);
        assert(false); // Should not reach here
    } catch (const std::exception& e) {
        assert(MyPeriod::GetLastError() == "Invalid period: Start date cannot be after end date");
    }
    
    std::cout << "✓ MyPeriod tests passed" << std::endl;
}

int main() {
    std::cout << "=== Running Tests ===" << std::endl;
    
    test_mystring();
    test_mydate();
    test_myperiod();
    
    std::cout << std::endl << "🎉 All tests passed!" << std::endl;
    
    return 0;
}
```

---

## 📚 Next Steps

After reviewing these examples:

1. **Try the examples** - Compile and run them to see the library in action
2. **Modify and experiment** - Change parameters and see the results
3. **Build your own applications** - Use the patterns shown here
4. **Read the API Reference** - Learn about all available methods
5. **Check the Testing Guide** - Learn how to write your own tests

For more information, see:
- [API Reference](API_REFERENCE.md)
- [Testing Guide](TESTING.md)
- [Installation Guide](INSTALLATION.md)
