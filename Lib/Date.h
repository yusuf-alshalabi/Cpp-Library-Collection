
#pragma warning(disable : 4996)
#pragma once

#include<iostream>
#include<string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "String.h"

class Date
{

private:

	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

	inline static const short Days[12] =
	{
		31,28,31,30,31,30,
		31,31,30,31,30,31
	};

	inline static constexpr const char* DayNames[7] =
	{
		"Sun","Mon","Tue","Wed","Thu","Fri","Sat"
	};

	inline static constexpr const char* MonthNames[12] =
	{
		"Jan","Feb","Mar",
		"Apr","May","Jun",
		"Jul","Aug","Sep",
		"Oct","Nov","Dec"
	};

	static void AdjustDayIfNeeded(Date& SourceDate)
	{
		short DaysInMonth =
			NumberOfDaysInAMonth(SourceDate.Month, SourceDate.Year);

		if (SourceDate.Day > DaysInMonth)
			SourceDate.Day = DaysInMonth;
	}


	static int DateToSerial(const Date& SourceDate)
	{
		int Serial = 0;

		// Add days of previous years
		for (int Year = 1; Year < SourceDate.GetYear(); Year++)
		{
			Serial += NumberOfDaysInAYear(Year);
		}

		// Add days of previous months
		for (int Month = 1; Month < SourceDate.GetMonth(); Month++)
		{
			Serial += NumberOfDaysInAMonth(Month, SourceDate.GetYear());
		}

		// Add current day
		Serial += (SourceDate.GetDay() - 1);
		return Serial;
	}

	static Date SerialToDate(int Serial)
	{
		Serial++;

		Date SourceDate;

		int Year = 1;

		while (Serial > NumberOfDaysInAYear(Year))
		{
			Serial -= NumberOfDaysInAYear(Year);
			Year++;
		}

		int Month = 1;

		while (Serial > NumberOfDaysInAMonth(Month, Year))
		{
			Serial -= NumberOfDaysInAMonth(Month, Year);
			Month++;
		}

		SourceDate.Year = Year;
		SourceDate.Month = Month;
		SourceDate.Day = Serial;

		return SourceDate;
	}


	static Date ShiftDays(int Days, const Date& SourceDate)
	{
		int Serial = DateToSerial(SourceDate);
		Serial += Days;

		if (Serial < 0)
		{
			throw std::out_of_range("Date cannot be before 01/01/0001.");
		}

		return SerialToDate(Serial);
	}

	static Date ShiftMonths(int Months, Date SourceDate)
	{
		int TotalMonths = (SourceDate.GetYear() - 1) * 12 + (SourceDate.GetMonth() - 1);

		TotalMonths += Months;

		if (TotalMonths < 0)
		{
			throw std::out_of_range("Date cannot be before 01/01/0001.");
		}

		SourceDate.SetYear((TotalMonths / 12) + 1);
		SourceDate.SetMonth((TotalMonths % 12) + 1);

		AdjustDayIfNeeded(SourceDate);

		return SourceDate;
	}

	static Date ShiftYears(int Years, Date SourceDate)
	{

		if (SourceDate.GetYear() + Years < 1)
		{
			throw std::out_of_range("Date cannot be before 01/01/0001.");
		}

		SourceDate.SetYear(SourceDate.GetYear() + Years);
		AdjustDayIfNeeded(SourceDate);

		return SourceDate;
	}



public:

	Date()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	Date(const std::string& sDate)
	{
		std::vector<std::string> vDate = String::Split(sDate, "/");

		if (vDate.size() != 3)
		{
			throw std::invalid_argument(
				"Invalid date format. Expected DD/MM/YYYY.");
		}

		try
		{
			_Day = static_cast<short>(std::stoi(vDate[0]));
			_Month = static_cast<short>(std::stoi(vDate[1]));
			_Year = static_cast<short>(std::stoi(vDate[2]));
		}
		catch (...)
		{
			throw std::invalid_argument(
				"Invalid date format. Expected DD/MM/YYYY.");
		}

		if (!IsValid())
		{
			throw std::invalid_argument(
				"Invalid date.");
		}
	}

	Date(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;

		if (!IsValid())
		{
			throw std::invalid_argument("invalid date.");
		}
	}

	Date(short DateOrderInYear, short Year)
	{
		//This will construct a date by date order in year  
		Date Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year = Date1.Year;
	}

	Date(const Date&) = default;

	Date(Date&&) noexcept = default;

	Date& operator=(const Date&) = default;

	Date& operator=(Date&&) noexcept = default;

	void SetDay(short Day) {
		_Day = Day;
	}

	short GetDay() const {
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) {
		_Month = Month;
	}

	short GetMonth() const {
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;


	void SetYear(short Year) {
		_Year = Year;
	}

	short GetYear() const {
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print() const
	{
		std::cout << DateToString() << std::endl;
	}

	static Date GetSystemDate()
	{
		return Date();
	}

	static	bool IsValidDate(const Date& Date)
	{

		if (Date.Day < 1 || Date.Day>31)
			return false;

		if (Date.Month < 1 || Date.Month>12)
			return false;

		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				if (Date.Day > 29)
					return false;
			}
			else
			{
				if (Date.Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

		if (Date.Day > DaysInMonth)
			return false;

		return true;

	}

	bool IsValid()const
	{
		return IsValidDate(*this);
	}

	static std::string DateToString(const Date& Date)
	{
		std::ostringstream Out;

		Out << std::setfill('0')
			<< std::setw(2) << Date.Day << "/"
			<< std::setw(2) << Date.Month << "/"
			<< Date.Year;

		return Out.str();
	}

	std::string DateToString()const
	{
		return  DateToString(*this);
	}

	static bool IsLeapYear(short Year)
	{

		// if year is divisible by 4 AND not divisible by 100  
		// OR if year is divisible by 400  
		// then it is a leap year  
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool IsLeapYear() const
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInAYear(short Year)
	{
		return  IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInAYear() const
	{
		return  NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return  NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear() const
	{
		return  NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year)
	{
		return  NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear() const
	{
		return  NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return  NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear() const
	{
		return  NumberOfSecondsInAYear(_Year);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{

		if (Month < 1 || Month>12)
			return  0;

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : Days[Month - 1];

	}

	short NumberOfDaysInAMonth() const
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return  NumberOfDaysInAMonth(Month, Year) * 24;
	}

	short NumberOfHoursInAMonth() const
	{
		return  NumberOfDaysInAMonth(_Month, _Year) * 24;
	}

	static int NumberOfMinutesInAMonth(short Month, short Year)
	{
		return  NumberOfHoursInAMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInAMonth() const
	{
		return  NumberOfHoursInAMonth(_Month, _Year) * 60;
	}

	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return  NumberOfMinutesInAMonth(Month, Year) * 60;
	}

	int NumberOfSecondsInAMonth() const
	{
		return  NumberOfMinutesInAMonth(_Month, _Year) * 60;
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian:  
		//0:sun, 1:Mon, 2:Tue...etc  
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder() const
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	static std::string DayShortName(short DayOfWeekOrder)
	{
		std::string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder];

	}

	static std::string DayShortName(short Day, short Month, short Year)
	{
		return DayNames[DayOfWeekOrder(Day, Month, Year)];

	}

	std::string DayShortName() const
	{

		std::string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];

	}

	static std::string MonthShortName(short MonthNumber)
	{
		return (MonthNames[MonthNumber - 1]);
	}

	std::string MonthShortName() const
	{

		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;

		// Index of the day from 0 to 6  
		int current = DayOfWeekOrder(1, Month, Year);

		NumberOfDays = NumberOfDaysInAMonth(Month, Year);

		// Print the current month name  
		std::printf("\n  _______________%s_______________\n\n",
			MonthShortName(Month).c_str());

		// Print the columns  
		std::printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		// Print appropriate spaces  
		int i;
		for (i = 0; i < current; i++)
			std::printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			std::printf("%5d", j);


			if (++i == 7)
			{
				i = 0;
				std::printf("\n");
			}
		}

		std::printf("\n  _________________________________\n");

	}

	void PrintMonthCalendar() const
	{
		PrintMonthCalendar(_Month, _Year);
	}

	static void PrintYearCalendar(int Year)
	{
		std::printf("\n  _________________________________\n\n");
		std::printf("           Calendar - %d\n", Year);
		std::printf("  _________________________________\n");


		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}

		return;
	}

	void PrintYearCalendar() const
	{
		std::printf("\n  _________________________________\n\n");
		std::printf("           Calendar - %d\n", _Year);
		std::printf("  _________________________________\n");


		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, _Year);
		}

		return;
	}

	static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{


		short TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	short DaysFromTheBeginingOfTheYear() const
	{


		short TotalDays = 0;

		for (int i = 1; i <= _Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, _Year);
		}

		TotalDays += _Day;

		return TotalDays;
	}

	static Date GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{

		Date Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}

		}

		return Date;
	}

	void AddDays(short Days)
	{


		short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
		short MonthDays = 0;

		_Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(_Month, _Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				_Month++;

				if (_Month > 12)
				{
					_Month = 1;
					_Year++;

				}
			}
			else
			{
				_Day = RemainingDays;
				break;
			}

		}


	}

	static bool IsDate1BeforeDate2(const Date& Date1, const Date& Date2)
	{
		return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}

	bool IsDateBeforeDate2(Date Date2) const
	{
		//note: *this sends the current object :-)   
		return  IsDate1BeforeDate2(*this, Date2);

	}

	static bool IsDate1EqualDate2(const Date& Date1, const Date& Date2)
	{
		return  (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}

	bool IsDateEqualDate2(Date Date2) const
	{
		return  IsDate1EqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(const Date& SourceDate)
	{

		return (SourceDate.Day == NumberOfDaysInAMonth(SourceDate.Month, SourceDate.Year));

	}

	bool IsLastDayInMonth() const
	{

		return IsLastDayInMonth(*this);

	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	static Date AddOneDay(Date Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void AddOneDay()

	{
		*this = AddOneDay(*this);
	}

	static void  SwapDates(Date& FirstDate, Date& SecondDate)
	{

		Date TempDate;
		TempDate = FirstDate;
		FirstDate = SecondDate;
		SecondDate = TempDate;

	}

	static int GetDifferenceInDays(const Date& StartDate, const Date& EndDate ,bool IncludeEndDay = false)
	{
		int Difference = DateToSerial(EndDate) - DateToSerial(StartDate);

		if (IncludeEndDay)
		{
			if (Difference >= 0)
				Difference++;
			else
				Difference--;
		}

		return Difference;
	}

	int GetDifferenceInDays(Date Date2, bool IncludeEndDay = false) const
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static short CalculateMyAgeInDays(const Date& BirthDate)
	{
		return GetDifferenceInDays(BirthDate, Date::GetSystemDate(), true);
	}
	//above no need to have nonstatic function for the object because it does not depend on any data from it.  

	static Date IncreaseDateByOneWeek(Date& SourceDate)
	{
		return ShiftDays(7, SourceDate);
	}

	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static Date IncreaseDateByXWeeks(short Weeks, Date& SourceDate)
	{
		return ShiftDays(Weeks * 7, SourceDate);
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		*this = IncreaseDateByXWeeks(Weeks, *this);
	}

	static Date IncreaseDateByOneMonth(Date& SourceDate)
	{
		return ShiftMonths(1, SourceDate);
	}

	void IncreaseDateByOneMonth()
	{

		*this = IncreaseDateByOneMonth(*this);

	}

	static Date IncreaseDateByXDays(short Days, Date& SourceDate)
	{
		return ShiftDays(Days, SourceDate);
	}

	void IncreaseDateByXDays(short Days)
	{

		*this = IncreaseDateByXDays(Days, *this);
	}

	static Date IncreaseDateByXMonths(short Months, Date& SourceDate)
	{
		return ShiftMonths(Months, SourceDate);
	}
	
	void IncreaseDateByXMonths(short Months)
	{
		*this = IncreaseDateByXMonths(Months, *this);
	}

	static Date IncreaseDateByOneYear(Date& SourceDate)
	{
		return ShiftYears(1, SourceDate);
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static Date IncreaseDateByXYears(short Years, Date& SourceDate)
	{
		return ShiftYears(Years, SourceDate);
	}

	void IncreaseDateByXYears(short Years)
	{
		*this = IncreaseDateByXYears(Years, *this);
	}

	static Date IncreaseDateByOneDecade(Date& SourceDate)
	{
		return ShiftYears(10, SourceDate);
	}

	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static Date IncreaseDateByXDecades(short Decade, Date& SourceDate)
	{
		return ShiftYears(Decade * 10, SourceDate);
	}

	void IncreaseDateByXDecades(short Decade)
	{
		*this = IncreaseDateByXDecades(Decade, *this);
	}

	static Date IncreaseDateByOneCentury(Date& SourceDate)
	{
		return ShiftYears(100, SourceDate);
	}

	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static Date IncreaseDateByOneMillennium(Date& SourceDate)
	{
		return ShiftYears(1000, SourceDate);
	}

	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static Date DecreaseDateByOneDay(Date SourceDate)
	{
		return ShiftDays(-1, SourceDate);
	}

	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static Date DecreaseDateByOneWeek(Date& SourceDate)
	{

		return ShiftDays(-7, SourceDate);
	}

	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static Date DecreaseDateByXWeeks(short Weeks, Date& SourceDate)
	{
		return ShiftDays(-Weeks * 7, SourceDate);
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		*this = DecreaseDateByXWeeks(Weeks, *this);
	}

	static Date DecreaseDateByOneMonth(Date& SourceDate)
	{
		return ShiftMonths(-1, SourceDate);
	}

	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static Date DecreaseDateByXDays(short Days, Date& SourceDate)
	{
		return ShiftDays(-Days, SourceDate);
	}

	void DecreaseDateByXDays(short Days)
	{
		*this =	DecreaseDateByXDays(Days, *this);
	}

	static Date DecreaseDateByXMonths(short Months, Date& SourceDate)
	{
		return ShiftMonths(-Months, SourceDate);
	}

	void DecreaseDateByXMonths(short Months)
	{
		*this = DecreaseDateByXMonths(Months, *this);
	}

	static Date DecreaseDateByOneYear(Date& SourceDate)
	{
		return ShiftYears(-1, SourceDate);
	}

	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static Date DecreaseDateByXYears(short Years, Date& SourceDate)
	{
		return ShiftYears(-Years, SourceDate);
	}

	void DecreaseDateByXYears(short Years)
	{
		*this = DecreaseDateByXYears(Years, *this);
	}

	static Date DecreaseDateByOneDecade(Date& SourceDate)
	{
		return ShiftYears(-10, SourceDate);
	}

	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static Date DecreaseDateByXDecades(short Decades, Date& SourceDate)
	{
		return ShiftYears(-Decades * 10, SourceDate);
	}

	void DecreaseDateByXDecades(short Decades)
	{
		*this = DecreaseDateByXDecades(Decades, *this);
	}

	static Date DecreaseDateByOneCentury(Date& SourceDate)
	{
		return ShiftYears(-100, SourceDate);
	}

	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	static Date DecreaseDateByOneMillennium(Date& SourceDate)
	{
		return ShiftYears(-1000, SourceDate);
	}

	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}


	static short IsEndOfWeek(const Date& Date)
	{
		return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}

	short IsEndOfWeek() const
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(const Date& Date)
	{
		//Weekends are Fri and Sat  
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd() const
	{
		return  IsWeekEnd(*this);
	}

	static bool IsBusinessDay(const Date& Date)
	{
		//Weekends are Sun,Mon,Tue,Wed and Thur  

	   /*
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex >= 5 && DayIndex <= 4);
	   */

	   //shorter method is to invert the IsWeekEnd: this will save updating code.  
		return !IsWeekEnd(Date);

	}

	bool IsBusinessDay() const
	{
		return  IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(const Date& Date)
	{
		return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}

	short DaysUntilTheEndOfWeek() const
	{
		return  DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(const Date& Date1)
	{

		Date EndOfMontDate;
		EndOfMontDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
		EndOfMontDate.Month = Date1.Month;
		EndOfMontDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfMontDate, true);

	}

	short DaysUntilTheEndOfMonth() const
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(const Date& Date1)
	{

		Date EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfYearDate, true);

	}

	short DaysUntilTheEndOfYear() const
	{
		return  DaysUntilTheEndOfYear(*this);
	}

	//i added this method to calculate business days between 2 days  
	static short CalculateBusinessDays(Date StartDate, Date EndDate)
	{

		short Days = 0;
		while (IsDate1BeforeDate2(StartDate, EndDate))
		{
			if (IsBusinessDay(StartDate))
				Days++;

			StartDate = AddOneDay(StartDate);
		}

		return Days;

	}

	static short CalculateVacationDays(Date StartDate, Date EndDate)
	{
		/*short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}*/

		return CalculateBusinessDays(StartDate, EndDate);

	}
	//above method is eough , no need to have method for the object  

	static Date CalculateVacationReturnDate(Date StartDate, short VacationDays)
	{

		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{

			if (IsWeekEnd(StartDate))
				WeekEndCounter++;

			StartDate = AddOneDay(StartDate);
		}
		//to add weekends   
		for (short i = 1; i <= WeekEndCounter; i++)
			StartDate = AddOneDay(StartDate);

		return StartDate;
	}

	static bool IsDate1AfterDate2(const Date& Date1, const Date& Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));

	}

	bool IsDateAfterDate2(const Date& Date2) const
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(const Date& Date1, const Date& Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		/* if (IsDate1AfterDate2(Date1,Date2))
			 return enDateCompare::After;*/

			 //this is faster  
		return enDateCompare::After;

	}

	enDateCompare CompareDates(const Date& Date2) const
	{
		return CompareDates(*this, Date2);
	}

};