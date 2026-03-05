#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MyDate.h"

namespace MyLib {
    //ProgrammingAdvices.com
    //Mohammed Abu-Hadhoud
    class clsUtil
    {

    public:
        enum enCharType {
            SamallLetter = 1, CapitalLetter = 2,
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
                //Capital/Samall/Digits only
                CharType = (enCharType)RandomNumber(1, 3);

            }

            switch (CharType)
            {

            case enCharType::SamallLetter:
            {
                return char(RandomNumber(97, 122));
                break;
            }
            case enCharType::CapitalLetter:
            {
                return char(RandomNumber(65, 90));
                break;
            }
            case enCharType::SpecialCharacter:
            {
                return char(RandomNumber(33, 47));
                break;
            }
            case enCharType::Digit:
            {
                return char(RandomNumber(48, 57));
                break;
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

                Word = Word + GetRandomCharacter(CharType);

            }
            return Word;
        }

    };
}
