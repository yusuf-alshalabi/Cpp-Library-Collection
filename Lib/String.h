
#pragma once

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <ostream>

class String
{

private:
	std::string _Value;

public:

	String() = default;
	~String() = default;

	String(const std::string& Value)
		: _Value(Value)
	{
	}

	String(std::string&& Value)
		: _Value(std::move(Value))
	{
	}

	String(const String& Other)
		: _Value(Other._Value)
	{
	}

	String(String&& Other) noexcept
		: _Value(std::move(Other._Value))
	{
	}

	String& operator=(const String& Other)
	{
		if (this != &Other)
		{
			_Value = Other._Value;
		}

		return *this;
	}

	String& operator=(String&& Other) noexcept
	{
		if (this != &Other)
		{
			_Value = std::move(Other._Value);
		}

		return *this;
	}

	bool operator==(const String& Other) const
	{
		return _Value == Other._Value;
	}

	bool operator!=(const String& Other) const
	{
		return !(*this == Other);
	}

	bool operator<(const String& Other) const
	{
		return _Value < Other._Value;
	}

	bool operator>(const String& Other) const
	{
		return _Value > Other._Value;
	}

	bool operator<=(const String& Other) const
	{
		return _Value <= Other._Value;
	}

	bool operator>=(const String& Other) const
	{
		return _Value >= Other._Value;
	}

	operator std::string() const
	{
		return _Value;
	}

	friend std::ostream& operator<<(std::ostream& Output, const String& S)
	{
		Output << S._Value;
		return Output;
	}

	String operator+(const String& Other) const
	{
		return String(_Value + Other._Value);
	}

	String operator+(const std::string& Other) const
	{
		return String(_Value + Other);
	}

	String& operator+=(const String& Other)
	{
		_Value += Other._Value;

		return *this;
	}

	String& operator+=(const std::string& Other)
	{
		_Value += Other;

		return *this;
	}

	char& operator[](size_t Index)
	{
		return _Value[Index];
	}

	const char& operator[](size_t Index) const
	{
		return _Value[Index];
	}

	void CheckIndex(size_t Index) const
	{
		if (Index >= _Value.length())
		{
			throw std::out_of_range(
				"String index is out of range."
			);
		}
	}

	char& At(size_t Index)
	{
		CheckIndex(Index);

		return _Value[Index];
	}

	const char& At(size_t Index) const
	{
		CheckIndex(Index);

		return _Value[Index];
	}

	void SetValue(const std::string& Value) {
		_Value = Value;
	}

	std::string GetValue() const {
		return _Value;
	}

	const std::string& GetValueRef() const
	{
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) std::string Value;


	static size_t Length(const std::string& S1) {
		return S1.length();
	}

	size_t Length() const
	{
		return Length(_Value);
	};

	static size_t CountWords(const std::string& S1)
	{
		std::string temp = Trim(S1);   // remove leading and trailing spaces  
		std::string delim = " ";
		size_t Counter = 0;
		size_t pos = 0;
		std::string sWord;

		while ((pos = temp.find(delim)) != std::string::npos)
		{
			sWord = temp.substr(0, pos);
			if (!sWord.empty())
			{
				Counter++;
			}
			temp.erase(0, pos + delim.length());

			// skip any consecutive spaces after erasing  
			while (!temp.empty() && temp[0] == ' ')
			{
				temp.erase(0, 1);
			}
		}

		// count the last word if exists  
		if (!temp.empty())
		{
			Counter++;
		}

		return Counter;
	}

	size_t CountWords() const
	{
		return CountWords(_Value);
	};

	static bool IsEmpty(const std::string& S1)
	{
		return S1.empty();
	}

	bool IsEmpty() const
	{
		return _Value.empty();
	}

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

	bool IsPalindrome() const
	{
		return IsPalindrome(_Value);
	}

	static bool Contains(const std::string& S1, const std::string& S2)
	{
		return S1.find(S2) != std::string::npos;
	}

	bool Contains(const std::string& S2) const
	{
		return Contains(_Value, S2);
	}

	static bool Contains(const std::string& S1, char Ch)
	{
		return S1.find(Ch) != std::string::npos;
	}

	bool Contains(char Ch) const
	{
		return Contains(_Value, Ch);
	}

	static size_t IndexOf(
		const std::string& S1,
		const std::string& Value)
	{
		return S1.find(Value);
	}

	size_t IndexOf(const std::string& Value) const
	{
		return IndexOf(_Value, Value);
	}

	static size_t IndexOf(const std::string& S1, char Ch)
	{
		return S1.find(Ch);
	}

	size_t IndexOf(char Ch) const
	{
		return IndexOf(_Value, Ch);
	}

	static size_t LastIndexOf(
		const std::string& S1,
		const std::string& Value)
	{
		return S1.rfind(Value);
	}

	size_t LastIndexOf(const std::string& Value) const
	{
		return LastIndexOf(_Value, Value);
	}

	static size_t LastIndexOf(const std::string& S1, char Ch)
	{
		return S1.rfind(Ch);
	}

	size_t LastIndexOf(char Ch) const
	{
		return LastIndexOf(_Value, Ch);
	}

	static bool StartsWith(const std::string& S1, const std::string& prefix)
	{
		return S1.rfind(prefix, 0) == 0;
	}

	bool StartsWith(const std::string& prefix) const
	{
		return StartsWith(_Value, prefix);
	}

	static bool EndsWith(const std::string& S1, const std::string& Suffix)
	{
		return S1.size() >= Suffix.size() &&
			S1.compare(S1.size() - Suffix.size(), Suffix.size(), Suffix) == 0;
	}

	bool EndsWith(const std::string& Suffix) const
	{
		return EndsWith(_Value, Suffix);
	}

	static std::string  UpperFirstLetterOfEachWord(std::string S1)
	{

		bool isFirstLetter = true;

		const size_t Length = S1.length();
		for (size_t i = 0; i < Length; i++)
		{

			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(S1[i])));
			}

			isFirstLetter = (S1[i] == ' ' ? true : false);

		}

		return S1;
	}

	void  UpperFirstLetterOfEachWord()
	{
		// no need to return value , this function will directly update the object value    
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static std::string  LowerFirstLetterOfEachWord(std::string S1)
	{

		bool isFirstLetter = true;

		const size_t Length = S1.length();
		for (size_t i = 0; i < Length; i++)
		{

			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(S1[i])));
			}

			isFirstLetter = (S1[i] == ' ' ? true : false);

		}

		return S1;
	}

	void  LowerFirstLetterOfEachWord()
	{


		// no need to return value , this function will directly update the object value    
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static std::string UpperAllString(std::string S1)
	{
		for (char& Ch : S1)
		{
			Ch = static_cast<char>(std::toupper(static_cast<unsigned char>(Ch)));
		}
		return S1;
	}

	void  UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static std::string LowerAllString(std::string S1)
	{
		for (char& Ch : S1)
		{
			Ch = static_cast<char>(std::tolower(static_cast<unsigned char>(Ch)));
		}
		return S1;
	}

	void  LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char  InvertLetterCase(char char1)
	{
		unsigned char Ch = static_cast<unsigned char>(char1);

		return std::isupper(Ch)
			? static_cast<char>(std::tolower(Ch))
			: static_cast<char>(std::toupper(Ch));
	}

	static std::string InvertAllLettersCase(std::string S1)
	{
		for (char& Ch : S1)
		{
			Ch = InvertLetterCase(Ch);
		}
		return S1;
	}

	void  InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	enum class CharacterType
	{
		All,
		Letters,
		CapitalLetters,
		SmallLetters,
		Digits,
		Spaces,
		Punctuations,
		Vowels
	};

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

	size_t CountCharacters(
		CharacterType Type = CharacterType::All) const
	{
		return CountCharacters(_Value, Type);
	}

	static size_t CountCapitalLetters(const std::string& S1)
	{
		return CountCharacters(S1, CharacterType::CapitalLetters);
	}

	size_t  CountCapitalLetters() const
	{
		return CountCapitalLetters(_Value);
	}

	static size_t CountSmallLetters(const std::string& S1)
	{
		return CountCharacters(S1, CharacterType::SmallLetters);
	}

	size_t  CountSmallLetters() const
	{
		return CountSmallLetters(_Value);
	}

	static size_t CountDigits(const std::string& S1)
	{
		return CountCharacters(S1, CharacterType::Digits);
	}

	size_t CountDigits() const
	{
		return CountDigits(_Value);
	}

	static size_t CountSpaces(const std::string& S1)
	{
		return CountCharacters(S1, CharacterType::Spaces);
	}

	size_t CountSpaces() const
	{
		return CountSpaces(_Value);
	}

	static size_t CountPunctuations(const std::string& S1)
	{
		return CountCharacters(S1, CharacterType::Punctuations);
	}

	size_t CountPunctuations() const
	{
		return CountPunctuations(_Value);
	}

	static size_t  CountSpecificLetter(const std::string& S1, char Letter, bool MatchCase = true)
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

	size_t  CountSpecificLetter(char Letter, bool MatchCase = true) const
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Ch1)
	{
		Ch1 = static_cast<char>(std::tolower(static_cast<unsigned char>(Ch1)));

		return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));

	}

	static size_t  CountVowels(const std::string& S1)
	{
		return CountCharacters(S1, CharacterType::Vowels);
	}

	size_t  CountVowels() const
	{
		return CountVowels(_Value);
	}

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

	std::vector<std::string> Split(std::string Delim) const
	{
		return Split(_Value, Delim);
	}

	static std::string JoinString(const std::vector<std::string>& vString, const std::string& Delim)
	{
		if (vString.empty())
			return "";

		std::string S1;

		for (const std::string& s : vString)
		{
			S1 += s + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());
	}

	static std::string JoinString(const std::string arrString[], size_t Length, const std::string& Delim)
	{
		if (Length <= 0)
			return "";

		std::string S1;

		for (size_t i = 0; i < Length; i++)
		{
			S1 += arrString[i] + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());
	}

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

	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

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

	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static std::string Trim(const std::string& S1)
	{
		return TrimLeft(TrimRight(S1));
	}

	void Trim()
	{
		_Value = Trim(_Value);
	}

	static std::string ReplaceWord(std::string S1, const std::string& StringToReplace, const std::string& sRepalceTo, bool MatchCase = true)
	{

		std::vector<std::string> vString = Split(S1, " ");

		for (std::string& s : vString)
		{

			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = sRepalceTo;
				}

			}
			else
			{
				if (LowerAllString(s) == LowerAllString(StringToReplace))
				{
					s = sRepalceTo;
				}

			}

		}

		return JoinString(vString, " ");
	}

	void ReplaceWord(const std::string& StringToReplace, const std::string& sReplaceTo, bool MatchCase = true)
	{
		_Value = ReplaceWord(_Value, StringToReplace, sReplaceTo, MatchCase);
	}

	static std::string Append(const std::string& S1, const std::string& S2)
	{
		return S1 + S2;
	}

	void Append(const std::string& S2)
	{
		_Value = Append(_Value, S2);
	}

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

	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}

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

	void Insert(
		size_t Position,
		const std::string& Value)
	{
		_Value = Insert(_Value, Position, Value);
	}

	void Clear()
	{
		_Value.clear();
	}

	void ReverseInPlace()
	{
		_Value = Reverse(_Value);
	}

	static std::string TakeFirst(const std::string& S1, size_t Count)
	{
		if (Count >= S1.length())
			return S1;

		return S1.substr(0, Count);
	}

	std::string TakeFirst(size_t Count) const
	{
		return TakeFirst(_Value, Count);
	}

	static std::string TakeLast(const std::string& S1, size_t Count)
	{
		if (Count >= S1.length())
			return S1;

		return S1.substr(S1.length() - Count);
	}

	std::string TakeLast(size_t Count) const
	{
		return TakeLast(_Value, Count);
	}

	static std::string Substring(const std::string& S1, size_t Position, size_t Length)
	{
		return S1.substr(Position, Length);
	}

	std::string Substring(size_t Position, size_t Length) const
	{
		return Substring(_Value, Position, Length);
	}

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

	std::string Repeat(size_t Times) const
	{
		return Repeat(_Value, Times);
	}

	static std::string Reverse(const std::string& S1)
	{
		std::string Result;
		Result.reserve(S1.length());

		for (size_t i = S1.length(); i > 0; --i)
		{
			Result += S1[i - 1];
		}

		return Result;
	}

	std::string Reverse() const
	{
		return Reverse(_Value);
	}

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

	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

};