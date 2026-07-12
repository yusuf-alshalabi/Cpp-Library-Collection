
#pragma once

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>

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

    char& operator[](size_t Index)
    {
        return _Value[Index];
    }


    const char& operator[](size_t Index) const
    {
        return _Value[Index];
    }

    char& At(size_t Index)
    {
        if (Index >= _Value.length())
        {
            throw std::out_of_range("String index is out of range.");
        }

        return _Value[Index];
    }

    const char& At(size_t Index) const
    {
        if (Index >= _Value.length())
        {
            throw std::out_of_range("String index is out of range.");
        }

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
        short pos = 0;
        std::string sWord;

        while ((pos = temp.find(delim)) != std::string::npos)
        {
            sWord = temp.substr(0, pos);
            if (sWord != "")
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
        if (temp != "")
        {
            Counter++;
        }

        return Counter;
    }

    size_t CountWords() const
    {
        return CountWords(_Value);
    };

    static std::string  UpperFirstLetterOfEachWord(std::string S1)
    {

        bool isFirstLetter = true;

        for (size_t i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);

        }

        return S1;
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

        for (size_t i = S1.lenght ; i > 0; --i)
        {
            Result += S1[i-1];
        }

        return Result;
    }

     std::string Reverse() const 
     {
         return Reverse(_Value);
     }

    void ReverseInPlace ()
    {
        _Value = Reverse(_Value);
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

    static bool IsEmpty(const std::string& S1)
    {
        return S1.empty();
    }

    bool IsEmpty() const
    {
        return _Value.empty();
    }

    void  UpperFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value    
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static std::string  LowerFirstLetterOfEachWord(std::string S1)
    {

        bool isFirstLetter = true;

        for (size_t i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = tolower(S1[i]);

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

    static std::string  UpperAllString(std::string S1)
    {
        for (size_t i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }

    void  UpperAllString()
    {
        _Value = UpperAllString(_Value);
    }

    static std::string  LowerAllString(std::string S1)
    {
        for (size_t i = 0; i < S1.length(); i++)
        {
            S1[i] = tolower(S1[i]);
        }
        return S1;
    }

    void  LowerAllString()
    {
        _Value = LowerAllString(_Value);
    }

    static char  InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    static std::string  InvertAllLettersCase(std::string S1)
    {
        for (size_t i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertLetterCase(S1[i]);
        }
        return S1;
    }

    void  InvertAllLettersCase()
    {
        _Value = InvertAllLettersCase(_Value);
    }

    enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

    static size_t CountLetters(const std::string& S1, enWhatToCount WhatToCount = enWhatToCount::All)
    {


        if (WhatToCount == enWhatToCount::All)
        {
            return S1.length();
        }

        size_t Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {

            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
                Counter++;


            if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
                Counter++;


        }

        return Counter;

    }

    static size_t  CountCapitalLetters(const std::string& S1)
    {

        size_t Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {

            if (isupper(S1[i]))
                Counter++;

        }

        return Counter;
    }

    size_t  CountCapitalLetters() const
    {
        return CountCapitalLetters(_Value);
    }

    static size_t  CountSmallLetters(const std::string& S1)
    {

        size_t Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {

            if (islower(S1[i]))
                Counter++;

        }

        return Counter;
    }

    size_t  CountSmallLetters() const
    {
        return CountSmallLetters(_Value);
    }

    static size_t  CountSpecificLetter(const std::string& S1, char Letter, bool MatchCase = true)
    {

        size_t Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {

            if (MatchCase)
            {
                if (S1[i] == Letter)
                    Counter++;
            }
            else
            {
                if (tolower(S1[i]) == tolower(Letter))
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
        Ch1 = tolower(Ch1);

        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));

    }

    static size_t  CountVowels(const std::string& S1)
    {

        size_t Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {

            if (IsVowel(S1[i]))
                Counter++;

        }

        return Counter;
    }

    size_t  CountVowels() const
    {
        return CountVowels(_Value);
    }

    static std::vector<std::string> Split(std::string S1, const std::string& Delim)
    {

        std::vector<std::string> vString;

        short pos = 0;
        std::string sWord; // define a string variable    

        // use find() function to get the position of the delimiters    
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word     
            if (sWord != "")
            {
                vString.push_back(sWord);
            }

            S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
        }

        if (S1 != "")
        {
            vString.push_back(S1); // it adds last word of the string.  
        }

        return vString;

    }

    std::vector<std::string> Split(std::string Delim) const
    {
        return Split(_Value, Delim);
    }

    static std::string TrimLeft(const std::string& S1)
    {
        for (size_t i = 0; i < S1.length(); i++)
        {
            if (!isspace(static_cast<unsigned char>(S1[i])))
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
            if (!isspace(static_cast<unsigned char>(S1[i - 1])))
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

    static std::string JoinString(const std::string arrString[], short Length, const std::string& Delim)
    {
        if (Length <= 0)
            return "";

        std::string S1;

        for (short i = 0; i < Length; i++)
        {
            S1 += arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    static std::string ReverseWordsInString(const std::string& S1)
    {

        std::vector<std::string> vString;
        std::string S2 = "";

        vString = Split(S1, " ");

        // declare iterator  
        std::vector<std::string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {

            --iter;

            S2 += *iter + " ";

        }

        S2 = S2.substr(0, S2.length() - 1); //remove last space.  

        return S2;
    }

    void ReverseWordsInString()
    {
        _Value = ReverseWordsInString(_Value);
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

    static std::string Append(const std::string& S1, const std::string& S2)
    {
        return S1 + S2;
    }

    void Append(const std::string& S2)
    {
        _Value = Append(_Value, S2);
    }

    void ReplaceWord(const std::string& StringToReplace, const std::string& sReplaceTo, bool MatchCase = true)
    {
        _Value = ReplaceWord(_Value, StringToReplace, sReplaceTo, MatchCase);
    }

    static std::string RemovePunctuations(const std::string& S1)
    {

        std::string S2 = "";

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
            {
                S2 += S1[i];
            }
        }

        return S2;

    }

    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
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

    static std::string Substring(const std::string& S1, size_t Position, size_t Length)
    {
        return S1.substr(Position, Length);
    }

    std::string Substring(size_t Position, size_t Length) const
    {
        return Substring(_Value, Position, Length);
    }

    std::string TakeLast(size_t Count) const
    {
        return TakeLast(_Value, Count);
    }

    void Clear()
    {
        _Value.clear();
    }

};