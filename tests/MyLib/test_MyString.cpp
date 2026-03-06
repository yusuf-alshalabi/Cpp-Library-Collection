#include <iostream>
#include <cassert>
#include "../../include/MyLib/MyString.h"

using namespace MyLib;

void test_mystring_basic() {
    std::cout << "Testing MyString basic functionality...\n";
    
    // Test constructor
    MyString str("Hello World");
    assert(str.GetValue() == "Hello World");
    
    // Test word counting
    assert(str.CountWords() == 2);
    
    // Test string operations
    assert(str.UpperAllString() == "HELLO WORLD");
    assert(str.LowerAllString() == "hello world");
    
    // Test palindrome
    MyString palindrome("racecar");
    assert(palindrome.IsPalindrome() == true);
    
    std::cout << "✓ MyString basic tests passed\n\n";
}

void test_mystring_error_handling() {
    std::cout << "Testing MyString error handling...\n";
    
    // Clear any previous errors
    MyString::ClearError();
    
    // Test empty string
    MyString emptyStr("");
    assert(emptyStr.GetValue() == "");
    
    std::cout << "✓ MyString error handling tests passed\n\n";
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
