#include <iostream>
#include <cassert>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"

using namespace MyLib;

void test_mystring_basic() {
    std::cout << "Testing MyString basic functionality...\n";
    
    // Test constructor
    MyString str("Hello World");
    assert(str.GetValue() == "Hello World");
    
    // Test word counting
    assert(str.CountWords() == 2);
    
    // Test string operations
    assert(MyString::UpperAllString(str.GetValue()) == "HELLO WORLD");
    assert(MyString::LowerAllString(str.GetValue()) == "hello world");
    
    // Test palindrome
    MyString palindrome("racecar");
    assert(palindrome.IsPalindrome() == true);
    
    std::cout << "✓ MyString basic tests passed\n";
}

void test_mystring_error_handling() {
    std::cout << "Testing MyString error handling...\n";
    
    // Clear any previous errors
    MyString::ClearError();
    
    // Test empty string validation
    try {
        MyString empty("");
        assert(false); // Should not reach here
    } catch (const std::exception& e) {
        assert(MyString::GetLastError() == "Cannot create MyString with empty value");
    }
    
    std::cout << "✓ MyString error handling tests passed\n";
}

void test_mydate_basic() {
    std::cout << "Testing MyDate basic functionality...\n";
    
    // Test constructor
    MyDate date(15, 8, 1990);
    assert(date.GetDay() == 15);
    assert(date.GetMonth() == 8);
    assert(date.GetYear() == 1990);
    
    // Test string constructor
    MyDate date2("25/12/2023");
    assert(date2.GetDay() == 25);
    assert(date2.GetMonth() == 12);
    assert(date2.GetYear() == 2023);
    
    std::cout << "✓ MyDate basic tests passed\n";
}

void test_mydate_error_handling() {
    std::cout << "Testing MyDate error handling...\n";
    
    // Clear any previous errors
    MyDate::ClearError();
    
    // Test invalid date format
    try {
        MyDate invalid("32-13-2024");  // Wrong delimiter
        assert(false); // Should not reach here
    } catch (const std::exception& e) {
        assert(MyDate::GetLastError() == "Invalid date format. Expected DD/MM/YYYY");
    }
    
    std::cout << "✓ MyDate error handling tests passed\n";
}

void test_myperiod_basic() {
    std::cout << "Testing MyPeriod basic functionality...\n";
    
    // Test constructor
    MyDate start(1, 1, 2024);
    MyDate end(31, 12, 2024);
    MyPeriod period(start, end);
    
    assert(period.GetStartDate().GetDay() == 1);
    assert(period.GetEndDate().GetDay() == 31);
    
    // Test duration
    int duration = period.GetDurationInDays();
    std::cout << "Actual duration: " << duration << " days" << std::endl;
    assert(duration == 366); // 2024 is a leap year
    
    std::cout << "✓ MyPeriod basic tests passed\n";
}

void test_myperiod_error_handling() {
    std::cout << "Testing MyPeriod error handling...\n";
    
    // Clear any previous errors
    MyPeriod::ClearError();
    
    // Test invalid period (start after end)
    try {
        MyDate start(31, 12, 2024);
        MyDate end(1, 1, 2024);
        MyPeriod invalid(start, end);
        assert(false); // Should not reach here
    } catch (const std::exception& e) {
        assert(MyPeriod::GetLastError() == "Invalid period: Start date cannot be after end date");
    }
    
    std::cout << "✓ MyPeriod error handling tests passed\n";
}

int main() {
    std::cout << "=== C++ Library Collection Tests ===\n\n";
    
    try {
        test_mystring_basic();
        test_mystring_error_handling();
        test_mydate_basic();
        test_mydate_error_handling();
        test_myperiod_basic();
        test_myperiod_error_handling();
        
        std::cout << "\n🎉 All tests passed successfully!\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cout << "\n❌ Test failed: " << e.what() << std::endl;
        std::cout << "Last error: " << MyString::GetLastError() << std::endl;
        return 1;
    }
}
