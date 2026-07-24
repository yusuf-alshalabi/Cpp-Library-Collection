#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <limits>
#include <type_traits>
#include <cctype>
#include "Date.h"

namespace Core
{
	/**
	 * @class InputValidate
	 * @brief Utility class providing robust console input validation and user prompt routines.
	 *
	 * @details Handles input stream errors, buffer cleansing, numeric range checks,
	 * string validation, and date entry processing using Modern C++ features (C++17/C++20).
	 */
	class InputValidate
	{

	public:

		/**
		 * @brief Checks whether a numeric value lies within a specified inclusive range.
		 *
		 * @tparam T Numeric integral or floating-point type.
		 * @param Number The value to validate.
		 * @param From Lower bound (or upper bound if inverted).
		 * @param To Upper bound (or lower bound if inverted).
		 * @return true if \p Number is between \p From and \p To, false otherwise.
		 * @note Automatically swaps bounds if \p From is greater than \p To.
		 */
		template <typename T>
		static bool IsNumberBetween(T Number, T From, T To)
		{
			static_assert(std::is_integral_v<T> ||
				std::is_floating_point_v<T>,
				"Only numeric types allowed!");

			if (From > To)
				return Number >= To && Number <= From;

			return Number >= From && Number <= To;
		}

		/**
		 * @brief Checks whether a Date object falls within a specified inclusive range.
		 *
		 * @param date The Date object to evaluate.
		 * @param From Start date boundary.
		 * @param To End date boundary.
		 * @return true if \p date is within range, false otherwise.
		 * @note Swaps limits automatically if \p From is greater than \p To.
		 */
		static bool IsDateBetween(const Date& date, const Date& From, const Date& To)
		{
			if (From > To)
				return date >= To && date <= From;

			return date >= From && date <= To;
		}

		/**
		 * @brief Reads a generic numeric input from standard input stream with error handling.
		 *
		 * @tparam T Numeric type to read (defaults to int).
		 * @param Message Prompt message displayed to the user.
		 * @param ErrorMessage Error prompt shown upon invalid stream state or bad input.
		 * @return T Validated numeric value entered by the user.
		 * @details Clears the fail state of \c std::cin and flushes leftover characters
		 * in the buffer to guarantee clean stream state for subsequent reads.
		 */
		template <typename T = int>
		static T ReadNumber(std::string_view Message = "Enter a number:", std::string_view ErrorMessage = "Invalid Number, Enter again:")
		{
			static_assert(std::is_integral_v<T> ||
				std::is_floating_point_v<T>,
				"ReadNumber accepts only numeric types!");

			T Number;
			std::cout << Message << " ";

			while (!(std::cin >> Number))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage << "\n" << Message << " ";
			}

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return Number;
		}

		/**
		 * @brief Reads a strictly positive numeric value (> 0).
		 *
		 * @tparam T Numeric type (defaults to int).
		 * @param Message Prompt message shown to the user.
		 * @param ErrorMessage Error prompt shown if input is less than or equal to zero.
		 * @return T Validated positive numeric value.
		 */
		template <typename T = int>
		static T ReadPositiveNumber(std::string_view Message = "Enter a positive number:", std::string_view ErrorMessage = "Invalid Number, Enter a positive number:")
		{
			T Number;
			do
			{
				Number = ReadNumber<T>(Message);
				if (Number <= 0)
				{
					std::cout << ErrorMessage << "\n";
				}
			} while (Number <= 0);

			return Number;
		}

		/**
		 * @brief Reads a numeric value forced within an inclusive range [From, To].
		 *
		 * @tparam T Numeric type (defaults to int).
		 * @param From Minimum acceptable value.
		 * @param To Maximum acceptable value.
		 * @param Message Prompt message shown to the user.
		 * @param ErrorMessage Error message shown if input falls outside the range.
		 * @return T Validated numeric value within range.
		 */
		template <typename T = int>
		static T ReadNumberBetween(T From, T To, std::string_view Message = "Enter a number:", std::string_view ErrorMessage = "Number is not within range, Enter again:")
		{
			T Number;
			do
			{
				Number = ReadNumber<T>(Message);
				if (!IsNumberBetween(Number, From, To))
				{
					std::cout << ErrorMessage << "\n";
				}
			} while (!IsNumberBetween(Number, From, To));

			return Number;
		}

		/**
		 * @brief Reads a confirmation choice from the user (Y/N or y/n).
		 *
		 * @param Message Prompt question to display.
		 * @return true if user answered 'y' or 'Y', false if 'n' or 'N'.
		 * @details Performs case-insensitive verification and safely consumes buffer line breaks.
		 */
		static bool ReadYesNoOption(std::string_view Message = "Are you sure?")
		{
			char Choice;
			do
			{
				std::cout << Message << " (Y/N): ";
				std::cin >> Choice;

				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				Choice = static_cast<char>(std::tolower(static_cast<unsigned char>(Choice)));

				if (Choice != 'y' && Choice != 'n')
				{
					std::cout << "Invalid choice! Please enter 'Y' or 'N'.\n";
				}

			} while (Choice != 'y' && Choice != 'n');

			return Choice == 'y';
		}

		/**
		 * @brief Reads a single character input.
		 *
		 * @param Message Prompt message shown to the user.
		 * @return char The character entered by the user.
		 */
		static char ReadCharacter(std::string_view Message = "Enter a character:")
		{
			char Character;
			std::cout << Message << " ";
			std::cin >> Character;

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return Character;
		}

		/**
		 * @brief Reads a non-empty text line from standard input.
		 *
		 * @param Message Prompt message shown to the user.
		 * @param ErrorMessage Error message shown if the user submits an empty line.
		 * @return std::string Validated non-empty string.
		 * @details Leverages \c std::ws to skip leading whitespace characters.
		 */
		static std::string ReadString(std::string_view Message = "Enter a text:", std::string_view ErrorMessage = "Invalid input! Text cannot be empty.")
		{
			std::string Text;
			do
			{
				std::cout << Message << " ";
				std::getline(std::cin >> std::ws, Text);

				if (Text.empty())
				{
					std::cout << ErrorMessage << "\n";
				}

			} while (Text.empty());

			return Text;
		}

		/**
		 * @brief Reads and validates a Date object from standard input stream.
		 *
		 * @param Message Prompt message shown to the user.
		 * @param ErrorMessage Error message shown when date parsing fails or calendar date is invalid.
		 * @return Date A fully validated Date instance.
		 * @details Catches runtime exceptions and handles stream recovery seamlessly.
		 */
		static Date ReadDate(std::string_view Message = "Enter Date (DD/MM/YYYY):",
			std::string_view ErrorMessage = "Invalid Date Format or Calendar Date! Try again:")
		{
			Date date;
			bool isValid = false;

			std::cout << Message << " ";

			while (!isValid)
			{
				try
				{
					if (std::cin >> date)
					{
						isValid = true;
					}
					else
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << ErrorMessage << "\n" << Message << " ";
					}
				}
				catch (...)
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << ErrorMessage << "\n" << Message << " ";
				}
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return date;
		}

		/**
		 * @brief Helper function to verify the validity of a given Date object.
		 *
		 * @param date Reference to the Date object to validate.
		 * @return true if date is valid according to calendar rules, false otherwise.
		 */
		static bool IsValidDate(const Date& date)
		{
			return date.IsValid();
		}

	};
}