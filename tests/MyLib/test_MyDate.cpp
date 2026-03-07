#include <iostream>
#include <cassert>
#include "../../include/MyLib/MyDate.h"

using namespace MyLib;

// Test helper functions for cleaner assertions
void assert_equal(int expected, int actual, const std::string& test_name) {
    assert(expected == actual);
    std::cout << "✓ " << test_name << " test passed\n";
}

void assert_equal(long long expected, long long actual, const std::string& test_name) {
    assert(expected == actual);
    std::cout << "✓ " << test_name << " test passed\n";
}

void assert_equal(const std::string& expected, const std::string& actual, const std::string& test_name) {
    assert(expected == actual);
    std::cout << "✓ " << test_name << " test passed\n";
}

void assert_true(bool condition, const std::string& test_name) {
    assert(condition);
    std::cout << "✓ " << test_name << " test passed\n";
}

// Test data constants for better readability
namespace TestData {
    const std::string VALID_DATE_STR = "25/12/2023";
    const std::string INVALID_FORMAT_STR = "invalid";
    const std::string INVALID_COMPONENTS_STR = "32/13/2023";
    const int VALID_DAY = 25;
    const int VALID_MONTH = 12;
    const int VALID_YEAR = 2023;
    const int LEAP_YEAR = 2024;
    const int NON_LEAP_YEAR = 2023;
}

void test_constructors() {
    std::cout << "Testing constructors...\n";
    
    // Default constructor should create today's date
    MyDate today;
    assert_true(today.GetDay() >= 1 && today.GetDay() <= 31, "Default: valid day range");
    assert_true(today.GetMonth() >= 1 && today.GetMonth() <= 12, "Default: valid month range");
    assert_true(today.GetYear() >= 1900, "Default: valid year range");
    
    // String constructor
    MyDate dateFromString(TestData::VALID_DATE_STR);
    assert_equal(TestData::VALID_DAY, dateFromString.GetDay(), "String constructor: day");
    assert_equal(TestData::VALID_MONTH, dateFromString.GetMonth(), "String constructor: month");
    assert_equal(TestData::VALID_YEAR, dateFromString.GetYear(), "String constructor: year");
    
    // DMY constructor
    MyDate dateFromComponents(TestData::VALID_DAY, TestData::VALID_MONTH, TestData::VALID_YEAR);
    assert_equal(TestData::VALID_DAY, dateFromComponents.GetDay(), "DMY constructor: day");
    assert_equal(TestData::VALID_MONTH, dateFromComponents.GetMonth(), "DMY constructor: month");
    assert_equal(TestData::VALID_YEAR, dateFromComponents.GetYear(), "DMY constructor: year");
    
    // Day order in year constructor (60th day of 2023 = March 1)
    MyDate dateFromDayOrder(60, TestData::NON_LEAP_YEAR);
    assert_equal(1, dateFromDayOrder.GetDay(), "Day order constructor: day");
    assert_equal(3, dateFromDayOrder.GetMonth(), "Day order constructor: month");
    assert_equal(TestData::NON_LEAP_YEAR, dateFromDayOrder.GetYear(), "Day order constructor: year");
    
    std::cout << "✓ Constructor tests passed\n\n";
}

void test_getters_setters() {
    std::cout << "Testing getters and setters...\n";
    
    MyDate date(1, 1, TestData::VALID_YEAR);
    
    // Test initial getters
    assert_equal(1, date.GetDay(), "Getter: initial day");
    assert_equal(1, date.GetMonth(), "Getter: initial month");
    assert_equal(TestData::VALID_YEAR, date.GetYear(), "Getter: initial year");
    
    // Test setters
    date.SetDay(15);
    date.SetMonth(6);
    date.SetYear(TestData::LEAP_YEAR);
    
    assert_equal(15, date.GetDay(), "Setter: day");
    assert_equal(6, date.GetMonth(), "Setter: month");
    assert_equal(TestData::LEAP_YEAR, date.GetYear(), "Setter: year");
    
    std::cout << "✓ Getters and setters tests passed\n\n";
}

void test_error_handling() {
    std::cout << "Testing error handling...\n";
    
    // Test error clearing and retrieval
    MyDate::ClearError();
    assert_equal("", MyDate::GetLastError().c_str(), "Error handling: clear and get");
    
    // Test invalid date format exception
    try {
        MyDate invalidDate(TestData::INVALID_FORMAT_STR);
        assert_true(false, "Exception: should throw for invalid format");
    } catch (const std::invalid_argument&) {
        assert_equal("Invalid date format. Expected DD/MM/YYYY", 
                   MyDate::GetLastError().c_str(), "Exception: invalid format message");
    }
    
    // Test invalid date components exception
    MyDate::ClearError();
    try {
        MyDate invalidDate(TestData::INVALID_COMPONENTS_STR);
        assert_true(false, "Exception: should throw for invalid components");
    } catch (const std::invalid_argument&) {
        assert_equal("Invalid date format. Cannot parse date components", 
                   MyDate::GetLastError().c_str(), "Exception: invalid components message");
    }
    
    std::cout << "✓ Error handling tests passed\n\n";
}

void test_validation() {
    std::cout << "Testing validation...\n";
    
    // Test valid date
    MyDate validDate(TestData::VALID_DATE_STR);
    assert_true(validDate.IsValid(), "Validation: valid date instance");
    
    // Test leap year validation (Feb 29, 2024)
    MyDate leapYearDate(29, 2, TestData::LEAP_YEAR);
    assert_true(MyDate::IsValidDate(leapYearDate), "Validation: leap year date");
    
    // Test invalid date (Apr 31, 2023)
    MyDate invalidDate(31, 4, TestData::NON_LEAP_YEAR);
    assert_true(!MyDate::IsValidDate(invalidDate), "Validation: invalid April date");
    
    std::cout << "✓ Validation tests passed\n\n";
}

void test_formatting() {
    std::cout << "Testing formatting...\n";
    
    MyDate date(TestData::VALID_DATE_STR);
    
    // Test static DateToString
    std::string staticResult = MyDate::DateToString(date);
    assert_equal(TestData::VALID_DATE_STR, staticResult.c_str(), "Formatting: static DateToString");
    
    // Test instance DateToString
    std::string instanceResult = date.DateToString();
    assert_equal(TestData::VALID_DATE_STR, instanceResult.c_str(), "Formatting: instance DateToString");
    
    // Test Print method (visual verification)
    std::cout << "Testing Print method output:\n";
    date.Print();
    
    std::cout << "✓ Formatting tests passed\n\n";
}

void test_comparisons() {
    std::cout << "Testing comparisons...\n";
    
    MyDate date1(TestData::VALID_DATE_STR);
    MyDate date2("26/12/2023");
    MyDate date3(TestData::VALID_DATE_STR); // Same as date1
    
    // Test static comparison methods
    assert_true(MyDate::IsDate1EqualDate2(date1, date3), "Comparison: static equal dates");
    assert_true(!MyDate::IsDate1EqualDate2(date1, date2), "Comparison: static different dates");
    assert_true(MyDate::IsDate1BeforeDate2(date1, date2), "Comparison: static before");
    assert_true(MyDate::IsDate1AfterDate2(date2, date1), "Comparison: static after");
    
    // Test instance comparison methods
    assert_true(date1.IsDateEqualDate2(date3), "Comparison: instance equal dates");
    assert_true(!date1.IsDateEqualDate2(date2), "Comparison: instance different dates");
    assert_true(date1.IsDateBeforeDate2(date2), "Comparison: instance before");
    assert_true(date2.IsDateAfterDate2(date1), "Comparison: instance after");
    
    // Test CompareDates enum
    assert_true(MyDate::CompareDates(date1, date3) == MyDate::enDateCompare::Equal, "CompareDates: equal");
    assert_true(MyDate::CompareDates(date1, date2) == MyDate::enDateCompare::Before, "CompareDates: before");
    assert_true(MyDate::CompareDates(date2, date1) == MyDate::enDateCompare::After, "CompareDates: after");
    
    std::cout << "✓ Comparison tests passed\n\n";
}

void test_basic_arithmetic() {
    std::cout << "Testing basic arithmetic...\n";
    
    MyDate date(TestData::VALID_DATE_STR);
    
    // Test AddDays (adds 1 day to Dec 25)
    MyDate testDate = date;
    testDate.AddDays(1);
    assert_equal(26, testDate.GetDay(), "Arithmetic: AddDays day");
    assert_equal(12, testDate.GetMonth(), "Arithmetic: AddDays month");
    assert_equal(TestData::VALID_YEAR, testDate.GetYear(), "Arithmetic: AddDays year");
    
    // Test AddOneDay
    MyDate nextDay = MyDate::AddOneDay(date);
    assert_equal(26, nextDay.GetDay(), "Arithmetic: AddOneDay day");
    assert_equal(12, nextDay.GetMonth(), "Arithmetic: AddOneDay month");
    assert_equal(TestData::VALID_YEAR, nextDay.GetYear(), "Arithmetic: AddOneDay year");
    
    // Test GetDifferenceInDays
    MyDate startDate("25/12/2023");
    MyDate endDate("27/12/2023");
    assert_equal(2, MyDate::GetDifferenceInDays(startDate, endDate), "Arithmetic: difference in days");
    
    std::cout << "✓ Basic arithmetic tests passed\n\n";
}

void test_utility_functions() {
    std::cout << "Testing utility functions...\n";
    
    // Test leap year detection
    assert_true(MyDate::isLeapYear(TestData::LEAP_YEAR), "Utility: static leap year detection");
    assert_true(!MyDate::isLeapYear(TestData::NON_LEAP_YEAR), "Utility: static non-leap year");
    
    MyDate leapYearInstance("01/01/" + std::to_string(TestData::LEAP_YEAR));
    MyDate nonLeapYearInstance("01/01/" + std::to_string(TestData::NON_LEAP_YEAR));
    assert_true(leapYearInstance.isLeapYear(), "Utility: instance leap year detection");
    assert_true(!nonLeapYearInstance.isLeapYear(), "Utility: instance non-leap year detection");
    
    // Test days in month calculation
    assert_equal(29, MyDate::NumberOfDaysInAMonth(2, TestData::LEAP_YEAR), "Utility: Feb days in leap year");
    assert_equal(28, MyDate::NumberOfDaysInAMonth(2, TestData::NON_LEAP_YEAR), "Utility: Feb days in non-leap year");
    assert_equal(30, MyDate::NumberOfDaysInAMonth(4, TestData::NON_LEAP_YEAR), "Utility: April days");
    assert_equal(31, MyDate::NumberOfDaysInAMonth(12, TestData::NON_LEAP_YEAR), "Utility: December days");
    
    // Test days in year calculation
    assert_equal(366, MyDate::NumberOfDaysInAYear(TestData::LEAP_YEAR), "Utility: days in leap year");
    assert_equal(365, MyDate::NumberOfDaysInAYear(TestData::NON_LEAP_YEAR), "Utility: days in non-leap year");
    
    // Test day and month names
    assert_equal("Sun", MyDate::DayShortName(0).c_str(), "Utility: Sunday name");
    assert_equal("Dec", MyDate::MonthShortName(12).c_str(), "Utility: December name");
    
    // Test day of week calculation
    MyDate testDate(TestData::VALID_DATE_STR);
    int dayOfWeek = testDate.DayOfWeekOrder();
    assert_true(dayOfWeek >= 0 && dayOfWeek <= 6, "Utility: day of week range");
    
    std::cout << "✓ Utility function tests passed\n\n";
}

void test_time_calculations() {
    std::cout << "Testing time calculations...\n";
    
    // Test hours in year
    assert_equal(365LL * 24, MyDate::NumberOfHoursInAYear(TestData::NON_LEAP_YEAR), "Time: hours in non-leap year");
    assert_equal(366LL * 24, MyDate::NumberOfHoursInAYear(TestData::LEAP_YEAR), "Time: hours in leap year");
    
    // Test minutes in year
    assert_equal(365LL * 24 * 60, MyDate::NumberOfMinutesInAYear(TestData::NON_LEAP_YEAR), "Time: minutes in non-leap year");
    
    // Test seconds in year
    assert_equal(365LL * 24 * 60 * 60, MyDate::NumberOfSecondsInAYear(TestData::NON_LEAP_YEAR), "Time: seconds in non-leap year");
    
    // Test hours in month
    assert_equal(31 * 24, MyDate::NumberOfHoursInAMonth(12, TestData::NON_LEAP_YEAR), "Time: hours in December");
    assert_equal(29 * 24, MyDate::NumberOfHoursInAMonth(2, TestData::LEAP_YEAR), "Time: hours in Feb (leap)");
    
    std::cout << "✓ Time calculation tests passed\n\n";
}

void test_business_calculations() {
    std::cout << "Testing business calculations...\n";
    
    // Test weekend detection (Friday/Saturday are weekends in this implementation)
    MyDate friday("01/12/2023");    // Friday
    MyDate saturday("02/12/2023");  // Saturday
    MyDate sunday("03/12/2023");    // Sunday
    MyDate monday("04/12/2023");    // Monday
    
    assert_equal(1, friday.IsEndOfWeek(), "Business: Friday is end of week");
    assert_equal(0, saturday.IsEndOfWeek(), "Business: Saturday is not end of week");
    
    assert_true(friday.IsWeekEnd(), "Business: Friday is weekend");
    assert_true(saturday.IsWeekEnd(), "Business: Saturday is weekend");
    assert_true(!sunday.IsWeekEnd(), "Business: Sunday is not weekend");
    assert_true(!monday.IsWeekEnd(), "Business: Monday is not weekend");
    
    assert_true(!friday.IsBusinessDay(), "Business: Friday is not business day");
    assert_true(!saturday.IsBusinessDay(), "Business: Saturday is not business day");
    assert_true(sunday.IsBusinessDay(), "Business: Sunday is business day");
    assert_true(monday.IsBusinessDay(), "Business: Monday is business day");
    
    // Test business days calculation
    MyDate workWeekStart("01/12/2023"); // Friday
    MyDate workWeekEnd("07/12/2023");   // Thursday
    assert_equal(5, MyDate::CalculateBusinessDays(workWeekStart, workWeekEnd), "Business: business days in week");
    
    // Test vacation days calculation
    assert_equal(2, MyDate::CalculateVacationDays(workWeekStart, workWeekEnd), "Business: vacation days in week");
    
    // Test vacation return date calculation
    MyDate vacationStart("01/12/2023"); // Friday
    MyDate returnDate = MyDate::CalculateVacationReturnDate(vacationStart, 5);
    assert_equal(7, returnDate.GetDay(), "Business: vacation return day");
    assert_equal(12, returnDate.GetMonth(), "Business: vacation return month");
    
    std::cout << "✓ Business calculation tests passed\n\n";
}

void test_advanced_arithmetic() {
    std::cout << "Testing advanced arithmetic...\n";
    
    MyDate baseDate(TestData::VALID_DATE_STR);
    
    // Test increase by one week (Dec 25 -> Jan 1)
    MyDate nextWeek = MyDate::IncreaseDateByOneWeek(baseDate);
    assert_equal(1, nextWeek.GetDay(), "Advanced: increase one week day");
    assert_equal(1, nextWeek.GetMonth(), "Advanced: increase one week month");
    assert_equal(TestData::LEAP_YEAR, nextWeek.GetYear(), "Advanced: increase one week year");
    
    // Test increase by one month (Dec 15 -> Jan 15)
    MyDate nextMonth = MyDate::IncreaseDateByOneMonth(MyDate(15, 12, TestData::VALID_YEAR));
    assert_equal(15, nextMonth.GetDay(), "Advanced: increase one month day");
    assert_equal(1, nextMonth.GetMonth(), "Advanced: increase one month month");
    assert_equal(TestData::LEAP_YEAR, nextMonth.GetYear(), "Advanced: increase one month year");
    
    // Test increase by one year
    MyDate nextYear = MyDate::IncreaseDateByOneYear(MyDate(15, 6, TestData::VALID_YEAR));
    assert_equal(15, nextYear.GetDay(), "Advanced: increase one year day");
    assert_equal(6, nextYear.GetMonth(), "Advanced: increase one year month");
    assert_equal(TestData::LEAP_YEAR, nextYear.GetYear(), "Advanced: increase one year year");
    
    std::cout << "✓ Advanced arithmetic tests passed\n\n";
}

void test_decrease_arithmetic() {
    std::cout << "Testing decrease arithmetic...\n";
    
    // Test decrease by one day (Jan 1 -> Dec 31)
    MyDate previousDay = MyDate::DecreaseDateByOneDay(MyDate(1, 1, TestData::LEAP_YEAR));
    assert_equal(31, previousDay.GetDay(), "Decrease: one day day");
    assert_equal(12, previousDay.GetMonth(), "Decrease: one day month");
    assert_equal(TestData::VALID_YEAR, previousDay.GetYear(), "Decrease: one day year");
    
    // Test decrease by one month
    MyDate previousMonth = MyDate::DecreaseDateByOneMonth(MyDate(15, 2, TestData::LEAP_YEAR));
    assert_equal(15, previousMonth.GetDay(), "Decrease: one month day");
    assert_equal(1, previousMonth.GetMonth(), "Decrease: one month month");
    assert_equal(TestData::LEAP_YEAR, previousMonth.GetYear(), "Decrease: one month year");
    
    // Test decrease by one year
    MyDate previousYear = MyDate::DecreaseDateByOneYear(MyDate(15, 6, TestData::LEAP_YEAR));
    assert_equal(15, previousYear.GetDay(), "Decrease: one year day");
    assert_equal(6, previousYear.GetMonth(), "Decrease: one year month");
    assert_equal(TestData::VALID_YEAR, previousYear.GetYear(), "Decrease: one year year");
    
    std::cout << "✓ Decrease arithmetic tests passed\n\n";
}

void test_period_calculations() {
    std::cout << "Testing period calculations...\n";
    
    // Test days from beginning of year
    MyDate janFirst("01/01/2023");
    MyDate decLast("31/12/2023");
    MyDate marFirst("01/03/2024"); // Leap year
    
    assert_equal(1, janFirst.DaysFromTheBeginingOfTheYear(), "Period: days from beginning (Jan 1)");
    assert_equal(365, decLast.DaysFromTheBeginingOfTheYear(), "Period: days from beginning (Dec 31)");
    assert_equal(61, marFirst.DaysFromTheBeginingOfTheYear(), "Period: days from beginning (Mar 1, leap)");
    
    // Test date from day order in year
    MyDate dateFromOrder = MyDate::GetDateFromDayOrderInYear(60, TestData::NON_LEAP_YEAR);
    assert_equal(1, dateFromOrder.GetDay(), "Period: date from order day");
    assert_equal(3, dateFromOrder.GetMonth(), "Period: date from order month");
    assert_equal(TestData::NON_LEAP_YEAR, dateFromOrder.GetYear(), "Period: date from order year");
    
    // Test last day checks
    MyDate lastDayDate("31/12/2023");
    MyDate notLastDayDate("15/12/2023");
    assert_true(lastDayDate.IsLastDayInMonth(), "Period: is last day in month (true)");
    assert_true(!notLastDayDate.IsLastDayInMonth(), "Period: is last day in month (false)");
    
    assert_true(MyDate::IsLastMonthInYear(12), "Period: is last month in year (true)");
    assert_true(!MyDate::IsLastMonthInYear(6), "Period: is last month in year (false)");
    
    std::cout << "✓ Period calculation tests passed\n\n";
}

void test_system_functions() {
    std::cout << "Testing system functions...\n";
    
    // Test system date
    MyDate systemDate = MyDate::GetSystemDate();
    assert_true(systemDate.GetDay() >= 1 && systemDate.GetDay() <= 31, "System: valid day");
    assert_true(systemDate.GetMonth() >= 1 && systemDate.GetMonth() <= 12, "System: valid month");
    assert_true(systemDate.GetYear() >= TestData::VALID_YEAR, "System: valid year");
    
    // Test age calculation
    MyDate birthDate("01/01/2000");
    assert_true(MyDate::CalculateMyAgeInDays(birthDate) > 0, "System: age calculation positive");
    
    // Test date swap
    MyDate date1("01/01/2023");
    MyDate date2("31/12/2023");
    MyDate::SwapDates(date1, date2);
    assert_equal(31, date1.GetDay(), "System: swap first day");
    assert_equal(12, date1.GetMonth(), "System: swap first month");
    assert_equal(1, date2.GetDay(), "System: swap second day");
    assert_equal(1, date2.GetMonth(), "System: swap second month");
    
    std::cout << "✓ System function tests passed\n\n";
}

void test_calendar_functions() {
    std::cout << "Testing calendar functions...\n";
    
    // Test calendar printing (visual verification)
    std::cout << "Testing PrintMonthCalendar (static):\n";
    MyDate::PrintMonthCalendar(12, TestData::VALID_YEAR);
    
    std::cout << "Testing PrintMonthCalendar (instance):\n";
    MyDate date("15/06/2023");
    date.PrintMonthCalendar();
    
    std::cout << "Testing PrintYearCalendar (static):\n";
    MyDate::PrintYearCalendar(TestData::VALID_YEAR);
    
    std::cout << "✓ Calendar function tests passed\n\n";
}

void test_end_of_period_functions() {
    std::cout << "Testing end of period functions...\n";
    
    MyDate sunday("03/12/2023"); // Sunday
    MyDate monday("04/12/2023"); // Monday
    MyDate saturday("09/12/2023"); // Saturday
    
    // Test days until end of week
    assert_equal(6, sunday.DaysUntilTheEndOfWeek(), "End period: days to week end (Sunday)");
    assert_equal(5, monday.DaysUntilTheEndOfWeek(), "End period: days to week end (Monday)");
    assert_equal(0, saturday.DaysUntilTheEndOfWeek(), "End period: days to week end (Saturday)");
    
    // Test days until end of month
    MyDate monthStart("01/12/2023");
    MyDate monthMiddle("15/12/2023");
    MyDate monthEnd("31/12/2023");
    
    assert_equal(30, monthStart.DaysUntilTheEndOfMonth(), "End period: days to month end (start)");
    assert_equal(16, monthMiddle.DaysUntilTheEndOfMonth(), "End period: days to month end (middle)");
    assert_equal(0, monthEnd.DaysUntilTheEndOfMonth(), "End period: days to month end (end)");
    
    // Test days until end of year
    MyDate yearStart("01/01/2023");
    MyDate yearMiddle("02/07/2023");
    MyDate yearEnd("31/12/2023");
    
    assert_equal(364, yearStart.DaysUntilTheEndOfYear(), "End period: days to year end (start)");
    assert_equal(182, yearMiddle.DaysUntilTheEndOfYear(), "End period: days to year end (middle)");
    assert_equal(0, yearEnd.DaysUntilTheEndOfYear(), "End period: days to year end (end)");
    
    std::cout << "✓ End of period tests passed\n\n";
}

int main() {
    std::cout << "=== MyDate Unit Tests ===\n\n";
    
    test_constructors();
    test_getters_setters();
    test_error_handling();
    test_validation();
    test_formatting();
    test_comparisons();
    test_basic_arithmetic();
    test_utility_functions();
    test_time_calculations();
    test_business_calculations();
    test_advanced_arithmetic();
    test_decrease_arithmetic();
    test_period_calculations();
    test_system_functions();
    test_calendar_functions();
    test_end_of_period_functions();
    
    std::cout << "🎉 All MyDate tests passed successfully!\n";
    return 0;
}
