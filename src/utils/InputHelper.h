#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <string>

using namespace std;

class InputHelper {
public:
    static string getLine();
    static int getInt();
    static double getDouble();
    static void clearScreen();
    static void pause();
    static string getPassword();
    static string getValidatedEmail();
    static string getNormalizedHall();
    static bool isValidRoomForHall(const string& hall, const string& room);
    static bool isValidBed(const string& bed);
    static bool isNumeric(const string& str);
    static string getNumericLine();
};

#endif
