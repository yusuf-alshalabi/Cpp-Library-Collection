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

void test_mydate_time_functions() {
    std::cout << "Testing MyDate time functions...\n";
    
    // Test hours in year
    long long hours2023 = MyDate::NumberOfHoursInAYear(2023);
    assert(hours2023 == 365 * 24);
    long long hours2024 = MyDate::NumberOfHoursInAYear(2024);
    assert(hours2024 == 366 * 24);
    std::cout << "✓ NumberOfHoursInAYear test passed\n";
    
    // Test minutes in year
    long long minutes2023 = MyDate::NumberOfMinutesInAYear(2023);
    assert(minutes2023 == 365 * 24 * 60);
    std::cout << "✓ NumberOfMinutesInAYear test passed\n";
    
    // Test seconds in year
    long long seconds2023 = MyDate::NumberOfSecondsInAYear(2023);
    assert(seconds2023 == 365 * 24 * 60 * 60);
    std::cout << "✓ NumberOfSecondsInAYear test passed\n";
    
    // Test hours in month
    short hoursDec2023 = MyDate::NumberOfHoursInAMonth(12, 2023);
    assert(hoursDec2023 == 31 * 24);
    short hoursFeb2024 = MyDate::NumberOfHoursInAMonth(2, 2024);
    assert(hoursFeb2024 == 29 * 24);
    std::cout << "✓ NumberOfHoursInAMonth test passed\n";
    
    // Test minutes in month
    int minutesDec2023 = MyDate::NumberOfMinutesInAMonth(12, 2023);
    assert(minutesDec2023 == 31 * 24 * 60);
    std::cout << "✓ NumberOfMinutesInAMonth test passed\n";
    
    // Test seconds in month
    int secondsDec2023 = MyDate::NumberOfSecondsInAMonth(12, 2023);
    assert(secondsDec2023 == 31 * 24 * 60 * 60);
    std::cout << "✓ NumberOfSecondsInAMonth test passed\n";
    
    // Test instance time functions
    MyDate date("15/06/2023");
    assert(date.NumberOfHoursInAYear() == 365 * 24);
    assert(date.NumberOfMinutesInAYear() == 365 * 24 * 60);
    assert(date.NumberOfSecondsInAYear() == 365 * 24 * 60 * 60);
    std::cout << "✓ Instance time functions test passed\n";
    
    std::cout << "✓ MyDate time functions tests passed\n\n";
}

void test_mydate_advanced_arithmetic() {
    std::cout << "Testing MyDate advanced arithmetic functions...\n";
    
    // Test IncreaseDateByOneWeek
    MyDate date("25/12/2023");
    MyDate nextWeek = MyDate::IncreaseDateByOneWeek(date);
    assert(nextWeek.GetDay() == 1);
    assert(nextWeek.GetMonth() == 1);
    assert(nextWeek.GetYear() == 2024);
    std::cout << "✓ IncreaseDateByOneWeek (static) test passed\n";
    
    // Test IncreaseDateByOneWeek (instance)
    MyDate date2("25/12/2023");
    date2.IncreaseDateByOneWeek();
    assert(date2.GetDay() == 1);
    assert(date2.GetMonth() == 1);
    assert(date2.GetYear() == 2024);
    std::cout << "✓ IncreaseDateByOneWeek (instance) test passed\n";
    
    // Test IncreaseDateByXWeeks
    MyDate date3("25/12/2023");
    MyDate twoWeeksLater = date3.IncreaseDateByXWeeks(2, date3);
    assert(twoWeeksLater.GetDay() == 8);
    assert(twoWeeksLater.GetMonth() == 1);
    assert(twoWeeksLater.GetYear() == 2024);
    std::cout << "✓ IncreaseDateByXWeeks test passed\n";
    
    // Test IncreaseDateByOneMonth
    MyDate date4("15/01/2023");
    MyDate nextMonth = MyDate::IncreaseDateByOneMonth(date4);
    assert(nextMonth.GetDay() == 15);
    assert(nextMonth.GetMonth() == 2);
    assert(nextMonth.GetYear() == 2023);
    std::cout << "✓ IncreaseDateByOneMonth (static) test passed\n";
    
    // Test IncreaseDateByOneMonth (instance)
    MyDate date5("15/01/2023");
    date5.IncreaseDateByOneMonth();
    assert(date5.GetDay() == 15);
    assert(date5.GetMonth() == 2);
    assert(date5.GetYear() == 2023);
    std::cout << "✓ IncreaseDateByOneMonth (instance) test passed\n";
    
    // Test IncreaseDateByOneYear
    MyDate date6("15/06/2023");
    MyDate nextYear = MyDate::IncreaseDateByOneYear(date6);
    assert(nextYear.GetDay() == 15);
    assert(nextYear.GetMonth() == 6);
    assert(nextYear.GetYear() == 2024);
    std::cout << "✓ IncreaseDateByOneYear test passed\n";
    
    // Test IncreaseDateByOneDecade
    MyDate date7("15/06/2023");
    MyDate nextDecade = date7.IncreaseDateByOneDecade(date7);
    assert(nextDecade.GetDay() == 15);
    assert(nextDecade.GetMonth() == 6);
    assert(nextDecade.GetYear() == 2033);
    std::cout << "✓ IncreaseDateByOneDecade test passed\n";
    
    // Test IncreaseDateByOneCentury
    MyDate date8("15/06/2023");
    MyDate nextCentury = date8.IncreaseDateByOneCentury(date8);
    assert(nextCentury.GetDay() == 15);
    assert(nextCentury.GetMonth() == 6);
    assert(nextCentury.GetYear() == 2123);
    std::cout << "✓ IncreaseDateByOneCentury test passed\n";
    
    // Test IncreaseDateByOneMillennium
    MyDate date9("15/06/2023");
    MyDate nextMillennium = date9.IncreaseDateByOneMillennium(date9);
    assert(nextMillennium.GetDay() == 15);
    assert(nextMillennium.GetMonth() == 6);
    assert(nextMillennium.GetYear() == 3023);
    std::cout << "✓ IncreaseDateByOneMillennium test passed\n";
    
    std::cout << "✓ MyDate advanced arithmetic tests passed\n\n";
}

void test_mydate_decrease_functions() {
    std::cout << "Testing MyDate decrease functions...\n";
    
    // Test DecreaseDateByOneDay
    MyDate date("01/01/2024");
    MyDate previousDay = MyDate::DecreaseDateByOneDay(date);
    assert(previousDay.GetDay() == 31);
    assert(previousDay.GetMonth() == 12);
    assert(previousDay.GetYear() == 2023);
    std::cout << "✓ DecreaseDateByOneDay (static) test passed\n";
    
    // Test DecreaseDateByOneDay (instance)
    MyDate date2("01/01/2024");
    date2.DecreaseDateByOneDay();
    assert(date2.GetDay() == 31);
    assert(date2.GetMonth() == 12);
    assert(date2.GetYear() == 2023);
    std::cout << "✓ DecreaseDateByOneDay (instance) test passed\n";
    
    // Test DecreaseDateByOneWeek
    MyDate date3("08/01/2024");
    MyDate previousWeek = MyDate::DecreaseDateByOneWeek(date3);
    assert(previousWeek.GetDay() == 1);
    assert(previousWeek.GetMonth() == 1);
    assert(previousWeek.GetYear() == 2024);
    std::cout << "✓ DecreaseDateByOneWeek test passed\n";
    
    // Test DecreaseDateByOneMonth
    MyDate date4("15/02/2024");
    MyDate previousMonth = MyDate::DecreaseDateByOneMonth(date4);
    assert(previousMonth.GetDay() == 15);
    assert(previousMonth.GetMonth() == 1);
    assert(previousMonth.GetYear() == 2024);
    std::cout << "✓ DecreaseDateByOneMonth test passed\n";
    
    // Test DecreaseDateByOneYear
    MyDate date5("15/06/2024");
    MyDate previousYear = MyDate::DecreaseDateByOneYear(date5);
    assert(previousYear.GetDay() == 15);
    assert(previousYear.GetMonth() == 6);
    assert(previousYear.GetYear() == 2023);
    std::cout << "✓ DecreaseDateByOneYear test passed\n";
    
    // Test DecreaseDateByOneDecade
    MyDate date6("15/06/2024");
    MyDate previousDecade = date6.DecreaseDateByOneDecade(date6);
    assert(previousDecade.GetDay() == 15);
    assert(previousDecade.GetMonth() == 6);
    assert(previousDecade.GetYear() == 2014);
    std::cout << "✓ DecreaseDateByOneDecade test passed\n";
    
    // Test DecreaseDateByOneCentury
    MyDate date7("15/06/2024");
    MyDate previousCentury = date7.DecreaseDateByOneCentury(date7);
    assert(previousCentury.GetDay() == 15);
    assert(previousCentury.GetMonth() == 6);
    assert(previousCentury.GetYear() == 1924);
    std::cout << "✓ DecreaseDateByOneCentury test passed\n";
    
    // Test DecreaseDateByOneMillennium
    MyDate date8("15/06/2024");
    MyDate previousMillennium = date8.DecreaseDateByOneMillennium(date8);
    assert(previousMillennium.GetDay() == 15);
    assert(previousMillennium.GetMonth() == 6);
    assert(previousMillennium.GetYear() == 1024);
    std::cout << "✓ DecreaseDateByOneMillennium test passed\n";
    
    std::cout << "✓ MyDate decrease functions tests passed\n\n";
}

void test_mydate_calculations() {
    std::cout << "Testing MyDate calculation functions...\n";
    
    // Test DaysFromTheBeginingOfTheYear
    MyDate date1("01/01/2023");
    assert(date1.DaysFromTheBeginingOfTheYear() == 1);
    
    MyDate date2("31/12/2023");
    assert(date2.DaysFromTheBeginingOfTheYear() == 365);
    
    MyDate date3("01/03/2024"); // Leap year
    assert(date3.DaysFromTheBeginingOfTheYear() == 61); // 31 + 29 + 1
    std::cout << "✓ DaysFromTheBeginingOfTheYear test passed\n";
    
    // Test static DaysFromTheBeginingOfTheYear
    assert(MyDate::DaysFromTheBeginingOfTheYear(15, 6, 2023) == 166);
    std::cout << "✓ DaysFromTheBeginingOfTheYear (static) test passed\n";
    
    // Test GetDateFromDayOrderInYear
    MyDate date4 = MyDate::GetDateFromDayOrderInYear(60, 2023);
    assert(date4.GetDay() == 1);
    assert(date4.GetMonth() == 3);
    assert(date4.GetYear() == 2023);
    std::cout << "✓ GetDateFromDayOrderInYear test passed\n";
    
    // Test IsLastDayInMonth
    MyDate lastDay("31/12/2023");
    MyDate notLastDay("15/12/2023");
    assert(lastDay.IsLastDayInMonth() == true);
    assert(notLastDay.IsLastDayInMonth() == false);
    std::cout << "✓ IsLastDayInMonth test passed\n";
    
    // Test IsLastMonthInYear
    assert(MyDate::IsLastMonthInYear(12) == true);
    assert(MyDate::IsLastMonthInYear(6) == false);
    std::cout << "✓ IsLastMonthInYear test passed\n";
    
    // Test CalculateMyAgeInDays
    MyDate birthDate("01/01/2000");
    short ageInDays = MyDate::CalculateMyAgeInDays(birthDate);
    assert(ageInDays > 0); // Should be positive
    std::cout << "✓ CalculateMyAgeInDays test passed\n";
    
    // Test SwapDates
    MyDate date5("01/01/2023");
    MyDate date6("31/12/2023");
    MyDate::SwapDates(date5, date6);
    assert(date5.GetDay() == 31);
    assert(date5.GetMonth() == 12);
    assert(date6.GetDay() == 1);
    assert(date6.GetMonth() == 1);
    std::cout << "✓ SwapDates test passed\n";
    
    // Test GetSystemDate
    MyDate systemDate = MyDate::GetSystemDate();
    assert(systemDate.GetDay() >= 1 && systemDate.GetDay() <= 31);
    assert(systemDate.GetMonth() >= 1 && systemDate.GetMonth() <= 12);
    assert(systemDate.GetYear() >= 2023);
    std::cout << "✓ GetSystemDate test passed\n";
    
    std::cout << "✓ MyDate calculation functions tests passed\n\n";
}

void test_mydate_end_of_period() {
    std::cout << "Testing MyDate end of period functions...\n";
    
    // Test DaysUntilTheEndOfWeek
    MyDate sunday("03/12/2023"); // Sunday
    MyDate monday("04/12/2023"); // Monday
    MyDate saturday("09/12/2023"); // Saturday
    
    assert(sunday.DaysUntilTheEndOfWeek() == 6); // Sunday to Saturday
    assert(monday.DaysUntilTheEndOfWeek() == 5); // Monday to Saturday
    assert(saturday.DaysUntilTheEndOfWeek() == 0); // Saturday is end of week
    std::cout << "✓ DaysUntilTheEndOfWeek test passed\n";
    
    // Test static DaysUntilTheEndOfWeek
    assert(MyDate::DaysUntilTheEndOfWeek(sunday) == 6);
    assert(MyDate::DaysUntilTheEndOfWeek(saturday) == 0);
    std::cout << "✓ DaysUntilTheEndOfWeek (static) test passed\n";
    
    // Test DaysUntilTheEndOfMonth
    MyDate startOfMonth("01/12/2023");
    MyDate middleOfMonth("15/12/2023");
    MyDate endOfMonth("31/12/2023");
    
    assert(startOfMonth.DaysUntilTheEndOfMonth() == 30); // 31-1 = 30 days
    assert(middleOfMonth.DaysUntilTheEndOfMonth() == 16); // 31-15 = 16 days
    assert(endOfMonth.DaysUntilTheEndOfMonth() == 0); // Last day
    std::cout << "✓ DaysUntilTheEndOfMonth test passed\n";
    
    // Test static DaysUntilTheEndOfMonth
    assert(MyDate::DaysUntilTheEndOfMonth(startOfMonth) == 30);
    assert(MyDate::DaysUntilTheEndOfMonth(endOfMonth) == 0);
    std::cout << "✓ DaysUntilTheEndOfMonth (static) test passed\n";
    
    // Test DaysUntilTheEndOfYear
    MyDate startOfYear("01/01/2023");
    MyDate middleOfYear("02/07/2023"); // Around middle of year
    MyDate endOfYear("31/12/2023");
    
    assert(startOfYear.DaysUntilTheEndOfYear() == 364); // 365-1 = 364 days
    assert(middleOfYear.DaysUntilTheEndOfYear() == 182); // Approximately half year remaining
    assert(endOfYear.DaysUntilTheEndOfYear() == 0); // Last day
    std::cout << "✓ DaysUntilTheEndOfYear test passed\n";
    
    // Test static DaysUntilTheEndOfYear
    assert(MyDate::DaysUntilTheEndOfYear(startOfYear) == 364);
    assert(MyDate::DaysUntilTheEndOfYear(endOfYear) == 0);
    std::cout << "✓ DaysUntilTheEndOfYear (static) test passed\n";
    
    std::cout << "✓ MyDate end of period functions tests passed\n\n";
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
    test_mydate_calendar();
    test_mydate_business_vacation();
    test_mydate_time_functions();
    test_mydate_advanced_arithmetic();
    test_mydate_decrease_functions();
    test_mydate_calculations();
    test_mydate_end_of_period();
    
    std::cout << "🎉 All MyDate tests passed successfully!\n";
    return 0;
}
