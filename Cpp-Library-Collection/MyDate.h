#pragma warning(disable : 4996)
#pragma once

#include<iostream>
#include<string>
#include "MyString.h"

class MyDate
{

private:

	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:

	MyDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	MyDate(std::string sDate)
	{
		std::vector <std::string> vDate;
		vDate = MyString::Split(sDate, "/");

		_Day = std::stoi(vDate[0]);
		_Month = std::stoi(vDate[1]);
		_Year = std::stoi(vDate[2]);
	}

	MyDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	MyDate(short DateOrderInYear, short Year)
	{
		// This will construct a date by date order in year
		MyDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
		_Day = Date1.GetDay();
		_Month = Date1.GetMonth();
		_Year = Date1.GetYear();
	}

	// ---- Getters & Setters ----

	void SetDay(short Day) { _Day = Day; }
	short GetDay() const { return _Day; }

	void SetMonth(short Month) { _Month = Month; }
	short GetMonth() const { return _Month; }

	void SetYear(short Year) { _Year = Year; }
	short GetYear() const { return _Year; }

	// ---- Print ----

	void Print()
	{
		std::cout << DateToString() << std::endl;
	}

	// ---- System Date ----

	static MyDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return MyDate(Day, Month, Year);
	}

	// ---- Validation ----

	static bool IsValidDate(MyDate Date)
	{
		if (Date.GetDay() < 1 || Date.GetDay() > 31)
			return false;

		if (Date.GetMonth() < 1 || Date.GetMonth() > 12)
			return false;

		if (Date.GetMonth() == 2)
		{
			if (isLeapYear(Date.GetYear()))
			{
				if (Date.GetDay() > 29)
					return false;
			}
			else
			{
				if (Date.GetDay() > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear());

		if (Date.GetDay() > DaysInMonth)
			return false;

		return true;
	}

	bool IsValid()
	{
		return IsValidDate(*this);
	}

	// ---- Date To String ----

	static std::string DateToString(MyDate Date)
	{
		return std::to_string(Date.GetDay()) + "/" +
			std::to_string(Date.GetMonth()) + "/" +
			std::to_string(Date.GetYear());
	}

	std::string DateToString()
	{
		return DateToString(*this);
	}

	// ---- Leap Year ----

	static bool isLeapYear(short Year)
	{
		// if year is divisible by 4 AND not divisible by 100
		// OR if year is divisible by 400
		// then it is a leap year
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}

	// ---- Days / Hours / Minutes / Seconds in Year ----

	static short NumberOfDaysInAYear(short Year)
	{
		return isLeapYear(Year) ? 365 : 364;
	}

	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(_Year);
	}

	// ---- Days / Hours / Minutes / Seconds in Month ----

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
			return 0;

		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return NumberOfDaysInAMonth(Month, Year) * 24;
	}

	short NumberOfHoursInAMonth()
	{
		return NumberOfDaysInAMonth(_Month, _Year) * 24;
	}

	static int NumberOfMinutesInAMonth(short Month, short Year)
	{
		return NumberOfHoursInAMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInAMonth()
	{
		return NumberOfHoursInAMonth(_Month, _Year) * 60;
	}

	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return NumberOfMinutesInAMonth(Month, Year) * 60;
	}

	int NumberOfSecondsInAMonth()
	{
		return NumberOfMinutesInAMonth(_Month, _Year) * 60;
	}

	// ---- Day of Week ----

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian: 0=Sun, 1=Mon, 2=Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder()
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
		std::string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
	}

	std::string DayShortName()
	{
		std::string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
	}

	// ---- Month Name ----

	static std::string MonthShortName(short MonthNumber)
	{
		std::string Months[12] = { "Jan", "Feb", "Mar",
					   "Apr", "May", "Jun",
					   "Jul", "Aug", "Sep",
					   "Oct", "Nov", "Dec"
		};
		return (Months[MonthNumber - 1]);
	}

	std::string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	// ---- Calendar ----

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;
		int current = DayOfWeekOrder(1, Month, Year);
		NumberOfDays = NumberOfDaysInAMonth(Month, Year);

		std::printf("\n  _______________%s_______________\n\n",
			MonthShortName(Month).c_str());
		std::printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

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

	void PrintMonthCalendar()
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
	}

	void PrintYearCalendar()
	{
		std::printf("\n  _________________________________\n\n");
		std::printf("           Calendar - %d\n", _Year);
		std::printf("  _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, _Year);
		}
	}

	// ---- Days From Beginning of Year ----

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

	short DaysFromTheBeginingOfTheYear()
	{
		short TotalDays = 0;

		for (int i = 1; i <= _Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, _Year);
		}

		TotalDays += _Day;
		return TotalDays;
	}

	// ---- Get Date From Day Order In Year ----

	static MyDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		MyDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.SetYear(Year);
		Date.SetMonth(1);

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.GetMonth(), Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.SetMonth(Date.GetMonth() + 1);
			}
			else
			{
				Date.SetDay(RemainingDays);
				break;
			}
		}

		return Date;
	}

	// ---- Add Days ----

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

	// ---- Date Comparison ----

	static bool IsDate1BeforeDate2(MyDate Date1, MyDate Date2)
	{
		return (Date1.GetYear() < Date2.GetYear()) ? true :
			((Date1.GetYear() == Date2.GetYear()) ?
				(Date1.GetMonth() < Date2.GetMonth() ? true :
					(Date1.GetMonth() == Date2.GetMonth() ?
						Date1.GetDay() < Date2.GetDay() : false)) : false);
	}

	bool IsDateBeforeDate2(MyDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(MyDate Date1, MyDate Date2)
	{
		return (Date1.GetYear() == Date2.GetYear()) ?
			((Date1.GetMonth() == Date2.GetMonth()) ?
				((Date1.GetDay() == Date2.GetDay()) ? true : false) : false) : false;
	}

	bool IsDateEqualDate2(MyDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(MyDate Date1, MyDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(MyDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	// ---- Last Day / Month Checks ----

	static bool IsLastDayInMonth(MyDate Date)
	{
		return (Date.GetDay() == NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear()));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	// ---- Add One Day ----

	static MyDate AddOneDay(MyDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.GetMonth()))
			{
				Date.SetMonth(1);
				Date.SetDay(1);
				Date.SetYear(Date.GetYear() + 1);
			}
			else
			{
				Date.SetDay(1);
				Date.SetMonth(Date.GetMonth() + 1);
			}
		}
		else
		{
			Date.SetDay(Date.GetDay() + 1);
		}

		return Date;
	}

	void AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	// ---- Swap Dates ----

	static void SwapDates(MyDate& Date1, MyDate& Date2)
	{
		MyDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	// ---- Difference In Days ----

	static int GetDifferenceInDays(MyDate Date1, MyDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}

	int GetDifferenceInDays(MyDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	// ---- Age ----

	static short CalculateMyAgeInDays(MyDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, MyDate::GetSystemDate(), true);
	}

	// ---- Increase By One Week ----

	static MyDate IncreaseDateByOneWeek(MyDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	// ---- Increase By X Weeks ----

	MyDate IncreaseDateByXWeeks(short Weeks, MyDate& Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(Weeks, *this);
	}

	// ---- Increase By One Month ----

	MyDate IncreaseDateByOneMonth(MyDate& Date)
	{
		if (Date.GetMonth() == 12)
		{
			Date.SetMonth(1);
			Date.SetYear(Date.GetYear() + 1);
		}
		else
		{
			Date.SetMonth(Date.GetMonth() + 1);
		}

		// day should not exceed max days in the new month
		// example: 31/1/2022 + one month = 28/2/2022 not 31/2/2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear());
		if (Date.GetDay() > NumberOfDaysInCurrentMonth)
		{
			Date.SetDay(NumberOfDaysInCurrentMonth);
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	// ---- Increase By X Days ----

	MyDate IncreaseDateByXDays(short Days, MyDate& Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(Days, *this);
	}

	// ---- Increase By X Months ----

	MyDate IncreaseDateByXMonths(short Months, MyDate& Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(Months, *this);
	}

	// ---- Increase By One Year ----

	static MyDate IncreaseDateByOneYear(MyDate& Date)
	{
		Date.SetYear(Date.GetYear() + 1);
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	// ---- Increase By X Years ----

	MyDate IncreaseDateByXYears(short Years, MyDate& Date)
	{
		Date.SetYear(Date.GetYear() + Years);
		return Date;
	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(Years, *this);
	}

	// ---- Increase By One Decade ----

	MyDate IncreaseDateByOneDecade(MyDate& Date)
	{
		// Period of 10 years
		Date.SetYear(Date.GetYear() + 10);
		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	// ---- Increase By X Decades ----

	MyDate IncreaseDateByXDecades(short Decade, MyDate& Date)
	{
		Date.SetYear(Date.GetYear() + Decade * 10);
		return Date;
	}

	void IncreaseDateByXDecades(short Decade)
	{
		IncreaseDateByXDecades(Decade, *this);
	}

	// ---- Increase By One Century ----

	MyDate IncreaseDateByOneCentury(MyDate& Date)
	{
		// Period of 100 years
		Date.SetYear(Date.GetYear() + 100);
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	// ---- Increase By One Millennium ----

	MyDate IncreaseDateByOneMillennium(MyDate& Date)
	{
		// Period of 1000 years
		Date.SetYear(Date.GetYear() + 1000);
		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	// ---- Decrease By One Day ----

	static MyDate DecreaseDateByOneDay(MyDate Date)
	{
		if (Date.GetDay() == 1)
		{
			if (Date.GetMonth() == 1)
			{
				Date.SetMonth(12);
				Date.SetDay(31);
				Date.SetYear(Date.GetYear() - 1);
			}
			else
			{
				Date.SetMonth(Date.GetMonth() - 1);
				Date.SetDay(NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear()));
			}
		}
		else
		{
			Date.SetDay(Date.GetDay() - 1);
		}

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	// ---- Decrease By One Week ----

	static MyDate DecreaseDateByOneWeek(MyDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	// ---- Decrease By X Weeks ----

	static MyDate DecreaseDateByXWeeks(short Weeks, MyDate& Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}

	// ---- Decrease By One Month ----

	static MyDate DecreaseDateByOneMonth(MyDate& Date)
	{
		if (Date.GetMonth() == 1)
		{
			Date.SetMonth(12);
			Date.SetYear(Date.GetYear() - 1);
		}
		else
		{
			Date.SetMonth(Date.GetMonth() - 1);
		}

		// day should not exceed max days in the new month
		// example: 31/3/2022 - one month = 28/2/2022 not 31/2/2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear());
		if (Date.GetDay() > NumberOfDaysInCurrentMonth)
		{
			Date.SetDay(NumberOfDaysInCurrentMonth);
		}

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	// ---- Decrease By X Days ----

	static MyDate DecreaseDateByXDays(short Days, MyDate& Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}

	// ---- Decrease By X Months ----

	static MyDate DecreaseDateByXMonths(short Months, MyDate& Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}

	// ---- Decrease By One Year ----

	static MyDate DecreaseDateByOneYear(MyDate& Date)
	{
		Date.SetYear(Date.GetYear() - 1);
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	// ---- Decrease By X Years ----

	static MyDate DecreaseDateByXYears(short Years, MyDate& Date)
	{
		Date.SetYear(Date.GetYear() - Years);
		return Date;
	}

	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}

	// ---- Decrease By One Decade ----

	static MyDate DecreaseDateByOneDecade(MyDate& Date)
	{
		// Period of 10 years
		Date.SetYear(Date.GetYear() - 10);
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	// ---- Decrease By X Decades ----

	static MyDate DecreaseDateByXDecades(short Decades, MyDate& Date)
	{
		Date.SetYear(Date.GetYear() - Decades * 10);
		return Date;
	}

	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(Decades, *this);
	}

	// ---- Decrease By One Century ----

	static MyDate DecreaseDateByOneCentury(MyDate& Date)
	{
		// Period of 100 years
		Date.SetYear(Date.GetYear() - 100);
		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	// ---- Decrease By One Millennium ----

	static MyDate DecreaseDateByOneMillennium(MyDate& Date)
	{
		// Period of 1000 years
		Date.SetYear(Date.GetYear() - 1000);
		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	// ---- Week / Business Day Checks ----

	static short IsEndOfWeek(MyDate Date)
	{
		return DayOfWeekOrder(Date.GetDay(), Date.GetMonth(), Date.GetYear()) == 6;
	}

	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(MyDate Date)
	{
		// Weekends are Fri and Sat
		short DayIndex = DayOfWeekOrder(Date.GetDay(), Date.GetMonth(), Date.GetYear());
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(MyDate Date)
	{
		// Business days are Sun, Mon, Tue, Wed, Thu
		// shorter method: invert IsWeekEnd to avoid updating code in two places
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	// ---- Days Until End of Week / Month / Year ----

	static short DaysUntilTheEndOfWeek(MyDate Date)
	{
		return 6 - DayOfWeekOrder(Date.GetDay(), Date.GetMonth(), Date.GetYear());
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(MyDate Date1)
	{
		MyDate EndOfMontDate;
		EndOfMontDate.SetDay(NumberOfDaysInAMonth(Date1.GetMonth(), Date1.GetYear()));
		EndOfMontDate.SetMonth(Date1.GetMonth());
		EndOfMontDate.SetYear(Date1.GetYear());

		return GetDifferenceInDays(Date1, EndOfMontDate, true);
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(MyDate Date1)
	{
		MyDate EndOfYearDate;
		EndOfYearDate.SetDay(31);
		EndOfYearDate.SetMonth(12);
		EndOfYearDate.SetYear(Date1.GetYear());

		return GetDifferenceInDays(Date1, EndOfYearDate, true);
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	// ---- Business / Vacation Days ----

	static short CalculateBusinessDays(MyDate DateFrom, MyDate DateTo)
	{
		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}
		return Days;
	}

	static short CalculateVacationDays(MyDate DateFrom, MyDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}

	static MyDate CalculateVacationReturnDate(MyDate DateFrom, short VacationDays)
	{
		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{
			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}

		// add weekends back
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}

	// ---- Compare Dates ----

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(MyDate Date1, MyDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		// faster than calling IsDate1AfterDate2
		return enDateCompare::After;
	}

	enDateCompare CompareDates(MyDate Date2)
	{
		return CompareDates(*this, Date2);
	}

};
