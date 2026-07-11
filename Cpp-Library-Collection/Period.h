
#pragma once
#include "Date.h"

class Period
{
public:

    Date StartDate;
    Date EndDate;

    Period(Date StartDate, Date EndDate)
    {
        if (Date::IsDate1AfterDate2(StartDate, EndDate)) {
            Date::SwapDates(StartDate, EndDate);
        }

        this->StartDate = StartDate;
        this->EndDate = EndDate;

    }

    static bool IsOverlapPeriods(Period Period1, Period Period2)
    {

        if (
            Date::CompareDates(Period2.EndDate, Period1.StartDate) == Date::enDateCompare::Before
            ||
            Date::CompareDates(Period2.StartDate, Period1.EndDate) == Date::enDateCompare::After
            )
            return false;
        else
            return true;

    }


    bool IsOverLapWith(Period Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    void Print()
    {
        std::cout << "Period Start: ";
        StartDate.Print();


        std::cout << "Period End: ";
        EndDate.Print();


    }

};