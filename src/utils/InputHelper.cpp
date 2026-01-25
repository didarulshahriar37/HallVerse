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
        cout << "Invalid input. Please enter a valid integer: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string InputHelper::getLine() {
    string input;
    getline(cin, input);
    return input;
}

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
    if(room.size() != 3){
        return false;
    } 
    int number = 0;
    try{
        number = stoi(room);
    }
    catch(...){
        return false;
    }
    int floor = number/100;
    int roomNum = number % 100;
    if(!((floor == 1 || floor == 2) && (roomNum >=1 && roomNum <=30))){
        return false;
    }
    return true;
}

bool InputHelper::isValidBed(const string& bed){
    if(bed.size() != 1){
        return false;
    }
    char c = tolower(bed[0]);
    return (c == 'a' || c == 'b' || c == 'd');
}