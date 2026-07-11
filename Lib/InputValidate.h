#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "Date.h"

class InputValidate
{

public:

	static bool IsNumberBetween(short Number, short From, short To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsDateBetween(const Date& date, const Date& From, const Date& To)
	{
		//Date>=From && Date<=To  
		if ((Date::IsDate1AfterDate2(date, From) || Date::IsDate1EqualDate2(date, From))
			&&
			(Date::IsDate1BeforeDate2(date, To) || Date::IsDate1EqualDate2(date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From  
		if ((Date::IsDate1AfterDate2(date, To) || Date::IsDate1EqualDate2(date, To))
			&&
			(Date::IsDate1BeforeDate2(date, From) || Date::IsDate1EqualDate2(date, From))
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