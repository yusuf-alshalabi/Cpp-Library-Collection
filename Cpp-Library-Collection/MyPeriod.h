
#pragma once
#include "MyDate.h"

class MyPeriod
{
public:

    MyDate StartDate;
    MyDate EndDate;

    MyPeriod(MyDate StartDate, MyDate DateTo)
    {
        this->StartDate = StartDate;
        this->EndDate = DateTo;

    }

    static bool IsOverlapPeriods(MyPeriod Period1, MyPeriod Period2)
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


    bool IsOverLapWith(MyPeriod Period2)
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
