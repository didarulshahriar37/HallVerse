#include <iostream>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif
#include <string>
#include <sstream>
#include "../services/FileHandler.h"
#include "../services/Hasher.h"
#include "../managers/StudentManager.h"
#include "../managers/ComplaintManager.h"
#include "../managers/WorkerManager.h"
#include "../managers/WorkAssignmentManager.h"
#include "../managers/EntryExitManager.h"
#include "../managers/AuthenticationManager.h"
#include "../managers/DashboardManager.h"
#include "../managers/RoomManager.h"
#include "../utils/InputHelper.h"
#include "../utils/DateTimeHelper.h"
#include "../models/Student.h"
#include "../models/Complaint.h"
using namespace std;

class HallVerseApp {
private:
    FileHandler fileHandler;
    Hasher hasher;
    StudentManager studentManager;
    ComplaintManager complaintManager;
    WorkerManager workerManager;
    EntryExitManager entryExitManager;
    AuthenticationManager authManager;
    WorkAssignmentManager assignmentManager;
    DashboardManager dashboardManager;
    RoomManager roomManager;

    std::string currentUserID;
    bool isAdmin;

    void showWelcome() {
        std::cout << "\n";
        std::cout << "╔═══════════════════════════════════════════╗\n";
        std::cout << "║                                           ║\n";
        std::cout << "║           WELCOME TO HALLVERSE            ║\n";
        std::cout << "║    Islamic University of Technology       ║\n";
        std::cout << "║                                           ║\n";
        std::cout << "╚═══════════════════════════════════════════╝\n";
    }

    void showMainMenu() {
        std::cout << "\n========== MAIN MENU ==========" << "\n";
        std::cout << "1. Admin Login\n";
        std::cout << "2. Student Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
    }
     void showStudentMenu() {
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
     void showAdminMenu() {
        cout << "\n========== ADMIN MENU ==========" << "\n";
        cout << "1. View Dashboard\n";
        cout << "2. Manage Students\n";
        cout << "3. View All Complaints\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
    }
    void handleStudentProfile() {
        Student* student = studentManager.getStudent(currentUserID);
        if (student) {
            student->viewProfile();
        } else {
            std::cout << "Student profile not found.\n";
        }
        InputHelper::pause();
    }
    
    void handleLogEntryExit() {
        std::cout << "\n========== ENTRY/EXIT ==========\n";
        std::cout << "1. Log Entry\n";
        std::cout << "2. Log Exit\n";
        std::cout << "Choice: ";
        int choice = InputHelper::getInt();
        
        if (choice == 1) {
            entryExitManager.logEntry(currentUserID);
        } else if (choice == 2) {
            entryExitManager.logExit(currentUserID);
        } else {
            std::cout << "Invalid choice!\n";
        }
        InputHelper::pause();
    }

    bool performLogin(bool isAdminLogin) {
        InputHelper::clearScreen();
        std::cout << "\n========== " << (isAdminLogin ? "ADMIN" : "STUDENT") << " LOGIN ==========" << "\n";
        std::cout << "Username: ";
        std::string username = InputHelper::getLine();
        std::cout << "Password: ";
        std::string password = InputHelper::getLine();
        
        if (authManager.login(username, password, isAdminLogin)) {
            currentUserID = username;
            isAdmin = isAdminLogin;
            std::cout << "\n\u2713 Login successful! Welcome, " << username << "\n";
            InputHelper::pause();
            return true;
        } else {
            std::cout << "\n\u2717 Invalid credentials!\n";
            InputHelper::pause();
            return false;
        }
    }

    void handleUpdateEmail() {
        Student* student = studentManager.getStudent(currentUserID);
        if (student) {
            std::cout << "\nCurrent Email: " << student->getEmail() << "\n";
            std::cout << "Enter new email: ";
            std::string email = InputHelper::getLine();
            student->updateEmail(email);
            studentManager.updateStudent(*student);
        }
        InputHelper::pause();
    }

    void handleUpdateContact() {
        Student* student = studentManager.getStudent(currentUserID);
        if (student) {
            std::cout << "\nCurrent Emergency Contact: " << student->getEmergencyContact() << "\n";
            std::cout << "Enter new contact: ";
            std::string contact = InputHelper::getLine();
            student->updateEmergencyContact(contact);
            studentManager.updateStudent(*student);
        }
        InputHelper::pause();
    }
    
    void handleManageStudents() {
        std::cout << "\n========== MANAGE STUDENTS ==========\n";
        std::cout << "1. View All Students\n";
        // std::cout << "2. Add Student\n";
        // std::cout << "3. Remove Student\n";
        // std::cout << "4. Verify Payment (Clear Dues)\n";
        std::cout << "Choice: ";
        int choice = InputHelper::getInt();
        
        if (choice == 1) {
                std::cout << "\n========== ALL STUDENTS ==========" << "\n";
                std::cout << std::left << std::setw(12) << "ID"
                          << std::setw(28) << "Name"
                          << std::setw(8) << "Room"
                          << std::setw(6) << "Bed"
                          << std::setw(10) << "Hall"
                          << std::right << std::setw(10) << "Dues" << "\n";
                std::cout << "────────────────────────────────────────────────────────────────────────────\n";
                for (const auto& s : studentManager.getAllStudents()) {
                    std::cout << std::left << std::setw(12) << s.getStudentID()
                              << std::setw(28) << s.getName()
                              << std::setw(8) << s.getRoomNumber()
                              << std::setw(6) << s.getBedNumber()
                              << std::setw(10) << s.getHallName();
                    std::cout << std::right << std::fixed << std::setprecision(2) << std::setw(10) << s.getHallDues() << "\n";
                }
            InputHelper::pause();
    }
}
     void handleViewAllComplaints() {
        std::cout << "\n========== ALL COMPLAINTS ==========\n";
        auto& complaints = complaintManager.getAllComplaints();
        if (complaints.empty()) {
            std::cout << "No complaints found.\n";
        } else {
            for (const auto& c : complaints) {
                Student* s = studentManager.getStudent(c.getStudentID());
                std::cout << "\n┌─────────────────────────────────────┐\n";
                std::cout << "│ Complaint ID: " << c.getComplaintID() << "\n";
                std::cout << "│ Student: " << (s ? s->getName() : "Unknown") << "\n";
                std::cout << "│ Room: " << (s ? s->getRoomNumber() : "N/A") << "\n";
                std::cout << "│ Category: " << c.getCategory() << "\n";
                std::cout << "│ Description: " << c.getDescription() << "\n";
                std::cout << "│ Status: " << c.getStatus() << "\n";
                std::cout << "│ Date: " << c.getDate() << "\n";
                std::cout << "└─────────────────────────────────────┘\n";
            }
        }
        InputHelper::pause();
    }
    void handleResetPassword() {
        std::cout << "\n========== RESET PASSWORD ==========\n";
        std::cout << "Enter current password: ";
        std::string currentPassword = InputHelper::getLine();
        
        // Verify current password
        if (!authManager.login(currentUserID, currentPassword, false)) {
            std::cout << "\n✗ Current password is incorrect!\n";
            InputHelper::pause();
            return;
        }
        
        std::cout << "Enter new password: ";
        std::string newPassword = InputHelper::getLine();
        std::cout << "Confirm new password: ";
        std::string confirmPassword = InputHelper::getLine();
        
        if (newPassword != confirmPassword) {
            std::cout << "\n✗ Passwords do not match!\n";
        } else {
            authManager.resetPassword(currentUserID, newPassword, false);
            std::cout << "\n✓ Password reset successfully!\n";
        }
        InputHelper::pause();
    }
    