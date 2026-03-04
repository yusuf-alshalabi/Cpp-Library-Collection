#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

namespace MyLib {

class MyString
{

private:
    std::string _Value;

public:

    MyString()
    {
        _Value = "";
    }

    MyString(const std::string& Value)
    {
        _Value = Value;
    }

    // Move constructor
    MyString(std::string&& Value) noexcept
        : _Value(std::move(Value))
    {
    }

    void SetValue(const std::string& Value)
    {
        _Value = Value;
    }

    std::string GetValue() const
    {
        return _Value;
    }

    // ---- Operators ----

    bool operator==(const MyString& other) const
    {
        return _Value == other._Value;
    }

    MyString operator+(const MyString& other) const
    {
        return MyString(_Value + other._Value);
    }

    // Move assignment operator
    MyString& operator=(MyString&& other) noexcept
    {
        if (this != &other)
        {
            _Value = std::move(other._Value);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& s)
    {
        return os << s._Value;
    }

    // ---- Length ----

    static size_t Length(const std::string& S1)
    {
        return S1.length();
    }

    size_t Length() const
    {
        return _Value.length();
    }

    // ---- Count Words ----

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
    }

    // ---- Upper / Lower First Letter Of Each Word ----

    static std::string UpperFirstLetterOfEachWord(const std::string& S1)
    {
        std::string temp = S1; // local copy to modify
        bool isFirstLetter = true;

        for (size_t i = 0; i < temp.length(); i++)
        {
            if (temp[i] != ' ' && isFirstLetter)
            {
                temp[i] = toupper(temp[i]);
            }
            isFirstLetter = (temp[i] == ' ' ? true : false);
        }

        return temp;
    }

    void UpperFirstLetterOfEachWord() const
    {
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static std::string LowerFirstLetterOfEachWord(const std::string& S1)
    {
        std::string temp = S1; // local copy to modify
        bool isFirstLetter = true;

        for (size_t i = 0; i < temp.length(); i++)
        {
            if (temp[i] != ' ' && isFirstLetter)
            {
                temp[i] = tolower(temp[i]);
            }
            isFirstLetter = (temp[i] == ' ' ? true : false);
        }

        return temp;
    }

    void LowerFirstLetterOfEachWord() const
    {
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    // ---- Upper / Lower All String ----

    static std::string UpperAllString(const std::string& S1)
    {
        std::string temp = S1; // local copy to modify
        for (size_t i = 0; i < temp.length(); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        return temp;
    }

    void UpperAllString() const
    {
        _Value = UpperAllString(_Value);
    }

    static std::string LowerAllString(const std::string& S1)
    {
        std::string temp = S1; // local copy to modify
        for (size_t i = 0; i < temp.length(); i++)
        {
            temp[i] = tolower(temp[i]);
        }
        return temp;
    }

    void LowerAllString() const
    {
        _Value = LowerAllString(_Value);
    }

    // ---- Invert Case ----

    static char InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    static std::string InvertAllLettersCase(const std::string& S1)
    {
        std::string temp = S1; // local copy to modify
        for (size_t i = 0; i < temp.length(); i++)
        {
            temp[i] = InvertLetterCase(temp[i]);
        }
        return temp;
    }

    void InvertAllLettersCase() const
    {
        _Value = InvertAllLettersCase(_Value);
    }

    // ---- Count Letters ----

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

    // ---- Count Capital / Small Letters ----

    static size_t CountCapitalLetters(const std::string& S1)
    {
        size_t Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (isupper(S1[i]))
                Counter++;
        }

        return Counter;
    }

    size_t CountCapitalLetters() const
    {
        return CountCapitalLetters(_Value);
    }

    static size_t CountSmallLetters(const std::string& S1)
    {
        size_t Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (islower(S1[i]))
                Counter++;
        }

        return Counter;
    }

    size_t CountSmallLetters() const
    {
        return CountSmallLetters(_Value);
    }

    // ---- Count Specific Letter ----

    static size_t CountSpecificLetter(const std::string& S1, char Letter, bool MatchCase = true)
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

    size_t CountSpecificLetter(char Letter, bool MatchCase = true) const
    {
        return CountSpecificLetter(_Value, Letter, MatchCase);
    }

    // ---- Vowels ----

    static bool IsVowel(char Ch1)
    {
        Ch1 = tolower(Ch1);
        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }

    static size_t CountVowels(const std::string& S1)
    {
        size_t Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
                Counter++;
        }

        return Counter;
    }

    size_t CountVowels() const
    {
        return CountVowels(_Value);
    }

    // ---- Split ----

    static std::vector<std::string> Split(const std::string& S1, const std::string& Delim)
    {
        std::vector<std::string> vString;
        
        if (S1.empty() || Delim.empty())
            return vString;

        size_t pos = 0;
        std::string temp = S1; // local copy to modify
        std::string sWord;

        // use find() to get position of delimiter
        while ((pos = temp.find(Delim)) != std::string::npos)
        {
            sWord = temp.substr(0, pos); // store word
            if (sWord != "")
            {
                vString.push_back(sWord);
            }

            // erase until position and move to next word
            temp.erase(0, pos + Delim.length());
        }

        // add last word if exists
        if (temp != "")
        {
            vString.push_back(temp);
        }

        return vString;
    }

    std::vector<std::string> Split(const std::string& Delim) const
    {
        return Split(_Value, Delim);
    }

    // ---- Trim ----

    static std::string TrimLeft(const std::string& S1)
    {
        if (S1.empty())
            return "";

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (!isspace(static_cast<unsigned char>(S1[i])))
            {
                return S1.substr(i, S1.length() - i);
            }
        }
        return "";
    }

    void TrimLeft() const
    {
        _Value = TrimLeft(_Value);
    }

    static std::string TrimRight(const std::string& S1)
    {
        for (size_t i = S1.length() - 1; i >= 0; i--)
        {
            if (!isspace(static_cast<unsigned char>(S1[i])))
            {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    void TrimRight() const
    {
        _Value = TrimRight(_Value);
    }

    static std::string Trim(const std::string& S1)
    {
        return TrimLeft(TrimRight(S1));
    }

    void Trim() const
    {
        _Value = Trim(_Value);
    }

    // ---- Join ----

    static std::string JoinString(const std::vector<std::string>& vString, const std::string& Delim)
    {
        if (vString.empty())
            return "";
            
        std::string result;
        result.reserve(vString.size() * 20); // rough estimate to reduce reallocations
        
        for (const auto& s : vString)
        {
            if (!result.empty())
                result += Delim;
            result += s;
        }

        return result;
    }

    static std::string JoinString(std::string arrString[], size_t Length, const std::string& Delim)
    {
        if (Length == 0)
            return "";
            
        std::string result;
        result.reserve(Length * 20); // rough estimate to reduce reallocations
        
        for (size_t i = 0; i < Length; ++i)
        {
            if (i > 0)
                result += Delim;
            result += arrString[i];
        }

        return result;
    }

    // ---- Reverse Words ----

    static std::string ReverseWordsInString(const std::string& S1)
    {
        std::vector<std::string> vString = Split(S1, " ");
        std::string result;

        for (auto it = vString.rbegin(); it != vString.rend(); ++it)
        {
            if (!result.empty())
                result += " ";
            result += *it;
        }

        return result;
    }

    void ReverseWordsInString()
    {
        _Value = ReverseWordsInString(_Value);
    }

    // ---- Replace Word ----

    static std::string ReplaceWord(const std::string& S1, const std::string& StringToReplace, const std::string& sReplaceTo, bool MatchCase = true)
    {
        std::vector<std::string> vString = Split(S1, " ");

        for (std::string& s : vString)
        {
            if (MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sReplaceTo;
                }
            }
            else
            {
                if (LowerAllString(s) == LowerAllString(StringToReplace))
                {
                    s = sReplaceTo;
                }
            }
        }

        return JoinString(vString, " ");
    }

    std::string ReplaceWord(const std::string& StringToReplace, const std::string& sReplaceTo, bool MatchCase = true) const
    {
        return ReplaceWord(_Value, StringToReplace, sReplaceTo, MatchCase);
    }

    // ---- Remove Punctuations ----

    static std::string RemovePunctuations(const std::string& S1)
    {
        if (S1.empty())
            return "";
            
        std::string S2 = "";
        S2.reserve(S1.length()); // reserve space for efficiency

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

    // ---- Contains / StartsWith / EndsWith ----

    static bool Contains(const std::string& S1, const std::string& S2)
    {
        return S1.find(S2) != std::string::npos;
    }

    bool Contains(const std::string& S2) const
    {
        return Contains(_Value, S2);
    }

    static bool StartsWith(const std::string& S1, const std::string& prefix)
    {
        return S1.rfind(prefix, 0) == 0;
    }

    bool StartsWith(const std::string& prefix) const
    {
        return StartsWith(_Value, prefix);
    }

    static bool EndsWith(const std::string& S1, const std::string& suffix)
    {
        return S1.size() >= suffix.size() &&
            S1.compare(S1.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    bool EndsWith(const std::string& suffix) const
    {
        return EndsWith(_Value, suffix);
    }

    // ---- Repeat ----

    static std::string Repeat(const std::string& S1, int times)
    {
        if (times <= 0 || S1.empty())
            return "";
            
        std::string result;
        result.reserve(S1.size() * times);
        
        for (int i = 0; i < times; ++i)
        {
            result += S1;
        }
        return result;
    }

    std::string Repeat(int times) const
    {
        return Repeat(_Value, times);
    }

    // ---- IsPalindrome ----

    static bool IsPalindrome(const std::string& S1)
    {
        std::string lower = LowerAllString(S1);
        std::string reversed = std::string(lower.rbegin(), lower.rend());
        return lower == reversed;
    }

    bool IsPalindrome() const
    {
        return IsPalindrome(_Value);
    }

};

} // namespace MyLib
