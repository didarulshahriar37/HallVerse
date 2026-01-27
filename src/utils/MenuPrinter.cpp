#include "MenuPrinter.h"
#include <iostream>

using namespace std;

// Shows the main menu
void MenuPrinter::showMainMenu() {
    cout << "\n========== MAIN MENU ==========" << "\n";
    cout << "1. Admin Login\n";
    cout << "2. Student Login\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

// Shows the student menu after logging in as a student
void MenuPrinter::showStudentMenu() {
    cout << "\n========== STUDENT MENU ==========" << "\n";
    cout << "1. View Profile\n";
    cout << "2. Update Email\n";
    cout << "3. Update Emergency Contact\n";
    cout << "4. File Complaint\n";
    cout << "5. View My Complaints\n";
    cout << "6. Log Entry/Exit\n";
    cout << "7. Reset Password\n";
    cout << "8. Logout\n";
    cout << "Enter your choice: ";
}

// Shows the admin menu after logging in as an admin
void MenuPrinter::showAdminMenu() {
    cout << "\n========== ADMIN MENU ==========" << "\n";
    cout << "1. View Dashboard\n";
    cout << "2. Manage Students\n";
    cout << "3. View All Complaints\n";
    cout << "4. Logout\n";
    cout << "Enter your choice: ";
}

// Shows the entry/exit logging menu for students
void MenuPrinter::entryExitMenu() {
    cout << "\n========== ENTRY/EXIT ==========\n";
    cout << "1. Log Entry\n";
    cout << "2. Log Exit\n";
    cout << "Choice: ";
}

// Shows the complaint filing menu for students
void MenuPrinter::filingComplaintMenu() {
    cout << "\n=== FILE A COMPLAINT ===\n";
    cout << "Select Category:\n";
    cout << "  1. Electricity\n";
    cout << "  2. Plumbing\n";
    cout << "  3. Housekeeping\n";
    cout << "  4. Internet\n";
    cout << "  5. Other\n";
    cout << "Choose (1-5): ";
}