
#pragma warning(disable : 4996)
#pragma once

#include<iostream>
#include<string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <array>
#include "String.h"

class Date
{

private:

	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

	inline static constexpr std::array<short, 12> Days =
	{
		31,28,31,30,31,30,
		31,31,30,31,30,31
	};

	inline static constexpr std::array<const char*, 7> DayNames =
	{
		"Sun","Mon","Tue","Wed","Thu","Fri","Sat"
	};

	inline static constexpr const char* DayFullNames[7] =
	{
		"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"
	};

	inline static constexpr std::array<const char*, 12> MonthNames =
	{
		"Jan","Feb","Mar",
		"Apr","May","Jun",
		"Jul","Aug","Sep",
		"Oct","Nov","Dec"
	};

	inline static constexpr const char* MonthFullNames[12] =
	{
		"January","February","March",
		"April"  ,"May"     ,"June",
		"July"   ,"August"  ,"September",
		"October","November","December"
	};

	static void AdjustDayIfNeeded(Date& SourceDate)
	{
		short DaysInMonth =
			NumberOfDaysInAMonth(SourceDate.Month, SourceDate.Year);

		if (SourceDate.Day > DaysInMonth)
			SourceDate.Day = DaysInMonth;
	}

	static void ReplaceAll(std::string& Text,const std::string& OldValue,const std::string& NewValue)
	{
		size_t Position = 0;

		while ((Position = Text.find(OldValue, Position)) != std::string::npos)
		{
			Text.replace(Position, OldValue.length(), NewValue);
			Position += NewValue.length();
		}
	}

	static int DateToSerial(const Date& SourceDate)
	{
		int PreviousYears = SourceDate.GetYear() - 1;

		int Serial =
			PreviousYears * 365
			+ PreviousYears / 4
			- PreviousYears / 100
			+ PreviousYears / 400;

		for (short Month = 1; Month < SourceDate.GetMonth(); Month++)
		{
			Serial += NumberOfDaysInAMonth(Month, SourceDate.GetYear());
		}

		Serial += SourceDate.GetDay() - 1;

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

	enum CompareResult { Before = -1, Equal = 0, After = 1 };

	static CompareResult CompareDates(const Date& FirstDate,
		const Date& SecondDate)
	{
		if (FirstDate.Year < SecondDate.Year)
			return CompareResult::Before;

		if (FirstDate.Year > SecondDate.Year)
			return CompareResult::After;

		if (FirstDate.Month < SecondDate.Month)
			return CompareResult::Before;

		if (FirstDate.Month > SecondDate.Month)
			return CompareResult::After;

		if (FirstDate.Day < SecondDate.Day)
			return CompareResult::Before;

		if (FirstDate.Day > SecondDate.Day)
			return CompareResult::After;

		return CompareResult::Equal;
	}

	CompareResult CompareDates(const Date& SecondDate) const
	{
		return CompareDates(*this, SecondDate);
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

	bool operator==(const Date& Other) const
	{
		return CompareDates(*this, Other) == CompareResult::Equal;
	}

	bool operator!=(const Date& Other) const
	{
		return !(*this == Other);
	}

	bool operator<(const Date& Other) const
	{
		return CompareDates(*this, Other) == CompareResult::Before;
	}

	bool operator>(const Date& Other) const
	{
		return CompareDates(*this, Other) == CompareResult::After;
	}

	bool operator<=(const Date& Other) const
	{
		return !(*this > Other);
	}

	bool operator>=(const Date& Other) const
	{
		return !(*this < Other);
	}

	Date operator+(int Days) const
	{
		return ShiftDays(Days, *this);
	}

	Date operator-(int Days) const
	{
		return ShiftDays(-Days, *this);
	}

	Date& operator+=(int Days)
	{
		*this = ShiftDays(Days, *this);
		return *this;
	}

	Date& operator-=(int Days)
	{
		*this = ShiftDays(-Days, *this);
		return *this;
	}

	Date & operator++()
	{
		*this = ShiftDays(1, *this);
		return *this;
	}

	Date operator++(int)
	{
		Date Temp = *this;
		*this = ShiftDays(1, *this);
		return Temp;
	}

	Date & operator--()
	{
		*this = ShiftDays(-1, *this);
		return *this;
	}

	Date operator--(int)
	{
		Date Temp = *this;
		*this = ShiftDays(-1, *this);
		return Temp;
	}

	int operator-(const Date& Other) const
	{
		return GetDifferenceInDays(Other, *this);
	}

	friend std::ostream& operator<<(std::ostream& Out, const Date& Date)
	{
		Out << Date.ToString();
		return Out;
	}

	friend std::istream& operator>>(std::istream& In, Date& DateObj)
	{
		std::string Input;
		In >> Input;
		DateObj = Date(Input);
		return In;
	}

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
		std::cout << ToString() << std::endl;
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

	static std::string ToString(const Date& SourceDate,std::string Format = "DD/MM/YYYY")
	{
		ReplaceAll(
			Format,
			"YYYY",
			std::to_string(SourceDate.Year));

		ReplaceAll(
			Format,
			"YY",
			std::to_string(SourceDate.Year % 100));

		ReplaceAll(
			Format,
			"MMMM",
			MonthName(SourceDate.Month));

		ReplaceAll(
			Format,
			"MMM",
			MonthShortName(SourceDate.Month));

		ReplaceAll(
			Format,
			"DD",
			(SourceDate.Day < 10 ? "0" : "") +
			std::to_string(SourceDate.Day));

		ReplaceAll(
			Format,
			"D",
			std::to_string(SourceDate.Day));

		ReplaceAll(
			Format,
			"MM",
			(SourceDate.Month < 10 ? "0" : "") +
			std::to_string(SourceDate.Month));

		ReplaceAll(
			Format,
			"M",
			std::to_string(SourceDate.Month));

		return Format;
	}

	std::string ToString(std::string Format = "DD/MM/YYYY") const
	{
		return ToString(*this, Format);
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

	static std::string DayName(short DayOfWeek)
	{
		return DayFullNames[DayOfWeek];
	}

	std::string DayName() const
	{
		return DayName(DayOfWeekOrder());
	}

	static std::string MonthShortName(short MonthNumber)
	{
		return (MonthNames[MonthNumber - 1]);
	}

	std::string MonthShortName() const
	{

		return MonthShortName(_Month);
	}

	static std::string MonthName(short Month)
	{
		return MonthFullNames[Month - 1];
	}

	std::string MonthName() const
	{
		return MonthName(_Month);
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
		PrintYearCalendar(_Year);
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
		*this = ShiftDays(Days, *this);
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
		return ShiftDays(1, Date);
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

	static Date IncreaseDateByOneWeek(const Date& SourceDate)
	{
		return ShiftDays(7, SourceDate);
	}

	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static Date IncreaseDateByXWeeks(short Weeks, const Date& SourceDate)
	{
		return ShiftDays(Weeks * 7, SourceDate);
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		*this = IncreaseDateByXWeeks(Weeks, *this);
	}

	static Date IncreaseDateByOneMonth(const Date& SourceDate)
	{
		return ShiftMonths(1, SourceDate);
	}

	void IncreaseDateByOneMonth()
	{

		*this = IncreaseDateByOneMonth(*this);

	}

	static Date IncreaseDateByXDays(short Days, const Date& SourceDate)
	{
		return ShiftDays(Days, SourceDate);
	}

	void IncreaseDateByXDays(short Days)
	{

		*this = IncreaseDateByXDays(Days, *this);
	}

	static Date IncreaseDateByXMonths(short Months, const Date& SourceDate)
	{
		return ShiftMonths(Months, SourceDate);
	}
	
	void IncreaseDateByXMonths(short Months)
	{
		*this = IncreaseDateByXMonths(Months, *this);
	}

	static Date IncreaseDateByOneYear(const Date& SourceDate)
	{
		return ShiftYears(1, SourceDate);
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static Date IncreaseDateByXYears(short Years, const Date& SourceDate)
	{
		return ShiftYears(Years, SourceDate);
	}

	void IncreaseDateByXYears(short Years)
	{
		*this = IncreaseDateByXYears(Years, *this);
	}

	static Date IncreaseDateByOneDecade(const Date& SourceDate)
	{
		return ShiftYears(10, SourceDate);
	}

	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static Date IncreaseDateByXDecades(short Decade, const Date& SourceDate)
	{
		return ShiftYears(Decade * 10, SourceDate);
	}

	void IncreaseDateByXDecades(short Decade)
	{
		*this = IncreaseDateByXDecades(Decade, *this);
	}

	static Date IncreaseDateByOneCentury(const Date& SourceDate)
	{
		return ShiftYears(100, SourceDate);
	}

	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static Date IncreaseDateByOneMillennium(const Date& SourceDate)
	{
		return ShiftYears(1000, SourceDate);
	}

	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static Date DecreaseDateByOneDay(const Date& SourceDate)
	{
		return ShiftDays(-1, SourceDate);
	}

	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static Date DecreaseDateByOneWeek(const Date& SourceDate)
	{

		return ShiftDays(-7, SourceDate);
	}

	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static Date DecreaseDateByXWeeks(short Weeks, const Date& SourceDate)
	{
		return ShiftDays(-Weeks * 7, SourceDate);
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		*this = DecreaseDateByXWeeks(Weeks, *this);
	}

	static Date DecreaseDateByOneMonth(const Date& SourceDate)
	{
		return ShiftMonths(-1, SourceDate);
	}

	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static Date DecreaseDateByXDays(short Days, const Date& SourceDate)
	{
		return ShiftDays(-Days, SourceDate);
	}

	void DecreaseDateByXDays(short Days)
	{
		*this =	DecreaseDateByXDays(Days, *this);
	}

	static Date DecreaseDateByXMonths(short Months, const Date& SourceDate)
	{
		return ShiftMonths(-Months, SourceDate);
	}

	void DecreaseDateByXMonths(short Months)
	{
		*this = DecreaseDateByXMonths(Months, *this);
	}

	static Date DecreaseDateByOneYear(const Date& SourceDate)
	{
		return ShiftYears(-1, SourceDate);
	}

	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static Date DecreaseDateByXYears(short Years, const Date& SourceDate)
	{
		return ShiftYears(-Years, SourceDate);
	}

	void DecreaseDateByXYears(short Years)
	{
		*this = DecreaseDateByXYears(Years, *this);
	}

	static Date DecreaseDateByOneDecade(const Date& SourceDate)
	{
		return ShiftYears(-10, SourceDate);
	}

	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static Date DecreaseDateByXDecades(short Decades, const Date& SourceDate)
	{
		return ShiftYears(-Decades * 10, SourceDate);
	}

	void DecreaseDateByXDecades(short Decades)
	{
		*this = DecreaseDateByXDecades(Decades, *this);
	}

	static Date DecreaseDateByOneCentury(const Date& SourceDate)
	{
		return ShiftYears(-100, SourceDate);
	}

	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	static Date DecreaseDateByOneMillennium(const Date& SourceDate)
	{
		return ShiftYears(-1000, SourceDate);
	}

	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}


	static bool IsEndOfWeek(const Date& Date)
	{
		return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}

	bool IsEndOfWeek() const
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
		while (StartDate < EndDate)
		{
			if (IsBusinessDay(StartDate))
				Days++;

			StartDate++;
		}

		return Days;

	}

	static short CalculateVacationDays(Date StartDate, Date EndDate)
	{
		/*short Days = 0;
		while (IsDateBeforeDate(StartDate, EndDate))
		{
			if (IsBusinessDay(StartDate))
				Days++;

			StartDate = AddOneDay(StartDate);
		}*/

		return CalculateBusinessDays(StartDate, EndDate);

	}
	//above method is eough , no need to have method for the object  

	static Date CalculateVacationReturnDate(Date StartDate, short VacationDays)
	{
		while (VacationDays > 0)
		{
			if (IsBusinessDay(StartDate))
			{
				VacationDays--;
			}
			StartDate++;
		}

		while (IsWeekEnd(StartDate))
		{
			StartDate++;
		}

		return StartDate;
	}

	static bool IsDateBeforeDate(const Date& FirstDate, const Date& SecondDate)
	{
		return CompareDates(FirstDate, SecondDate) == CompareResult::Before;
	}

	bool IsDateBeforeDate(const Date& SecondDate) const
	{
		//note: *this sends the current object :-)   
		return  IsDateBeforeDate(*this, SecondDate);

	}

	static bool IsDateEqualDate(const Date& FirstDate, const Date& SecondDate)
	{
		return  CompareDates(FirstDate, SecondDate) == CompareResult::Equal;
	}

	bool IsDateEqualDate(const Date& SecondDate) const
	{
		return  IsDateEqualDate(*this, SecondDate);
	}

	static bool IsDateAfterDate(const Date& FirstDate, const Date& SecondDate)
	{
		return CompareDates(FirstDate, SecondDate) == CompareResult::After;
	}

	bool IsDateAfterDate(const Date& SecondDate) const
	{
		return IsDateAfterDate(*this, SecondDate);
	}

};