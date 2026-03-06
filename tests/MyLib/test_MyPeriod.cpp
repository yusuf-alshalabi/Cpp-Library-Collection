#include <iostream>
#include <cassert>
#include "../../include/MyLib/MyDate.h"
#include "../../include/MyLib/MyPeriod.h"

using namespace MyLib;

void test_myperiod_constructors() {
    std::cout << "Testing MyPeriod constructors...\n";
    
    // Test constructor with dates
    MyDate startDate("01/01/2023");
    MyDate endDate("31/12/2023");
    MyPeriod period(startDate, endDate);
    
    assert(period.GetStartDate().ToString() == "01/01/2023");
    assert(period.GetEndDate().ToString() == "31/12/2023");
    
    std::cout << "✓ MyPeriod constructor tests passed\n\n";
}

void test_myperiod_getters_setters() {
    std::cout << "Testing MyPeriod getters and setters...\n";
    
    // Test getters
    MyDate startDate("01/01/2023");
    MyDate endDate("31/12/2023");
    MyPeriod period(startDate, endDate);
    
    assert(period.GetStartDate().ToString() == "01/01/2023");
    assert(period.GetEndDate().ToString() == "31/12/2023");
    std::cout << "✓ Getters test passed\n";
    
    // Test setters
    MyDate newStart("15/06/2023");
    MyDate newEnd("15/12/2023");
    
    period.SetStartDate(newStart);
    period.SetEndDate(newEnd);
    
    assert(period.GetStartDate().ToString() == "15/06/2023");
    assert(period.GetEndDate().ToString() == "15/12/2023");
    std::cout << "✓ Setters test passed\n";
    
    std::cout << "✓ MyPeriod getters and setters tests passed\n\n";
}

void test_myperiod_constructors_operators() {
    std::cout << "Testing MyPeriod constructors and operators...\n";
    
    // Test move constructor
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod original(start, end);
    
    MyPeriod moved(std::move(original));
    assert(moved.GetStartDate().ToString() == "01/01/2023");
    assert(moved.GetEndDate().ToString() == "31/12/2023");
    std::cout << "✓ Move constructor test passed\n";
    
    // Test move assignment operator
    MyDate start2("15/06/2023");
    MyDate end2("15/12/2023");
    MyPeriod original2(start2, end2);
    
    MyPeriod assigned;
    assigned = std::move(original2);
    assert(assigned.GetStartDate().ToString() == "15/06/2023");
    assert(assigned.GetEndDate().ToString() == "15/12/2023");
    std::cout << "✓ Move assignment operator test passed\n";
    
    std::cout << "✓ MyPeriod constructors and operators tests passed\n\n";
}

void test_myperiod_error_handling() {
    std::cout << "Testing MyPeriod error handling...\n";
    
    // Clear any previous errors
    MyPeriod::ClearError();
    assert(MyPeriod::GetLastError() == "");
    std::cout << "✓ ClearError and GetLastError test passed\n";
    
    // Test constructor exception
    try {
        MyDate invalidStart("31/12/2023");
        MyDate invalidEnd("01/01/2023");
        MyPeriod invalidPeriod(invalidStart, invalidEnd);
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        assert(MyPeriod::GetLastError() == "Invalid period: Start date cannot be after end date");
        std::cout << "✓ Constructor exception test passed\n";
    }
    
    std::cout << "✓ MyPeriod error handling tests passed\n\n";
}

void test_myperiod_validation() {
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

void test_myperiod_overlap_functions() {
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
    
    // Test non-overlapping periods
    MyDate start3("01/01/2024");
    MyDate end3("31/12/2024");
    MyPeriod period3(start3, end3);
    
    assert(MyPeriod::IsOverlapPeriods(period1, period3) == false);
    assert(period1.IsOverLapWith(period3) == false);
    std::cout << "✓ Non-overlapping periods test passed\n";
    
    std::cout << "✓ MyPeriod overlap functions tests passed\n\n";
}

void test_myperiod_duration_functions() {
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
    
    std::cout << "✓ MyPeriod duration functions tests passed\n\n";
}

void test_myperiod_duration() {
    std::cout << "Testing MyPeriod duration...\n";
    
    MyDate start("01/01/2023");
    MyDate end("31/12/2023");
    MyPeriod period(start, end);
    
    // Test length in days
    int length = period.LengthInDays();
    assert(length == 364); // 2023 is not a leap year
    
    // Test length in months
    int months = period.LengthInMonths();
    assert(months == 11); // Jan to Dec is 11 full months
    
    // Test length in years
    int years = period.LengthInYears();
    assert(years == 0); // Less than 1 full year
    
    std::cout << "✓ MyPeriod duration tests passed\n\n";
}

void test_myperiod_contains() {
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

void test_myperiod_overlap() {
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

void test_myperiod_utilities() {
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

int main() {
    std::cout << "=== MyPeriod Unit Tests ===\n\n";
    
    test_myperiod_constructors();
    test_myperiod_validation();
    test_myperiod_duration();
    test_myperiod_contains();
    test_myperiod_overlap();
    test_myperiod_utilities();
    
    std::cout << "🎉 All MyPeriod tests passed successfully!\n";
    return 0;
}
