#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include "../../include/MyLib/MyString.h"

using namespace MyLib;

void test_mystring_constructors_operators() {
    std::cout << "Testing MyString constructors and operators...\n";
    
    // Test default constructor
    MyString defaultStr;
    assert(defaultStr.GetValue() == "");
    std::cout << "✓ Default constructor test passed\n";
    
    // Test parameterized constructor
    MyString paramStr("Hello World");
    assert(paramStr.GetValue() == "Hello World");
    std::cout << "✓ Parameterized constructor test passed\n";
    
    // Test move constructor
    MyString moveStr(std::string("Move Test"));
    assert(moveStr.GetValue() == "Move Test");
    std::cout << "✓ Move constructor test passed\n";
    
    // Test copy constructor (implicit)
    MyString copyStr(paramStr);
    assert(copyStr.GetValue() == "Hello World");
    std::cout << "✓ Copy constructor test passed\n";
    
    // Test operator==
    MyString str1("Test");
    MyString str2("Test");
    MyString str3("Different");
    assert(str1 == str2);
    assert(!(str1 == str3));
    std::cout << "✓ Operator== test passed\n";
    
    // Test operator+
    MyString strA("Hello");
    MyString strB(" World");
    MyString strC = strA + strB;
    assert(strC.GetValue() == "Hello World");
    std::cout << "✓ Operator+ test passed\n";
    
    // Test move assignment operator
    MyString moveAssign;
    moveAssign = MyString("Move Assignment");
    assert(moveAssign.GetValue() == "Move Assignment");
    std::cout << "✓ Move assignment operator test passed\n";
    
    std::cout << "✓ MyString constructors and operators tests passed\n\n";
}

void test_mystring_length_functions() {
    std::cout << "Testing MyString length functions...\n";
    
    // Test static Length function
    assert(MyString::Length("Hello") == 5);
    assert(MyString::Length("") == 0);
    assert(MyString::Length("Hello World") == 11);
    std::cout << "✓ Length (static) test passed\n";
    
    // Test instance Length function
    MyString str1("Hello");
    assert(str1.Length() == 5);
    
    MyString str2("Hello World");
    assert(str2.Length() == 11);
    
    MyString str3("");
    assert(str3.Length() == 0);
    std::cout << "✓ Length (instance) test passed\n";
    
    // Test operator<< (stream output)
    std::ostringstream oss;
    MyString streamStr("Test Output");
    oss << streamStr;
    assert(oss.str() == "Test Output");
    std::cout << "✓ Operator<< test passed\n";
    
    std::cout << "✓ MyString length functions tests passed\n\n";
}

void test_mystring_error_handling() {
    std::cout << "Testing MyString error handling...\n";
    
    // Clear any previous errors
    MyString::ClearError();
    assert(MyString::GetLastError() == "");
    std::cout << "✓ ClearError and GetLastError test passed\n";
    
    // Test empty string constructor exception
    try {
        MyString emptyStr("");
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        assert(MyString::GetLastError() == "Cannot create MyString with empty value");
        std::cout << "✓ Empty string constructor exception test passed\n";
    }
    
    // Clear error for next test
    MyString::ClearError();
    
    // Test SetValue with empty string exception
    MyString validStr("Valid");
    try {
        validStr.SetValue("");
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        assert(MyString::GetLastError() == "Cannot set empty value to MyString");
        std::cout << "✓ SetValue empty string exception test passed\n";
    }
    
    // Test CountWords error handling
    MyString::ClearError();
    size_t wordCount = MyString::CountWords("");
    assert(wordCount == 0);
    assert(MyString::GetLastError() == "Cannot count words in empty string");
    std::cout << "✓ CountWords error handling test passed\n";
    
    std::cout << "✓ MyString error handling tests passed\n\n";
}

void test_mystring_case_operations() {
    std::cout << "Testing MyString case operations...\n";
    
    // Test UpperFirstLetterOfEachWord
    std::string upperFirst = MyString::UpperFirstLetterOfEachWord("hello world");
    assert(upperFirst == "Hello World");
    std::cout << "✓ UpperFirstLetterOfEachWord (static) test passed\n";
    
    // Test LowerFirstLetterOfEachWord
    std::string lowerFirst = MyString::LowerFirstLetterOfEachWord("HELLO WORLD");
    assert(lowerFirst == "hELLO wORLD");
    std::cout << "✓ LowerFirstLetterOfEachWord (static) test passed\n";
    
    // Test InvertLetterCase
    char invertedChar = MyString::InvertLetterCase('A');
    assert(invertedChar == 'a');
    invertedChar = MyString::InvertLetterCase('b');
    assert(invertedChar == 'B');
    std::cout << "✓ InvertLetterCase test passed\n";
    
    // Test InvertAllLettersCase
    std::string inverted = MyString::InvertAllLettersCase("Hello World");
    assert(inverted == "hELLO wORLD");
    std::cout << "✓ InvertAllLettersCase (static) test passed\n";
    
    std::cout << "✓ MyString case operations tests passed\n\n";
}

void test_mystring_case_instance_methods() {
    std::cout << "Testing MyString case instance methods...\n";
    
    // Test UpperFirstLetterOfEachWord instance method
    MyString str1("hello world");
    str1.UpperFirstLetterOfEachWord();
    assert(str1.GetValue() == "Hello World");
    std::cout << "✓ UpperFirstLetterOfEachWord (instance) test passed\n";
    
    // Test LowerFirstLetterOfEachWord instance method
    MyString str2("HELLO WORLD");
    str2.LowerFirstLetterOfEachWord();
    assert(str2.GetValue() == "hELLO wORLD");
    std::cout << "✓ LowerFirstLetterOfEachWord (instance) test passed\n";
    
    // Test UpperAllString instance method
    MyString str3("hello world");
    str3.UpperAllString();
    assert(str3.GetValue() == "HELLO WORLD");
    std::cout << "✓ UpperAllString (instance) test passed\n";
    
    // Test LowerAllString instance method
    MyString str4("HELLO WORLD");
    str4.LowerAllString();
    assert(str4.GetValue() == "hello world");
    std::cout << "✓ LowerAllString (instance) test passed\n";
    
    // Test InvertAllLettersCase instance method
    MyString str5("Hello World");
    str5.InvertAllLettersCase();
    assert(str5.GetValue() == "hELLO wORLD");
    std::cout << "✓ InvertAllLettersCase (instance) test passed\n";
    
    std::cout << "✓ MyString case instance methods tests passed\n\n";
}

void test_mystring_counting_operations() {
    std::cout << "Testing MyString counting operations...\n";
    
    // Test CountLetters with different enum values
    std::string testStr = "Hello World 123";
    assert(MyString::CountLetters(testStr, MyString::All) == 13);
    assert(MyString::CountLetters(testStr, MyString::CapitalLetters) == 2);
    assert(MyString::CountLetters(testStr, MyString::SmallLetters) == 8);
    std::cout << "✓ CountLetters (static) with enum test passed\n";
    
    // Test CountCapitalLetters
    assert(MyString::CountCapitalLetters("Hello World") == 2);
    std::cout << "✓ CountCapitalLetters (static) test passed\n";
    
    // Test CountSmallLetters
    assert(MyString::CountSmallLetters("Hello World") == 8);
    std::cout << "✓ CountSmallLetters (static) test passed\n";
    
    // Test CountSpecificLetter with case matching
    assert(MyString::CountSpecificLetter("Hello World", 'l') == 3);
    assert(MyString::CountSpecificLetter("Hello World", 'L') == 2);
    std::cout << "✓ CountSpecificLetter (case sensitive) test passed\n";
    
    // Test CountSpecificLetter without case matching
    assert(MyString::CountSpecificLetter("Hello World", 'l', false) == 5);
    std::cout << "✓ CountSpecificLetter (case insensitive) test passed\n";
    
    // Test IsVowel
    assert(MyString::IsVowel('a') == true);
    assert(MyString::IsVowel('E') == true);
    assert(MyString::IsVowel('b') == false);
    assert(MyString::IsVowel('Z') == false);
    std::cout << "✓ IsVowel test passed\n";
    
    // Test CountVowels
    assert(MyString::CountVowels("Hello World") == 3); // e, o, o
    assert(MyString::CountVowels("AEIOU") == 5);
    assert(MyString::CountVowels("bcdfg") == 0);
    std::cout << "✓ CountVowels (static) test passed\n";
    
    std::cout << "✓ MyString counting operations tests passed\n\n";
}

void test_mystring_counting_instance_methods() {
    std::cout << "Testing MyString counting instance methods...\n";
    
    // Test CountLetters instance method with enum
    MyString str1("Hello World 123");
    assert(str1.CountLetters(MyString::All) == 13);
    assert(str1.CountLetters(MyString::CapitalLetters) == 2);
    assert(str1.CountLetters(MyString::SmallLetters) == 8);
    std::cout << "✓ CountLetters (instance with enum) test passed\n";
    
    // Test CountCapitalLetters instance method
    MyString str2("Hello World");
    assert(str2.CountCapitalLetters() == 2);
    std::cout << "✓ CountCapitalLetters (instance) test passed\n";
    
    // Test CountSmallLetters instance method
    MyString str3("Hello World");
    assert(str3.CountSmallLetters() == 8);
    std::cout << "✓ CountSmallLetters (instance) test passed\n";
    
    // Test CountSpecificLetter instance method with case matching
    MyString str4("Hello World");
    assert(str4.CountSpecificLetter('l') == 3);
    assert(str4.CountSpecificLetter('L') == 2);
    std::cout << "✓ CountSpecificLetter (instance, case sensitive) test passed\n";
    
    // Test CountSpecificLetter instance method without case matching
    MyString str5("Hello World");
    assert(str5.CountSpecificLetter('l', false) == 5);
    std::cout << "✓ CountSpecificLetter (instance, case insensitive) test passed\n";
    
    // Test CountVowels instance method
    MyString str6("Hello World");
    assert(str6.CountVowels() == 3); // e, o, o
    std::cout << "✓ CountVowels (instance) test passed\n";
    
    std::cout << "✓ MyString counting instance methods tests passed\n\n";
}

void test_mystring_advanced_operations() {
    std::cout << "Testing MyString advanced operations...\n";
    
    // Test ReverseWordsInString
    std::string reversed = MyString::ReverseWordsInString("Hello World Test");
    assert(reversed == "Test World Hello");
    std::cout << "✓ ReverseWordsInString (static) test passed\n";
    
    // Test ReplaceWord with case matching
    std::string replaced = MyString::ReplaceWord("Hello World Hello", "Hello", "Hi", true);
    assert(replaced == "Hi World Hi");
    std::cout << "✓ ReplaceWord (case sensitive) test passed\n";
    
    // Test ReplaceWord without case matching
    std::string replacedCase = MyString::ReplaceWord("Hello World hello", "hello", "Hi", false);
    assert(replacedCase == "Hi World Hi");
    std::cout << "✓ ReplaceWord (case insensitive) test passed\n";
    
    // Test RemovePunctuations
    std::string noPunct = MyString::RemovePunctuations("Hello, World! How are you?");
    assert(noPunct == "Hello World How are you");
    std::cout << "✓ RemovePunctuations (static) test passed\n";
    
    // Test Contains
    assert(MyString::Contains("Hello World", "World") == true);
    assert(MyString::Contains("Hello World", "Test") == false);
    std::cout << "✓ Contains (static) test passed\n";
    
    // Test StartsWith
    assert(MyString::StartsWith("Hello World", "Hello") == true);
    assert(MyString::StartsWith("Hello World", "World") == false);
    std::cout << "✓ StartsWith (static) test passed\n";
    
    // Test EndsWith
    assert(MyString::EndsWith("Hello World", "World") == true);
    assert(MyString::EndsWith("Hello World", "Hello") == false);
    std::cout << "✓ EndsWith (static) test passed\n";
    
    // Test Repeat
    assert(MyString::Repeat("Hi", 3) == "HiHiHi");
    assert(MyString::Repeat("Test", 0) == "");
    assert(MyString::Repeat("", 5) == "");
    std::cout << "✓ Repeat (static) test passed\n";
    
    // Test IsPalindrome
    assert(MyString::IsPalindrome("racecar") == true);
    assert(MyString::IsPalindrome("hello") == false);
    assert(MyString::IsPalindrome("A man a plan a canal Panama") == true);
    std::cout << "✓ IsPalindrome (static) test passed\n";
    
    std::cout << "✓ MyString advanced operations tests passed\n\n";
}

void test_mystring_split_trim_functions() {
    std::cout << "Testing MyString split and trim functions...\n";
    
    // Test Split instance method
    MyString str1("word1,word2,word3");
    std::vector<std::string> words = str1.Split(",");
    assert(words.size() == 3);
    assert(words[0] == "word1");
    assert(words[1] == "word2");
    assert(words[2] == "word3");
    std::cout << "✓ Split (instance) test passed\n";
    
    // Test TrimLeft instance method
    MyString str2("   Hello");
    str2.TrimLeft();
    assert(str2.GetValue() == "Hello");
    std::cout << "✓ TrimLeft (instance) test passed\n";
    
    // Test TrimRight instance method
    MyString str3("Hello   ");
    str3.TrimRight();
    assert(str3.GetValue() == "Hello");
    std::cout << "✓ TrimRight (instance) test passed\n";
    
    // Test Trim instance method
    MyString str4("   Hello World   ");
    str4.Trim();
    assert(str4.GetValue() == "Hello World");
    std::cout << "✓ Trim (instance) test passed\n";
    
    // Test JoinString static methods
    std::vector<std::string> joinVec = {"A", "B", "C"};
    assert(MyString::JoinString(joinVec, ",") == "A,B,C");
    std::cout << "✓ JoinString with vector test passed\n";
    
    std::string joinArr[] = {"X", "Y", "Z"};
    assert(MyString::JoinString(joinArr, 3, "|") == "X|Y|Z");
    std::cout << "✓ JoinString with array test passed\n";
    
    // Test JoinString edge cases
    std::vector<std::string> emptyVec;
    assert(MyString::JoinString(emptyVec, ",") == "");
    assert(MyString::JoinString(joinArr, 0, ",") == "");
    std::cout << "✓ JoinString edge cases test passed\n";
    
    std::cout << "✓ MyString split and trim functions tests passed\n\n";
}

void test_mystring_utility_functions() {
    std::cout << "Testing MyString utility functions...\n";
    
    // Test string splitting
    MyString testStr("word1,word2,word3");
    std::vector<std::string> words = testStr.Split(",");
    assert(words.size() == 3);
    assert(words[0] == "word1");
    assert(words[1] == "word2");
    assert(words[2] == "word3");
    
    // Test string trimming
    MyString trimStr("  Hello  ");
    std::string trimmed = trimStr.Trim();
    assert(trimmed == "Hello");
    
    std::cout << "✓ MyString utility functions tests passed\n\n";
}

int main() {
    std::cout << "=== MyString Unit Tests ===\n\n";
    
    test_mystring_constructors_operators();
    test_mystring_error_handling();
    test_mystring_case_operations();
    test_mystring_counting_operations();
    test_mystring_advanced_operations();
    test_mystring_utility_functions();
    
    std::cout << "🎉 All MyString tests passed successfully!\n";
    return 0;
}
