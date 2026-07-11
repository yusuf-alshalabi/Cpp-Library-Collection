#include <iostream>

#include "../Lib/String.h"
#include "../Lib/Date.h"
#include "../Lib/Period.h"
#include "../Lib/Util.h"
#include "../Lib/InputValidate.h"

int main()
{
    Util::Srand();

    std::cout << "========== String ==========\n\n";

    String text("   hello world from cpp library   ");

    std::cout << "Original: [" << text.Value << "]\n";

    text.Trim();
    std::cout << "Trim: " << text.Value << '\n';

    text.UpperFirstLetterOfEachWord();
    std::cout << "Title Case: " << text.Value << '\n';

    std::cout << "Words Count: " << text.CountWords() << '\n';
    std::cout << "Vowels Count: " << text.CountVowels() << '\n';

    std::cout << "\n========== Date ==========\n\n";

    Date today;
    Date future(1, 1, 2027);

    std::cout << "Today: ";
    today.Print();

    std::cout << "Future Date: ";
    future.Print();

    std::cout << "Difference in Days: "
        << today.GetDifferenceInDays(future)
        << '\n';

    today.AddOneDay();

    std::cout << "Tomorrow: ";
    today.Print();

    std::cout << "\n========== Period ==========\n\n";

    Period period1(Date(1, 7, 2026), Date(15, 7, 2026));
    Period period2(Date(10, 7, 2026), Date(20, 7, 2026));

    period1.Print();
    std::cout << '\n';

    period2.Print();
    std::cout << '\n';

    std::cout << "Overlap: "
        << (period1.IsOverLapWith(period2) ? "Yes" : "No")
        << '\n';

    std::cout << "\n========== Util ==========\n\n";

    std::cout << "Random Number: "
        << Util::RandomNumber(1, 100)
        << '\n';

    std::cout << "Random Word: "
        << Util::GenerateWord(Util::MixChars, 8)
        << '\n';

    std::cout << "Random Key: "
        << Util::GenerateKey()
        << '\n';

    std::string encrypted = Util::EncryptText("Programming", 5);

    std::cout << "Encrypted: " << encrypted << '\n';

    std::cout << "Decrypted: "
        << Util::DecryptText(encrypted, 5)
        << '\n';

    std::cout << "\n========== InputValidate ==========\n\n";

    std::cout << "Enter your age (18 - 60): ";

    int age = InputValidate::ReadIntNumberBetween(18, 60);

    std::cout << "Age = " << age << '\n';

    return 0;
}