
#pragma once
#include "Date.h"

class Period
{

private:

    void Normalize()
    {
        if (StartDate > EndDate)
        {
            Date::SwapDates(StartDate, EndDate);
        }
    }

public:

    Date StartDate;
    Date EndDate;

    Period(const Date& StartDate, const Date& EndDate)
        : StartDate(StartDate), EndDate(EndDate)
    {
        Normalize();
    }

    bool operator==(const Period& Other) const
    {
        return (this->StartDate == Other.StartDate && this->EndDate == Other.EndDate);
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
        In >> PeriodObj.StartDate >> PeriodObj.EndDate;
        PeriodObj.Normalize();
        return In;
    }

    int PeriodLengthInDays(bool IncludeEndDay = true) const
    {
        return Date::GetDifferenceInDays(StartDate, EndDate, IncludeEndDay);
    }

    static bool IsDateInPeriod(const Date& DateToCheck, const Period& PeriodToCheck)
    {
        return !(DateToCheck < PeriodToCheck.StartDate || DateToCheck > PeriodToCheck.EndDate);
    }

    bool IsDateInPeriod(const Date& DateToCheck) const
    {
        return IsDateInPeriod(DateToCheck, *this);
    }

    static bool IsOverlapPeriods(const Period& Period1, const Period& Period2)
    {
        return !(Period2.EndDate < Period1.StartDate || Period2.StartDate > Period1.EndDate);
    }


    bool IsOverLapWith(const Period& Period2) const
    {
        return IsOverlapPeriods(*this, Period2);
    }

    void Print(std::ostream& Out = std::cout) const
    {
		Out << "Period Start: " << StartDate.ToString() << "\n";
        Out << "Period End: " << EndDate.ToString() << "\n";
    }

};