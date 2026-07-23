
#include <iostream>

#include "../Lib/String.h"
#include "../Lib/Date.h"
#include "../Lib/Period.h"
#include "../Lib/Util.h"
#include "../Lib/InputValidate.h"
#include "../Tests/TestRunner.h"


int main()
{
    Util::Srand();

    std::cout << "\n==================================================\n";
    std::cout << "         STARTING ALL CORE LIBRARY TESTS          \n";
    std::cout << "==================================================\n\n";

    TestRunner::TestString();

    std::cout << "\nPress Enter to continue to Date tests...";
    std::cin.get();

    TestRunner::TestDate();

    std::cout << "\nPress Enter to continue to Period tests...";
    std::cin.get();

    TestRunner::TestPeriod();

    std::cout << "\nPress Enter to continue to Util tests...";
    std::cin.get();

    TestRunner::TestUtil();

    std::cout << "\nPress Enter to continue to Interactive InputValidate tests...";
    std::cin.get();

    TestRunner::TestInputValidate();

    std::cout << "\n==================================================\n";
    std::cout << "         ALL SUITES EXECUTED SUCCESSFULLY!        \n";
    std::cout << "==================================================\n";

    return 0;
}