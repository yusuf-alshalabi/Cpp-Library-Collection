#pragma once
#include <iostream>
#include <string>
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
			//Date>=From && Date<=To  
			if ((Date::IsDateAfterDate(date, From) || Date::IsDateEqualDate(date, From))
				&&
				(Date::IsDateBeforeDate(date, To) || Date::IsDateEqualDate(date, To))
				)
			{
				return true;
			}

			//Date>=To && Date<=From  
			if ((Date::IsDateAfterDate(date, To) || Date::IsDateEqualDate(date, To))
				&&
				(Date::IsDateBeforeDate(date, From) || Date::IsDateEqualDate(date, From))
				)
			{
				return true;
			}

			return false;
		}

		static int ReadIntNumber(const std::string& ErrorMessage = "Invalid Number, Enter again\n")
		{
			int Number;
			while (!(std::cin >> Number)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage;
			}
			return Number;
		}

		static int ReadIntNumberBetween(int From, int To, const std::string& ErrorMessage = "Number is not within range, Enter again:\n")
		{
			int Number = ReadIntNumber();

			while (!IsNumberBetween(Number, From, To))
			{
				std::cout << ErrorMessage;
				Number = ReadIntNumber();
			}
			return Number;
		}

		static double ReadDblNumber(const std::string& ErrorMessage = "Invalid Number, Enter again\n")
		{
			double Number;
			while (!(std::cin >> Number)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage;
			}
			return Number;
		}

		static double ReadDblNumberBetween(double From, double To, const std::string& ErrorMessage = "Number is not within range, Enter again:\n")
		{
			double Number = ReadDblNumber();

			while (!IsNumberBetween(Number, From, To)) {
				std::cout << ErrorMessage;
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