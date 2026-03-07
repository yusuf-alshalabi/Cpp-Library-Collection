#include <iostream>
#include <cassert>
#include "../../include/MyLib/MyDate.h"
#include "../../include/MyLib/MyPeriod.h"

using namespace MyLib;

// Test data constants for better readability and maintainability
namespace PeriodTestData {
    // Valid test dates
    const std::string VALID_START_DATE = "01/01/2023";
    const std::string VALID_END_DATE = "31/12/2023";
    const std::string MID_YEAR_DATE = "15/06/2023";
    
    // Invalid test dates for error testing
    const std::string INVALID_START_DATE = "31/12/2023";
    const std::string INVALID_END_DATE = "01/01/2023";
    
    // Years for testing
    const int YEAR_2023 = 2023;
    const int YEAR_2024 = 2024;
    const int YEAR_1900 = 1900;
    const int YEAR_2100 = 2100;
    const int YEAR_2099 = 2099;
    
    // Period spans
    const int DAYS_IN_YEAR = 364; // 2023 is not leap year
    const int MONTHS_IN_YEAR = 11; // Jan to Dec is 11 months
}

// Helper functions for cleaner assertions
void assert_equal(const std::string& expected, const std::string& actual, const std::string& test_name) {
    assert(expected == actual);
    std::cout << "✓ " << test_name << " test passed\n";
}

void assert_equal(int expected, int actual, const std::string& test_name) {
    assert(expected == actual);
    std::cout << "✓ " << test_name << " test passed\n";
}

void assert_true(bool condition, const std::string& test_name) {
    assert(condition);
    std::cout << "✓ " << test_name << " test passed\n";
}

// ===== CONSTRUCTOR TESTS =====
void test_constructors() {
    std::cout << "Testing constructors...\n";
    
    // Test default constructor
    MyPeriod defaultPeriod;
    assert_equal("01/01/1900", defaultPeriod.GetStartDate().DateToString(), "Default constructor start date");
    assert_equal("01/01/1900", defaultPeriod.GetEndDate().DateToString(), "Default constructor end date");
    assert_true(defaultPeriod.IsValid(), "Default constructor validity");
    
    // Test constructor with dates
    MyDate startDate(PeriodTestData::VALID_START_DATE);
    MyDate endDate(PeriodTestData::VALID_END_DATE);
    MyPeriod period(startDate, endDate);
    
    assert_equal(PeriodTestData::VALID_START_DATE, period.GetStartDate().DateToString(), "Parameterized constructor start");
    assert_equal(PeriodTestData::VALID_END_DATE, period.GetEndDate().DateToString(), "Parameterized constructor end");
    
    std::cout << "✓ Constructor tests passed\n\n";
}

// ===== GETTERS & SETTERS TESTS =====
void test_getters_setters() {
    std::cout << "Testing getters and setters...\n";
    
    // Test getters
    MyDate startDate(PeriodTestData::VALID_START_DATE);
    MyDate endDate(PeriodTestData::VALID_END_DATE);
    MyPeriod period(startDate, endDate);
    
    assert_equal(PeriodTestData::VALID_START_DATE, period.GetStartDate().DateToString(), "GetStartDate");
    assert_equal(PeriodTestData::VALID_END_DATE, period.GetEndDate().DateToString(), "GetEndDate");
    
    // Test valid setters
    MyDate newStart(PeriodTestData::MID_YEAR_DATE);
    MyDate newEnd(PeriodTestData::MID_YEAR_DATE);
    
    period.SetStartDate(newStart);
    period.SetEndDate(newEnd);
    
    assert_equal(PeriodTestData::MID_YEAR_DATE, period.GetStartDate().DateToString(), "SetStartDate");
    assert_equal(PeriodTestData::MID_YEAR_DATE, period.GetEndDate().DateToString(), "SetEndDate");
    
    // Test invalid SetStartDate
    MyPeriod::ClearError();
    try {
        MyDate invalidStart(PeriodTestData::INVALID_START_DATE);
        period.SetStartDate(invalidStart);
        assert_true(false, "Should throw exception for invalid SetStartDate");
    } catch (const std::invalid_argument&) {
        assert_equal("Invalid period: Start date cannot be after end date", 
                   MyPeriod::GetLastError().c_str(), "SetStartDate validation");
    }
    
    // Test invalid SetEndDate
    MyPeriod::ClearError();
    try {
        MyDate invalidEnd(PeriodTestData::INVALID_END_DATE);
        period.SetEndDate(invalidEnd);
        assert_true(false, "Should throw exception for invalid SetEndDate");
    } catch (const std::invalid_argument&) {
        assert_equal("Invalid period: End date cannot be before start date", 
                   MyPeriod::GetLastError().c_str(), "SetEndDate validation");
    }
    
    std::cout << "✓ Getters and setters tests passed\n\n";
}

// ===== COPY/MOVE OPERATORS TESTS =====
void test_constructors_and_operators() {
    std::cout << "Testing constructors and operators...\n";
    
    // Test constructor with dates
    MyDate start(PeriodTestData::VALID_START_DATE);
    MyDate end(PeriodTestData::VALID_END_DATE);
    MyPeriod original(start, end);
    
    // Test copy constructor
    MyPeriod copied(original);
    assert_equal(PeriodTestData::VALID_START_DATE, copied.GetStartDate().DateToString(), "Copy constructor start");
    assert_equal(PeriodTestData::VALID_END_DATE, copied.GetEndDate().DateToString(), "Copy constructor end");
    
    // Test move constructor
    MyPeriod moved(std::move(original));
    assert_equal(PeriodTestData::VALID_START_DATE, moved.GetStartDate().DateToString(), "Move constructor start");
    assert_equal(PeriodTestData::VALID_END_DATE, moved.GetEndDate().DateToString(), "Move constructor end");
    
    // Test copy assignment operator
    MyDate start2(PeriodTestData::MID_YEAR_DATE);
    MyDate end2(PeriodTestData::MID_YEAR_DATE);
    MyPeriod original2(start2, end2);
    MyPeriod copyAssigned;
    copyAssigned = original2;
    assert_equal(PeriodTestData::MID_YEAR_DATE, copyAssigned.GetStartDate().DateToString(), "Copy assignment start");
    assert_equal(PeriodTestData::MID_YEAR_DATE, copyAssigned.GetEndDate().DateToString(), "Copy assignment end");
    
    // Test move assignment operator
    MyPeriod assigned;
    assigned = std::move(original2);
    assert_equal(PeriodTestData::MID_YEAR_DATE, assigned.GetStartDate().DateToString(), "Move assignment start");
    assert_equal(PeriodTestData::MID_YEAR_DATE, assigned.GetEndDate().DateToString(), "Move assignment end");
    
    // Test self-assignment (copy)
    MyDate selfStart(PeriodTestData::VALID_START_DATE);
    MyDate selfEnd(PeriodTestData::VALID_END_DATE);
    MyPeriod selfPeriod(selfStart, selfEnd);
    selfPeriod = selfPeriod; // Should not crash
    assert_equal(PeriodTestData::VALID_START_DATE, selfPeriod.GetStartDate().DateToString(), "Self-assignment copy start");
    assert_equal(PeriodTestData::VALID_END_DATE, selfPeriod.GetEndDate().DateToString(), "Self-assignment copy end");
    
    // Test self-assignment (move)
    MyPeriod selfMovePeriod(selfStart, selfEnd);
    selfMovePeriod = std::move(selfMovePeriod); // Should not crash
    assert_equal(PeriodTestData::VALID_START_DATE, selfMovePeriod.GetStartDate().DateToString(), "Self-assignment move start");
    assert_equal(PeriodTestData::VALID_END_DATE, selfMovePeriod.GetEndDate().DateToString(), "Self-assignment move end");
    
    std::cout << "✓ Constructors and operators tests passed\n\n";
}

// ===== ERROR HANDLING TESTS =====
void test_error_handling() {
    std::cout << "Testing error handling...\n";
    
    // Clear and check error functions
    MyPeriod::ClearError();
    assert_equal("", MyPeriod::GetLastError().c_str(), "ClearError and GetLastError");
    
    // Test constructor exception
    try {
        MyDate invalidStart(PeriodTestData::INVALID_START_DATE);
        MyDate invalidEnd(PeriodTestData::INVALID_END_DATE);
        MyPeriod invalidPeriod(invalidStart, invalidEnd);
        assert_true(false, "Should throw exception for invalid constructor");
    } catch (const std::invalid_argument&) {
        assert_equal("Invalid period: Start date cannot be after end date", 
                   MyPeriod::GetLastError().c_str(), "Constructor exception");
    }
    
    std::cout << "✓ Error handling tests passed\n\n";
}

// ===== VALIDATION TESTS =====
void test_validation() {
    std::cout << "Testing MyPeriod validation...\n";
    
    // Test valid period
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod validPeriod(start, end);
    assert(validPeriod.IsValid() == true);
    
    // Test invalid period (end before start)
    MyDate invalidStart("31/12/2023");
    MyDate invalidEnd("01/01/2023");
    MyPeriod invalidPeriod(invalidStart, invalidEnd);
    assert(invalidPeriod.IsValid() == false);
    
    std::cout << "✓ MyPeriod validation tests passed\n\n";
}

// ===== OVERLAP FUNCTIONS TESTS =====
void test_overlap_functions() {
    std::cout << "Testing MyPeriod overlap functions...\n";
    
    MyDate start1("01/01/2023");
    MyDate end1("31/12/2023");
    MyPeriod period1(start1, end1);
    
    // Test static IsOverlapPeriods
    MyDate start2("15/06/2023");
    MyDate end2("15/12/2024");
    MyPeriod period2(start2, end2);
    
    assert(MyPeriod::IsOverlapPeriods(period1, period2) == true);
    std::cout << "✓ IsOverlapPeriods (static) test passed\n";
    
    // Test instance IsOverLapWith
    assert(period1.IsOverLapWith(period2) == true);
    std::cout << "✓ IsOverLapWith (instance) test passed\n";
    
    // Test IsOverlap alias
    assert(period1.IsOverlap(period2) == true);
    std::cout << "✓ IsOverlap (alias) test passed\n";
    
    // Test non-overlapping periods
    MyDate start3("01/01/2024");
    MyDate end3("31/12/2024");
    MyPeriod period3(start3, end3);
    
    assert(MyPeriod::IsOverlapPeriods(period1, period3) == false);
    assert(period1.IsOverLapWith(period3) == false);
    assert(period1.IsOverlap(period3) == false);
    std::cout << "✓ Non-overlapping periods test passed\n";
    
    std::cout << "✓ MyPeriod overlap functions tests passed\n\n";
}

// ===== DURATION FUNCTIONS TESTS =====
void test_duration_functions() {
    std::cout << "Testing MyPeriod duration functions...\n";
    
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod period(start, end);
    
    // Test GetDurationInDays
    int duration = period.GetDurationInDays();
    assert(duration == 364); // 2023 is not a leap year
    std::cout << "✓ GetDurationInDays test passed\n";
    
    // Test LengthInDays (alias)
    int lengthDays = period.LengthInDays();
    assert(lengthDays == 364);
    std::cout << "✓ LengthInDays test passed\n";
    
    // Test LengthInMonths
    int months = period.LengthInMonths();
    assert(months == 11); // Jan to Dec is 11 full months
    std::cout << "✓ LengthInMonths test passed\n";
    
    // Test LengthInYears
    int years = period.LengthInYears();
    assert(years == 0); // Less than 1 full year
    std::cout << "✓ LengthInYears test passed\n";
    
    // Test multi-year period
    MyDate multiYearStart("01/01/2020");
    MyDate multiYearEnd("31/12/2023");
    MyPeriod multiYearPeriod(multiYearStart, multiYearEnd);
    
    int multiYearDays = multiYearPeriod.LengthInDays();
    int multiYearMonths = multiYearPeriod.LengthInMonths();
    int multiYears = multiYearPeriod.LengthInYears();
    
    assert(multiYearDays > 1000); // Should be more than 1000 days
    assert(multiYearMonths == 47); // 2020-2023 is 47 full months
    assert(multiYears == 3); // Almost 4 full years
    std::cout << "✓ Multi-year period test passed\n";
    
    std::cout << "✓ MyPeriod duration functions tests passed\n\n";
}

// ===== CONTAINS TESTS =====
void test_contains() {
    std::cout << "Testing MyPeriod contains...\n";
    
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod period(start, end);
    
    // Test date within period
    MyDate within("15/06/2023");
    assert(period.Contains(within) == true);
    
    // Test date before period
    MyDate before("01/01/2022");
    assert(period.Contains(before) == false);
    
    // Test date after period
    MyDate after("01/01/2024");
    assert(period.Contains(after) == false);
    
    // Test boundary dates
    assert(period.Contains(start) == true);
    assert(period.Contains(end) == true);
    
    std::cout << "✓ MyPeriod contains tests passed\n\n";
}

// ===== CONTAINS EDGE CASES TESTS =====
void test_contains_edge_cases() {
    std::cout << "Testing MyPeriod Contains edge cases...\n";
    
    // Test same-day period
    MyDate sameDay("15/06/2023");
    MyPeriod sameDayPeriod(sameDay, sameDay);
    
    assert(sameDayPeriod.Contains(sameDay) == true);
    std::cout << "✓ Same-day period contains test passed\n";
    
    // Test dates one day outside boundaries
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod period(start, end);
    
    MyDate beforeStart("31/12/2022");
    MyDate afterEnd("01/01/2024");
    
    assert(period.Contains(beforeStart) == false);
    assert(period.Contains(afterEnd) == false);
    std::cout << "✓ Outside boundaries test passed\n";
    
    // Test with leap year
    MyDate leapStart("01/01/2020");
    MyDate leapEnd("31/12/2020");
    MyPeriod leapPeriod(leapStart, leapEnd);
    
    MyDate feb29("29/02/2020");
    assert(leapPeriod.Contains(feb29) == true);
    std::cout << "✓ Leap year date test passed\n";
    
    // Test period spanning multiple years
    MyDate multiYearStart("15/06/2022");
    MyDate multiYearEnd("15/06/2024");
    MyPeriod multiYearPeriod(multiYearStart, multiYearEnd);
    
    MyDate inMiddle("01/01/2023");
    assert(multiYearPeriod.Contains(inMiddle) == true);
    std::cout << "✓ Multi-year period test passed\n";
    
    // Test with very small period (1 day)
    MyDate dayStart("01/01/2023");
    MyDate dayEnd("01/01/2023");
    MyPeriod dayPeriod(dayStart, dayEnd);
    
    assert(dayPeriod.Contains(dayStart) == true);
    MyDate nextDay("02/01/2023");
    assert(dayPeriod.Contains(nextDay) == false);
    std::cout << "✓ One-day period test passed\n";
    
    std::cout << "✓ MyPeriod Contains edge cases tests passed\n\n";
}

// ===== OVERLAP TESTS =====
void test_overlap() {
    std::cout << "Testing MyPeriod overlap...\n";
    
    MyDate start1("01/01/2023");
    MyDate end1("31/12/2023");
    MyPeriod period1(start1, end1);
    
    // Test overlapping period
    MyDate start2("15/06/2023");
    MyDate end2("15/12/2024");
    MyPeriod overlappingPeriod(start2, end2);
    assert(period1.IsOverlap(overlappingPeriod) == true);
    
    // Test non-overlapping period
    MyDate start3("01/01/2024");
    MyDate end3("31/12/2024");
    MyPeriod nonOverlappingPeriod(start3, end3);
    assert(period1.IsOverlap(nonOverlappingPeriod) == false);
    
    std::cout << "✓ MyPeriod overlap tests passed\n\n";
}

// ===== OVERLAP EDGE CASES TESTS =====
void test_overlap_edge_cases() {
    std::cout << "Testing MyPeriod overlap edge cases...\n";
    
    // Test identical periods
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod period1(start, end);
    MyPeriod period2(start, end);
    
    assert(period1.IsOverlap(period2) == true);
    std::cout << "✓ Identical periods overlap test passed\n";
    
    // Test periods touching at boundaries (end == start)
    MyDate start1("01/01/2023");
    MyDate end1("31/12/2023");
    MyPeriod period1_boundary(start1, end1);
    
    MyDate start2("31/12/2023");  // Same as end of period1
    MyDate end2("31/12/2024");
    MyPeriod period2_boundary(start2, end2);
    
    assert(period1_boundary.IsOverlap(period2_boundary) == true);
    std::cout << "✓ Boundary touching overlap test passed\n";
    
    // Test periods touching at boundaries (start == end)
    MyDate start3("01/01/2022");
    MyDate end3("01/01/2023");  // Same as start of period1
    MyPeriod period3_boundary(start3, end3);
    
    assert(period3_boundary.IsOverlap(period1) == true);
    std::cout << "✓ Reverse boundary touching overlap test passed\n";
    
    // Test one period completely contained within another
    MyDate outerStart("01/01/2022");
    MyDate outerEnd("31/12/2024");
    MyPeriod outerPeriod(outerStart, outerEnd);
    
    MyDate innerStart("15/06/2023");
    MyDate innerEnd("15/12/2023");
    MyPeriod innerPeriod(innerStart, innerEnd);
    
    assert(outerPeriod.IsOverlap(innerPeriod) == true);
    assert(innerPeriod.IsOverlap(outerPeriod) == true);
    std::cout << "✓ Contained period overlap test passed\n";
    
    // Test same-day periods overlapping
    MyDate sameDay("15/06/2023");
    MyPeriod sameDay1(sameDay, sameDay);
    MyPeriod sameDay2(sameDay, sameDay);
    
    assert(sameDay1.IsOverlap(sameDay2) == true);
    std::cout << "✓ Same-day periods overlap test passed\n";
    
    // Test non-overlapping with gap
    MyDate gapStart1("01/01/2023");
    MyDate gapEnd1("31/12/2023");
    MyPeriod gapPeriod1(gapStart1, gapEnd1);
    
    MyDate gapStart2("15/06/2024");  // Clear gap between periods
    MyDate gapEnd2("15/12/2024");
    MyPeriod gapPeriod2(gapStart2, gapEnd2);
    
    assert(gapPeriod1.IsOverlap(gapPeriod2) == false);
    std::cout << "✓ Non-overlapping with gap test passed\n";
    
    // Test overlapping by one day
    MyDate oneDayStart1("01/01/2023");
    MyDate oneDayEnd1("15/06/2023");
    MyPeriod oneDayPeriod1(oneDayStart1, oneDayEnd1);
    
    MyDate oneDayStart2("15/06/2023");  // Same day as end of first
    MyDate oneDayEnd2("31/12/2023");
    MyPeriod oneDayPeriod2(oneDayStart2, oneDayEnd2);
    
    assert(oneDayPeriod1.IsOverlap(oneDayPeriod2) == true);
    std::cout << "✓ One-day overlap test passed\n";
    
    std::cout << "✓ MyPeriod overlap edge cases tests passed\n\n";
}

// ===== UTILITIES TESTS =====
void test_utilities() {
    std::cout << "Testing MyPeriod utilities...\n";
    
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod period(start, end);
    
    // Test is same day
    MyDate sameDay("01/01/2023");
    MyDate differentDay("02/01/2023");
    assert(period.IsSameDay(sameDay) == true);
    assert(period.IsSameDay(differentDay) == false);
    
    // Test to string
    std::string periodStr = period.ToString();
    assert(periodStr.find("01/01/2023") != std::string::npos);
    assert(periodStr.find("31/12/2023") != std::string::npos);
    
    std::cout << "✓ MyPeriod utility tests passed\n\n";
}

// ===== PRINT UTILITIES TESTS =====
void test_print_utilities() {
    std::cout << "Testing MyPeriod print and utilities...\n";
    
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod period(start, end);
    
    // Test Print method (visual verification)
    std::cout << "Testing Print method output:\n";
    period.Print();
    std::cout << "✓ Print method test passed\n";
    
    // Test ToString method
    std::string periodStr = period.ToString();
    assert(periodStr.find("Period: 01/01/2023 to 31/12/2023") != std::string::npos);
    std::cout << "✓ ToString test passed\n";
    
    // Test IsSameDay method
    MyDate sameDay("01/01/2023");
    MyDate differentDay("02/01/2023");
    assert(period.IsSameDay(sameDay) == false); // Period spans multiple days, not same-day period
    assert(period.IsSameDay(differentDay) == false);
    std::cout << "✓ IsSameDay test passed\n";
    
    // Test IsSameDay with same-day period
    MyDate sameStart("15/06/2023");
    MyDate sameEnd("15/06/2023");
    MyPeriod sameDayPeriod(sameStart, sameEnd);
    assert(sameDayPeriod.IsSameDay(sameStart) == true);
    std::cout << "✓ IsSameDay (same-day period) test passed\n";
    
    std::cout << "✓ MyPeriod print and utilities tests passed\n\n";
}

// ===== EXTREME CASES TESTS =====
void test_extreme_cases() {
    std::cout << "Testing MyPeriod extreme cases...\n";
    
    // Test very old dates
    MyDate oldStart("01/01/1900");
    MyDate oldEnd("31/12/1900");
    MyPeriod oldPeriod(oldStart, oldEnd);
    
    assert(oldPeriod.IsValid() == true);
    assert(oldPeriod.LengthInDays() == 364); // 1900 is not a leap year
    std::cout << "✓ Very old dates test passed\n";
    
    // Test future dates
    MyDate futureStart("01/01/2100");
    MyDate futureEnd("31/12/2100");
    MyPeriod futurePeriod(futureStart, futureEnd);
    
    assert(futurePeriod.IsValid() == true);
    assert(futurePeriod.LengthInYears() == 0); // Less than 1 full year
    std::cout << "✓ Future dates test passed\n";
    
    // Test very long period (century)
    MyDate centuryStart("01/01/2000");
    MyDate centuryEnd("31/12/2099");
    MyPeriod centuryPeriod(centuryStart, centuryEnd);
    
    assert(centuryPeriod.IsValid() == true);
    assert(centuryPeriod.LengthInYears() == 99); // Almost 100 years
    assert(centuryPeriod.LengthInMonths() == 1199); // 100 years * 12 - 1 month
    std::cout << "✓ Century period test passed\n";
    
    // Test period spanning year 2000 (leap year)
    MyDate y2kStart("01/01/1999");
    MyDate y2kEnd("31/12/2000");
    MyPeriod y2kPeriod(y2kStart, y2kEnd);
    
    assert(y2kPeriod.IsValid() == true);
    assert(y2kPeriod.LengthInDays() > 700); // Should be more than 700 days
    std::cout << "✓ Y2K period test passed\n";
    
    // Test same-day period with different date
    MyDate testDate("25/12/2023");
    MyPeriod christmasPeriod(testDate, testDate);
    
    assert(christmasPeriod.Contains(testDate) == true);
    assert(christmasPeriod.IsSameDay(testDate) == true);
    assert(christmasPeriod.LengthInDays() == 0);
    std::cout << "✓ Same-day period edge case test passed\n";
    
    std::cout << "✓ MyPeriod extreme cases tests passed\n\n";
}

int main() {
    std::cout << "=== MyPeriod Unit Tests ===\n\n";
    
    test_constructors();
    test_getters_setters();
    test_constructors_and_operators();
    test_error_handling();
    test_validation();
    test_overlap_functions();
    test_duration_functions();
    test_contains();
    test_contains_edge_cases();
    test_overlap();
    test_overlap_edge_cases();
    test_utilities();
    test_print_utilities();
    test_extreme_cases();
    
    std::cout << "🎉 All MyPeriod tests passed successfully!\n";
    return 0;
}
