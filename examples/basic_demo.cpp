#include <iostream>
#include <chrono>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"
#include "MyLib/MyUtil.h"
#include "MyLib/MyInputValidate.h"

int main() {
    using namespace MyLib;
    
    std::cout << "=== C++ Library Collection Demo ===\n\n";
    
    // =================================================================
    // 1. STRING OPERATIONS DEMO
    // =================================================================
    std::cout << "1. STRING OPERATIONS:\n";
    std::cout << "-------------------\n";
    
    MyString text("Hello World From C++ Library");
    std::cout << "Original: " << text.GetValue() << std::endl;
    std::cout << "Length: " << text.Length() << std::endl;
    std::cout << "Word Count: " << text.CountWords() << std::endl;
    
    // Case operations
    std::cout << "\nCase Operations:\n";
    std::cout << "Upper First Letters: " << MyString::UpperFirstLetterOfEachWord(text.GetValue()) << std::endl;
    std::cout << "All Upper: " << MyString::UpperAllString(text.GetValue()) << std::endl;
    std::cout << "All Lower: " << MyString::LowerAllString(text.GetValue()) << std::endl;
    std::cout << "Invert Case: " << MyString::InvertAllLettersCase(text.GetValue()) << std::endl;
    
    // Character analysis
    std::cout << "\nCharacter Analysis:\n";
    std::cout << "Capital Letters: " << text.CountCapitalLetters() << std::endl;
    std::cout << "Small Letters: " << text.CountSmallLetters() << std::endl;
    std::cout << "Vowel Count: " << text.CountVowels() << std::endl;
    std::cout << "Specific Letter 'l': " << text.CountSpecificLetter('l') << std::endl;
    
    // String operations
    std::cout << "\nString Operations:\n";
    std::cout << "Trim '  hello  ': '" << MyString::Trim("  hello  ") << "'" << std::endl;
    std::cout << "Reversed Words: " << MyString::ReverseWordsInString(text.GetValue()) << std::endl;
    std::cout << "Replace 'World' with 'Universe': " << text.ReplaceWord("World", "Universe") << std::endl;
    std::cout << "Remove Punctuations: " << MyString::RemovePunctuations("Hello, World!") << std::endl;
    
    // String checks
    std::cout << "\nString Checks:\n";
    std::cout << "Contains 'Library': " << (text.Contains("Library") ? "Yes" : "No") << std::endl;
    std::cout << "StartsWith 'Hello': " << (text.StartsWith("Hello") ? "Yes" : "No") << std::endl;
    std::cout << "EndsWith 'Library': " << (text.EndsWith("Library") ? "Yes" : "No") << std::endl;
    std::cout << "Is Palindrome 'racecar': " << (MyString::IsPalindrome("racecar") ? "Yes" : "No") << std::endl;
    std::cout << "Repeat 'Hi' 3 times: " << MyString::Repeat("Hi", 3) << std::endl;
    
    std::cout << std::endl;
    
    // =================================================================
    // 2. DATE OPERATIONS DEMO
    // =================================================================
    std::cout << "2. DATE OPERATIONS:\n";
    std::cout << "-----------------\n";
    
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today: ";
    today.Print();
    
    MyDate birthday(15, 8, 1990);
    std::cout << "Birthday: ";
    birthday.Print();
    
    MyDate stringDate("25/12/2023");
    std::cout << "String Date (25/12/2023): ";
    stringDate.Print();
    
    // Date validation
    std::cout << "\nDate Validation:\n";
    std::cout << "Is Valid Birthday: " << (birthday.IsValid() ? "Yes" : "No") << std::endl;
    std::cout << "Is Leap Year (1990): " << (birthday.isLeapYear() ? "Yes" : "No") << std::endl;
    std::cout << "Is Leap Year (2024): " << (MyDate(1, 1, 2024).isLeapYear() ? "Yes" : "No") << std::endl;
    
    // Date information
    std::cout << "\nDate Information:\n";
    std::cout << "Day of Week (Birthday): " << birthday.DayShortName() << std::endl;
    std::cout << "Month Name (Birthday): " << birthday.MonthShortName() << std::endl;
    std::cout << "Days from Beginning of Year: " << birthday.DaysFromTheBeginingOfTheYear() << std::endl;
    
    // Time calculations
    std::cout << "\nTime Calculations:\n";
    std::cout << "Days in Year (2024): " << MyDate::NumberOfDaysInAYear(2024) << std::endl;
    std::cout << "Hours in Year (2024): " << MyDate::NumberOfHoursInAYear(2024) << std::endl;
    std::cout << "Days in Month (Feb 2024): " << MyDate::NumberOfDaysInAMonth(2, 2024) << std::endl;
    
    // Date manipulation
    std::cout << "\nDate Manipulation:\n";
    MyDate modifiedDate = birthday;
    std::cout << "Original Birthday: ";
    modifiedDate.Print();
    
    modifiedDate.AddDays(10);
    std::cout << "After adding 10 days: ";
    modifiedDate.Print();
    
    modifiedDate.IncreaseDateByOneMonth();
    std::cout << "After adding 1 month: ";
    modifiedDate.Print();
    
    modifiedDate.IncreaseDateByOneYear();
    std::cout << "After adding 1 year: ";
    modifiedDate.Print();
    
    // Business days
    std::cout << "\nBusiness Days:\n";
    std::cout << "Is Business Day (Today): " << (today.IsBusinessDay() ? "Yes" : "No") << std::endl;
    std::cout << "Is Weekend (Today): " << (today.IsWeekEnd() ? "Yes" : "No") << std::endl;
    std::cout << "Days Until End of Month: " << today.DaysUntilTheEndOfMonth() << std::endl;
    
    std::cout << std::endl;
    
    // =================================================================
    // 3. PERIOD OPERATIONS DEMO
    // =================================================================
    std::cout << "3. PERIOD OPERATIONS:\n";
    std::cout << "-------------------\n";
    
    MyDate startDate(1, 1, 2024);
    MyDate endDate(31, 12, 2024);
    MyPeriod year2024(startDate, endDate);
    
    std::cout << "Year 2024 Period: ";
    year2024.Print();
    std::cout << "Duration: " << year2024.GetDurationInDays() << " days" << std::endl;
    std::cout << "Length in Months: " << year2024.LengthInMonths() << " months" << std::endl;
    std::cout << "Length in Years: " << year2024.LengthInYears() << " years" << std::endl;
    
    // Overlap demo
    std::cout << "\nPeriod Overlap:\n";
    MyDate period1Start(1, 6, 2024);
    MyDate period1End(30, 6, 2024);
    MyPeriod period1(period1Start, period1End);
    
    MyDate period2Start(15, 6, 2024);
    MyDate period2End(15, 7, 2024);
    MyPeriod period2(period2Start, period2End);
    
    std::cout << "Period 1: ";
    period1.Print();
    std::cout << "Period 2: ";
    period2.Print();
    std::cout << "Period 1 overlaps with Period 2: " << (period1.IsOverLapWith(period2) ? "Yes" : "No") << std::endl;
    
    // Contains demo
    MyDate testDate(15, 6, 2024);
    std::cout << "Date 15/6/2024 is in Period 1: " << (period1.Contains(testDate) ? "Yes" : "No") << std::endl;
    
    std::cout << std::endl;
    
    // =================================================================
    // 4. UTILITY FUNCTIONS DEMO
    // =================================================================
    std::cout << "4. UTILITY FUNCTIONS:\n";
    std::cout << "--------------------\n";
    
    // Initialize random seed
    MyUtil::Srand();
    
    // Random numbers
    std::cout << "Random Numbers:\n";
    std::cout << "Random number (1-100): " << MyUtil::RandomNumber(1, 100) << std::endl;
    std::cout << "Random number (50-75): " << MyUtil::RandomNumber(50, 75) << std::endl;
    
    // Random characters
    std::cout << "\nRandom Characters:\n";
    std::cout << "Random small letter: " << MyUtil::GetRandomCharacter(MyUtil::SmallLetter) << std::endl;
    std::cout << "Random capital letter: " << MyUtil::GetRandomCharacter(MyUtil::CapitalLetter) << std::endl;
    std::cout << "Random digit: " << MyUtil::GetRandomCharacter(MyUtil::Digit) << std::endl;
    std::cout << "Random special character: " << MyUtil::GetRandomCharacter(MyUtil::SpecialCharacter) << std::endl;
    std::cout << "Random mixed character: " << MyUtil::GetRandomCharacter(MyUtil::MixChars) << std::endl;
    
    // Random words and keys
    std::cout << "\nRandom Words and Keys:\n";
    std::cout << "Random word (5 letters): " << MyUtil::GenerateWord(MyUtil::CapitalLetter, 5) << std::endl;
    std::cout << "Random key: " << MyUtil::GenerateKey() << std::endl;
    std::cout << "Random number key: " << MyUtil::GenerateKey(MyUtil::Digit) << std::endl;
    
    // Array operations
    std::cout << "\nArray Operations:\n";
    int numbers[5];
    std::string stringWords[3];
    
    MyUtil::FillArrayWithRandomNumbers(numbers, 5, 1, 10);
    std::cout << "Random numbers array: ";
    for (int i = 0; i < 5; i++) std::cout << numbers[i] << " ";
    std::cout << std::endl;
    
    MyUtil::FillArrayWithRandomWords(stringWords, 3, MyUtil::CapitalLetter, 4);
    std::cout << "Random words array: ";
    for (int i = 0; i < 3; i++) std::cout << stringWords[i] << " ";
    std::cout << std::endl;
    
    // Shuffle demo
    std::cout << "Original numbers: ";
    for (int i = 0; i < 5; i++) std::cout << numbers[i] << " ";
    std::cout << std::endl;
    
    MyUtil::ShuffleArray(numbers, 5);
    std::cout << "Shuffled numbers: ";
    for (int i = 0; i < 5; i++) std::cout << numbers[i] << " ";
    std::cout << std::endl;
    
    // Encryption demo
    std::cout << "\nEncryption:\n";
    std::string originalText = "Hello World";
    std::string encrypted = MyUtil::EncryptText(originalText, 5);
    std::string decrypted = MyUtil::DecryptText(encrypted, 5);
    
    std::cout << "Original: " << originalText << std::endl;
    std::cout << "Encrypted (+5): " << encrypted << std::endl;
    std::cout << "Decrypted (-5): " << decrypted << std::endl;
    
    std::cout << std::endl;
    
    // =================================================================
    // 5. INPUT VALIDATION DEMO
    // =================================================================
    std::cout << "5. INPUT VALIDATION:\n";
    std::cout << "-------------------\n";
    
    // Note: In real applications, these would wait for user input
    // For demo purposes, we'll show the functionality
    
    std::cout << "Input validation functions available:\n";
    std::cout << "- ReadIntNumber(): Safe integer input\n";
    std::cout << "- ReadIntNumberBetween(from, to): Integer with range validation\n";
    std::cout << "- ReadDblNumber(): Safe double input\n";
    std::cout << "- ReadDblNumberBetween(from, to): Double with range validation\n";
    std::cout << "- IsNumberBetween(num, from, to): Template function for any numeric type\n";
    std::cout << "- IsDateBetween(date, from, to): Date range validation\n";
    std::cout << "- IsValidDate(date): Date validation\n";
    
    // Demonstrate validation functions
    std::cout << "\nValidation Examples:\n";
    std::cout << "Is 5 between 1-10: " << (MyInputValidate::IsNumberBetween(5, 1, 10) ? "Yes" : "No") << std::endl;
    std::cout << "Is 15 between 1-10: " << (MyInputValidate::IsNumberBetween(15, 1, 10) ? "Yes" : "No") << std::endl;
    std::cout << "Is 3.14 between 1.0-5.0: " << (MyInputValidate::IsNumberBetween(3.14, 1.0, 5.0) ? "Yes" : "No") << std::endl;
    
    MyDate date1(1, 6, 2024);
    MyDate date2(15, 6, 2024);
    MyDate date3(30, 6, 2024);
    std::cout << "Is 15/6/2024 between 1/6/2024 and 30/6/2024: " << (MyInputValidate::IsDateBetween(date2, date1, date3) ? "Yes" : "No") << std::endl;
    std::cout << "Is birthday valid: " << (MyInputValidate::IsValidDate(birthday) ? "Yes" : "No") << std::endl;
    
    std::cout << std::endl;
    
    // =================================================================
    // 6. ERROR HANDLING DEMO
    // =================================================================
    std::cout << "6. ERROR HANDLING:\n";
    std::cout << "-----------------\n";
    
    // String error handling
    std::cout << "String Error Handling:\n";
    try {
        MyString emptyString("");
        std::cout << "This should not print" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;
        std::cout << "Last error: " << MyString::GetLastError() << std::endl;
    }
    
    // Date error handling
    std::cout << "\nDate Error Handling:\n";
    try {
        MyDate invalidDate("32/13/2024");
        std::cout << "This should not print" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;
        std::cout << "Last error: " << MyDate::GetLastError() << std::endl;
    }
    
    // Period error handling
    std::cout << "\nPeriod Error Handling:\n";
    try {
        MyDate start(31, 12, 2024);
        MyDate end(1, 1, 2024);
        MyPeriod invalidPeriod(start, end);
        std::cout << "This should not print" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;
        std::cout << "Last error: " << MyPeriod::GetLastError() << std::endl;
    }
    
    std::cout << std::endl;
    
    // =================================================================
    // 7. ADVANCED FEATURES DEMO
    // =================================================================
    std::cout << "7. ADVANCED FEATURES:\n";
    std::cout << "---------------------\n";
    
    // Advanced string operations
    std::cout << "Advanced String Operations:\n";
    std::vector<std::string> splitWords = text.Split(" ");
    std::cout << "Split words: ";
    for (const auto& word : splitWords) std::cout << "[" << word << "] ";
    std::cout << std::endl;
    
    std::string joined = MyString::JoinString(splitWords, "-");
    std::cout << "Joined with '-': " << joined << std::endl;
    
    // Advanced date operations
    std::cout << "\nAdvanced Date Operations:\n";
    MyDate vacationStart(1, 6, 2024);
    MyDate vacationEnd(15, 6, 2024);
    int businessDays = MyDate::CalculateBusinessDays(vacationStart, vacationEnd);
    int vacationDays = MyDate::CalculateVacationDays(vacationStart, vacationEnd);
    
    std::cout << "Business days in vacation: " << businessDays << std::endl;
    std::cout << "Vacation days (including weekends): " << vacationDays << std::endl;
    
    MyDate returnDate = MyDate::CalculateVacationReturnDate(vacationStart, 10);
    std::cout << "Vacation return date (10 business days): ";
    returnDate.Print();
    
    // Date comparison
    std::cout << "\nDate Comparison:\n";
    MyDate dateA(15, 6, 2024);
    MyDate dateB(20, 6, 2024);
    
    MyDate::enDateCompare comparison = MyDate::CompareDates(dateA, dateB);
    std::string compResult = (comparison == MyDate::enDateCompare::Before) ? "Before" :
                           (comparison == MyDate::enDateCompare::After) ? "After" : "Equal";
    std::cout << "15/6/2024 compared to 20/6/2024: " << compResult << std::endl;
    
    std::cout << std::endl;
    
    // =================================================================
    // 8. PERFORMANCE DEMO
    // =================================================================
    std::cout << "8. PERFORMANCE FEATURES:\n";
    std::cout << "-----------------------\n";
    
    // Efficient string operations
    std::cout << "Efficient Operations:\n";
    std::string longText = MyString::Repeat("Hello ", 1000);
    std::cout << "Created long string with " << longText.length() << " characters" << std::endl;
    std::cout << "Word count in long string: " << MyString::CountWords(longText) << std::endl;
    
    // Efficient array operations
    std::cout << "\nEfficient Array Operations:\n";
    int largeArray[100];
    MyUtil::FillArrayWithRandomNumbers(largeArray, 100, 1, 1000);
    
    auto start = std::chrono::high_resolution_clock::now();
    MyUtil::ShuffleArray(largeArray, 100);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Shuffled 100 elements in " << duration.count() << " microseconds" << std::endl;
    
    std::cout << std::endl;
    
    // =================================================================
    // SUMMARY
    // =================================================================
    std::cout << "=== DEMO SUMMARY ===\n";
    std::cout << "[DONE] String Operations: Complete\n";
    std::cout << "[DONE] Date Operations: Complete\n";
    std::cout << "[DONE] Period Operations: Complete\n";
    std::cout << "[DONE] Utility Functions: Complete\n";
    std::cout << "[DONE] Input Validation: Complete\n";
    std::cout << "[DONE] Error Handling: Complete\n";
    std::cout << "[DONE] Advanced Features: Complete\n";
    std::cout << "[DONE] Performance Features: Complete\n";
    std::cout << "\n*** C++ Library Collection Comprehensive Demo Complete! ***\n";
    std::cout << "\nThis demo showcases all major features of the C++ Library Collection:\n";
    std::cout << "- 5 Core Classes: MyString, MyDate, MyPeriod, MyUtil, MyInputValidate\n";
    std::cout << "- Professional error handling\n";
    std::cout << "- Template-based generic programming\n";
    std::cout << "- Efficient algorithms and data structures\n";
    std::cout << "- Clean, modern C++17 code\n";
    std::cout << "- Comprehensive documentation and examples\n";
    
    return 0;
}
