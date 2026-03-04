#include "InputHelper.h"
#include <iostream>
#include <cctype>
#include <limits>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

using namespace std;

// Get integer input with validation
int InputHelper::getInt() {
    int value;
    while(!(cin >> value)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid integer: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Get double input with validation
double InputHelper::getDouble() {
    double value;
    while(!(cin >> value)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid integer: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Get line input
string InputHelper::getLine() {
    string input;
    getline(cin, input);
    return input;
}

// Get password input without echoing
string InputHelper::getPassword() {
    #ifdef _WIN32
        // Windows implementation
        string password = "";
        char c;
        FILE* inputFile = stdin;
        while ((c = _getch()) != '\r') {
            if (c == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                    cout.flush();
                }
            } else if (c != '\0') {
                password += c;
                cout << '*';
                cout.flush();
            }
        }
        cout << '\n';
        return password;
    #else
        // Unix/Linux implementation
        string password = "";
        char c;
        system("stty -echo");
        while ((c = getchar()) != '\n') {
            if (c == 127 || c == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                }
            } else {
                password += c;
            }
        }
        system("stty echo");
        return password;
    #endif
}

// Clear the console screen
void InputHelper::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void InputHelper::pause() {
    cout << "Press Enter to continue...";
    cin.get();
}

string InputHelper::getValidatedEmail() {
    while (true) {
        string email = getLine();
        // Check for spaces
        if (email.find(' ') != string::npos) {
            cout << "Invalid email! Email cannot contain spaces.\nTry again: ";
            continue;
        }
        if (email.length() > 14 && email.substr(email.length() - 14) == "@iut-dhaka.edu") {
            return email;
        } else {
            cout << "Invalid email!\nTry again: ";
        }
    }
}

string InputHelper::getNormalizedHall(){
    while(true){
        string hall = getLine();
        size_t start = hall.find_first_not_of("\t\r\n");
        size_t end = hall.find_last_not_of("\t\r\n");
        if(start == string::npos){
            cout << "Please enter Hall (North/South): ";
            continue;
        }
        hall = hall.substr(start, end - start + 1);
        for(auto& c : hall) c = tolower(c);
        if(hall == "north" || hall == "n"){
            return "North";
        }
        if(hall == "south" || hall == "s"){
            return "South";
        }
        else{
            cout << "Invalid Hall. Please enter correct Hall Name (North/South): ";
        }
    }
}

// valid room : 101-130, 201-230
bool InputHelper::isValidRoomForHall(const string& hall, const string& room){
    if(room.size() != 3 || !isNumeric(room)){
        return false;
    } 
    int number = stoi(room);
    int floor = number/100;
    int roomNum = number % 100;
    if(!((floor == 1 || floor == 2) && (roomNum >=1 && roomNum <=30))){
        return false;
    }
    return true;
}

// valid beds: A, B, C, D
bool InputHelper::isValidBed(const string& bed){
    if(bed.size() != 1){
        return false;
    }
    char c = tolower(bed[0]);
    return (c == 'a' || c == 'b' || c == 'c' || c == 'd');
}

bool InputHelper::isNumeric(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

string InputHelper::getNumericLine() {
    while (true) {
        string input = getLine();
        if (isNumeric(input)) {
            return input;
        } else {
            cout << "Invalid input! Please enter numbers only: ";
        }
    }
}

// Get non-negative double input with validation
double InputHelper::getNonNegativeDouble() {
    double value;
    while(true){
        if(!(cin >> value)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid amount: ";
        } else if (value < 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Amount cannot be negative: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}