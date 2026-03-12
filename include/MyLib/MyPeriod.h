#pragma once
#include "MyLib/MyDate.h"
#include <stdexcept>

namespace MyLib {

class MyPeriod
{
private:
    MyDate _StartDate;
    MyDate _EndDate;
    
    // Error handling
    static std::string _lastError;

public:

    // ---- Getters & Setters ----

    void SetStartDate(const MyDate& StartDate) { 
        if (MyDate::CompareDates(StartDate, _EndDate) == MyDate::enDateCompare::After) {
            _lastError = "Invalid period: Start date cannot be after end date";
            throw std::invalid_argument("MyPeriod: Start date cannot be after end date");
        }
        _StartDate = StartDate; 
    }
    MyDate GetStartDate() const { return _StartDate; }

    void SetEndDate(const MyDate& EndDate) { 
        if (MyDate::CompareDates(_StartDate, EndDate) == MyDate::enDateCompare::After) {
            _lastError = "Invalid period: End date cannot be before start date";
            throw std::invalid_argument("MyPeriod: End date cannot be before start date");
        }
        _EndDate = EndDate; 
    }
    MyDate GetEndDate() const { return _EndDate; }

    // ---- Constructor ----

    // Default constructor - creates a valid single-day period
    MyPeriod() : _StartDate(1, 1, 1900), _EndDate(1, 1, 1900) {}

    MyPeriod(const MyDate& StartDate, const MyDate& EndDate)
        : _StartDate(StartDate), _EndDate(EndDate) {
        
        // Validate that start date is not after end date
        if (MyDate::CompareDates(StartDate, EndDate) == MyDate::enDateCompare::After)
        {
            _lastError = "Invalid period: Start date cannot be after end date";
            throw std::invalid_argument("MyPeriod: Start date cannot be after end date");
        }
    }

    // Move constructor
    MyPeriod(MyPeriod&& other) noexcept
        : _StartDate(std::move(other._StartDate)), _EndDate(std::move(other._EndDate))
    {
    }

    // Copy constructor
    MyPeriod(const MyPeriod& other)
        : _StartDate(other._StartDate), _EndDate(other._EndDate)
    {
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

    // Move assignment operator
    MyPeriod& operator=(MyPeriod&& other) noexcept
    {
        if (this != &other)
        {
            _StartDate = std::move(other._StartDate);
            _EndDate = std::move(other._EndDate);
        }
        return *this;
    }

    // Copy assignment operator
    MyPeriod& operator=(const MyPeriod& other)
    {
        if (this != &other)
        {
            _StartDate = other._StartDate;
            _EndDate = other._EndDate;
        }
        return *this;
    }

    bool IsOverLapWith(const MyPeriod& Period2) const
    {
        return IsOverlapPeriods(*this, Period2);
    }

    // Error handling methods
    static std::string GetLastError()
    {
        return _lastError;
    }

    static void ClearError()
    {
        _lastError.clear();
    }

    // ---- Duration ----

    int GetDurationInDays() const
    {
        return MyDate::GetDifferenceInDays(_StartDate, _EndDate, true);
    }

    // ---- Validation ----

    bool IsValid() const
    {
        return MyDate::CompareDates(_StartDate, _EndDate) != MyDate::enDateCompare::After;
    }

    // ---- Contains ----

    bool Contains(const MyDate& date) const
    {
        return MyDate::CompareDates(date, _StartDate) != MyDate::enDateCompare::Before &&
               MyDate::CompareDates(date, _EndDate) != MyDate::enDateCompare::After;
    }

    // ---- Length Methods ----

    int LengthInDays() const
    {
        return GetDurationInDays();
    }

    int LengthInMonths() const
    {
        int months = (_EndDate.GetYear() - _StartDate.GetYear()) * 12;
        months += _EndDate.GetMonth() - _StartDate.GetMonth();
        return months;
    }

    int LengthInYears() const
    {
        int years = _EndDate.GetYear() - _StartDate.GetYear();
        if (_EndDate.GetMonth() < _StartDate.GetMonth() || 
            (_EndDate.GetMonth() == _StartDate.GetMonth() && _EndDate.GetDay() < _StartDate.GetDay())) {
            years--;
        }
        return years;
    }

    // ---- Overlap ----

    bool IsOverlap(const MyPeriod& other) const
    {
        return IsOverLapWith(other);
    }

    // ---- Utilities ----

    bool IsSameDay(const MyDate& date) const
    {
        return _StartDate.DateToString() == date.DateToString() && _EndDate.DateToString() == date.DateToString();
    }

    std::string ToString() const
    {
        return "Period: " + _StartDate.DateToString() + " to " + _EndDate.DateToString();
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

} // namespace MyLib
