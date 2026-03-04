#ifndef DATETIMEHELPER_H
#define DATETIMEHELPER_H

#include <string>
using namespace std;
class DateTimeHelper {
public:
    static string getCurrentDateTime();
    static string getCurrentDate();
    static string getCurrentTime();
};

#endif