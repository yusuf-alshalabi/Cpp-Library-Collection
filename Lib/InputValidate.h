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

		static int ReadIntNumberBetween(int From, int To, std::string_view ErrorMessage = "Number is not within range, Enter again:")
		{
			int Number = ReadNumber<int>(ErrorMessage);

			while (!IsNumberBetween(Number, From, To))
			{
				std::cout << ErrorMessage << "\n";
				Number = ReadNumber<int>(ErrorMessage);
			}
			return Number;
		}

		static double ReadDblNumberBetween(double From, double To, std::string_view ErrorMessage = "Number is not within range, Enter again:")
		{
			double Number = ReadNumber<double>(ErrorMessage);

			while (!IsNumberBetween(Number, From, To)) {
				std::cout << ErrorMessage << "\n";
				Number = ReadNumber<double>(ErrorMessage);
			}
			return Number;
		}

		static bool IsValidDate(const Date& Date)
		{
			return	Date::IsValidDate(Date);
		}

	};
}