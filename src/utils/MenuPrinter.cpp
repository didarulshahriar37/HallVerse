#include "MenuPrinter.h"
#include <iostream>

using namespace std;

void MenuPrinter::showMainMenu() {
    std::cout << "\n========== MAIN MENU ==========" << "\n";
    std::cout << "1. Admin Login\n";
    std::cout << "2. Student Login\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

void MenuPrinter::showStudentMenu() {
    std::cout << "\n========== STUDENT MENU ==========" << "\n";
    std::cout << "1. View Profile\n";
    std::cout << "2. Update Email\n";
    std::cout << "3. Update Emergency Contact\n";
    std::cout << "4. File Complaint\n";
    std::cout << "5. View My Complaints\n";
    std::cout << "6. Log Entry/Exit\n";
    std::cout << "7. Reset Password\n";
    std::cout << "8. Logout\n";
    std::cout << "Enter your choice: ";
}

void MenuPrinter::showAdminMenu() {
    cout << "\n========== ADMIN MENU ==========" << "\n";
    cout << "1. View Dashboard\n";
    cout << "2. Manage Students\n";
    cout << "3. View All Complaints\n";
    cout << "4. Logout\n";
    cout << "Enter your choice: ";
}