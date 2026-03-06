#include <iostream>
#include <cassert>
#include "../../include/MyLib/MyUtil.h"

using namespace MyLib;

void test_myutil_random_functions() {
    std::cout << "Testing MyUtil random functions...\n";
    
    // Test Srand and RandomNumber
    clsUtil::Srand();
    int randNum = clsUtil::RandomNumber(1, 100);
    assert(randNum >= 1 && randNum <= 100);
    std::cout << "✓ RandomNumber test passed\n";
    
    // Test GetRandomCharacter - ALL enum types
    char capitalChar = clsUtil::GetRandomCharacter(clsUtil::CapitalLetter);
    assert(capitalChar >= 'A' && capitalChar <= 'Z');
    std::cout << "✓ GetRandomCharacter (CapitalLetter) test passed\n";
    
    char smallChar = clsUtil::GetRandomCharacter(clsUtil::SamallLetter);
    assert(smallChar >= 'a' && smallChar <= 'z');
    std::cout << "✓ GetRandomCharacter (SamallLetter) test passed\n";
    
    char digitChar = clsUtil::GetRandomCharacter(clsUtil::Digit);
    assert(digitChar >= '0' && digitChar <= '9');
    std::cout << "✓ GetRandomCharacter (Digit) test passed\n";
    
    char specialChar = clsUtil::GetRandomCharacter(clsUtil::SpecialCharacter);
    assert(specialChar >= '!' && specialChar <= '/');
    std::cout << "✓ GetRandomCharacter (SpecialCharacter) test passed\n";
    
    // Test MixChars (should return one of Capital, Small, or Digit)
    char mixChar = clsUtil::GetRandomCharacter(clsUtil::MixChars);
    assert((mixChar >= 'A' && mixChar <= 'Z') || 
           (mixChar >= 'a' && mixChar <= 'z') || 
           (mixChar >= '0' && mixChar <= '9'));
    std::cout << "✓ GetRandomCharacter (MixChars) test passed\n";
    
    std::cout << "✓ MyUtil random functions tests passed\n\n";
}

void test_myutil_generation_functions() {
    std::cout << "Testing MyUtil generation functions...\n";
    
    // Test GenerateWord
    std::string word = clsUtil::GenerateWord(clsUtil::CapitalLetter, 5);
    assert(word.length() == 5);
    std::cout << "✓ GenerateWord test passed: " << word << "\n";
    
    // Test GenerateKey
    std::string key = clsUtil::GenerateKey(clsUtil::CapitalLetter);
    assert(key.length() == 19); // 4*4 + 3 dashes = 19
    assert(key[4] == '-' && key[9] == '-' && key[14] == '-');
    std::cout << "✓ GenerateKey test passed: " << key << "\n";
    
    // Test GenerateKeys (this method prints to console, so we can't easily test output)
    // But we can at least verify it doesn't crash
    std::cout << "Testing GenerateKeys output:\n";
    clsUtil::GenerateKeys(2, clsUtil::CapitalLetter);
    std::cout << "✓ GenerateKeys test passed (no crash)\n";
    
    std::cout << "✓ MyUtil generation functions tests passed\n\n";
}

void test_myutil_swap_functions() {
    std::cout << "Testing MyUtil swap functions...\n";
    
    // Test int swap
    int a = 5, b = 10;
    clsUtil::Swap(a, b);
    assert(a == 10 && b == 5);
    std::cout << "✓ Swap (int) test passed\n";
    
    // Test double swap
    double d1 = 3.14, d2 = 2.71;
    clsUtil::Swap(d1, d2);
    assert(d1 == 2.71 && d2 == 3.14);
    std::cout << "✓ Swap (double) test passed\n";
    
    // Test string swap
    std::string str1 = "Hello", str2 = "World";
    clsUtil::Swap(str1, str2);
    assert(str1 == "World" && str2 == "Hello");
    std::cout << "✓ Swap (string) test passed\n";
    
    // Test bool swap
    bool flag1 = true, flag2 = false;
    clsUtil::Swap(flag1, flag2);
    assert(flag1 == false && flag2 == true);
    std::cout << "✓ Swap (bool) test passed\n";
    
    // Test char swap
    char c1 = 'A', c2 = 'B';
    clsUtil::Swap(c1, c2);
    assert(c1 == 'B' && c2 == 'A');
    std::cout << "✓ Swap (char) test passed\n";
    
    // Test MyDate swap
    MyDate date1("25/12/2023");
    MyDate date2("01/01/2024");
    clsUtil::Swap(date1, date2);
    assert(date1.ToString() == "01/01/2024");
    assert(date2.ToString() == "25/12/2023");
    std::cout << "✓ Swap (MyDate) test passed\n";
    
    std::cout << "✓ MyUtil swap functions tests passed\n\n";
}

void test_myutil_array_functions() {
    std::cout << "Testing MyUtil array functions...\n";
    
    // Test FillArrayWithRandomNumbers
    int arr[100];
    clsUtil::FillArrayWithRandomNumbers(arr, 10, 1, 50);
    for (int i = 0; i < 10; i++) {
        assert(arr[i] >= 1 && arr[i] <= 50);
    }
    std::cout << "✓ FillArrayWithRandomNumbers test passed\n";
    
    // Test FillArrayWithRandomWords
    std::string words[100];
    clsUtil::FillArrayWithRandomWords(words, 5, clsUtil::CapitalLetter, 3);
    for (int i = 0; i < 5; i++) {
        assert(words[i].length() == 3);
    }
    std::cout << "✓ FillArrayWithRandomWords test passed\n";
    
    // Test FillArrayWithRandomKeys
    std::string keys[100];
    clsUtil::FillArrayWithRandomKeys(keys, 3, clsUtil::CapitalLetter);
    for (int i = 0; i < 3; i++) {
        assert(keys[i].length() == 19);
    }
    std::cout << "✓ FillArrayWithRandomKeys test passed\n";
    
    // Test ShuffleArray (int)
    int testArr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    clsUtil::ShuffleArray(testArr, 10);
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
    clsUtil::ShuffleArray(stringArr, 5);
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
    short encryptionKey = 3;
    std::string encrypted = clsUtil::EncryptText(originalText, encryptionKey);
    std::string decrypted = clsUtil::DecryptText(encrypted, encryptionKey);
    assert(originalText == decrypted);
    std::cout << "✓ Basic Encrypt/Decrypt test passed\n";
    
    // Test that encryption changes the text
    assert(encrypted != originalText);
    std::cout << "✓ Encryption changes text test passed\n";
    
    // Test empty string
    std::string emptyText = "";
    std::string encryptedEmpty = clsUtil::EncryptText(emptyText, 5);
    std::string decryptedEmpty = clsUtil::DecryptText(encryptedEmpty, 5);
    assert(emptyText == decryptedEmpty);
    std::cout << "✓ Empty string encryption test passed\n";
    
    // Test negative encryption key
    std::string originalText2 = "Test";
    short negativeKey = -2;
    std::string encryptedNeg = clsUtil::EncryptText(originalText2, negativeKey);
    std::string decryptedNeg = clsUtil::DecryptText(encryptedNeg, negativeKey);
    assert(originalText2 == decryptedNeg);
    std::cout << "✓ Negative encryption key test passed\n";
    
    // Test special characters
    std::string specialText = "Hello@#$%";
    short specialKey = 10;
    std::string encryptedSpecial = clsUtil::EncryptText(specialText, specialKey);
    std::string decryptedSpecial = clsUtil::DecryptText(encryptedSpecial, specialKey);
    assert(specialText == decryptedSpecial);
    std::cout << "✓ Special characters encryption test passed\n";
    
    std::cout << "✓ MyUtil encryption functions tests passed\n\n";
}

void test_myutil_formatting_functions() {
    std::cout << "Testing MyUtil formatting functions...\n";
    
    // Test Tabs function
    std::string tabs = clsUtil::Tabs(3);
    assert(tabs.length() == 2); // Should have 2 tabs
    std::cout << "✓ Tabs test passed\n";
    
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
