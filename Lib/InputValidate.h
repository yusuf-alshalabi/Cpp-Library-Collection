#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <limits>
#include <type_traits>
#include "Date.h"

namespace Core
{
	class InputValidate
	{

	public:

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

		static bool IsDateBetween(const Date& date, const Date& From, const Date& To)
		{
			if (From > To)
				return date >= To && date <= From;

			return date >= From && date <= To;
		}

		template <typename T = int>
		static T ReadNumber(std::string_view ErrorMessage = "Invalid Number, Enter again")
		{
			static_assert(std::is_integral_v<T> ||
				std::is_floating_point_v<T>,
				"ReadNumber accepts only numeric types!");

			T Number;
			while (!(std::cin >> Number))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage << "\n";
			}
			return Number;
		}

		template <typename T = int>
		static T ReadPositiveNumber(std::string_view ErrorMessage = "Invalid Number, Enter a positive number:")
		{
			T Number;
			do
			{
				Number = ReadNumber<T>();
				if (Number <= 0)
				{
					std::cout << ErrorMessage << "\n";
				}
			} while (Number <= 0);

			return Number;
		}

		template <typename T = int>
		static T ReadNumberBetween(T From, T To, std::string_view ErrorMessage = "Number is not within range, Enter again:")
		{
			T Number = ReadNumber<T>();

			while (!IsNumberBetween(Number, From, To))
			{
				std::cout << ErrorMessage << "\n";
				Number = ReadNumber<T>();
			}
			return Number;
		}

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

		static char ReadCharacter(std::string_view Message = "Enter a character:")
		{
			char Character;
			std::cout << Message << " ";
			std::cin >> Character;

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return Character;
		}

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

		static Date ReadDate(std::string_view Message = "Enter Date (DD/MM/YYYY):",
			std::string_view ErrorMessage = "Invalid Date Format or Calendar Date! Try again:")
		{
			Date date;
			std::cout << Message << " ";

			while (!(std::cin >> date))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage << "\n" << Message << " ";
			}

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return date;
		}

		static bool IsValidDate(const Date& Date)
		{
			return	Date::IsValidDate(Date);
		}

	};
}