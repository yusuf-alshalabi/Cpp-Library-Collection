#include <iostream>

#include "../Lib/String.h"
#include "../Lib/Date.h"
#include "../Lib/Period.h"
#include "../Lib/Util.h"
#include "../Lib/InputValidate.h"

using namespace Core;

void TestInputValidate()
{
    std::cout << "========================================\n";
    std::cout << "   Testing Core::InputValidate Class    \n";
    std::cout << "========================================\n\n";

    // 1. Test IsNumberBetween
    std::cout << "--- 1. Testing IsNumberBetween ---\n";
    std::cout << "Is 15 between 10 and 20? " << (InputValidate::IsNumberBetween(15, 10, 20) ? "YES" : "NO") << "\n";
    std::cout << "Is 5.5 between 1.0 and 5.0? " << (InputValidate::IsNumberBetween(5.5, 1.0, 5.0) ? "YES" : "NO") << "\n\n";

    // 2. Test IsDateBetween & IsValidDate
    std::cout << "--- 2. Testing Date Validations ---\n";
    Date d1(10, 5, 2024);
    Date d2(1, 1, 2024);
    Date d3(31, 12, 2024);
    std::cout << "Is " << d1.ToString() << " valid? " << (InputValidate::IsValidDate(d1) ? "YES" : "NO") << "\n";
    std::cout << "Is " << d1.ToString() << " between " << d2.ToString() << " and " << d3.ToString() << "? "
        << (InputValidate::IsDateBetween(d1, d2, d3) ? "YES" : "NO") << "\n\n";

    // 3. Test ReadNumber
    std::cout << "--- 3. Testing ReadNumber ---\n";
    std::cout << ">> Try entering invalid input (e.g. 'abc') first, then a valid integer.\n";
    int intVal = InputValidate::ReadNumber<int>("Enter an integer:", "Invalid integer! Try again:");
    std::cout << "Result: " << intVal << "\n\n";

    std::cout << ">> Enter a double value:\n";
    double dblVal = InputValidate::ReadNumber<double>("Enter a double:", "Invalid double! Try again:");
    std::cout << "Result: " << dblVal << "\n\n";

    // 4. Test ReadPositiveNumber
    std::cout << "--- 4. Testing ReadPositiveNumber ---\n";
    std::cout << ">> Try entering 0 or a negative number first.\n";
    int posVal = InputValidate::ReadPositiveNumber<int>("Enter positive age:", "Age must be greater than 0!");
    std::cout << "Result: " << posVal << "\n\n";

    // 5. Test ReadNumberBetween
    std::cout << "--- 5. Testing ReadNumberBetween ---\n";
    std::cout << ">> Try entering a number outside [1 - 10] first.\n";
    int rangeVal = InputValidate::ReadNumberBetween<int>(1, 10, "Enter rating (1-10):", "Out of range! Must be 1 to 10.");
    std::cout << "Result: " << rangeVal << "\n\n";

    // 6. Test ReadCharacter
    std::cout << "--- 6. Testing ReadCharacter ---\n";
    char ch = InputValidate::ReadCharacter("Enter any character:");
    std::cout << "Result: " << ch << "\n\n";

    // 7. Test ReadString
    std::cout << "--- 7. Testing ReadString ---\n";
    std::cout << ">> Try hitting Enter directly to test empty input validation.\n";
    std::string str = InputValidate::ReadString("Enter your full name:", "Name cannot be empty!");
    std::cout << "Result: " << str << "\n\n";

    // 8. Test ReadYesNoOption
    std::cout << "--- 8. Testing ReadYesNoOption ---\n";
    bool choice = InputValidate::ReadYesNoOption("Do you want to save changes?");
    std::cout << "Result: " << (choice ? "User selected YES" : "User selected NO") << "\n\n";

    // 9. Test ReadDate
    std::cout << "--- 9. Testing ReadDate ---\n";
    std::cout << ">> Try entering an invalid date like '31/02/2026' or 'abc' first.\n";
    Date dateVal = InputValidate::ReadDate("Enter your birthdate (DD/MM/YYYY):", "Invalid date! Try again:");
    std::cout << "Result: " << dateVal.ToString() << "\n\n";

    std::cout << "========================================\n";
    std::cout << "      All Tests Completed Successfully! \n";
    std::cout << "========================================\n";
}

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

	int age = InputValidate::ReadNumberBetween(18, 60);

	std::cout << "Age = " << age << '\n';

	return 0;
}
