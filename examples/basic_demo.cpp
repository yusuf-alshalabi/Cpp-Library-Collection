#include <iostream>
#include "MyLib/MyString.h"
#include "MyLib/MyDate.h"
#include "MyLib/MyPeriod.h"

int main() {
    using namespace MyLib;
    
    std::cout << "=== C++ Library Collection Demo ===\n\n";
    
    // String Operations Demo
    std::cout << "1. String Operations:\n";
    MyString text("Hello World From C++ Library");
    std::cout << "Original: " << text.GetValue() << std::endl;
    std::cout << "Word Count: " << text.CountWords() << std::endl;
    std::cout << "Upper First Letters: " << text.UpperFirstLetterOfEachWord() << std::endl;
    std::cout << "All Upper: " << text.UpperAllString() << std::endl;
    std::cout << "All Lower: " << text.LowerAllString() << std::endl;
    std::cout << "Vowel Count: " << text.CountVowels() << std::endl;
    std::cout << "Is Palindrome: " << (text.IsPalindrome() ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
    
    // Date Operations Demo
    std::cout << "2. Date Operations:\n";
    MyDate today = MyDate::GetSystemDate();
    std::cout << "Today: ";
    today.Print();
    
    MyDate birthday(15, 8, 1990);
    std::cout << "Birthday: ";
    birthday.Print();
    
    std::cout << "Is Valid Birthday: " << (birthday.IsValid() ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
    
    // Period Operations Demo
    std::cout << "3. Period Operations:\n";
    MyDate startDate(1, 1, 2024);
    MyDate endDate(31, 12, 2024);
    MyPeriod year2024(startDate, endDate);
    
    std::cout << "Year 2024 Period: ";
    year2024.Print();
    std::cout << "Duration: " << year2024.GetDurationInDays() << " days" << std::endl;
    
    // Overlap Demo
    MyDate period1Start(1, 6, 2024);
    MyDate period1End(30, 6, 2024);
    MyPeriod period1(period1Start, period1End);
    
    MyDate period2Start(15, 6, 2024);
    MyDate period2End(15, 7, 2024);
    MyPeriod period2(period2Start, period2End);
    
    std::cout << "Period 1 overlaps with Period 2: " 
              << (period1.IsOverLapWith(period2) ? "Yes" : "No") << std::endl;
    
    // Error Handling Demo
    std::cout << "\n4. Error Handling:\n";
    try {
        MyString emptyString("");
        std::cout << "This should not print" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;
        std::cout << "Last error: " << MyString::GetLastError() << std::endl;
    }
    
    try {
        MyDate invalidDate("32/13/2024");
        std::cout << "This should not print" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;
        std::cout << "Last error: " << MyDate::GetLastError() << std::endl;
    }
    
    std::cout << "\n=== Demo Complete ===\n";
    return 0;
}
