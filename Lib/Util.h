
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
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
		return rand() % (To - From + 1) + From;
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
		Word.reserve(Length);

		for (int i = 1; i <= Length; i++)

		{

			Word += GetRandomCharacter(CharType);

		}
		return Word;
	}

	static std::string  GenerateKey(enCharType CharType = CapitalLetter)
	{

		std::string Key = "";
		Key.reserve(19); // Reserve space for the key (4 chars + 3 hyphens)

		Key = GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4);


		return Key;
	}

	static void PrintKeys(short NumberOfKeys, enCharType CharType = CapitalLetter, std::ostream& Output = std::cout)
	{
		for (int i = 1; i <= NumberOfKeys; i++)

		{
			Output << "Key [" << i << "] : ";
			Output << GenerateKey(CharType) << "\n";
		}

	}

	static void FillArrayWithRandomNumbers(int arr[], size_t arrLength, int From, int To)
	{
		for (size_t i = 0; i < arrLength; i++)
			arr[i] = RandomNumber(From, To);
	}

	static void FillArrayWithRandomWords(std::string arr[], size_t arrLength, enCharType CharType, short Wordlength)
	{
		for (size_t i = 0; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, Wordlength);

	}

	static void FillArrayWithRandomKeys(std::string arr[], size_t arrLength, enCharType CharType = CapitalLetter)
	{
		for (size_t i = 0; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}

	template<typename T>
	static void Swap(T& A, T& B)
	{
		T Temp = A;
		A = B;
		B = Temp;
	}

	template<typename T>
	static  void ShuffleArray(T arr[], size_t arrLength)
	{
		if (arrLength <= 1)
			return;

		for (size_t i = arrLength -1; i > 0; i--)
		{
			int randomIndex = RandomNumber(0, static_cast<int>(i));
			Swap(arr[i], arr[randomIndex]);
		}

	}

	static std::string  Tabs(short NumberOfTabs)
	{
		std::string t = "";
		t.reserve(NumberOfTabs);

		for (int i = 0; i < NumberOfTabs; i++)
		{
			t += "\t";
		}
		return t;

	}

	static std::string  EncryptText(const std::string& Text, short EncryptionKey)
	{
		std::string Result;
		Result.reserve(Text.length());

		for (char Ch : Text)
		{

			Result += static_cast<char>(Ch + EncryptionKey);

		}

		return Result;

	}

	static std::string  DecryptText(const std::string& Text, short EncryptionKey)
	{
		std::string Result;
		Result.reserve(Text.length());

		for (char Ch : Text)
		{

			Result += static_cast<char>(Ch - EncryptionKey);

		}
		return Result;

	}

};