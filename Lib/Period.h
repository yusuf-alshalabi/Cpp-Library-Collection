
#pragma once
#include "Date.h"

class Period
{
public:

    Date StartDate;
    Date EndDate;

    Period(Date StartDate, Date EndDate)
    {
        if (Date::IsDateAfterDate(StartDate, EndDate)) {
            Date::SwapDates(StartDate, EndDate);
        }

        this->StartDate = StartDate;
        this->EndDate = EndDate;

    }

    static bool IsOverlapPeriods(const Period& Period1, const Period& Period2)
    {

        if (Period2.EndDate < Period1.StartDate || Period2.StartDate > Period1.EndDate)
        {
            return false;
        }
        else
            return true;

    }


    bool IsOverLapWith(const Period& Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    void Print() const
    {
        std::cout << "Period Start: ";
        StartDate.Print();


        std::cout << "Period End: ";
        EndDate.Print();


    }

};