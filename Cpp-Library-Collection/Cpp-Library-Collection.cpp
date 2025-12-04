#include <iostream>
#include "MyPeriod.h"

int main()

{

    clsPeriod Period1(MyDate(1, 1, 2022), MyDate(10, 1, 2022));
    Period1.Print();

    cout << "\n";

    clsPeriod Period2(MyDate(3, 1, 2022), MyDate(5, 1, 2022));
    Period2.Print();


    //You can check like this
    cout << Period1.IsOverLapWith(Period2) << endl;


    //Also you can call the static method and send period 1 and period 2
    cout << clsPeriod::IsOverlapPeriods(Period1, Period2) << endl;


    return 0;
}