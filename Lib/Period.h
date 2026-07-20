
#pragma once
#include "Date.h"

class Period
{
public:

    Date StartDate;
    Date EndDate;

    Period(const Date& StartDate, const Date& EndDate)
        : StartDate(StartDate), EndDate(EndDate)
    {
        if (Date::IsDateAfterDate(this->StartDate, this->EndDate))
        {
            Date::SwapDates(this->StartDate, this->EndDate);
        }
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


    bool IsOverLapWith(const Period& Period2) const
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