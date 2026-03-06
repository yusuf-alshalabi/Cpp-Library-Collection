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
    
    // Test string constructor
    MyDate date("25/12/2023");
    assert(date.GetDay() == 25);
    assert(date.GetMonth() == 12);
    assert(date.GetYear() == 2023);
    
    std::cout << "✓ MyDate constructor tests passed\n\n";
}

void test_mydate_validation() {
    std::cout << "Testing MyDate validation...\n";
    
    // Test valid dates
    MyDate validDate("15/06/2023");
    assert(validDate.IsValid() == true);
    
    // Test invalid dates
    try {
        MyDate invalidDate("32/13/2023");
        assert(false); // Should not reach here
    } catch (...) {
        // Expected to throw exception
    }
    
    std::cout << "✓ MyDate validation tests passed\n\n";
}

void test_mydate_formatting() {
    std::cout << "Testing MyDate formatting...\n";
    
    MyDate date("25/12/2023");
    
    // Test date to string
    std::string dateStr = date.ToString();
    assert(dateStr == "25/12/2023");
    
    // Test formatted output
    std::string formatted = date.Format("DD-MM-YYYY");
    assert(formatted == "25-12-2023");
    
    std::cout << "✓ MyDate formatting tests passed\n\n";
}

void test_mydate_comparisons() {
    std::cout << "Testing MyDate comparisons...\n";
    
    MyDate date1("25/12/2023");
    MyDate date2("26/12/2023");
    MyDate date3("25/12/2023");
    
    assert(date1.IsEqual(date3) == true);
    assert(date1.IsEqual(date2) == false);
    assert(date1.IsBefore(date2) == true);
    assert(date2.IsAfter(date1) == true);
    
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
