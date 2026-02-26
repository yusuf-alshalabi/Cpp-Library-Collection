
#pragma once
#include "MyDate.h"

class MyPeriod
{
public:

    MyDate StartDate;
    MyDate EndDate;

    MyPeriod(const MyDate& StartDate, const MyDate& DateTo)
    {
        this->StartDate = StartDate;
        this->EndDate = DateTo;

    }

    static bool IsOverlapPeriods(const MyPeriod& Period1, const MyPeriod& Period2)
    {

        if (
            MyDate::CompareDates(Period2.EndDate, Period1.StartDate) == MyDate::enDateCompare::Before
            ||
            MyDate::CompareDates(Period2.StartDate, Period1.EndDate) == MyDate::enDateCompare::After
            )
            return false;
        else
            return true;

    }


    bool IsOverLapWith(const MyPeriod& Period2) const
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
