#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <type_traits>
#include <cmath>

namespace Core {
    /**
     * @class Util
     * @brief A utility class containing static helper methods for random generation, array manipulation, and text encryption.
     *
     * @details
     * Designed to provide common utility tasks for C++ applications.
     * It uses Modern C++ features such as Templates and Type Traits for type safety and performance.
     */
    class Util
    {
    private:
        // ASCII character boundaries to replace magic numbers with named constants
        static constexpr int ASCII_LOWERCASE_A = 97;
        static constexpr int ASCII_LOWERCASE_Z = 122;
        static constexpr int ASCII_UPPERCASE_A = 65;
        static constexpr int ASCII_UPPERCASE_Z = 90;
        static constexpr int ASCII_DIGIT_0 = 48;
        static constexpr int ASCII_DIGIT_9 = 57;
        static constexpr int ASCII_SPECIAL_START = 33;
        static constexpr int ASCII_SPECIAL_END = 47;

    public:
        /**
         * @enum enCharType
         * @brief Specifies the type of characters used for random text generation.
         */
        enum enCharType {
            SmallLetter = 1,      /**< Lowercase letters (a-z) */
            CapitalLetter = 2,    /**< Uppercase letters (A-Z) */
            Digit = 3,           /**< Digits (0-9) */
            MixChars = 4,        /**< A mix of letters and digits */
            SpecialCharacter = 5 /**< Special symbols like (!@#$) */
        };

        /**
         * @brief Seeds the random number generator.
         *
         * @details
         * **What it does:** Calls `srand(time(NULL))` to link pseudo-random numbers to system time.
         * **Why:** Without seeding, `rand()` generates the exact same sequence of numbers every time the application runs.
         * **Note:** Should be called only once at application startup.
         */
        static void Srand()
        {
            srand((unsigned)time(NULL));
        }

        /**
         * @brief Generates a random integer within a closed range [From, To].
         *
         * @tparam T The integer type (e.g., int, short, long long). Defaults to int.
         * @param From Lower bound of the range.
         * @param To Upper bound of the range.
         * @return T A random integer of type T.
         *
         * @details
         * **Under the Hood:**
         * 1. **`static_assert`**: Ensures at compile-time that `T` is an integral type (`is_integral_v`).
         * 2. **Overflow Prevention:** Converts bounds to `long long` before calculating `range` to prevent arithmetic overflow when bounds are close to integer limits.
         * 3. **Auto-Swap:** Swaps `From` and `To` if `From > To` to ensure valid range calculations.
         */
        template <typename T = int>
        static T RandomNumber(T From, T To)
        {
            static_assert(std::is_integral_v<T>, "RandomNumber accepts only integral types!");

            if (From == To)
            {
                return From;
            }

            if (From > To)
            {
                Swap(From, To);
            }

            long long range = static_cast<long long>(To) - static_cast<long long>(From) + 1;
            long long randomOffset = std::abs(static_cast<long long>(rand())) % range;

            return static_cast<T>(From + randomOffset);
        }

        /**
         * @brief Generates a random floating-point number within a continuous range [From, To].
         *
         * @tparam T Floating-point type (float, double, long double). Defaults to float.
         * @param From Lower bound.
         * @param To Upper bound.
         * @return T A random floating-point value.
         *
         * @details
         * **How it works:**
         * Modulo `%` does not work with floating-point numbers. Instead, it calculates a normalized fraction between 0.0 and 1.0:
         * \f$ \text{fraction} = \frac{\text{rand}()}{\text{RAND\_MAX}} \f$
         * It then scales and shifts this fraction across `[From, To]`.
         */
        template <typename T = float>
        static T RandomFloat(T From, T To)
        {
            static_assert(std::is_floating_point_v<T>, "RandomFloat accepts only floating-point types (float, double, long double)!");

            if (From == To)
            {
                return From;
            }

            if (From > To)
            {
                Swap(From, To);
            }

            T fraction = static_cast<T>(rand()) / static_cast<T>(RAND_MAX);

            return From + fraction * (To - From);
        }

        /**
         * @brief Generates a random character based on the specified character type.
         *
         * @param CharType The category of character to generate.
         * @return char The generated character.
         */
        static char GetRandomCharacter(enCharType CharType)
        {
            if (CharType == MixChars)
            {
                CharType = (enCharType)RandomNumber(1, 3);
            }

            switch (CharType)
            {
            case enCharType::SmallLetter:
                return char(RandomNumber(ASCII_LOWERCASE_A, ASCII_LOWERCASE_Z));
            case enCharType::CapitalLetter:
                return char(RandomNumber(ASCII_UPPERCASE_A, ASCII_UPPERCASE_Z));
            case enCharType::SpecialCharacter:
                return char(RandomNumber(ASCII_SPECIAL_START, ASCII_SPECIAL_END));
            case enCharType::Digit:
                return char(RandomNumber(ASCII_DIGIT_0, ASCII_DIGIT_9));
            default:
                return char(RandomNumber(ASCII_UPPERCASE_A, ASCII_UPPERCASE_Z));
            }
        }

        /**
         * @brief Generates a random word of a specified length.
         *
         * @param CharType The type of characters composing the word.
         * @param Length The desired word length.
         * @return std::string The generated word, or an empty string if Length <= 0.
         *
         * @details
         * **Memory Optimization:** Uses `Word.reserve(Length)` to pre-allocate memory once, preventing repeated heap reallocations during string concatenation in the loop.
         */
        static std::string GenerateWord(enCharType CharType, short Length)
        {
            if (Length <= 0)
                return "";

            std::string Word;
            Word.reserve(Length);

            for (short i = 0; i < Length; i++)
            {
                Word += GetRandomCharacter(CharType);
            }
            return Word;
        }

        /**
         * @brief Generates a formatted license key (e.g., XXXX-XXXX-XXXX-XXXX).
         *
         * @param CharType Character category for the key (defaults to CapitalLetter).
         * @return std::string A 19-character license key string.
         */
        static std::string GenerateKey(enCharType CharType = CapitalLetter)
        {
            std::string Key = "";
            Key.reserve(19); // 16 characters + 3 hyphens

            Key = GenerateWord(CharType, 4);
            Key += "-";
            Key += GenerateWord(CharType, 4);
            Key += "-";
            Key += GenerateWord(CharType, 4);
            Key += "-";
            Key += GenerateWord(CharType, 4);

            return Key;
        }

        /**
         * @brief Prints a specified number of license keys to an output stream.
         *
         * @param NumberOfKeys The count of keys to print.
         * @param CharType Character category for the keys.
         * @param Output Destination output stream (defaults to std::cout).
         */
        static void PrintKeys(short NumberOfKeys, enCharType CharType = CapitalLetter, std::ostream& Output = std::cout)
        {
            for (short i = 1; i <= NumberOfKeys; i++)
            {
                Output << "Key [" << i << "] : ";
                Output << GenerateKey(CharType) << "\n";
            }
        }

        /**
         * @brief Fills an integer array with random values.
         *
         * @param arr Target array.
         * @param arrLength Number of elements in the array.
         * @param From Minimum random value.
         * @param To Maximum random value.
         */
        static void FillArrayWithRandomNumbers(int arr[], size_t arrLength, int From, int To)
        {
            for (size_t i = 0; i < arrLength; i++)
                arr[i] = RandomNumber(From, To);
        }

        /**
         * @brief Fills a string array with random words.
         */
        static void FillArrayWithRandomWords(std::string arr[], size_t arrLength, enCharType CharType, short Wordlength)
        {
            for (size_t i = 0; i < arrLength; i++)
                arr[i] = GenerateWord(CharType, Wordlength);
        }

        /**
         * @brief Fills a string array with generated license keys.
         */
        static void FillArrayWithRandomKeys(std::string arr[], size_t arrLength, enCharType CharType = CapitalLetter)
        {
            for (size_t i = 0; i < arrLength; i++)
                arr[i] = GenerateKey(CharType);
        }

        /**
         * @brief Swaps two values of any type (Generic Swap).
         *
         * @tparam T Type of variables to swap.
         * @param A Reference to the first variable.
         * @param B Reference to the second variable.
         */
        template<typename T>
        static void Swap(T& A, T& B)
        {
            T Temp = A;
            A = B;
            B = Temp;
        }

        /**
         * @brief Shuffles an array randomly using the Fisher-Yates algorithm.
         *
         * @tparam T Element type of the array.
         * @param arr Target array.
         * @param arrLength Array element count.
         *
         * @details
         * **Algorithm:** Iterates backward from the last element to the first, swapping the current element with a randomly chosen element from the remaining unshuffled portion. This guarantees an unbiased uniform shuffle.
         */
        template<typename T>
        static void ShuffleArray(T arr[], size_t arrLength)
        {
            if (arrLength <= 1)
                return;

            for (size_t i = arrLength - 1; i > 0; i--)
            {
                size_t randomIndex = static_cast<size_t>(RandomNumber(0, static_cast<int>(i)));
                Swap(arr[i], arr[randomIndex]);
            }
        }

        /**
         * @brief Generates a string with a specified number of tab characters (`\t`).
         *
         * @param NumberOfTabs Count of tab characters desired.
         * @return std::string The resulting string, or empty string if NumberOfTabs <= 0.
         *
         * @details
         * **Efficiency:** Uses `std::string(count, char)` constructor to allocate and fill memory in a single step without manual loops.
         */
        static std::string Tabs(short NumberOfTabs)
        {
            if (NumberOfTabs <= 0)
                return "";

            return std::string(static_cast<size_t>(NumberOfTabs), '\t');
        }

        /**
         * @brief Encrypts text using a basic Caesar cipher algorithm.
         *
         * @param Text Plain text string to encrypt.
         * @param EncryptionKey Numerical shift value.
         * @return std::string Encrypted string (or empty if input is empty).
         */
        static std::string EncryptText(const std::string& Text, short EncryptionKey)
        {
            if (Text.empty())
                return "";

            std::string Result;
            Result.reserve(Text.length());

            for (char Ch : Text)
            {
                Result += static_cast<char>(Ch + EncryptionKey);
            }

            return Result;
        }

        /**
         * @brief Decrypts text encrypted with the Caesar cipher.
         *
         * @param Text Encrypted string to decrypt.
         * @param EncryptionKey Matching numerical shift value used during encryption.
         * @return std::string Decrypted plain text (or empty if input is empty).
         */
        static std::string DecryptText(const std::string& Text, short EncryptionKey)
        {
            if (Text.empty())
                return "";

            std::string Result;
            Result.reserve(Text.length());

            for (char Ch : Text)
            {
                Result += static_cast<char>(Ch - EncryptionKey);
            }

            return Result;
        }

    };
}