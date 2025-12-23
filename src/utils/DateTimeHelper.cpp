#include "DateTimeHelper.h"
#include <ctime>

using namespace std;

string DateTimeHelper::getCurrentDateTime() {
    time_t now = time(0);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buffer;
}
