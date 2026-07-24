
#pragma once
#include <iostream>

#include "../Lib/String.h"
#include "../Lib/Date.h"
#include "../Lib/Period.h"
#include "../Lib/Util.h"
#include "../Lib/InputValidate.h"


using namespace Core;

class TestRunner {
public:
    static void TestString()
    {
        std::cout << "========================================\n";
        std::cout << "      Testing Core::String Class        \n";
        std::cout << "========================================\n\n";

        // 1. Constructors & Assignment Operators
        std::cout << "--- 1. Testing Constructors & Operators ---\n";
        String s1("Hello World");
        String s2 = ", C++ 2026!";
        String s3 = s1 + s2;

        std::cout << "s1: " << s1 << "\n";
        std::cout << "s2: " << s2 << "\n";
        std::cout << "s3 (s1 + s2): " << s3 << "\n";

        s1 += " Programming";
        std::cout << "s1 after += : " << s1 << "\n";
        std::cout << "s1[0]: " << s1[0] << ", s1.At(4): " << s1.At(4) << "\n";
        std::cout << "Is s1 == s2? " << (s1 == s2 ? "YES" : "NO") << "\n\n";

        // 2. Case Conversion & Formatting
        std::cout << "--- 2. Testing Case Conversions ---\n";
        String titleText("WeLcOmE To C++ PrOgRaMmInG");
        std::cout << "Original Text: " << titleText << "\n";

        titleText.InvertAllLettersCase();
        std::cout << "Inverted Case: " << titleText << "\n";

        titleText.UpperFirstLetterOfEachWord();
        std::cout << "Title Case:    " << titleText << "\n";

        titleText.UpperAllString();
        std::cout << "Upper All:     " << titleText << "\n";

        titleText.LowerAllString();
        std::cout << "Lower All:     " << titleText << "\n\n";

        // 3. Trim, Modifications & In-place Mutations
        std::cout << "--- 3. Testing Trimming & Transformations ---\n";
        String padded("   --- Hello C++ World! ---   ");
        std::cout << "Padded String: [" << padded << "]\n";

        padded.Trim();
        std::cout << "Trimmed String: [" << padded << "]\n";

        padded.RemovePunctuations();
        std::cout << "Punctuation Removed: [" << padded << "]\n";

        padded.ReplaceWord("Hello", "Welcome");
        std::cout << "Word Replaced: " << padded << "\n";

        padded.ReverseWordsInString();
        std::cout << "Reversed Words: " << padded << "\n\n";

        // 4. Searching, Inspections & Substrings
        std::cout << "--- 4. Testing Inspections & Searching ---\n";
        String sample("cpp-library-collection.cpp");
        std::cout << "Sample String: " << sample << "\n";
        std::cout << "Length: " << sample.Length() << "\n";
        std::cout << "Count Words: " << sample.CountWords() << "\n";
        std::cout << "Contains 'library'? " << (sample.Contains("library") ? "YES" : "NO") << "\n";
        std::cout << "StartsWith 'cpp'? " << (sample.StartsWith("cpp") ? "YES" : "NO") << "\n";
        std::cout << "EndsWith '.cpp'? " << (sample.EndsWith(".cpp") ? "YES" : "NO") << "\n";
        std::cout << "First Index of 'p': " << sample.IndexOf('p') << "\n";
        std::cout << "Last Index of 'p': " << sample.LastIndexOf('p') << "\n";
        std::cout << "TakeFirst(3): " << sample.TakeFirst(3) << "\n";
        std::cout << "TakeLast(4): " << sample.TakeLast(4) << "\n";
        std::cout << "Substring(4, 7): " << sample.Substring(4, 7) << "\n\n";

        // 5. Character Counting & Categorization
        std::cout << "--- 5. Testing Character Counting ---\n";
        String metrics("User_Name123 @2026!");
        std::cout << "Metrics Text: " << metrics << "\n";
        std::cout << "Capital Letters: " << metrics.CountCapitalLetters() << "\n";
        std::cout << "Small Letters  : " << metrics.CountSmallLetters() << "\n";
        std::cout << "Digits         : " << metrics.CountDigits() << "\n";
        std::cout << "Spaces         : " << metrics.CountSpaces() << "\n";
        std::cout << "Punctuations   : " << metrics.CountPunctuations() << "\n";
        std::cout << "Vowels         : " << metrics.CountVowels() << "\n";
        std::cout << "Specific Letter 'e' (Case Insensitive): "
            << metrics.CountSpecificLetter('e', false) << "\n\n";

        // 6. Splitting, Joining & Palindrome
        std::cout << "--- 6. Testing Split, Join & Palindrome ---\n";
        String csvData("Apple,Banana,Cherry,Date");
        std::cout << "CSV String: " << csvData << "\n";

        std::vector<std::string> fruits = csvData.Split(",");
        std::cout << "Splitted Vector (" << fruits.size() << " items):\n";
        for (const auto& fruit : fruits)
        {
            std::cout << " - " << fruit << "\n";
        }

        std::string joined = String::JoinString(fruits, " | ");
        std::cout << "Joined Back: " << joined << "\n";

        String pal1("A man, a plan, a canal: Panama");
        String pal2("Hello World");
        std::cout << "Is [" << pal1 << "] Palindrome? " << (pal1.IsPalindrome() ? "YES" : "NO") << "\n";
        std::cout << "Is [" << pal2 << "] Palindrome? " << (pal2.IsPalindrome() ? "YES" : "NO") << "\n\n";

        std::cout << "========================================\n";
        std::cout << "      All Tests Completed Successfully! \n";
        std::cout << "========================================\n";
    }

    static void TestDate()
    {
        std::cout << "========================================\n";
        std::cout << "        Testing Core::Date Class        \n";
        std::cout << "========================================\n\n";

        // 1. Constructors & Getters/Setters
        std::cout << "--- 1. Constructors & Properties ---\n";
        Core::Date dSystem; // Default Constructor (System Date)
        Core::Date dCustom(22, 7, 2026); // Day, Month, Year
        Core::Date dString("15/08/2024"); // From String
        Core::Date dDayOrder(200, 2024); // Day order in leap year

        std::cout << "System Date: " << dSystem << "\n";
        std::cout << "Custom Date (22/07/2026): " << dCustom << "\n";
        std::cout << "Parsed String Date (15/08/2024): " << dString << "\n";
        std::cout << "Date from Day Order 200/2024: " << dDayOrder << "\n";

        // Testing Property/Getters/Setters
        dCustom.SetDay(10);
        dCustom.SetMonth(12);
        dCustom.SetYear(2025);
        std::cout << "Modified via Properties: " << dCustom.GetDay() << "/"
            << dCustom.GetMonth() << "/" << dCustom.GetYear() << "\n\n";

        // 2. Comparisons & Operators
        std::cout << "--- 2. Comparisons & Relational Operators ---\n";
        Core::Date d1(1, 1, 2025);
        Core::Date d2(1, 1, 2025);
        Core::Date d3(15, 6, 2026);

        std::cout << "d1: " << d1 << " | d2: " << d2 << " | d3: " << d3 << "\n";
        std::cout << "d1 == d2? " << (d1 == d2 ? "YES" : "NO") << "\n";
        std::cout << "d1 != d3? " << (d1 != d3 ? "YES" : "NO") << "\n";
        std::cout << "d1 < d3?  " << (d1 < d3 ? "YES" : "NO") << "\n";
        std::cout << "d3 > d1?  " << (d3 > d1 ? "YES" : "NO") << "\n";
        std::cout << "d1 <= d2? " << (d1 <= d2 ? "YES" : "NO") << "\n";
        std::cout << "d3 >= d1? " << (d3 >= d1 ? "YES" : "NO") << "\n\n";

        // 3. Date Arithmetic & Overloaded Operators
        std::cout << "--- 3. Date Arithmetic (+, -, ++, --, +=, -=) ---\n";
        Core::Date dBase(28, 2, 2024); // Leap year
        std::cout << "Base Date: " << dBase << "\n";

        Core::Date dPlus10 = dBase + 10;
        std::cout << "dBase + 10 days: " << dPlus10 << "\n";

        Core::Date dMinus5 = dBase - 5;
        std::cout << "dBase - 5 days: " << dMinus5 << "\n";

        dBase += 2;
        std::cout << "dBase after += 2: " << dBase << "\n";

        dBase -= 2;
        std::cout << "dBase after -= 2: " << dBase << "\n";

        std::cout << "Prefix ++dBase: " << ++dBase << "\n";
        std::cout << "Postfix dBase++: " << dBase++ << "\n";
        std::cout << "After Postfix ++: " << dBase << "\n";
        std::cout << "Prefix --dBase: " << --dBase << "\n";
        std::cout << "Postfix dBase--: " << dBase-- << "\n";
        std::cout << "After Postfix --: " << dBase << "\n";

        int diff = Core::Date(10, 3, 2026) - Core::Date(1, 3, 2026);
        std::cout << "Difference (10/03/2026 - 01/03/2026): " << diff << " days\n\n";

        // 4. Formatting & String Conversion
        std::cout << "--- 4. String Conversions & Custom Formats ---\n";
        Core::Date dFmt(5, 4, 2026);
        std::cout << "Default (DD/MM/YYYY) : " << dFmt.ToString() << "\n";
        std::cout << "Custom (YYYY-MM-DD)  : " << dFmt.ToString("YYYY-MM-DD") << "\n";
        std::cout << "Full Month (D MMMM YY): " << dFmt.ToString("D MMMM YY") << "\n";
        std::cout << "Short Month (DD/MMM/YYYY): " << dFmt.ToString("DD/MMM/YYYY") << "\n\n";

        // 5. Leap Year & Time Unit Calculations
        std::cout << "--- 5. Leap Year & Time Metrics ---\n";
        short yearLeap = 2024, yearNormal = 2025;
        std::cout << yearLeap << " Is Leap Year? " << (Core::Date::IsLeapYear(yearLeap) ? "YES" : "NO") << "\n";
        std::cout << yearNormal << " Is Leap Year? " << (Core::Date::IsLeapYear(yearNormal) ? "YES" : "NO") << "\n";
        std::cout << "Days in 2024: " << Core::Date::NumberOfDaysInAYear(2024) << "\n";
        std::cout << "Hours in Feb 2024 (Leap): " << Core::Date::NumberOfHoursInAMonth(2, 2024) << "\n";
        std::cout << "Minutes in 2025: " << Core::Date::NumberOfMinutesInAYear(2025) << "\n";
        std::cout << "Seconds in Jan 2025: " << Core::Date::NumberOfSecondsInAMonth(1, 2025) << "\n\n";

        // 6. Day & Month Metadata
        std::cout << "--- 6. Day & Month Metadata ---\n";
        Core::Date dMeta(22, 7, 2026);
        std::cout << "Date: " << dMeta << "\n";
        std::cout << "Day of Week Order (0=Sun): " << dMeta.DayOfWeekOrder() << "\n";
        std::cout << "Day Short Name: " << dMeta.DayShortName() << "\n";
        std::cout << "Day Full Name: " << dMeta.DayName() << "\n";
        std::cout << "Month Short Name: " << dMeta.MonthShortName() << "\n";
        std::cout << "Month Full Name: " << dMeta.MonthName() << "\n";
        std::cout << "Day Order in Year: " << dMeta.DaysFromTheBeginingOfTheYear() << "\n";
        std::cout << "Is Last Day in Month? " << (dMeta.IsLastDayInMonth() ? "YES" : "NO") << "\n\n";

        // 7. Increasing & Decreasing Date Helpers
        std::cout << "--- 7. Increasing & Decreasing Helpers ---\n";
        Core::Date dShift(1, 1, 2026);
        std::cout << "Start Date: " << dShift << "\n";

        dShift.IncreaseDateByOneWeek();
        std::cout << "After +1 Week: " << dShift << "\n";

        dShift.IncreaseDateByXMonths(5);
        std::cout << "After +5 Months: " << dShift << "\n";

        dShift.IncreaseDateByOneYear();
        std::cout << "After +1 Year: " << dShift << "\n";

        dShift.IncreaseDateByOneDecade();
        std::cout << "After +1 Decade: " << dShift << "\n";

        dShift.DecreaseDateByOneCentury();
        std::cout << "After -1 Century: " << dShift << "\n\n";

        // 8. Business Days, Weekends & Vacations
        std::cout << "--- 8. Business Days & Vacation Logic ---\n";
        Core::Date dFri(24, 7, 2026); // Friday
        std::cout << "Date (24/07/2026 - Friday): " << dFri << "\n";
        std::cout << "Is End of Week (Sat)? " << (dFri.IsEndOfWeek() ? "YES" : "NO") << "\n";
        std::cout << "Is Weekend (Fri/Sat)? " << (dFri.IsWeekEnd() ? "YES" : "NO") << "\n";
        std::cout << "Is Business Day? " << (dFri.IsBusinessDay() ? "YES" : "NO") << "\n";

        Core::Date vStart(1, 8, 2026);
        Core::Date vEnd(15, 8, 2026);
        std::cout << "Business Days between " << vStart << " and " << vEnd << ": "
            << Core::Date::CalculateBusinessDays(vStart, vEnd) << " days\n";

        Core::Date returnDate = Core::Date::CalculateVacationReturnDate(vStart, 7);
        std::cout << "Return Date for 7 Business Days Vacation starting " << vStart << ": " << returnDate << "\n\n";

        // 9. Swap, Countdown & Validation
        std::cout << "--- 9. Swap, Countdown & Validation ---\n";
        Core::Date dSwap1(1, 1, 2020), dSwap2(31, 12, 2030);
        std::cout << "Before Swap -> d1: " << dSwap1 << ", d2: " << dSwap2 << "\n";
        Core::Date::SwapDates(dSwap1, dSwap2);
        std::cout << "After Swap  -> d1: " << dSwap1 << ", d2: " << dSwap2 << "\n";

        Core::Date dMidYear(1, 7, 2026);
        std::cout << "Days until end of month from " << dMidYear << ": " << dMidYear.DaysUntilTheEndOfMonth() << "\n";
        std::cout << "Days until end of year from " << dMidYear << ": " << dMidYear.DaysUntilTheEndOfYear() << "\n";

        try
        {
            Core::Date dInvalidTest(31, 2, 2026);
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Successfully caught invalid date exception: " << e.what() << "\n\n";
        }

        // 10. Calendars Output
        std::cout << "--- 10. Calendar Printing ---\n";
        std::cout << "Month Calendar Test (July 2026):";
        Core::Date(1, 7, 2026).PrintMonthCalendar();

        std::cout << "\n========================================\n";
        std::cout << "       Date Tests Completed!            \n";
        std::cout << "========================================\n";
    }

    static void TestPeriod()
    {
        std::cout << "========================================\n";
        std::cout << "       Testing Core::Period Class       \n";
        std::cout << "========================================\n\n";

        // 1. Constructors & Auto-Normalization
        std::cout << "--- 1. Testing Constructors & Auto-Normalization ---\n";
        Date dStart(1, 1, 2026);
        Date dEnd(10, 1, 2026);

        Period pNormal(dStart, dEnd);
        std::cout << "Normal Period (01/01/2026 -> 10/01/2026):\n";
        pNormal.Print();

        Period pSwapped(dEnd, dStart); // Swapped dates to test Normalize()
        std::cout << "Swapped Period Input (10/01/2026 -> 01/01/2026) Auto-Normalized:\n";
        pSwapped.Print();
        std::cout << "\n";

        // 2. Properties & Encapsulation
        std::cout << "--- 2. Testing Properties & Safe Setters ---\n";
        Period pProp;
        pProp.StartDate = Date(15, 5, 2026);
        pProp.EndDate = Date(5, 5, 2026); // Should trigger Normalize via property setter

        std::cout << "Period set via Properties (Start: 15/05/2026, End: 05/05/2026):\n";
        std::cout << "Actual StartDate Property: " << pProp.StartDate << "\n";
        std::cout << "Actual EndDate Property  : " << pProp.EndDate << "\n\n";

        // 3. Length & Business Days Calculations
        std::cout << "--- 3. Testing Length & Business Days Calculations ---\n";
        Period pCalc(Date(1, 1, 2026), Date(10, 1, 2026));
        std::cout << "Period: " << pCalc.StartDate << " -> " << pCalc.EndDate << "\n";
        std::cout << "Length (Including End Day): " << pCalc.PeriodLengthInDays(true) << " days\n";
        std::cout << "Length (Excluding End Day): " << pCalc.PeriodLengthInDays(false) << " days\n";
        std::cout << "Calculated Business Days  : " << pCalc.CalculateBusinessDays() << " days\n\n";

        // 4. Date Belonging Inspection (IsDateInPeriod)
        std::cout << "--- 4. Testing Date Belonging (IsDateInPeriod) ---\n";
        Period pFeb(Date(1, 2, 2026), Date(28, 2, 2026));
        Date dInside(15, 2, 2026);
        Date dOutside(5, 3, 2026);

        std::cout << "Period: " << pFeb.StartDate << " -> " << pFeb.EndDate << "\n";
        std::cout << "Is " << dInside << " inside period? " << (pFeb.IsDateInPeriod(dInside) ? "YES" : "NO") << "\n";
        std::cout << "Is " << dOutside << " inside period? " << (pFeb.IsDateInPeriod(dOutside) ? "YES" : "NO") << "\n\n";

        // 5. Overlap Detection & Extraction
        std::cout << "--- 5. Testing Overlap Operations ---\n";
        Period p1(Date(1, 1, 2026), Date(20, 1, 2026));
        Period p2(Date(15, 1, 2026), Date(30, 1, 2026));
        Period p3(Date(25, 1, 2026), Date(31, 1, 2026));

        std::cout << "Period 1: " << p1.StartDate << " -> " << p1.EndDate << "\n";
        std::cout << "Period 2: " << p2.StartDate << " -> " << p2.EndDate << "\n";
        std::cout << "Period 3: " << p3.StartDate << " -> " << p3.EndDate << "\n\n";

        std::cout << "Does Period 1 overlap with Period 2? " << (p1.IsOverLapWith(p2) ? "YES" : "NO") << "\n";
        std::cout << "Does Period 1 overlap with Period 3? " << (p1.IsOverLapWith(p3) ? "YES" : "NO") << "\n";

        Period overlapResult;
        if (p1.GetOverlapPeriod(p2, overlapResult))
        {
            std::cout << "Extracted Overlap Period (P1 & P2):\n";
            std::cout << " -> Start: " << overlapResult.StartDate << " | End: " << overlapResult.EndDate << "\n";
        }
        std::cout << "Overlap Days between Period 1 and Period 2: " << p1.GetOverlapDays(p2) << " days\n\n";

        // 6. Period Containment Checks
        std::cout << "--- 6. Testing Period Containment (Contains) ---\n";
        Period mainPeriod(Date(1, 1, 2026), Date(31, 1, 2026));
        Period subPeriod(Date(10, 1, 2026), Date(20, 1, 2026));

        std::cout << "Main Period: " << mainPeriod.StartDate << " -> " << mainPeriod.EndDate << "\n";
        std::cout << "Sub Period : " << subPeriod.StartDate << " -> " << subPeriod.EndDate << "\n";
        std::cout << "Does Main Period contain Sub Period? " << (mainPeriod.Contains(subPeriod) ? "YES" : "NO") << "\n";
        std::cout << "Does Sub Period contain Main Period? " << (subPeriod.Contains(mainPeriod) ? "YES" : "NO") << "\n\n";

        // 7. Relational & Equality Operators
        std::cout << "--- 7. Testing Operators (==, !=, <<) ---\n";
        Period pEq1(Date(1, 1, 2026), Date(10, 1, 2026));
        Period pEq2(Date(1, 1, 2026), Date(10, 1, 2026));
        Period pEq3(Date(1, 1, 2026), Date(15, 1, 2026));

        std::cout << "Is pEq1 == pEq2? " << (pEq1 == pEq2 ? "YES" : "NO") << "\n";
        std::cout << "Is pEq1 != pEq3? " << (pEq1 != pEq3 ? "YES" : "NO") << "\n";
        std::cout << "Stream Output (<<) Test:\n" << pEq1 << "\n";

        std::cout << "========================================\n";
        std::cout << "      All Tests Completed Successfully! \n";
        std::cout << "========================================\n";
    }

    static void TestInputValidate()
    {
        std::cout << "========================================\n";
        std::cout << "   Testing Core::InputValidate Class    \n";
        std::cout << "========================================\n\n";

        // 1. Test IsNumberBetween
        std::cout << "--- 1. Testing IsNumberBetween ---\n";
        std::cout << "Is 15 between 10 and 20? " << (InputValidate::IsNumberBetween(15, 10, 20) ? "YES" : "NO") << "\n";
        std::cout << "Is 5.5 between 1.0 and 5.0? " << (InputValidate::IsNumberBetween(5.5, 1.0, 5.0) ? "YES" : "NO") << "\n\n";

        // 2. Test IsDateBetween & IsValidDate
        std::cout << "--- 2. Testing Date Validations ---\n";
        Date d1(10, 5, 2024);
        Date d2(1, 1, 2024);
        Date d3(31, 12, 2024);
        std::cout << "Is " << d1.ToString() << " valid? " << (InputValidate::IsValidDate(d1) ? "YES" : "NO") << "\n";
        std::cout << "Is " << d1.ToString() << " between " << d2.ToString() << " and " << d3.ToString() << "? "
            << (InputValidate::IsDateBetween(d1, d2, d3) ? "YES" : "NO") << "\n\n";

        // 3. Test ReadNumber
        std::cout << "--- 3. Testing ReadNumber ---\n";
        std::cout << ">> Try entering invalid input (e.g. 'abc') first, then a valid integer.\n";
        int intVal = InputValidate::ReadNumber<int>("Enter an integer:", "Invalid integer! Try again:");
        std::cout << "Result: " << intVal << "\n\n";

        std::cout << ">> Enter a double value:\n";
        double dblVal = InputValidate::ReadNumber<double>("Enter a double:", "Invalid double! Try again:");
        std::cout << "Result: " << dblVal << "\n\n";

        // 4. Test ReadPositiveNumber
        std::cout << "--- 4. Testing ReadPositiveNumber ---\n";
        std::cout << ">> Try entering 0 or a negative number first.\n";
        int posVal = InputValidate::ReadPositiveNumber<int>("Enter positive age:", "Age must be greater than 0!");
        std::cout << "Result: " << posVal << "\n\n";

        // 5. Test ReadNumberBetween
        std::cout << "--- 5. Testing ReadNumberBetween ---\n";
        std::cout << ">> Try entering a number outside [1 - 10] first.\n";
        int rangeVal = InputValidate::ReadNumberBetween<int>(1, 10, "Enter rating (1-10):", "Out of range! Must be 1 to 10.");
        std::cout << "Result: " << rangeVal << "\n\n";

        // 6. Test ReadCharacter
        std::cout << "--- 6. Testing ReadCharacter ---\n";
        char ch = InputValidate::ReadCharacter("Enter any character:");
        std::cout << "Result: " << ch << "\n\n";

        // 7. Test ReadString
        std::cout << "--- 7. Testing ReadString ---\n";
        std::cout << ">> Try hitting Enter directly to test empty input validation.\n";
        std::string str = InputValidate::ReadString("Enter your full name:", "Name cannot be empty!");
        std::cout << "Result: " << str << "\n\n";

        // 8. Test ReadYesNoOption
        std::cout << "--- 8. Testing ReadYesNoOption ---\n";
        bool choice = InputValidate::ReadYesNoOption("Do you want to save changes?");
        std::cout << "Result: " << (choice ? "User selected YES" : "User selected NO") << "\n\n";

        // 9. Test ReadDate
        std::cout << "--- 9. Testing ReadDate ---\n";
        std::cout << ">> Try entering an invalid date like '31/02/2026' or 'abc' first.\n";
        Date dateVal = InputValidate::ReadDate("Enter your birthdate (DD/MM/YYYY):", "Invalid date! Try again:");
        std::cout << "Result: " << dateVal.ToString() << "\n\n";

        std::cout << "========================================\n";
        std::cout << "      All Tests Completed Successfully! \n";
        std::cout << "========================================\n";
    }

    static void TestUtil()
    {
        // 1. Seed Random Generator
        Util::Srand();

        std::cout << "========================================\n";
        std::cout << "       Testing Core::Util Class         \n";
        std::cout << "========================================\n\n";

        // 2. Test RandomNumber (Template for Integrals) & RandomFloat
        std::cout << "--- 1. Testing Random Number & Float Generation ---\n";
        std::cout << "Random Int (1 to 100): " << Util::RandomNumber(1, 100) << "\n";
        std::cout << "Random Int (-50 to 50): " << Util::RandomNumber(-50, 50) << "\n";
        std::cout << "Random Short (Template): " << Util::RandomNumber<short>(10, 30) << "\n";
        std::cout << "Random Float (1.5 to 9.5): " << Util::RandomFloat(1.5f, 9.5f) << "\n";     
        std::cout << "Random Double (-10.5 to -1.2): " << Util::RandomFloat(-10.5, -1.2) << "\n\n"; 

        // 3. Test GetRandomCharacter
        std::cout << "--- 2. Testing GetRandomCharacter ---\n";
        std::cout << "Small Letter: " << Util::GetRandomCharacter(Util::SmallLetter) << "\n";
        std::cout << "Capital Letter: " << Util::GetRandomCharacter(Util::CapitalLetter) << "\n";
        std::cout << "Digit: " << Util::GetRandomCharacter(Util::Digit) << "\n";
        std::cout << "Special Character: " << Util::GetRandomCharacter(Util::SpecialCharacter) << "\n";
        std::cout << "Mix Character: " << Util::GetRandomCharacter(Util::MixChars) << "\n\n";

        // 4. Test GenerateWord & GenerateKey & PrintKeys
        std::cout << "--- 3. Testing Words & Keys Generation ---\n";
        std::cout << "Generated Word (8 chars, Mixed): " << Util::GenerateWord(Util::MixChars, 8) << "\n";
        std::cout << "Generated Key (Default): " << Util::GenerateKey() << "\n";
        std::cout << "Printing 3 Keys:\n";
        Util::PrintKeys(3, Util::CapitalLetter);
        std::cout << "\n";

        // 5. Test FillArray Methods & ShuffleArray
        std::cout << "--- 4. Testing Array Operations & Shuffle ---\n";
        constexpr size_t ARR_SIZE = 5;

        int intArr[ARR_SIZE];
        Util::FillArrayWithRandomNumbers(intArr, ARR_SIZE, 10, 99);
        std::cout << "Random Int Array: ";
        for (int val : intArr) std::cout << val << " ";
        std::cout << "\n";

        Util::ShuffleArray(intArr, ARR_SIZE);
        std::cout << "Shuffled Int Array: ";
        for (int val : intArr) std::cout << val << " ";
        std::cout << "\n\n";

        std::string wordArr[ARR_SIZE];
        Util::FillArrayWithRandomWords(wordArr, ARR_SIZE, Util::CapitalLetter, 5);
        std::cout << "Random Words Array: ";
        for (const auto& w : wordArr) std::cout << w << " ";
        std::cout << "\n\n";

        std::string keyArr[ARR_SIZE];
        Util::FillArrayWithRandomKeys(keyArr, ARR_SIZE, Util::CapitalLetter);
        std::cout << "Random Keys Array:\n";
        for (size_t i = 0; i < ARR_SIZE; ++i)
        {
            std::cout << "  [" << i << "] " << keyArr[i] << "\n";
        }
        std::cout << "\n";

        // 6. Test Swap
        std::cout << "--- 5. Testing Swap ---\n";
        int a = 10, b = 20;
        std::cout << "Before Swap: a = " << a << ", b = " << b << "\n";
        Util::Swap(a, b);
        std::cout << "After Swap : a = " << a << ", b = " << b << "\n\n";

        // 7. Test Tabs
        std::cout << "--- 6. Testing Tabs ---\n";
        std::cout << "Line Start" << Util::Tabs(3) << "Line After 3 Tabs\n\n";

        // 8. Test EncryptText & DecryptText
        std::cout << "--- 7. Testing Encryption & Decryption ---\n";
        std::string originalText = "Programming Modern C++ 2026";
        short key = 5;
        std::string encrypted = Util::EncryptText(originalText, key);
        std::string decrypted = Util::DecryptText(encrypted, key);

        std::cout << "Original Text : " << originalText << "\n";
        std::cout << "Encrypted Text: " << encrypted << "\n";
        std::cout << "Decrypted Text: " << decrypted << "\n\n";

        std::cout << "========================================\n";
        std::cout << "      All Tests Completed Successfully! \n";
        std::cout << "========================================\n";
    }

};