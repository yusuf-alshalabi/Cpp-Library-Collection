#include <iostream>
#include <cassert>
#include "../../include/MyLib/MyDate.h"

using namespace MyLib;

void test_mydate_constructors() {
    std::cout << "Testing MyDate constructors...\n";
    
    // Test default constructor (should be today's date)
    MyDate today;
    assert(today.GetDay() >= 1 && today.GetDay() <= 31);
    assert(today.GetMonth() >= 1 && today.GetMonth() <= 12);
    assert(today.GetYear() >= 1900);
    std::cout << "✓ Default constructor test passed\n";
    
    // Test string constructor
    MyDate date("25/12/2023");
    assert(date.GetDay() == 25);
    assert(date.GetMonth() == 12);
    assert(date.GetYear() == 2023);
    std::cout << "✓ String constructor test passed\n";
    
    // Test day/month/year constructor
    MyDate date2(15, 6, 2023);
    assert(date2.GetDay() == 15);
    assert(date2.GetMonth() == 6);
    assert(date2.GetYear() == 2023);
    std::cout << "✓ Day/Month/Year constructor test passed\n";
    
    // Test date order in year constructor
    MyDate date3(60, 2023); // 60th day of 2023 = March 1 (non-leap year)
    assert(date3.GetDay() == 1);
    assert(date3.GetMonth() == 3);
    assert(date3.GetYear() == 2023);
    std::cout << "✓ Date order in year constructor test passed\n";
    
    std::cout << "✓ MyDate constructor tests passed\n\n";
}

void test_mydate_getters_setters() {
    std::cout << "Testing MyDate getters and setters...\n";
    
    MyDate date(1, 1, 2023);
    
    // Test getters
    assert(date.GetDay() == 1);
    assert(date.GetMonth() == 1);
    assert(date.GetYear() == 2023);
    std::cout << "✓ Getters test passed\n";
    
    // Test setters
    date.SetDay(15);
    date.SetMonth(6);
    date.SetYear(2024);
    
    assert(date.GetDay() == 15);
    assert(date.GetMonth() == 6);
    assert(date.GetYear() == 2024);
    std::cout << "✓ Setters test passed\n";
    
    std::cout << "✓ MyDate getters and setters tests passed\n\n";
}

void test_mydate_error_handling() {
    std::cout << "Testing MyDate error handling...\n";
    
    // Clear any previous errors
    MyDate::ClearError();
    assert(MyDate::GetLastError() == "");
    std::cout << "✓ ClearError and GetLastError test passed\n";
    
    // Test invalid date format
    try {
        MyDate invalidDate("invalid");
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        assert(MyDate::GetLastError() == "Invalid date format. Expected DD/MM/YYYY");
        std::cout << "✓ Invalid format exception test passed\n";
    }
    
    // Clear error for next test
    MyDate::ClearError();
    
    // Test invalid date components
    try {
        MyDate invalidDate("32/13/2023");
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        assert(MyDate::GetLastError() == "Invalid date format. Cannot parse date components");
        std::cout << "✓ Invalid components exception test passed\n";
    }
    
    std::cout << "✓ MyDate error handling tests passed\n\n";
}

void test_mydate_validation() {
    std::cout << "Testing MyDate validation...\n";
    
    // Test valid dates
    MyDate validDate("15/06/2023");
    assert(validDate.IsValid() == true);
    std::cout << "✓ Valid date test passed\n";
    
    // Test static validation
    MyDate testDate(29, 2, 2024); // Leap year
    assert(MyDate::IsValidDate(testDate) == true);
    std::cout << "✓ Static validation (leap year) test passed\n";
    
    MyDate invalidDate(31, 4, 2023); // April has 30 days
    assert(MyDate::IsValidDate(invalidDate) == false);
    std::cout << "✓ Static validation (invalid) test passed\n";
    
    std::cout << "✓ MyDate validation tests passed\n\n";
}

void test_mydate_formatting() {
    std::cout << "Testing MyDate formatting...\n";
    
    MyDate date("25/12/2023");
    
    // Test date to string (static)
    std::string dateStr = MyDate::DateToString(date);
    assert(dateStr == "25/12/2023");
    std::cout << "✓ DateToString (static) test passed\n";
    
    // Test date to string (instance)
    std::string dateStr2 = date.DateToString();
    assert(dateStr2 == "25/12/2023");
    std::cout << "✓ DateToString (instance) test passed\n";
    
    // Test print method
    std::cout << "Testing Print method output:\n";
    date.Print();
    std::cout << "✓ Print method test passed\n";
    
    std::cout << "✓ MyDate formatting tests passed\n\n";
}

void test_mydate_comparisons() {
    std::cout << "Testing MyDate comparisons...\n";
    
    MyDate date1("25/12/2023");
    MyDate date2("26/12/2023");
    MyDate date3("25/12/2023");
    
    // Test static comparison functions
    assert(MyDate::IsDate1EqualDate2(date1, date3) == true);
    assert(MyDate::IsDate1EqualDate2(date1, date2) == false);
    assert(MyDate::IsDate1BeforeDate2(date1, date2) == true);
    assert(MyDate::IsDate1AfterDate2(date2, date1) == true);
    std::cout << "✓ Static comparison functions test passed\n";
    
    // Test instance comparison functions
    assert(date1.IsDateEqualDate2(date3) == true);
    assert(date1.IsDateEqualDate2(date2) == false);
    assert(date1.IsDateBeforeDate2(date2) == true);
    assert(date2.IsDateAfterDate2(date1) == true);
    std::cout << "✓ Instance comparison functions test passed\n";
    
    // Test CompareDates with enum
    assert(MyDate::CompareDates(date1, date3) == MyDate::enDateCompare::Equal);
    assert(MyDate::CompareDates(date1, date2) == MyDate::enDateCompare::Before);
    assert(MyDate::CompareDates(date2, date1) == MyDate::enDateCompare::After);
    std::cout << "✓ CompareDates enum test passed\n";
    
    std::cout << "✓ MyDate comparison tests passed\n\n";
}

void test_mydate_arithmetic() {
    std::cout << "Testing MyDate arithmetic...\n";
    
    MyDate date("25/12/2023");
    
    // Test adding days
    MyDate tomorrow = date.AddDays(1);
    assert(tomorrow.GetDay() == 26);
    assert(tomorrow.GetMonth() == 12);
    assert(tomorrow.GetYear() == 2023);
    
    // Test subtracting days
    MyDate yesterday = date.AddDays(-1);
    assert(yesterday.GetDay() == 24);
    assert(yesterday.GetMonth() == 12);
    assert(yesterday.GetYear() == 2023);
    
    std::cout << "✓ MyDate arithmetic tests passed\n\n";
}

void test_mydate_utilities() {
    std::cout << "Testing MyDate utilities...\n";
    
    MyDate date("25/12/2023");
    
    // Test day of week
    int dayOfWeek = date.DayOfWeek();
    assert(dayOfWeek >= 0 && dayOfWeek <= 6);
    
    // Test is leap year
    assert(MyDate::IsLeapYear(2024) == true);
    assert(MyDate::IsLeapYear(2023) == false);
    
    // Test days in month
    assert(MyDate::DaysInMonth(2, 2024) == 29);
    assert(MyDate::DaysInMonth(2, 2023) == 28);
    assert(MyDate::DaysInMonth(4, 2023) == 30);
    assert(MyDate::DaysInMonth(12, 2023) == 31);
    
    std::cout << "✓ MyDate utility tests passed\n\n";
}

int main() {
    std::cout << "=== MyDate Unit Tests ===\n\n";
    
    test_mydate_constructors();
    test_mydate_validation();
    test_mydate_formatting();
    test_mydate_comparisons();
    test_mydate_arithmetic();
    test_mydate_utilities();
    
    std::cout << "🎉 All MyDate tests passed successfully!\n";
    return 0;
}
