#include <iostream>

#include "../Lib/String.h"
#include "../Lib/Date.h"
#include "../Lib/Period.h"
#include "../Lib/Util.h"
#include "../Lib/InputValidate.h"

using namespace Core;

void TestString()
{
    std::cout << "========================================\n";
    std::cout << "      Testing Core::String Class        \n";
    std::cout << "========================================\n\n";

    // 1. Constructors & Assignment Operators
    std::cout << "--- 1. Testing Constructors & Operators ---\n";
    String s1("Hello World");
    String s2 = ", C++ 2026!";
    String s3 = s1 + s2;

    std::cout << "s1: " << s1 << "\n";
    std::cout << "s2: " << s2 << "\n";
    std::cout << "s3 (s1 + s2): " << s3 << "\n";

    s1 += " Programming";
    std::cout << "s1 after += : " << s1 << "\n";
    std::cout << "s1[0]: " << s1[0] << ", s1.At(4): " << s1.At(4) << "\n";
    std::cout << "Is s1 == s2? " << (s1 == s2 ? "YES" : "NO") << "\n\n";

    // 2. Case Conversion & Formatting
    std::cout << "--- 2. Testing Case Conversions ---\n";
    String titleText("welcome to c++ programming library");
    std::cout << "Original Text: " << titleText << "\n";

    titleText.UpperFirstLetterOfEachWord();
    std::cout << "Title Case: " << titleText << "\n";

    titleText.UpperAllString();
    std::cout << "Upper All: " << titleText << "\n";

    titleText.LowerAllString();
    std::cout << "Lower All: " << titleText << "\n";

    titleText.InvertAllLettersCase();
    std::cout << "Inverted Case: " << titleText << "\n\n";

    // 3. Trim, Modifications & In-place Mutations
    std::cout << "--- 3. Testing Trimming & Transformations ---\n";
    String padded("   --- Hello C++ World! ---   ");
    std::cout << "Padded String: [" << padded << "]\n";

    padded.Trim();
    std::cout << "Trimmed String: [" << padded << "]\n";

    padded.RemovePunctuations();
    std::cout << "Punctuation Removed: [" << padded << "]\n";

    padded.ReplaceWord("Hello", "Welcome");
    std::cout << "Word Replaced: " << padded << "\n";

    padded.ReverseWordsInString();
    std::cout << "Reversed Words: " << padded << "\n\n";

    // 4. Searching, Inspections & Substrings
    std::cout << "--- 4. Testing Inspections & Searching ---\n";
    String sample("cpp-library-collection.cpp");
    std::cout << "Sample String: " << sample << "\n";
    std::cout << "Length: " << sample.Length() << "\n";
    std::cout << "Count Words: " << sample.CountWords() << "\n";
    std::cout << "Contains 'library'? " << (sample.Contains("library") ? "YES" : "NO") << "\n";
    std::cout << "StartsWith 'cpp'? " << (sample.StartsWith("cpp") ? "YES" : "NO") << "\n";
    std::cout << "EndsWith '.cpp'? " << (sample.EndsWith(".cpp") ? "YES" : "NO") << "\n";
    std::cout << "First Index of 'p': " << sample.IndexOf('p') << "\n";
    std::cout << "Last Index of 'p': " << sample.LastIndexOf('p') << "\n";
    std::cout << "TakeFirst(3): " << sample.TakeFirst(3) << "\n";
    std::cout << "TakeLast(4): " << sample.TakeLast(4) << "\n";
    std::cout << "Substring(4, 7): " << sample.Substring(4, 7) << "\n\n";

    // 5. Character Counting & Categorization
    std::cout << "--- 5. Testing Character Counting ---\n";
    String metrics("User_Name123 @2026!");
    std::cout << "Metrics Text: " << metrics << "\n";
    std::cout << "Capital Letters: " << metrics.CountCapitalLetters() << "\n";
    std::cout << "Small Letters  : " << metrics.CountSmallLetters() << "\n";
    std::cout << "Digits         : " << metrics.CountDigits() << "\n";
    std::cout << "Spaces         : " << metrics.CountSpaces() << "\n";
    std::cout << "Punctuations   : " << metrics.CountPunctuations() << "\n";
    std::cout << "Vowels         : " << metrics.CountVowels() << "\n";
    std::cout << "Specific Letter 'e' (Case Insensitive): "
        << metrics.CountSpecificLetter('e', false) << "\n\n";

    // 6. Splitting, Joining & Palindrome
    std::cout << "--- 6. Testing Split, Join & Palindrome ---\n";
    String csvData("Apple,Banana,Cherry,Date");
    std::cout << "CSV String: " << csvData << "\n";

    std::vector<std::string> fruits = csvData.Split(",");
    std::cout << "Splitted Vector (" << fruits.size() << " items):\n";
    for (const auto& fruit : fruits)
    {
        std::cout << " - " << fruit << "\n";
    }

    std::string joined = String::JoinString(fruits, " | ");
    std::cout << "Joined Back: " << joined << "\n";

    String pal1("A man, a plan, a canal: Panama");
    String pal2("Hello World");
    std::cout << "Is [" << pal1 << "] Palindrome? " << (pal1.IsPalindrome() ? "YES" : "NO") << "\n";
    std::cout << "Is [" << pal2 << "] Palindrome? " << (pal2.IsPalindrome() ? "YES" : "NO") << "\n\n";

    std::cout << "========================================\n";
    std::cout << "      All Tests Completed Successfully! \n";
    std::cout << "========================================\n";
}

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

void TestUtil()
{
    // 1. Seed Random Generator
    Util::Srand();

    std::cout << "========================================\n";
    std::cout << "       Testing Core::Util Class         \n";
    std::cout << "========================================\n\n";

    // 2. Test RandomNumber
    std::cout << "--- 1. Testing RandomNumber ---\n";
    std::cout << "Random Number between 1 and 100: " << Util::RandomNumber(1, 100) << "\n";
    std::cout << "Random Number between -50 and 50: " << Util::RandomNumber(-50, 50) << "\n\n";

    // 3. Test GetRandomCharacter
    std::cout << "--- 2. Testing GetRandomCharacter ---\n";
    std::cout << "Small Letter: " << Util::GetRandomCharacter(Util::SmallLetter) << "\n";
    std::cout << "Capital Letter: " << Util::GetRandomCharacter(Util::CapitalLetter) << "\n";
    std::cout << "Digit: " << Util::GetRandomCharacter(Util::Digit) << "\n";
    std::cout << "Special Character: " << Util::GetRandomCharacter(Util::SpecialCharacter) << "\n";
    std::cout << "Mix Character: " << Util::GetRandomCharacter(Util::MixChars) << "\n\n";

    // 4. Test GenerateWord & GenerateKey & PrintKeys
    std::cout << "--- 3. Testing Words & Keys Generation ---\n";
    std::cout << "Generated Word (8 chars, Mixed): " << Util::GenerateWord(Util::MixChars, 8) << "\n";
    std::cout << "Generated Key (Default): " << Util::GenerateKey() << "\n";
    std::cout << "Printing 3 Keys:\n";
    Util::PrintKeys(3, Util::CapitalLetter);
    std::cout << "\n";

    // 5. Test FillArray Methods & ShuffleArray
    std::cout << "--- 4. Testing Array Operations & Shuffle ---\n";
    constexpr size_t ARR_SIZE = 5;

    int intArr[ARR_SIZE];
    Util::FillArrayWithRandomNumbers(intArr, ARR_SIZE, 10, 99);
    std::cout << "Random Int Array: ";
    for (int val : intArr) std::cout << val << " ";
    std::cout << "\n";

    Util::ShuffleArray(intArr, ARR_SIZE);
    std::cout << "Shuffled Int Array: ";
    for (int val : intArr) std::cout << val << " ";
    std::cout << "\n\n";

    std::string wordArr[ARR_SIZE];
    Util::FillArrayWithRandomWords(wordArr, ARR_SIZE, Util::CapitalLetter, 5);
    std::cout << "Random Words Array: ";
    for (const auto& w : wordArr) std::cout << w << " ";
    std::cout << "\n\n";

    std::string keyArr[ARR_SIZE];
    Util::FillArrayWithRandomKeys(keyArr, ARR_SIZE, Util::CapitalLetter);
    std::cout << "Random Keys Array:\n";
    for (size_t i = 0; i < ARR_SIZE; ++i)
    {
        std::cout << "  [" << i << "] " << keyArr[i] << "\n";
    }
    std::cout << "\n";

    // 6. Test Swap
    std::cout << "--- 5. Testing Swap ---\n";
    int a = 10, b = 20;
    std::cout << "Before Swap: a = " << a << ", b = " << b << "\n";
    Util::Swap(a, b);
    std::cout << "After Swap : a = " << a << ", b = " << b << "\n\n";

    // 7. Test Tabs
    std::cout << "--- 6. Testing Tabs ---\n";
    std::cout << "Line Start" << Util::Tabs(3) << "Line After 3 Tabs\n\n";

    // 8. Test EncryptText & DecryptText
    std::cout << "--- 7. Testing Encryption & Decryption ---\n";
    std::string originalText = "Programming Modern C++ 2026";
    short key = 5;
    std::string encrypted = Util::EncryptText(originalText, key);
    std::string decrypted = Util::DecryptText(encrypted, key);

    std::cout << "Original Text : " << originalText << "\n";
    std::cout << "Encrypted Text: " << encrypted << "\n";
    std::cout << "Decrypted Text: " << decrypted << "\n\n";

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
