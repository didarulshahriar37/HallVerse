#include "InputHelper.h"
#include <iostream>
#include <cctype>
#include <limits>

using namespace std;

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

double InputHelper::getDouble() {
    double value;
    while(!(cin >> value)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string InputHelper::getLine() {
    string input;
    getline(cin, input);
    return input;
}