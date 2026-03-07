#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include "../../include/MyLib/MyString.h"

using namespace MyLib;

// Test helper functions
void assert_equal(const std::string& expected, const std::string& actual, const std::string& test_name) {
    assert(expected == actual);
    std::cout << "✓ " << test_name << " test passed\n";
}

void assert_true(bool condition, const std::string& test_name) {
    assert(condition);
    std::cout << "✓ " << test_name << " test passed\n";
}

void test_constructors_and_operators() {
    std::cout << "Testing constructors and operators...\n";
    
    // Default constructor
    MyString defaultStr;
    assert_equal("", defaultStr.GetValue(), "Default constructor");
    
    // Parameterized constructor
    MyString paramStr("Hello World");
    assert_equal("Hello World", paramStr.GetValue(), "Parameterized constructor");
    
    // Move constructor
    MyString moveStr(std::string("Move Test"));
    assert_equal("Move Test", moveStr.GetValue(), "Move constructor");
    
    // Copy constructor
    MyString copyStr(paramStr);
    assert_equal("Hello World", copyStr.GetValue(), "Copy constructor");
    
    // Equality operator
    MyString str1("Test"), str2("Test"), str3("Different");
    assert_true(str1 == str2, "Operator== (equal)");
    assert_true(!(str1 == str3), "Operator== (not equal)");
    
    // Concatenation operator
    MyString strA("Hello"), strB(" World");
    MyString strC = strA + strB;
    assert_equal("Hello World", strC.GetValue(), "Operator+");
    
    // Move assignment
    MyString moveAssign;
    moveAssign = MyString("Move Assignment");
    assert_equal("Move Assignment", moveAssign.GetValue(), "Move assignment");
    
    std::cout << "✓ Constructors and operators tests passed\n\n";
}

void test_length_and_stream() {
    std::cout << "Testing length and stream operations...\n";
    
    // Static Length function
    assert_true(MyString::Length("Hello") == 5, "Length static (Hello)");
    assert_true(MyString::Length("") == 0, "Length static (empty)");
    assert_true(MyString::Length("Hello World") == 11, "Length static (Hello World)");
    
    // Instance Length function
    MyString str1("Hello"), str2("Hello World"), str3("");
    assert_true(str1.Length() == 5, "Length instance (Hello)");
    assert_true(str2.Length() == 11, "Length instance (Hello World)");
    assert_true(str3.Length() == 0, "Length instance (empty)");
    
    // Stream output operator
    std::ostringstream oss;
    MyString streamStr("Test Output");
    oss << streamStr;
    assert_equal("Test Output", oss.str(), "Stream output operator");
    
    std::cout << "✓ Length and stream operations tests passed\n\n";
}

void test_error_handling() {
    std::cout << "Testing error handling...\n";
    
    // Clear and check error functions
    MyString::ClearError();
    assert_equal("", MyString::GetLastError(), "ClearError and GetLastError");
    
    // Empty string constructor exception
    try {
        MyString emptyStr("");
        assert_true(false, "Should throw exception for empty constructor");
    } catch (const std::invalid_argument&) {
        assert_equal("Cannot create MyString with empty value", MyString::GetLastError(), 
                   "Empty constructor exception");
    }
    
    // SetValue empty string exception
    MyString::ClearError();
    MyString validStr("Valid");
    try {
        validStr.SetValue("");
        assert_true(false, "Should throw exception for empty SetValue");
    } catch (const std::invalid_argument&) {
        assert_equal("Cannot set empty value to MyString", MyString::GetLastError(),
                   "Empty SetValue exception");
    }
    
    // CountWords error handling
    MyString::ClearError();
    size_t wordCount = MyString::CountWords("");
    assert_true(wordCount == 0, "CountWords empty returns 0");
    assert_equal("Cannot count words in empty string", MyString::GetLastError(),
               "CountWords error message");
    
    std::cout << "✓ Error handling tests passed\n\n";
}

void test_case_operations() {
    std::cout << "Testing case operations...\n";
    
    // Static case operations
    assert_equal("Hello World", MyString::UpperFirstLetterOfEachWord("hello world"), 
               "UpperFirstLetterOfEachWord static");
    assert_equal("hELLO wORLD", MyString::LowerFirstLetterOfEachWord("HELLO WORLD"),
               "LowerFirstLetterOfEachWord static");
    assert_equal('a', MyString::InvertLetterCase('A'), "InvertLetterCase (A->a)");
    assert_equal('B', MyString::InvertLetterCase('b'), "InvertLetterCase (b->B)");
    assert_equal("hELLO wORLD", MyString::InvertAllLettersCase("Hello World"),
               "InvertAllLettersCase static");
    assert_equal("HELLO WORLD", MyString::UpperAllString("hello world"),
               "UpperAllString static");
    assert_equal("hello world", MyString::LowerAllString("HELLO WORLD"),
               "LowerAllString static");
    
    // Instance case operations
    MyString str1("hello world");
    str1.UpperFirstLetterOfEachWord();
    assert_equal("Hello World", str1.GetValue(), "UpperFirstLetterOfEachWord instance");
    
    MyString str2("HELLO WORLD");
    str2.LowerFirstLetterOfEachWord();
    assert_equal("hELLO wORLD", str2.GetValue(), "LowerFirstLetterOfEachWord instance");
    
    MyString str3("hello world");
    str3.UpperAllString();
    assert_equal("HELLO WORLD", str3.GetValue(), "UpperAllString instance");
    
    MyString str4("HELLO WORLD");
    str4.LowerAllString();
    assert_equal("hello world", str4.GetValue(), "LowerAllString instance");
    
    MyString str5("Hello World");
    str5.InvertAllLettersCase();
    assert_equal("hELLO wORLD", str5.GetValue(), "InvertAllLettersCase instance");
    
    std::cout << "✓ Case operations tests passed\n\n";
}

void test_counting_operations() {
    std::cout << "Testing counting operations...\n";
    
    std::string testStr = "Hello World 123";
    
    // Static counting functions
    assert_true(MyString::CountLetters(testStr, MyString::All) == 13, "CountLetters (All)");
    assert_true(MyString::CountLetters(testStr, MyString::CapitalLetters) == 2, "CountLetters (Capital)");
    assert_true(MyString::CountLetters(testStr, MyString::SmallLetters) == 8, "CountLetters (Small)");
    assert_true(MyString::CountCapitalLetters("Hello World") == 2, "CountCapitalLetters");
    assert_true(MyString::CountSmallLetters("Hello World") == 8, "CountSmallLetters");
    assert_true(MyString::CountSpecificLetter("Hello World", 'l') == 3, "CountSpecificLetter case-sensitive");
    assert_true(MyString::CountSpecificLetter("Hello World", 'L') == 2, "CountSpecificLetter case-sensitive L");
    assert_true(MyString::CountSpecificLetter("Hello World", 'l', false) == 5, "CountSpecificLetter case-insensitive");
    assert_true(MyString::IsVowel('a'), "IsVowel (a)");
    assert_true(MyString::IsVowel('E'), "IsVowel (E)");
    assert_true(!MyString::IsVowel('b'), "IsVowel (b - not vowel)");
    assert_true(MyString::CountVowels("Hello World") == 3, "CountVowels (Hello World)");
    assert_true(MyString::CountVowels("AEIOU") == 5, "CountVowels (AEIOU)");
    assert_true(MyString::CountVowels("bcdfg") == 0, "CountVowels (no vowels)");
    
    // Instance counting functions
    MyString str1("Hello World 123");
    assert_true(str1.CountLetters(MyString::All) == 13, "Instance CountLetters (All)");
    assert_true(str1.CountLetters(MyString::CapitalLetters) == 2, "Instance CountLetters (Capital)");
    assert_true(str1.CountLetters(MyString::SmallLetters) == 8, "Instance CountLetters (Small)");
    
    MyString str2("Hello World");
    assert_true(str2.CountCapitalLetters() == 2, "Instance CountCapitalLetters");
    assert_true(str2.CountSmallLetters() == 8, "Instance CountSmallLetters");
    assert_true(str2.CountSpecificLetter('l') == 3, "Instance CountSpecificLetter case-sensitive");
    assert_true(str2.CountSpecificLetter('L') == 2, "Instance CountSpecificLetter case-sensitive L");
    assert_true(str2.CountSpecificLetter('l', false) == 5, "Instance CountSpecificLetter case-insensitive");
    assert_true(str2.CountVowels() == 3, "Instance CountVowels");
    
    std::cout << "✓ Counting operations tests passed\n\n";
}

void test_string_operations() {
    std::cout << "Testing string operations...\n";
    
    // Static string operations
    assert_equal("Test World Hello", MyString::ReverseWordsInString("Hello World Test"),
               "ReverseWordsInString static");
    assert_equal("Hi World Hi", MyString::ReplaceWord("Hello World Hello", "Hello", "Hi", true),
               "ReplaceWord case-sensitive");
    assert_equal("Hi World Hi", MyString::ReplaceWord("Hello World hello", "hello", "Hi", false),
               "ReplaceWord case-insensitive");
    assert_equal("Hello World How are you", MyString::RemovePunctuations("Hello, World! How are you?"),
               "RemovePunctuations static");
    assert_true(MyString::Contains("Hello World", "World"), "Contains (true)");
    assert_true(!MyString::Contains("Hello World", "Test"), "Contains (false)");
    assert_true(MyString::StartsWith("Hello World", "Hello"), "StartsWith (true)");
    assert_true(!MyString::StartsWith("Hello World", "World"), "StartsWith (false)");
    assert_true(MyString::EndsWith("Hello World", "World"), "EndsWith (true)");
    assert_true(!MyString::EndsWith("Hello World", "Hello"), "EndsWith (false)");
    assert_equal("HiHiHi", MyString::Repeat("Hi", 3), "Repeat (Hi, 3)");
    assert_equal("", MyString::Repeat("Test", 0), "Repeat (Test, 0)");
    assert_equal("", MyString::Repeat("", 5), "Repeat (empty, 5)");
    assert_true(MyString::IsPalindrome("racecar"), "IsPalindrome (racecar)");
    assert_true(!MyString::IsPalindrome("hello"), "IsPalindrome (hello)");
    assert_true(MyString::IsPalindrome("A man a plan a canal Panama"), "IsPalindrome (phrase)");
    
    // Instance string operations
    MyString str1("Hello World Test");
    str1.ReverseWordsInString();
    assert_equal("Test World Hello", str1.GetValue(), "ReverseWordsInString instance");
    
    MyString str2("Hello World Hello");
    assert_equal("Hi World Hi", str2.ReplaceWord("Hello", "Hi", true), "ReplaceWord instance case-sensitive");
    
    MyString str3("Hello World hello");
    assert_equal("Hi World Hi", str3.ReplaceWord("hello", "Hi", false), "ReplaceWord instance case-insensitive");
    
    MyString str4("Hello, World! How are you?");
    str4.RemovePunctuations();
    assert_equal("Hello World How are you", str4.GetValue(), "RemovePunctuations instance");
    
    MyString str5("Hello World");
    assert_true(str5.Contains("World"), "Instance Contains (true)");
    assert_true(!str5.Contains("Test"), "Instance Contains (false)");
    assert_true(str5.StartsWith("Hello"), "Instance StartsWith (true)");
    assert_true(!str5.StartsWith("World"), "Instance StartsWith (false)");
    assert_true(str5.EndsWith("World"), "Instance EndsWith (true)");
    assert_true(!str5.EndsWith("Hello"), "Instance EndsWith (false)");
    assert_equal("HiHiHi", str5.Repeat(3), "Instance Repeat (Hi, 3)");
    assert_equal("", str5.Repeat(0), "Instance Repeat (0)");
    
    MyString str6("racecar");
    assert_true(str6.IsPalindrome(), "Instance IsPalindrome (racecar)");
    
    MyString str7("hello");
    assert_true(!str7.IsPalindrome(), "Instance IsPalindrome (hello)");
    
    std::cout << "✓ String operations tests passed\n\n";
}

void test_split_and_join_operations() {
    std::cout << "Testing split and join operations...\n";
    
    // Split operations
    MyString testStr("word1,word2,word3");
    std::vector<std::string> words = testStr.Split(",");
    assert_true(words.size() == 3, "Split vector size");
    assert_equal("word1", words[0], "Split first element");
    assert_equal("word2", words[1], "Split second element");
    assert_equal("word3", words[2], "Split third element");
    
    // Static split
    std::vector<std::string> staticWords = MyString::Split("a,b,c", ",");
    assert_true(staticWords.size() == 3, "Static split size");
    
    // Join operations
    std::vector<std::string> joinVec = {"A", "B", "C"};
    assert_equal("A,B,C", MyString::JoinString(joinVec, ","), "Join vector");
    
    std::string joinArr[] = {"X", "Y", "Z"};
    assert_equal("X|Y|Z", MyString::JoinString(joinArr, 3, "|"), "Join array");
    
    // Edge cases
    std::vector<std::string> emptyVec;
    assert_equal("", MyString::JoinString(emptyVec, ","), "Join empty vector");
    assert_equal("", MyString::JoinString(joinArr, 0, ","), "Join zero length");
    
    std::cout << "✓ Split and join operations tests passed\n\n";
}

void test_trim_operations() {
    std::cout << "Testing trim operations...\n";
    
    // Static trim operations
    assert_equal("Hello", MyString::TrimLeft("   Hello"), "TrimLeft static");
    assert_equal("Hello", MyString::TrimRight("Hello   "), "TrimRight static");
    assert_equal("Hello", MyString::Trim("   Hello   "), "Trim static");
    assert_equal("", MyString::TrimLeft(""), "TrimLeft empty");
    assert_equal("", MyString::TrimRight(""), "TrimRight empty");
    assert_equal("", MyString::Trim(""), "Trim empty");
    
    // Instance trim operations
    MyString str1("   Hello");
    str1.TrimLeft();
    assert_equal("Hello", str1.GetValue(), "TrimLeft instance");
    
    MyString str2("Hello   ");
    str2.TrimRight();
    assert_equal("Hello", str2.GetValue(), "TrimRight instance");
    
    MyString str3("   Hello World   ");
    str3.Trim();
    assert_equal("Hello World", str3.GetValue(), "Trim instance");
    
    std::cout << "✓ Trim operations tests passed\n\n";
}

void test_word_counting() {
    std::cout << "Testing word counting...\n";
    
    // Static word counting
    assert_true(MyString::CountWords("Hello World") == 2, "CountWords (2 words)");
    assert_true(MyString::CountWords("Hello") == 1, "CountWords (1 word)");
    assert_true(MyString::CountWords("Hello   World") == 2, "CountWords with extra spaces");
    assert_true(MyString::CountWords("   Hello World   ") == 2, "CountWords with leading/trailing spaces");
    
    // Instance word counting
    MyString str1("Hello World Test");
    assert_true(str1.CountWords() == 3, "Instance CountWords (3 words)");
    
    MyString str2("Single");
    assert_true(str2.CountWords() == 1, "Instance CountWords (1 word)");
    
    std::cout << "✓ Word counting tests passed\n\n";
}

int main() {
    std::cout << "=== MyString Unit Tests ===\n\n";
    
    test_constructors_and_operators();
    test_length_and_stream();
    test_error_handling();
    test_case_operations();
    test_counting_operations();
    test_string_operations();
    test_split_and_join_operations();
    test_trim_operations();
    test_word_counting();
    
    std::cout << "🎉 All MyString tests passed successfully!\n";
    return 0;
}
