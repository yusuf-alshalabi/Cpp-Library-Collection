
#pragma once
#include "Date.h"

namespace Core
{
	class Period
	{

	private:

		Date _StartDate;
		Date _EndDate;

		void Normalize()
		{
			if (_StartDate > _EndDate)
			{
				Date::SwapDates(_StartDate, _EndDate);
			}
		}

	public:

		Period() :_StartDate(Date()), _EndDate(Date()){}

		Period(const Date& StartDate, const Date& EndDate)
			: _StartDate(StartDate), _EndDate(EndDate)
		{
			Normalize();
		}

		Date GetStartDate() const { return _StartDate; }
		void SetStartDate(const Date& Value)
		{
			_StartDate = Value;
			Normalize(); 
		}

		Date GetEndDate() const { return _EndDate; }
		void SetEndDate(const Date& Value)
		{
			_EndDate = Value;
			Normalize(); 
		}

		void SetPeriod(const Date& StartDate, const Date& EndDate)
		{
			_StartDate = StartDate;
			_EndDate = EndDate;
			Normalize();
		}

		bool operator==(const Period& Other) const
		{
			return (this->_StartDate == Other._StartDate && this->_EndDate == Other._EndDate);
		}

		bool operator!=(const Period& Other) const
		{
			return !(*this == Other);
		}

		friend std::ostream& operator<<(std::ostream& Out, const Period& PeriodObj)
		{
			PeriodObj.Print(Out);
			return Out;
		}

		friend std::istream& operator>>(std::istream& In, Period& PeriodObj)
		{
			In >> PeriodObj._StartDate >> PeriodObj._EndDate;
			PeriodObj.Normalize();
			return In;
		}

		int PeriodLengthInDays(bool IncludeEndDay = true) const
		{
			return Date::GetDifferenceInDays(_StartDate, _EndDate, IncludeEndDay);
		}

		static bool IsDateInPeriod(const Date& DateToCheck, const Period& PeriodToCheck)
		{
			return !(DateToCheck < PeriodToCheck._StartDate || DateToCheck > PeriodToCheck._EndDate);
		}

		bool IsDateInPeriod(const Date& DateToCheck) const
		{
			return IsDateInPeriod(DateToCheck, *this);
		}

		static bool IsOverlapPeriods(const Period& Period1, const Period& Period2)
		{
			return !(Period2._EndDate < Period1._StartDate || Period2._StartDate > Period1._EndDate);
		}

		bool IsOverLapWith(const Period& Period2) const
		{
			return IsOverlapPeriods(*this, Period2);
		}

		void Print(std::ostream& Out = std::cout) const
		{
			Out << "Period Start: " << _StartDate.ToString() << "\n";
			Out << "Period End: " << _EndDate.ToString() << "\n";
		}

		static bool Contains(const Period& MainPeriod, const Period& SubPeriod)
		{
			return (SubPeriod._StartDate >= MainPeriod._StartDate && SubPeriod._EndDate <= MainPeriod._EndDate);
		}

		bool Contains(const Period& SubPeriod) const
		{
			return Contains(*this, SubPeriod);
		}

		static bool GetOverlapPeriod(const Period& Period1, const Period& Period2, Period& Result)
		{
			if (!IsOverlapPeriods(Period1, Period2))
				return false;

			Date MaxStart = (Period1._StartDate > Period2._StartDate) ? Period1._StartDate : Period2._StartDate;
			Date MinEnd = (Period1._EndDate < Period2._EndDate) ? Period1._EndDate : Period2._EndDate;

			Result = Period(MaxStart, MinEnd);
			return true;
		}

		bool GetOverlapPeriod(const Period& Other, Period& Result) const
		{
			return GetOverlapPeriod(*this, Other, Result);
		}

		static int GetOverlapDays(const Period& Period1, const Period& Period2, bool IncludeEndDay = true)
		{
			Period Overlap;
			if (GetOverlapPeriod(Period1, Period2, Overlap))
			{
				return Overlap.PeriodLengthInDays(IncludeEndDay);
			}
			return 0;
		}

		int GetOverlapDays(const Period& Other, bool IncludeEndDay = true) const
		{
			return GetOverlapDays(*this, Other, IncludeEndDay);
		}

		static int CalculateBusinessDays(const Period& PeriodToCheck)
		{
			int BusinessDays = 0;
			Date CurrentDate = PeriodToCheck._StartDate;

			while (CurrentDate <= PeriodToCheck._EndDate)
			{
				if (CurrentDate.IsBusinessDay()) 
				{
					BusinessDays++;
				}
				CurrentDate++;
			}

			return BusinessDays;
		}

		int CalculateBusinessDays() const
		{
			return CalculateBusinessDays(*this);
		}
	};
}