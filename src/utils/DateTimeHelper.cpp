#include "DateTimeHelper.h"
#include <ctime>
#include <sstream>
#include <iomanip>
 
using namespace std;

// Get current date and time in "YYYY-MM-DD HH:MM:SS" format
std::string DateTimeHelper::getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << setfill('0') 
       << setw(4) << (1900 + ltm->tm_year) << "-"
       << setw(2) << (1 + ltm->tm_mon) << "-"
       << setw(2) << ltm->tm_mday << " "
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min << ":"
       << setw(2) << ltm->tm_sec;
    return ss.str();
}

// Get current date in "YYYY-MM-DD" format
string DateTimeHelper::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') 
       << setw(4) << (1900 + ltm->tm_year) << "-"
       << setw(2) << (1 + ltm->tm_mon) << "-"
       << setw(2) << ltm->tm_mday;
    return ss.str();
}

// Get current time in "HH:MM:SS" format
string DateTimeHelper::getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') 
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min << ":"
       << setw(2) << ltm->tm_sec;
    return ss.str();
}