#include <iostream>
#include <cassert>
#include <vector>
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
    
    test_mystring_basic();
    test_mystring_error_handling();
    test_mystring_utility_functions();
    
    std::cout << "🎉 All MyString tests passed successfully!\n";
    return 0;
}
