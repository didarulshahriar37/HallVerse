#include "MenuPrinter.h"
#include <iostream>

using namespace std;

void MenuPrinter::showMainMenu() {
    cout << "1. Admin Login" << endl;
    cout << "2. Student Login" << endl;
    cout << "0. Exit" << endl;
}

void MenuPrinter::showAdminMenu() {
    cout << "1. View Dashboard" << endl;
    cout << "2. Manage Complaints" << endl;
    cout << "3. Assign Workers" << endl;
    cout << "0. Logout" << endl;
}

void MenuPrinter::showStudentMenu() {
    cout << "1. View Profile" << endl;
    cout << "2. Submit Complaint" << endl;
    cout << "3. Entry / Exit" << endl;
    cout << "0. Logout" << endl;
}
