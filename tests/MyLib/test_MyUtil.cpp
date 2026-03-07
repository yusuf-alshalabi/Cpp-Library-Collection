#include <iostream>
#include <cassert>
#include "../../include/MyLib/MyUtil.h"

// Test data constants for better readability and maintainability
namespace UtilTestData {
    const int MIN_RANDOM = 1;
    const int MAX_RANDOM = 100;
    const int WORD_LENGTH = 5;
    const int KEY_PARTS = 4;
    const int ARRAY_SIZE = 10;
    const int TEST_KEYS = 3;
    const short ENCRYPTION_KEY = 3;
    const short NEGATIVE_KEY = -2;
    const short SPECIAL_KEY = 10;
}

using namespace MyLib;

void test_myutil_random_functions() {
    std::cout << "Testing MyUtil random functions...\n";
    
    // Test Srand and RandomNumber
    MyUtil::Srand();
    int randNum = MyUtil::RandomNumber(UtilTestData::MIN_RANDOM, UtilTestData::MAX_RANDOM);
    assert(randNum >= UtilTestData::MIN_RANDOM && randNum <= UtilTestData::MAX_RANDOM);
    std::cout << "✓ RandomNumber test passed\n";
    
    // Test GetRandomCharacter - ALL enum types
    char capitalChar = MyUtil::GetRandomCharacter(MyUtil::CapitalLetter);
    assert(capitalChar >= 'A' && capitalChar <= 'Z');
    std::cout << "✓ GetRandomCharacter (CapitalLetter) test passed\n";
    
    char smallChar = MyUtil::GetRandomCharacter(MyUtil::SmallLetter);
    assert(smallChar >= 'a' && smallChar <= 'z');
    std::cout << "✓ GetRandomCharacter (SmallLetter) test passed\n";
    
    char digitChar = MyUtil::GetRandomCharacter(MyUtil::Digit);
    assert(digitChar >= '0' && digitChar <= '9');
    std::cout << "✓ GetRandomCharacter (Digit) test passed\n";
    
    char specialChar = MyUtil::GetRandomCharacter(MyUtil::SpecialCharacter);
    assert(specialChar >= '!' && specialChar <= '/');
    std::cout << "✓ GetRandomCharacter (SpecialCharacter) test passed\n";
    
    // Test MixChars (should return one of Capital, Small, or Digit)
    char mixChar = MyUtil::GetRandomCharacter(MyUtil::MixChars);
    assert((mixChar >= 'A' && mixChar <= 'Z') || 
           (mixChar >= 'a' && mixChar <= 'z') || 
           (mixChar >= '0' && mixChar <= '9'));
    std::cout << "✓ GetRandomCharacter (MixChars) test passed\n";
    
    std::cout << "✓ MyUtil random functions tests passed\n\n";
}

void test_myutil_generation_functions() {
    std::cout << "Testing MyUtil generation functions...\n";
    
    // Test GenerateWord
    std::string word = MyUtil::GenerateWord(MyUtil::CapitalLetter, UtilTestData::WORD_LENGTH);
    assert(word.length() == UtilTestData::WORD_LENGTH);
    std::cout << "✓ GenerateWord test passed: " << word << "\n";
    
    // Test GenerateKey
    std::string key = MyUtil::GenerateKey(MyUtil::CapitalLetter);
    assert(key.length() == 19); // 4*4 + 3 dashes = 19
    assert(key[4] == '-' && key[9] == '-' && key[14] == '-');
    std::cout << "✓ GenerateKey test passed: " << key << "\n";
    
    // Test GenerateKeys (this method prints to console, so we can't easily test output)
    // But we can at least verify it doesn't crash
    std::cout << "Testing GenerateKeys output:\n";
    MyUtil::GenerateKeys(UtilTestData::TEST_KEYS, MyUtil::CapitalLetter);
    std::cout << "✓ GenerateKeys test passed (no crash)\n";
    
    std::cout << "✓ MyUtil generation functions tests passed\n\n";
}

void test_myutil_swap_functions() {
    std::cout << "Testing MyUtil swap functions...\n";
    
    // Test int swap
    int a = 5, b = 10;
    MyUtil::Swap(a, b);
    assert(a == 10 && b == 5);
    std::cout << "✓ Swap (int) test passed\n";
    
    // Test double swap
    double d1 = 3.14, d2 = 2.71;
    MyUtil::Swap(d1, d2);
    assert(d1 == 2.71 && d2 == 3.14);
    std::cout << "✓ Swap (double) test passed\n";
    
    // Test string swap
    std::string str1 = "Hello", str2 = "World";
    MyUtil::Swap(str1, str2);
    assert(str1 == "World" && str2 == "Hello");
    std::cout << "✓ Swap (string) test passed\n";
    
    // Test bool swap
    bool flag1 = true, flag2 = false;
    MyUtil::Swap(flag1, flag2);
    assert(flag1 == false && flag2 == true);
    std::cout << "✓ Swap (bool) test passed\n";
    
    // Test char swap
    char c1 = 'A', c2 = 'B';
    MyUtil::Swap(c1, c2);
    assert(c1 == 'B' && c2 == 'A');
    std::cout << "✓ Swap (char) test passed\n";
    
    // Test MyDate swap
    MyDate date1("25/12/2023");
    MyDate date2("01/01/2024");
    MyUtil::Swap(date1, date2);
    assert(date1.DateToString() == "01/01/2024");
    assert(date2.DateToString() == "25/12/2023");
    std::cout << "✓ Swap (MyDate) test passed\n";
    
    std::cout << "✓ MyUtil swap functions tests passed\n\n";
}

void test_myutil_array_functions() {
    std::cout << "Testing MyUtil array functions...\n";
    
    // Test FillArrayWithRandomNumbers
    int arr[100];
    MyUtil::FillArrayWithRandomNumbers(arr, UtilTestData::ARRAY_SIZE, UtilTestData::MIN_RANDOM, 50);
    for (int i = 0; i < UtilTestData::ARRAY_SIZE; i++) {
        assert(arr[i] >= UtilTestData::MIN_RANDOM && arr[i] <= 50);
    }
    std::cout << "✓ FillArrayWithRandomNumbers test passed\n";
    
    // Test FillArrayWithRandomWords
    std::string words[100];
    MyUtil::FillArrayWithRandomWords(words, 5, MyUtil::CapitalLetter, UtilTestData::WORD_LENGTH);
    for (int i = 0; i < 5; i++) {
        assert(words[i].length() == UtilTestData::WORD_LENGTH);
    }
    std::cout << "✓ FillArrayWithRandomWords test passed\n";
    
    // Test FillArrayWithRandomKeys
    std::string keys[100];
    MyUtil::FillArrayWithRandomKeys(keys, UtilTestData::TEST_KEYS, MyUtil::CapitalLetter);
    for (int i = 0; i < UtilTestData::TEST_KEYS; i++) {
        assert(keys[i].length() == 19);
    }
    std::cout << "✓ FillArrayWithRandomKeys test passed\n";
    
    // Test ShuffleArray (int)
    int testArr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    MyUtil::ShuffleArray(testArr, 10);
    // Check that array is shuffled (not all elements in original order)
    bool isShuffled = false;
    for (int i = 0; i < 10; i++) {
        if (testArr[i] != i + 1) {
            isShuffled = true;
            break;
        }
    }
    assert(isShuffled);
    std::cout << "✓ ShuffleArray (int) test passed\n";
    
    // Test ShuffleArray (string)
    std::string stringArr[5] = {"A", "B", "C", "D", "E"};
    MyUtil::ShuffleArray(stringArr, 5);
    // Check that array is shuffled
    bool isStringShuffled = false;
    for (int i = 0; i < 5; i++) {
        if (stringArr[i] != std::string(1, 'A' + i)) {
            isStringShuffled = true;
            break;
        }
    }
    assert(isStringShuffled);
    std::cout << "✓ ShuffleArray (string) test passed\n";
    
    std::cout << "✓ MyUtil array functions tests passed\n\n";
}

void test_myutil_encryption_functions() {
    std::cout << "Testing MyUtil encryption functions...\n";
    
    // Test basic Encrypt/Decrypt
    std::string originalText = "Hello World";
    std::string encrypted = MyUtil::EncryptText(originalText, UtilTestData::ENCRYPTION_KEY);
    std::string decrypted = MyUtil::DecryptText(encrypted, UtilTestData::ENCRYPTION_KEY);
    assert(originalText == decrypted);
    std::cout << "✓ Basic Encrypt/Decrypt test passed\n";
    
    // Test that encryption changes text
    assert(encrypted != originalText);
    std::cout << "✓ Encryption changes text test passed\n";
    
    // Test empty string
    std::string emptyText = "";
    std::string encryptedEmpty = MyUtil::EncryptText(emptyText, 5);
    std::string decryptedEmpty = MyUtil::DecryptText(encryptedEmpty, 5);
    assert(emptyText == decryptedEmpty);
    std::cout << "✓ Empty string encryption test passed\n";
    
    // Test negative encryption key
    std::string originalText2 = "Test";
    std::string encryptedNeg = MyUtil::EncryptText(originalText2, UtilTestData::NEGATIVE_KEY);
    std::string decryptedNeg = MyUtil::DecryptText(encryptedNeg, UtilTestData::NEGATIVE_KEY);
    assert(originalText2 == decryptedNeg);
    std::cout << "✓ Negative encryption key test passed\n";
    
    // Test special characters
    std::string specialText = "Hello@#$%";
    std::string encryptedSpecial = MyUtil::EncryptText(specialText, UtilTestData::SPECIAL_KEY);
    std::string decryptedSpecial = MyUtil::DecryptText(encryptedSpecial, UtilTestData::SPECIAL_KEY);
    assert(specialText == decryptedSpecial);
    std::cout << "✓ Special characters encryption test passed\n";
    
    std::cout << "✓ MyUtil encryption functions tests passed\n\n";
}

void test_myutil_formatting_functions() {
    std::cout << "Testing MyUtil formatting functions...\n";
    
    // Test Tabs function with edge cases
    std::string tabs1 = MyUtil::Tabs(1);
    assert(tabs1.length() == 0); // Should have 0 tabs for 1
    std::cout << "✓ Tabs(1) test passed\n";
    
    std::string tabs2 = MyUtil::Tabs(2);
    assert(tabs2.length() == 1); // Should have 1 tab for 2
    std::cout << "✓ Tabs(2) test passed\n";
    
    std::string tabs5 = MyUtil::Tabs(5);
    assert(tabs5.length() == 4); // Should have 4 tabs for 5
    std::cout << "✓ Tabs(5) test passed\n";
    
    std::string tabs10 = MyUtil::Tabs(10);
    assert(tabs10.length() == 9); // Should have 9 tabs for 10
    std::cout << "✓ Tabs(10) test passed\n";
    
    // Test that tabs are actually tab characters
    for (char c : tabs5) {
        assert(c == '\t');
    }
    std::cout << "✓ Tabs character validation test passed\n";
    
    std::cout << "✓ MyUtil formatting functions tests passed\n\n";
}

int main() {
    std::cout << "=== MyUtil Unit Tests ===\n\n";
    
    test_myutil_random_functions();
    test_myutil_generation_functions();
    test_myutil_swap_functions();
    test_myutil_array_functions();
    test_myutil_encryption_functions();
    test_myutil_formatting_functions();
    
    std::cout << "🎉 All MyUtil tests passed successfully!\n";
    return 0;
}
