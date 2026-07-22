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

		static int ReadIntNumber(std::string_view ErrorMessage = "Invalid Number, Enter again")
		{
			int Number;
			while (!(std::cin >> Number)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage << "\n";
			}
			return Number;
		}

		static int ReadIntNumberBetween(int From, int To, std::string_view ErrorMessage = "Number is not within range, Enter again:")
		{
			int Number = ReadIntNumber();

			while (!IsNumberBetween(Number, From, To))
			{
				std::cout << ErrorMessage << "\n";
				Number = ReadIntNumber();
			}
			return Number;
		}

		static double ReadDblNumber(std::string_view ErrorMessage = "Invalid Number, Enter again")
		{
			double Number;
			while (!(std::cin >> Number)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage << "\n";
			}
			return Number;
		}

		static double ReadDblNumberBetween(double From, double To, std::string_view ErrorMessage = "Number is not within range, Enter again:")
		{
			double Number = ReadDblNumber();

			while (!IsNumberBetween(Number, From, To)) {
				std::cout << ErrorMessage << "\n";
				Number = ReadDblNumber();
			}
			return Number;
		}

		static bool IsValidDate(const Date& Date)
		{
			return	Date::IsValidDate(Date);
		}

	};
}