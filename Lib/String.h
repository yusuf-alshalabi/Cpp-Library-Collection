#pragma once

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <ostream>
#include <iostream>

namespace Core
{
	/**
	 * @class String
	 * @brief A comprehensive utility class for advanced string manipulation, text parsing, and character analysis.
	 *
	 * @details
	 * Provides a hybrid interface containing both object-oriented stateful operations (on encapsulated string data)
	 * and static stateless helper methods. It focuses on memory performance (via `reserve`), type-safe character
	 * checks, and algorithmic string processing without unnecessary reallocations.
	 */
	class String
	{
	private:
		std::string _Value; /**< Internal string storage for instance operations. */

	public:

		/**
		 * @brief Constructs an empty String object.
		 */
		String() = default;

		/**
		 * @brief Destroys the String object.
		 */
		~String() = default;

		/**
		 * @brief Constructs a String object from a C-style string.
		 * @param Value Pointer to a null-terminated character array. Defaults to empty string if nullptr.
		 */
		String(const char* Value)
			: _Value(Value ? Value : "")
		{
		}

		/**
		 * @brief Constructs a String object by copying an std::string.
		 * @param Value Reference to the source std::string.
		 */
		String(const std::string& Value)
			: _Value(Value)
		{
		}

		/**
		 * @brief Move-constructs a String object from an rvalue std::string.
		 * @param Value Rvalue reference to std::string.
		 */
		String(std::string&& Value) noexcept
			: _Value(std::move(Value))
		{
		}

		/**
		 * @brief Copy constructor.
		 * @param Other Source String object.
		 */
		String(const String& Other)
			: _Value(Other._Value)
		{
		}

		/**
		 * @brief Move constructor.
		 * @param Other Source String object to move from.
		 */
		String(String&& Other) noexcept
			: _Value(std::move(Other._Value))
		{
		}

		/**
		 * @brief Copy assignment operator.
		 */
		String& operator=(const String& Other)
		{
			if (this != &Other)
			{
				_Value = Other._Value;
			}

			return *this;
		}

		/**
		 * @brief Move assignment operator.
		 */
		String& operator=(String&& Other) noexcept
		{
			if (this != &Other)
			{
				_Value = std::move(Other._Value);
			}

			return *this;
		}

		/** @brief Equality operator. */
		bool operator==(const String& Other) const
		{
			return _Value == Other._Value;
		}

		/** @brief Inequality operator. */
		bool operator!=(const String& Other) const
		{
			return !(*this == Other);
		}

		/** @brief Less-than operator. */
		bool operator<(const String& Other) const
		{
			return _Value < Other._Value;
		}

		/** @brief Greater-than operator. */
		bool operator>(const String& Other) const
		{
			return _Value > Other._Value;
		}

		/** @brief Less-than-or-equal operator. */
		bool operator<=(const String& Other) const
		{
			return _Value <= Other._Value;
		}

		/** @brief Greater-than-or-equal operator. */
		bool operator>=(const String& Other) const
		{
			return _Value >= Other._Value;
		}

		/**
		 * @brief Implicit conversion operator to std::string.
		 */
		operator std::string() const
		{
			return _Value;
		}

		/**
		 * @brief Overloaded stream insertion operator for outputting String objects.
		 */
		friend std::ostream& operator<<(std::ostream& Output, const String& S)
		{
			S.Print(Output);
			return Output;
		}

		/**
		 * @brief Concatenates two String objects into a new String instance.
		 */
		String operator+(const String& Other) const
		{
			return String(_Value + Other._Value);
		}

		/**
		 * @brief Appends another String to this instance.
		 */
		String& operator+=(const String& Other)
		{
			_Value += Other._Value;

			return *this;
		}

		/**
		 * @brief Unchecked subscript operator for character access (mutable).
		 */
		char& operator[](size_t Index)
		{
			return _Value[Index];
		}

		/**
		 * @brief Unchecked subscript operator for character access (read-only).
		 */
		const char& operator[](size_t Index) const
		{
			return _Value[Index];
		}

		/**
		 * @brief Validates if an index is within string boundaries.
		 *
		 * @param Index The index to check.
		 * @throws std::out_of_range If Index >= string length.
		 */
		void CheckIndex(size_t Index) const
		{
			if (Index >= _Value.length())
			{
				throw std::out_of_range(
					"String index is out of range."
				);
			}
		}

		/**
		 * @brief Bounds-checked character access (mutable).
		 *
		 * @param Index The character index.
		 * @return char& Reference to the character.
		 * @throws std::out_of_range If index is out of bounds.
		 */
		char& At(size_t Index)
		{
			CheckIndex(Index);

			return _Value[Index];
		}

		/**
		 * @brief Bounds-checked character access (read-only).
		 *
		 * @param Index The character index.
		 * @return const char& Const reference to the character.
		 * @throws std::out_of_range If index is out of bounds.
		 */
		const char& At(size_t Index) const
		{
			CheckIndex(Index);

			return _Value[Index];
		}

		/** @brief Updates the internal string value. */
		void SetValue(const std::string& Value) {
			_Value = Value;
		}

		/** @brief Returns a copy of the internal string. */
		std::string GetValue() const {
			return _Value;
		}

		/** @brief Returns a const reference to the internal string (zero-copy). */
		const std::string& GetValueRef() const
		{
			return _Value;
		}

		/** @brief Gets string length. */
		static size_t Length(const std::string& S1) {
			return S1.length();
		}

		/** @brief Gets length of internal string. */
		size_t Length() const
		{
			return Length(_Value);
		};

		/**
		 * @brief Counts total words in a string.
		 *
		 * @param S1 Target string.
		 * @return size_t Total word count.
		 *
		 * @details
		 * **Implementation:** Uses a single-pass state-machine algorithm to detect transitions
		 * between whitespace and non-whitespace characters without allocating temporary memory.
		 */
		static size_t CountWords(const std::string& S1)
		{
			size_t Counter = 0;
			bool InWord = false;

			for (char Ch : S1)
			{
				if (!std::isspace(static_cast<unsigned char>(Ch)))
				{
					if (!InWord)
					{
						InWord = true;
						Counter++;
					}
				}
				else
				{
					InWord = false;
				}
			}

			return Counter;
		}

		/** @brief Counts words in the internal string. */
		size_t CountWords() const
		{
			return CountWords(_Value);
		};

		/** @brief Checks if a string is empty. */
		static bool IsEmpty(const std::string& S1)
		{
			return S1.empty();
		}

		/** @brief Checks if the internal string is empty. */
		bool IsEmpty() const
		{
			return _Value.empty();
		}

		/**
		 * @brief Checks if a string reads the same forward and backward.
		 *
		 * @param S1 Input string.
		 * @return true If palindrome, false otherwise.
		 *
		 * @details
		 * **Algorithm:** Filters out non-alphanumeric characters and converts remaining
		 * characters to lowercase before performing half-length symmetric equality check.
		 */
		static bool IsPalindrome(const std::string& S1)
		{
			std::string Cleaned;

			for (char Ch : S1)
			{
				if (std::isalnum(static_cast<unsigned char>(Ch)))
				{
					Cleaned += std::tolower(static_cast<unsigned char>(Ch));
				}
			}

			return std::equal(
				Cleaned.begin(),
				Cleaned.begin() + Cleaned.size() / 2,
				Cleaned.rbegin());
		}

		/** @brief Checks if internal string is a palindrome. */
		bool IsPalindrome() const
		{
			return IsPalindrome(_Value);
		}

		/** @brief Checks if S1 contains substring S2. */
		static bool Contains(const std::string& S1, const std::string& S2)
		{
			return S1.find(S2) != std::string::npos;
		}

		/** @brief Checks if internal string contains substring S2. */
		bool Contains(const std::string& S2) const
		{
			return Contains(_Value, S2);
		}

		/** @brief Checks if S1 contains character Ch. */
		static bool Contains(const std::string& S1, char Ch)
		{
			return S1.find(Ch) != std::string::npos;
		}

		/** @brief Checks if internal string contains character Ch. */
		bool Contains(char Ch) const
		{
			return Contains(_Value, Ch);
		}

		/** @brief Finds first position of substring Value in S1. */
		static size_t IndexOf(
			const std::string& S1,
			const std::string& Value)
		{
			return S1.find(Value);
		}

		/** @brief Finds first position of substring Value in internal string. */
		size_t IndexOf(const std::string& Value) const
		{
			return IndexOf(_Value, Value);
		}

		/** @brief Finds first position of character Ch in S1. */
		static size_t IndexOf(const std::string& S1, char Ch)
		{
			return S1.find(Ch);
		}

		/** @brief Finds first position of character Ch in internal string. */
		size_t IndexOf(char Ch) const
		{
			return IndexOf(_Value, Ch);
		}

		/** @brief Finds last position of substring Value in S1. */
		static size_t LastIndexOf(
			const std::string& S1,
			const std::string& Value)
		{
			return S1.rfind(Value);
		}

		/** @brief Finds last position of substring Value in internal string. */
		size_t LastIndexOf(const std::string& Value) const
		{
			return LastIndexOf(_Value, Value);
		}

		/** @brief Finds last position of character Ch in S1. */
		static size_t LastIndexOf(const std::string& S1, char Ch)
		{
			return S1.rfind(Ch);
		}

		/** @brief Finds last position of character Ch in internal string. */
		size_t LastIndexOf(char Ch) const
		{
			return LastIndexOf(_Value, Ch);
		}

		/** @brief Checks if string S1 starts with a given prefix. */
		static bool StartsWith(const std::string& S1, const std::string& prefix)
		{
			return S1.rfind(prefix, 0) == 0;
		}

		/** @brief Checks if internal string starts with a given prefix. */
		bool StartsWith(const std::string& prefix) const
		{
			return StartsWith(_Value, prefix);
		}

		/** @brief Checks if string S1 ends with a given suffix. */
		static bool EndsWith(const std::string& S1, const std::string& Suffix)
		{
			return S1.size() >= Suffix.size() &&
				S1.compare(S1.size() - Suffix.size(), Suffix.size(), Suffix) == 0;
		}

		/** @brief Checks if internal string ends with a given suffix. */
		bool EndsWith(const std::string& Suffix) const
		{
			return EndsWith(_Value, Suffix);
		}

		/** @brief Converts the first letter of each word in a string to uppercase. */
		static std::string UpperFirstLetterOfEachWord(const std::string& S1)
		{

			bool isFirstLetter = true;

			const size_t Length = S1.length();
			std::string Result = S1; // Create a copy to modify
			for (size_t i = 0; i < Length; i++)
			{

				if (S1[i] != ' ' && isFirstLetter)
				{
					Result[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(Result[i])));
				}

				isFirstLetter = (Result[i] == ' ' ? true : false);

			}

			return Result;
		}

		/** @brief Capitalizes the first letter of each word in the internal string. */
		void UpperFirstLetterOfEachWord()
		{
			_Value = UpperFirstLetterOfEachWord(_Value);
		}

		/** @brief Converts the first letter of each word in a string to lowercase. */
		static std::string LowerFirstLetterOfEachWord(const std::string& S1)
		{

			bool isFirstLetter = true;

			const size_t Length = S1.length();
			std::string Result = S1; // Create a copy to modify
			for (size_t i = 0; i < Length; i++)
			{

				if (S1[i] != ' ' && isFirstLetter)
				{
					Result[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(Result[i])));
				}

				isFirstLetter = (Result[i] == ' ' ? true : false);

			}

			return Result;
		}

		/** @brief Lowercases the first letter of each word in the internal string. */
		void LowerFirstLetterOfEachWord()
		{
			_Value = LowerFirstLetterOfEachWord(_Value);
		}

		/** @brief Converts all characters in a string to uppercase. */
		static std::string UpperAllString(const std::string& S1)
		{
			std::string Result = S1;
			for (char& Ch : Result)
			{
				Ch = static_cast<char>(std::toupper(static_cast<unsigned char>(Ch)));
			}
			return Result;
		}

		/** @brief Converts internal string to uppercase. */
		void UpperAllString()
		{
			_Value = UpperAllString(_Value);
		}

		/** @brief Converts all characters in a string to lowercase. */
		static std::string LowerAllString(const std::string& S1)
		{
			std::string Result = S1;
			for (char& Ch : Result)
			{
				Ch = static_cast<char>(std::tolower(static_cast<unsigned char>(Ch)));
			}
			return Result;
		}

		/** @brief Converts internal string to lowercase. */
		void LowerAllString()
		{
			_Value = LowerAllString(_Value);
		}

		/** @brief Inverts the case of a single character. */
		static char InvertLetterCase(char char1)
		{
			unsigned char Ch = static_cast<unsigned char>(char1);

			return std::isupper(Ch)
				? static_cast<char>(std::tolower(Ch))
				: static_cast<char>(std::toupper(Ch));
		}

		/** @brief Inverts the case of all letters in a string. */
		static std::string InvertAllLettersCase(const std::string& S1)
		{
			std::string Result = S1;
			for (char& Ch : Result)
			{
				Ch = InvertLetterCase(Ch);
			}
			return Result;
		}

		/** @brief Inverts the case of all letters in the internal string. */
		void InvertAllLettersCase()
		{
			_Value = InvertAllLettersCase(_Value);
		}

		/**
		 * @enum CharacterType
		 * @brief Specifies categories for character counting and filtering.
		 */
		enum class CharacterType
		{
			All,           /**< Matches any character */
			Letters,       /**< Alphabetical characters (a-z, A-Z) */
			CapitalLetters,/**< Uppercase letters (A-Z) */
			SmallLetters,  /**< Lowercase letters (a-z) */
			Digits,        /**< Numeric digits (0-9) */
			Spaces,        /**< Whitespace characters */
			Punctuations,  /**< Punctuation marks */
			Vowels         /**< Vowel letters (a, e, i, o, u) */
		};

		/**
		 * @brief Counts characters in a string based on a specified filter category.
		 *
		 * @param S1 Input string.
		 * @param Type Filter category from CharacterType enum. Defaults to CharacterType::All.
		 * @return size_t Count of matching characters.
		 */
		static size_t CountCharacters(
			const std::string& S1,
			CharacterType Type = CharacterType::All)
		{
			size_t Counter = 0;

			for (char Ch : S1)
			{
				switch (Type)
				{
				case CharacterType::All:
					Counter++;
					break;

				case CharacterType::Letters:
					if (std::isalpha(static_cast<unsigned char>(Ch)))
						Counter++;
					break;

				case CharacterType::CapitalLetters:
					if (std::isupper(static_cast<unsigned char>(Ch)))
						Counter++;
					break;

				case CharacterType::SmallLetters:
					if (std::islower(static_cast<unsigned char>(Ch)))
						Counter++;
					break;

				case CharacterType::Digits:
					if (std::isdigit(static_cast<unsigned char>(Ch)))
						Counter++;
					break;

				case CharacterType::Spaces:
					if (std::isspace(static_cast<unsigned char>(Ch)))
						Counter++;
					break;

				case CharacterType::Punctuations:
					if (std::ispunct(static_cast<unsigned char>(Ch)))
						Counter++;
					break;
				case CharacterType::Vowels:
					if (IsVowel(Ch))
						Counter++;
					break;
				}
			}

			return Counter;
		}

		/** @brief Counts characters in the internal string by category. */
		size_t CountCharacters(
			CharacterType Type = CharacterType::All) const
		{
			return CountCharacters(_Value, Type);
		}

		/** @brief Counts uppercase letters in a string. */
		static size_t CountCapitalLetters(const std::string& S1)
		{
			return CountCharacters(S1, CharacterType::CapitalLetters);
		}

		/** @brief Counts uppercase letters in internal string. */
		size_t CountCapitalLetters() const
		{
			return CountCapitalLetters(_Value);
		}

		/** @brief Counts lowercase letters in a string. */
		static size_t CountSmallLetters(const std::string& S1)
		{
			return CountCharacters(S1, CharacterType::SmallLetters);
		}

		/** @brief Counts lowercase letters in internal string. */
		size_t CountSmallLetters() const
		{
			return CountSmallLetters(_Value);
		}

		/** @brief Counts digits in a string. */
		static size_t CountDigits(const std::string& S1)
		{
			return CountCharacters(S1, CharacterType::Digits);
		}

		/** @brief Counts digits in internal string. */
		size_t CountDigits() const
		{
			return CountDigits(_Value);
		}

		/** @brief Counts space characters in a string. */
		static size_t CountSpaces(const std::string& S1)
		{
			return CountCharacters(S1, CharacterType::Spaces);
		}

		/** @brief Counts space characters in internal string. */
		size_t CountSpaces() const
		{
			return CountSpaces(_Value);
		}

		/** @brief Counts punctuation marks in a string. */
		static size_t CountPunctuations(const std::string& S1)
		{
			return CountCharacters(S1, CharacterType::Punctuations);
		}

		/** @brief Counts punctuation marks in internal string. */
		size_t CountPunctuations() const
		{
			return CountPunctuations(_Value);
		}

		/**
		 * @brief Counts occurrences of a specific character in a string.
		 *
		 * @param S1 Source string.
		 * @param Letter Target character to search for.
		 * @param MatchCase Flag for case sensitivity. Defaults to true.
		 * @return size_t Total occurrences.
		 */
		static size_t CountSpecificLetter(const std::string& S1, char Letter, bool MatchCase = true)
		{

			size_t Counter = 0;

			for (char Ch : S1)
			{
				if (MatchCase)
				{
					if (Ch == Letter)
						Counter++;
				}
				else
				{
					if (std::tolower(static_cast<unsigned char>(Ch)) ==
						std::tolower(static_cast<unsigned char>(Letter)))
						Counter++;
				}
			}

			return Counter;
		}

		/** @brief Counts occurrences of a specific letter in internal string. */
		size_t CountSpecificLetter(char Letter, bool MatchCase = true) const
		{
			return CountSpecificLetter(_Value, Letter, MatchCase);
		}

		/** @brief Checks if a character is an English vowel (a, e, i, o, u). */
		static bool IsVowel(char Ch1)
		{
			Ch1 = static_cast<char>(std::tolower(static_cast<unsigned char>(Ch1)));

			return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));

		}

		/** @brief Counts vowel letters in a string. */
		static size_t CountVowels(const std::string& S1)
		{
			return CountCharacters(S1, CharacterType::Vowels);
		}

		/** @brief Counts vowel letters in internal string. */
		size_t CountVowels() const
		{
			return CountVowels(_Value);
		}

		/**
		 * @brief Tokenizes a string into a vector of strings based on a delimiter.
		 *
		 * @param S1 Input string.
		 * @param Delim Target delimiter sequence.
		 * @return std::vector<std::string> Vector containing non-empty tokens.
		 */
		static std::vector<std::string> Split(std::string S1, const std::string& Delim)
		{

			std::vector<std::string> vString;

			size_t pos = 0;
			std::string sWord; // define a string variable    

			// use find() function to get the position of the delimiters    
			while ((pos = S1.find(Delim)) != std::string::npos)
			{
				sWord = S1.substr(0, pos); // store the word     
				if (!sWord.empty())
				{
					vString.push_back(sWord);
				}

				S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
			}

			if (!S1.empty())
			{
				vString.push_back(S1); // it adds last word of the string.  
			}

			return vString;

		}

		/** @brief Tokenizes internal string into a vector of tokens. */
		std::vector<std::string> Split(const std::string& Delim) const
		{
			return Split(_Value, Delim);
		}

		/**
		 * @brief Concatenates a vector of strings using a delimiter.
		 *
		 * @param vString Vector of strings to join.
		 * @param Delim Delimiter string inserted between elements.
		 * @return std::string Joined result string.
		 *
		 * @details
		 * **Memory Optimization:** Pre-calculates exact required memory capacity and calls
		 * `Result.reserve()` once before loop execution to eliminate dynamic reallocations.
		 */
		static std::string JoinString(const std::vector<std::string>& vString, const std::string& Delim)
		{
			if (vString.empty())
				return "";

			size_t TotalLength = 0;
			for (const auto& s : vString)
			{
				TotalLength += s.length();
			}
			TotalLength += Delim.length() * (vString.size() - 1);

			std::string Result;
			Result.reserve(TotalLength);

			for (size_t i = 0; i < vString.size(); ++i)
			{
				Result += vString[i];
				if (i + 1 < vString.size())
				{
					Result += Delim;
				}
			}

			return Result;
		}

		/**
		 * @brief Concatenates a string array using a delimiter.
		 *
		 * @param arrString Array of strings.
		 * @param Length Number of elements in array.
		 * @param Delim Delimiter string inserted between elements.
		 * @return std::string Joined result string.
		 *
		 * @details
		 * **Memory Optimization:** Pre-calculates exact length requirements and reserves buffer space
		 * before joining to prevent dynamic heap reallocations.
		 */
		static std::string JoinString(const std::string arrString[], size_t Length, const std::string& Delim)
		{
			if (Length == 0)
				return "";

			size_t TotalLength = 0;
			for (size_t i = 0; i < Length; ++i)
			{
				TotalLength += arrString[i].length();
			}
			TotalLength += Delim.length() * (Length - 1);

			std::string Result;
			Result.reserve(TotalLength);

			for (size_t i = 0; i < Length; ++i)
			{
				Result += arrString[i];
				if (i + 1 < Length)
				{
					Result += Delim;
				}
			}

			return Result;
		}

		/** @brief Removes leading whitespaces from a string. */
		static std::string TrimLeft(const std::string& S1)
		{
			const size_t Length = S1.length();
			for (size_t i = 0; i < Length; i++)
			{
				if (!std::isspace(static_cast<unsigned char>(S1[i])))
				{
					return S1.substr(i, S1.length() - i);
				}
			}
			return "";
		}

		/** @brief Removes leading whitespaces from internal string. */
		void TrimLeft()
		{
			_Value = TrimLeft(_Value);
		}

		/** @brief Removes trailing whitespaces from a string. */
		static std::string TrimRight(const std::string& S1)
		{
			for (size_t i = S1.length(); i > 0; --i)
			{
				if (!std::isspace(static_cast<unsigned char>(S1[i - 1])))
				{
					return S1.substr(0, i);
				}
			}
			return "";
		}

		/** @brief Removes trailing whitespaces from internal string. */
		void TrimRight()
		{
			_Value = TrimRight(_Value);
		}

		/** @brief Trims both leading and trailing whitespaces from a string. */
		static std::string Trim(const std::string& S1)
		{
			return TrimLeft(TrimRight(S1));
		}

		/** @brief Trims both leading and trailing whitespaces from internal string. */
		void Trim()
		{
			_Value = Trim(_Value);
		}

		/**
		 * @brief Replaces occurrences of a target substring with a replacement string.
		 *
		 * @param S1 Source string.
		 * @param StringToReplace Target pattern to find.
		 * @param sReplaceTo Replacement text.
		 * @param MatchCase Case sensitivity flag. Defaults to true.
		 * @return std::string Resulting modified string.
		 *
		 * @details
		 * **Algorithm:** Implements a sliding-window character matcher. Preserves surrounding formatting,
		 * punctuation, and whitespaces while replacing matched patterns without splitting string buffers.
		 */
		static std::string ReplaceWord(
			const std::string& S1,
			const std::string& StringToReplace,
			const std::string& sReplaceTo,
			bool MatchCase = true)
		{
			if (S1.empty() || StringToReplace.empty())
				return S1;

			std::string Result;
			Result.reserve(S1.length());

			const size_t TextLen = S1.length();
			const size_t TargetLen = StringToReplace.length();

			size_t i = 0;
			while (i < TextLen)
			{
				bool Match = false;

				if (i + TargetLen <= TextLen)
				{
					Match = true;
					for (size_t j = 0; j < TargetLen; ++j)
					{
						char CharInText = S1[i + j];
						char CharInTarget = StringToReplace[j];

						if (!MatchCase)
						{
							CharInText = static_cast<char>(std::tolower(static_cast<unsigned char>(CharInText)));
							CharInTarget = static_cast<char>(std::tolower(static_cast<unsigned char>(CharInTarget)));
						}

						if (CharInText != CharInTarget)
						{
							Match = false;
							break;
						}
					}
				}

				if (Match)
				{
					Result += sReplaceTo;
					i += TargetLen;
				}
				else
				{
					Result += S1[i];
					i++;
				}
			}

			return Result;
		}

		/** @brief Replaces matching word patterns in internal string. */
		void ReplaceWord(const std::string& StringToReplace, const std::string& sReplaceTo, bool MatchCase = true)
		{
			_Value = ReplaceWord(_Value, StringToReplace, sReplaceTo, MatchCase);
		}

		/** @brief Appends S2 to S1. */
		static std::string Append(const std::string& S1, const std::string& S2)
		{
			return S1 + S2;
		}

		/** @brief Appends S2 to internal string. */
		void Append(const std::string& S2)
		{
			_Value = Append(_Value, S2);
		}

		/** @brief Removes all punctuation marks from a string. */
		static std::string RemovePunctuations(const std::string& S1)
		{
			std::string Result;
			Result.reserve(S1.length());

			for (char Ch : S1)
			{
				if (!std::ispunct(static_cast<unsigned char>(Ch)))
				{
					Result += Ch;
				}
			}
			return Result;

		}

		/** @brief Removes all punctuation marks from internal string. */
		void RemovePunctuations()
		{
			_Value = RemovePunctuations(_Value);
		}

		/**
		 * @brief Inserts a string value at a specific index.
		 *
		 * @param S1 Target base string.
		 * @param Position Index where insertion occurs.
		 * @param Value Substring to insert.
		 * @return std::string Modified string.
		 * @throws std::out_of_range If Position > S1.length().
		 *
		 * @details
		 * **Memory Optimization:** Uses `reserve(S1.length() + Value.length())` to perform single-allocation insertion.
		 */
		static std::string Insert(
			const std::string& S1,
			size_t Position,
			const std::string& Value)
		{
			if (Position > S1.length())
			{
				throw std::out_of_range(
					"Insert position is out of range."
				);
			}

			std::string Result;

			Result.reserve(
				S1.length() + Value.length()
			);

			for (size_t i = 0; i < Position; i++)
			{
				Result += S1[i];
			}

			Result += Value;

			for (size_t i = Position; i < S1.length(); i++)
			{
				Result += S1[i];
			}

			return Result;
		}

		/** @brief Inserts substring Value at Position in internal string. */
		void Insert(
			size_t Position,
			const std::string& Value)
		{
			_Value = Insert(_Value, Position, Value);
		}

		/** @brief Clears the internal string buffer. */
		void Clear()
		{
			_Value.clear();
		}

		/** @brief Extracts first Count characters from a string. */
		static std::string TakeFirst(const std::string& S1, size_t Count)
		{
			if (Count >= S1.length())
				return S1;

			return S1.substr(0, Count);
		}

		/** @brief Extracts first Count characters from internal string. */
		std::string TakeFirst(size_t Count) const
		{
			return TakeFirst(_Value, Count);
		}

		/** @brief Extracts last Count characters from a string. */
		static std::string TakeLast(const std::string& S1, size_t Count)
		{
			if (Count >= S1.length())
				return S1;

			return S1.substr(S1.length() - Count);
		}

		/** @brief Extracts last Count characters from internal string. */
		std::string TakeLast(size_t Count) const
		{
			return TakeLast(_Value, Count);
		}

		/** @brief Extracts a substring given a starting position and character length. */
		static std::string Substring(const std::string& S1, size_t Position, size_t Length)
		{
			return S1.substr(Position, Length);
		}

		/** @brief Extracts substring from internal string. */
		std::string Substring(size_t Position, size_t Length) const
		{
			return Substring(_Value, Position, Length);
		}

		/**
		 * @brief Repeats a string multiple times.
		 *
		 * @param S1 String to repeat.
		 * @param Times Number of repetitions.
		 * @return std::string Repeated string.
		 */
		static std::string Repeat(const std::string& S1, size_t Times)
		{
			if (Times == 0 || S1.empty())
				return "";

			std::string Result;
			Result.reserve(S1.length() * Times);

			for (size_t i = 0; i < Times; ++i)
			{
				Result += S1;
			}

			return Result;
		}

		/** @brief Repeats internal string specified number of times. */
		std::string Repeat(size_t Times) const
		{
			return Repeat(_Value, Times);
		}

		/**
		 * @brief Reverses characters in a string.
		 *
		 * @param S1 Target string.
		 * @return std::string Reversed string.
		 *
		 * @details
		 * **Algorithm:** Uses a two-pointer inward character swap technique ($O(N)$ time, $O(1)$ auxiliary space).
		 */
		static std::string Reverse(const std::string& S1)
		{
			if (S1.empty())
				return S1;

			std::string Result = S1;

			size_t Left = 0;
			size_t Right = Result.length() - 1;

			while (Left < Right)
			{
				std::swap(Result[Left], Result[Right]);
				Left++;
				Right--;
			}

			return Result;
		}

		/** @brief Returns a reversed copy of internal string. */
		std::string Reverse() const
		{
			return Reverse(_Value);
		}

		/** @brief Reverses internal string characters in-place. */
		void ReverseInPlace()
		{
			_Value = Reverse(_Value);
		}

		/**
		 * @brief Reverses word order within a string.
		 *
		 * @param S1 Source text.
		 * @return std::string String with reversed word order.
		 */
		static std::string ReverseWordsInString(const std::string& S1)
		{
			constexpr const char* Delimiter = " ";

			std::vector<std::string> Words = Split(S1, Delimiter);

			if (Words.empty())
				return "";

			std::string Result;
			Result.reserve(S1.length());

			auto Iter = Words.end();

			while (Iter != Words.begin())
			{
				--Iter;
				Result += *Iter;
				Result += Delimiter;
			}

			// Remove the last delimiter.
			Result.erase(Result.length() - std::char_traits<char>::length(Delimiter));

			return Result;
		}

		/** @brief Reverses word sequence in internal string. */
		void ReverseWordsInString()
		{
			_Value = ReverseWordsInString(_Value);
		}

		/**
		 * @brief Outputs internal string to a destination output stream.
		 *
		 * @param Out Target output stream. Defaults to std::cout.
		 */
		void Print(std::ostream& Out = std::cout) const
		{
			Out << _Value;
		}
	};
}