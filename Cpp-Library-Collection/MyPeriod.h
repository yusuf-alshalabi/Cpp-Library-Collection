#pragma once
#include "MyDate.h"

class MyPeriod
{
private:
    MyDate _StartDate;
    MyDate _EndDate;

public:

    // ---- Getters & Setters ----

    void SetStartDate(const MyDate& StartDate) { _StartDate = StartDate; }
    MyDate GetStartDate() const { return _StartDate; }

    void SetEndDate(const MyDate& EndDate) { _EndDate = EndDate; }
    MyDate GetEndDate() const { return _EndDate; }

    // ---- Constructor ----

    MyPeriod(const MyDate& StartDate, const MyDate& EndDate)
        : _StartDate(StartDate), _EndDate(EndDate) {
    }

    // ---- Overlap ----

    static bool IsOverlapPeriods(const MyPeriod& Period1, const MyPeriod& Period2)
    {
        if (
            MyDate::CompareDates(Period2.GetEndDate(), Period1.GetStartDate()) == MyDate::enDateCompare::Before
            ||
            MyDate::CompareDates(Period2.GetStartDate(), Period1.GetEndDate()) == MyDate::enDateCompare::After
            )
            return false;
        else
            return true;
    }

    bool IsOverLapWith(const MyPeriod& Period2) const
    {
        return IsOverlapPeriods(*this, Period2);
    }

    // ---- Duration ----

    int GetDurationInDays() const
    {
        return MyDate::GetDifferenceInDays(_StartDate, _EndDate, true);
    }

    // ---- Print ----

    void Print() const
    {
        std::cout << "Period Start: ";
        GetStartDate().Print();

        std::cout << "Period End: ";
        GetEndDate().Print();
    }

};
