#include "InputHelper.h"
#include <iostream>

using namespace std;

int InputHelper::getInt() {
    int value;
    cin >> value;
    return value;
}

string InputHelper::getString() {
    string value;
    cin.ignore();
    getline(cin, value);
    return value;
}
