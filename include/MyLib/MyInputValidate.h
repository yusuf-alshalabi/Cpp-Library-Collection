#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "MyLib/MyDate.h"

namespace MyLib {

	class MyInputValidate
	{

	public:

		// Template function for number range validation (eliminates code duplication)
		template<typename T>
		static bool IsNumberBetween(T Number, T From, T To)
		{
			return Number >= From && Number <= To;
		}

		// Simplified date range validation using CompareDates
		static bool IsDateBetween(MyDate Date, MyDate From, MyDate To)
		{
			// Determine the actual min and max dates (handles reversed ranges)
			MyDate minDate = (MyDate::CompareDates(From, To) == MyDate::enDateCompare::Before) ? From : To;
			MyDate maxDate = (MyDate::CompareDates(From, To) == MyDate::enDateCompare::After) ? From : To;
			
			// Check if Date is between minDate and maxDate (inclusive)
			return MyDate::CompareDates(Date, minDate) != MyDate::enDateCompare::Before && 
				   MyDate::CompareDates(Date, maxDate) != MyDate::enDateCompare::After;
		}

		// Fixed typo: IsValidDate instead of IsValideDate
		static bool IsValidDate(MyDate Date)
		{
			return MyDate::IsValidDate(Date);
		}

		// Safe integer input with error handling
		static int ReadIntNumber(std::string ErrorMessage = "Invalid Number, Enter again\n")
		{
			int Number;
			while (!(std::cin >> Number)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage;
			}
			return Number;
		}

		// Safe integer input with range validation
		static int ReadIntNumberBetween(int From, int To, std::string ErrorMessage = "Number is not within range, Enter again:\n")
		{
			int Number = ReadIntNumber();

			while (!IsNumberBetween(Number, From, To))
			{
				std::cout << ErrorMessage;
				Number = ReadIntNumber();
			}
			return Number;
		}

		// Safe double input with error handling
		static double ReadDblNumber(std::string ErrorMessage = "Invalid Number, Enter again\n")
		{
			double Number;
			while (!(std::cin >> Number)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << ErrorMessage;
			}
			return Number;
		}

		// Safe double input with range validation
		static double ReadDblNumberBetween(double From, double To, std::string ErrorMessage = "Number is not within range, Enter again:\n")
		{
			double Number = ReadDblNumber();

			while (!IsNumberBetween(Number, From, To)) {
				std::cout << ErrorMessage;
				Number = ReadDblNumber();
			}
			return Number;
		}
		static bool IsValidSDate(MyDate Date)
		{
			return	MyDate::IsValidDate(Date);
		}
	};

}