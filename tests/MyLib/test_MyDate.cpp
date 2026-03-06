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
    
    // Test AddDays (void function)
    MyDate testDate = date;
    testDate.AddDays(1);
    assert(testDate.GetDay() == 26);
    assert(testDate.GetMonth() == 12);
    assert(testDate.GetYear() == 2023);
    std::cout << "✓ AddDays test passed\n";
    
    // Test AddOneDay
    MyDate testDate2 = date;
    MyDate nextDay = MyDate::AddOneDay(testDate2);
    assert(nextDay.GetDay() == 26);
    assert(nextDay.GetMonth() == 12);
    assert(nextDay.GetYear() == 2023);
    std::cout << "✓ AddOneDay test passed\n";
    
    // Test GetDifferenceInDays
    MyDate date1("25/12/2023");
    MyDate date2("27/12/2023");
    int diff = MyDate::GetDifferenceInDays(date1, date2);
    assert(diff == 2);
    std::cout << "✓ GetDifferenceInDays test passed\n";
    
    std::cout << "✓ MyDate arithmetic tests passed\n\n";
}

void test_mydate_utilities() {
    std::cout << "Testing MyDate utilities...\n";
    
    MyDate date("25/12/2023");
    
    // Test day of week order
    int dayOfWeek = date.DayOfWeekOrder();
    assert(dayOfWeek >= 0 && dayOfWeek <= 6);
    std::cout << "✓ DayOfWeekOrder test passed\n";
    
    // Test is leap year (static)
    assert(MyDate::isLeapYear(2024) == true);
    assert(MyDate::isLeapYear(2023) == false);
    std::cout << "✓ isLeapYear (static) test passed\n";
    
    // Test is leap year (instance)
    MyDate leapYearDate("01/01/2024");
    MyDate normalYearDate("01/01/2023");
    assert(leapYearDate.isLeapYear() == true);
    assert(normalYearDate.isLeapYear() == false);
    std::cout << "✓ isLeapYear (instance) test passed\n";
    
    // Test number of days in month
    assert(MyDate::NumberOfDaysInAMonth(2, 2024) == 29);
    assert(MyDate::NumberOfDaysInAMonth(2, 2023) == 28);
    assert(MyDate::NumberOfDaysInAMonth(4, 2023) == 30);
    assert(MyDate::NumberOfDaysInAMonth(12, 2023) == 31);
    std::cout << "✓ NumberOfDaysInAMonth test passed\n";
    
    // Test number of days in year
    assert(MyDate::NumberOfDaysInAYear(2024) == 366);
    assert(MyDate::NumberOfDaysInAYear(2023) == 365);
    std::cout << "✓ NumberOfDaysInAYear test passed\n";
    
    // Test day short name
    std::string dayName = MyDate::DayShortName(0); // Sunday
    assert(dayName == "Sun");
    std::cout << "✓ DayShortName test passed\n";
    
    // Test month short name
    std::string monthName = MyDate::MonthShortName(12);
    assert(monthName == "Dec");
    std::cout << "✓ MonthShortName test passed\n";
    
    std::cout << "✓ MyDate utility tests passed\n\n";
}

void test_mydate_calendar() {
    std::cout << "Testing MyDate calendar functions...\n";
    
    // Test PrintMonthCalendar (visual verification)
    std::cout << "Testing PrintMonthCalendar output:\n";
    MyDate::PrintMonthCalendar(12, 2023);
    std::cout << "✓ PrintMonthCalendar (static) test passed\n";
    
    MyDate date("15/06/2023");
    std::cout << "Testing PrintMonthCalendar (instance) output:\n";
    date.PrintMonthCalendar();
    std::cout << "✓ PrintMonthCalendar (instance) test passed\n";
    
    // Test PrintYearCalendar (visual verification)
    std::cout << "Testing PrintYearCalendar output:\n";
    MyDate::PrintYearCalendar(2023);
    std::cout << "✓ PrintYearCalendar (static) test passed\n";
    
    std::cout << "✓ MyDate calendar tests passed\n\n";
}

void test_mydate_business_vacation() {
    std::cout << "Testing MyDate business and vacation functions...\n";
    
    // Test IsEndOfWeek
    MyDate friday("01/12/2023"); // Friday
    MyDate saturday("02/12/2023"); // Saturday
    MyDate sunday("03/12/2023"); // Sunday
    MyDate monday("04/12/2023"); // Monday
    
    assert(friday.IsEndOfWeek() == 1); // Friday is end of week
    assert(saturday.IsEndOfWeek() == 0); // Saturday is not end of week
    std::cout << "✓ IsEndOfWeek test passed\n";
    
    // Test IsWeekEnd
    assert(friday.IsWeekEnd() == true); // Friday is weekend
    assert(saturday.IsWeekEnd() == true); // Saturday is weekend
    assert(sunday.IsWeekEnd() == false); // Sunday is not weekend
    assert(monday.IsWeekEnd() == false); // Monday is not weekend
    std::cout << "✓ IsWeekEnd test passed\n";
    
    // Test IsBusinessDay
    assert(friday.IsBusinessDay() == false); // Friday is not business day
    assert(saturday.IsBusinessDay() == false); // Saturday is not business day
    assert(sunday.IsBusinessDay() == true); // Sunday is business day
    assert(monday.IsBusinessDay() == true); // Monday is business day
    std::cout << "✓ IsBusinessDay test passed\n";
    
    // Test CalculateBusinessDays
    MyDate startDate("01/12/2023"); // Friday
    MyDate endDate("07/12/2023"); // Thursday
    short businessDays = MyDate::CalculateBusinessDays(startDate, endDate);
    assert(businessDays == 5); // Sun, Mon, Tue, Wed, Thu = 5 days
    std::cout << "✓ CalculateBusinessDays test passed\n";
    
    // Test CalculateVacationDays
    short vacationDays = MyDate::CalculateVacationDays(startDate, endDate);
    assert(vacationDays == 2); // Fri, Sat = 2 days
    std::cout << "✓ CalculateVacationDays test passed\n";
    
    // Test CalculateVacationReturnDate
    MyDate vacationStart("01/12/2023"); // Friday
    MyDate returnDate = MyDate::CalculateVacationReturnDate(vacationStart, 5);
    assert(returnDate.GetDay() == 7); // Should return on Thursday
    assert(returnDate.GetMonth() == 12);
    std::cout << "✓ CalculateVacationReturnDate test passed\n";
    
    std::cout << "✓ MyDate business and vacation tests passed\n\n";
}

int main() {
    std::cout << "=== MyDate Unit Tests ===\n\n";
    
    test_mydate_constructors();
    test_mydate_getters_setters();
    test_mydate_error_handling();
    test_mydate_validation();
    test_mydate_formatting();
    test_mydate_comparisons();
    test_mydate_arithmetic();
    test_mydate_utilities();
    
    std::cout << "🎉 All MyDate tests passed successfully!\n";
    return 0;
}
