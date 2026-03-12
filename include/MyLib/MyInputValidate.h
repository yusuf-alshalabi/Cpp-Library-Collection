
#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "MyLib/MyDate.h"
namespace MyLib {

	class MyInputValidate
	{

	public:

		static bool IsNumberBetween(short Number, short From, short To)
		{
			if (Number >= From && Number <= To)
				return true;
			else
				return false;
		}

		static bool IsNumberBetween(int Number, int From, int To)
		{
			if (Number >= From && Number <= To)
				return true;
			else
				return false;

		}

		static bool IsNumberBetween(float Number, float From, float To)
		{
			if (Number >= From && Number <= To)
				return true;
			else
				return false;
		}

		static bool IsNumberBetween(double Number, double From, double To)
		{
			if (Number >= From && Number <= To)
				return true;
			else
				return false;
		}

		static bool IsDateBetween(MyDate Date, MyDate From, MyDate To)
		{
			//Date>=From && Date<=To
			if ((MyDate::IsDate1AfterDate2(Date, From) || MyDate::IsDate1EqualDate2(Date, From))
				&&
				(MyDate::IsDate1BeforeDate2(Date, To) || MyDate::IsDate1EqualDate2(Date, To))
				)
			{
				return true;
			}

			//Date>=To && Date<=From
			if ((MyDate::IsDate1AfterDate2(Date, To) || MyDate::IsDate1EqualDate2(Date, To))
				&&
				(MyDate::IsDate1BeforeDate2(Date, From) || MyDate::IsDate1EqualDate2(Date, From))
				)
			{
				return true;
			}

			return false;
		}

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

		static double ReadDblNumber(std::string ErrorMessage = "Invalid Number, Enter again\n")
		{
			double Number;
			while (!(std::cin >> Number)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize > ::max(), '\n');
				std::cout << ErrorMessage;
			}
			return Number;
		}

		static double ReadDblNumberBetween(double From, double To, std::string ErrorMessage = "Number is not within range, Enter again:\n")
		{
			double Number = ReadDblNumber();

			while (!IsNumberBetween(Number, From, To)) {
				std::cout << ErrorMessage;
				Number = ReadDblNumber();
			}
			return Number;
		}

		static bool IsValideDate(MyDate Date)
		{
			return	MyDate::IsValidDate(Date);
		}

	};

}