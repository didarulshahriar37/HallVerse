#ifndef DATETIMEHELPER_H
#define DATETIMEHELPER_H

#include <string>

class DateTimeHelper {
public:
    static std::string getCurrentDateTime();
    static std::string getCurrentDate();
    static std::string getCurrentTime();
};

#endif