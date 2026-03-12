#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MyLib/MyDate.h"

namespace MyLib {
    //ProgrammingAdvices.com
    //Mohammed Abu-Hadhoud
    class MyUtil
    {

    public:
        // ASCII character ranges for better readability
        static constexpr int ASCII_LOWERCASE_A = 97;
        static constexpr int ASCII_LOWERCASE_Z = 122;
        static constexpr int ASCII_UPPERCASE_A = 65;
        static constexpr int ASCII_UPPERCASE_Z = 90;
        static constexpr int ASCII_DIGIT_0 = 48;
        static constexpr int ASCII_DIGIT_9 = 57;
        static constexpr int ASCII_SPECIAL_START = 33;
        static constexpr int ASCII_SPECIAL_END = 47;

        enum enCharType {
            SmallLetter = 1, CapitalLetter = 2,
            Digit = 3, MixChars = 4, SpecialCharacter = 5
        };

        static void  Srand()
        {
            //Seeds the random number generator in C++, called only once
            srand((unsigned)time(NULL));
        }

        static  int RandomNumber(int From, int To)
        {
            //Function to generate a random number
            int randNum = rand() % (To - From + 1) + From;
            return randNum;
        }

        static char GetRandomCharacter(enCharType CharType)
        {

            //updated this method to accept mixchars
            if (CharType == MixChars)
            {
                //Capital/Small/Digits only
                CharType = (enCharType)RandomNumber(1, 3);

            }

            switch (CharType)
            {

            case enCharType::SmallLetter:
            {
                return char(RandomNumber(ASCII_LOWERCASE_A, ASCII_LOWERCASE_Z));
                break;
            }
            case enCharType::CapitalLetter:
            {
                return char(RandomNumber(ASCII_UPPERCASE_A, ASCII_UPPERCASE_Z));
                break;
            }
            case enCharType::SpecialCharacter:
            {
                return char(RandomNumber(ASCII_SPECIAL_START, ASCII_SPECIAL_END));
                break;
            }
            case enCharType::Digit:
            {
                return char(RandomNumber(ASCII_DIGIT_0, ASCII_DIGIT_9));
                break;
            }
            default:
            {
                return char(RandomNumber(ASCII_UPPERCASE_A, ASCII_UPPERCASE_Z));
                break;
            }
            }
        }

        static  std::string GenerateWord(enCharType CharType, short Length)

        {
            std::string Word;

            for (int i = 1; i <= Length; i++)

            {

                Word = Word + GetRandomCharacter(CharType);

            }
            return Word;
        }

        static std::string  GenerateKey(enCharType CharType = CapitalLetter)
        {
            std::string Key = GenerateWord(CharType, 4);
            Key += "-" + GenerateWord(CharType, 4);
            Key += "-" + GenerateWord(CharType, 4);
            Key += "-" + GenerateWord(CharType, 4);
            return Key;
        }

        static void GenerateKeys(short NumberOfKeys, enCharType CharType)
        {

            for (int i = 1; i <= NumberOfKeys; i++)

            {
                std::cout << "Key [" << i << "] : ";
                std::cout << GenerateKey(CharType) << std::endl;
            }

        }

        static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
        {
            for (int i = 0; i < arrLength; i++)
                arr[i] = RandomNumber(From, To);
        }

        static void FillArrayWithRandomWords(std::string arr[100], int arrLength, enCharType CharType, short Wordlength)
        {
            for (int i = 0; i < arrLength; i++)
                arr[i] = GenerateWord(CharType, Wordlength);

        }

        static void FillArrayWithRandomKeys(std::string arr[100], int arrLength, enCharType CharType)
        {
            for (int i = 0; i < arrLength; i++)
               arr[i] = GenerateKey(CharType);
        }

        // Template-based swap function to eliminate code duplication
        template<typename T>
        static void Swap(T& A, T& B)
        {
            T Temp = A;
            A = B;
            B = Temp;
        }

        // Specialized swap for MyDate to use the class method
        static void Swap(MyDate& A, MyDate& B)
        {
            MyDate::SwapDates(A, B);
        }

        static  void ShuffleArray(int arr[100], int arrLength)
        {

            for (int i = 0; i < arrLength; i++)
            {
                Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
            }

        }

        static  void ShuffleArray(std::string arr[100], int arrLength)
        {

            for (int i = 0; i < arrLength; i++)
            {
                Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
            }

        }

        static std::string  Tabs(short NumberOfTabs)
        {
            std::string t = "";

            for (int i = 1; i < NumberOfTabs; i++)
            {
                t += "\t";
            }
            return t;
        }

        static std::string  EncryptText(std::string Text, short EncryptionKey)
        {

            for (int i = 0; i < Text.length(); i++)
            {

                Text[i] = char((int)Text[i] + EncryptionKey);

            }

            return Text;

        }

        static std::string  DecryptText(std::string Text, short EncryptionKey)
        {

            for (int i = 0; i < Text.length(); i++)
            {

                Text[i] = char((int)Text[i] - EncryptionKey);

            }
            return Text;

        }

    };
}
