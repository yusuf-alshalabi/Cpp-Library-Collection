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
