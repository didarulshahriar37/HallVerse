#include "DateTimeHelper.h"
#include <ctime>
#include <sstream>
#include <iomanip>
 
using namespace std;
std::string DateTimeHelper::getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << std::setfill('0') 
       << std::setw(4) << (1900 + ltm->tm_year) << "-"
       << std::setw(2) << (1 + ltm->tm_mon) << "-"
       << std::setw(2) << ltm->tm_mday << " "
       << std::setw(2) << ltm->tm_hour << ":"
       << std::setw(2) << ltm->tm_min << ":"
       << std::setw(2) << ltm->tm_sec;
    return ss.str();
}

std::string DateTimeHelper::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << std::setfill('0') 
       << std::setw(4) << (1900 + ltm->tm_year) << "-"
       << std::setw(2) << (1 + ltm->tm_mon) << "-"
       << std::setw(2) << ltm->tm_mday;
    return ss.str();
}

std::string DateTimeHelper::getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << std::setfill('0') 
       << std::setw(2) << ltm->tm_hour << ":"
       << std::setw(2) << ltm->tm_min << ":"
       << std::setw(2) << ltm->tm_sec;
    return ss.str();
}