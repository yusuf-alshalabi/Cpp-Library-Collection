//ProgrammingAdvices.com
//Mohammed Abu-Hadhoud

#pragma once
#include <iostream>
#include <string>
#include "Date.h"

class Util
{

public:
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
            //Capital/Samll/Digits only  
            CharType = (enCharType)RandomNumber(1, 3);

        }

        switch (CharType)
        {

        case enCharType::SmallLetter:
        {
            return char(RandomNumber(97, 122));
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumber(65, 90));
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumber(33, 47));
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
        }
    default:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        }
    }

    static  std::string GenerateWord(enCharType CharType, short Length)

    {
        std::string Word;

        for (int i = 1; i <= Length; i++)

        {

            Word += GetRandomCharacter(CharType);

        }
        return Word;
    }

    static std::string  GenerateKey(enCharType CharType = CapitalLetter)
    {

        std::string Key = "";


        Key = GenerateWord(CharType, 4) + "-";
        Key += GenerateWord(CharType, 4) + "-";
        Key += GenerateWord(CharType, 4) + "-";
        Key += GenerateWord(CharType, 4);


        return Key;
    }

    static void PrintKeys(short NumberOfKeys, enCharType CharType)
    {

        for (int i = 1; i <= NumberOfKeys; i++)

        {
            std::cout << "Key [" << i << "] : ";
            std::cout << GenerateKey(CharType) << std:: endl;
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

    template<typename T>
    static void Swap(T& A, T& B)
    {
        T Temp = A;
        A = B;
        B = Temp;
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

        for (int i = 0; i < NumberOfTabs; i++)
        {
            t += "\t";
        }
        return t;

    }

    static std::string  EncryptText(std::string Text, short EncryptionKey)
    {

        for (size_t i = 0; i < Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);

        }

        return Text;

    }

    static std::string  DecryptText(std::string Text, short EncryptionKey)
    {

        for (size_t i = 0; i < Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);

        }
        return Text;

    }

};