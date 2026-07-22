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

		static bool IsValidDate(const Date& Date)
		{
			return	Date::IsValidDate(Date);
		}

	};
}