#include "../include/MyLib/MyString.h"
#include "../include/MyLib/MyDate.h"
#include "../include/MyLib/MyPeriod.h"

namespace MyLib {
    // Define static member variables
    std::string MyString::_lastError;
    std::string MyDate::_lastError;
    std::string MyPeriod::_lastError;
}
