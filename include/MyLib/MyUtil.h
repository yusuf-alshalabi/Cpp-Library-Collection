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

    };
}
