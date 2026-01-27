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
#include "../utils/MenuPrinter.h"
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

    // Menu display functions
    void showMainMenu() {
        MenuPrinter::showMainMenu();
    }
     void showStudentMenu() {
        MenuPrinter::showStudentMenu();
    }
     void showAdminMenu() {
        MenuPrinter::showAdminMenu();
    }

    // ------------- Student side features starts here ----------------
    // Handles viewing student profile
    void handleStudentProfile() {
        Student* student = studentManager.getStudent(currentUserID);
        if (student) {
            student->viewProfile();
        } else {
            std::cout << "Student profile not found.\n";
        }
        InputHelper::pause();
    }
    
    // Handles logging entry/exit
    void handleLogEntryExit() {
        MenuPrinter::entryExitMenu();
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

    // Handles updating email
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

    // Handles updating emergency contact
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

    // Handles filing a complaint
    void handleFileComplaint() {
        MenuPrinter::filingComplaintMenu();
        int catChoice = InputHelper::getInt();
        std::string category;
        switch (catChoice) {
            case 1: category = "Electricity"; break;
            case 2: category = "Plumbing"; break;
            case 3: category = "Housekeeping"; break;
            case 4: category = "Internet"; break;
            case 5: category = "Other"; break;
            default: category = "Other"; break;
        }

        std::cout << "Enter Description: ";
        std::string description = InputHelper::getLine();
        std::string cid = "C" + std::to_string(complaintManager.getAllComplaints().size() + 1);
        Complaint c(cid, category, description, "Pending", DateTimeHelper::getCurrentDate(), currentUserID);
        complaintManager.createComplaint(c);
        InputHelper::pause();
    }

    // Handles viewing student's own complaints
    void handleViewMyComplaints() {
        std::cout << "\n=== MY COMPLAINTS ===\n";
        auto comps = complaintManager.getComplaintsByStudent(currentUserID);
        if (comps.empty()) {
            std::cout << "You have no complaints filed.\n";
        } else {
            for (const auto& c : comps) {
                std::cout << "\nComplaint ID: " << c.getComplaintID() << "\n";
                std::cout << "Category: " << c.getCategory() << "\n";
                std::cout << "Description: " << c.getDescription() << "\n";
                std::cout << "Status: " << c.getStatus() << "\n";
                std::cout << "Date: " << c.getDate() << "\n";
            }
        }
        InputHelper::pause();
    }
    // ------------- Student side features ends here ----------------
    
    // Authentication handling
    bool performLogin(bool isAdminLogin) {
        InputHelper::clearScreen();
        std::cout << "\n========== " << (isAdminLogin ? "ADMIN" : "STUDENT") << " LOGIN ==========" << "\n";
        std::cout << "Username: ";
        std::string username = InputHelper::getLine();
        std::cout << "Password: ";
        std::string password = InputHelper::getPassword();
        
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
    
    // Handles managing students (admin)
    void handleManageStudents() {
        std::cout << "\n========== MANAGE STUDENTS ==========\n";
        std::cout << "1. View All Students\n";
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

    // Handles viewing all complaints (admin)
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

    // Handles resetting password
    void handleResetPassword() {
        std::cout << "\n========== RESET PASSWORD ==========\n";
        std::cout << "Enter current password: ";
        std::string currentPassword = InputHelper::getPassword();
        
        // Verify current password
        if (!authManager.login(currentUserID, currentPassword, false)) {
            std::cout << "\n✗ Current password is incorrect!\n";
            InputHelper::pause();
            return;
        }
        
        std::cout << "Enter new password: ";
        std::string newPassword = InputHelper::getPassword();
        std::cout << "Confirm new password: ";
        std::string confirmPassword = InputHelper::getPassword();
        
        if (newPassword != confirmPassword) {
            std::cout << "\n✗ Passwords do not match!\n";
        } else {
            authManager.resetPassword(currentUserID, newPassword, false);
            std::cout << "\n✓ Password reset successfully!\n";
        }
        InputHelper::pause();
    }

    // Student flow after login
    void studentFlow() {
        bool loggedIn = true;
        while (loggedIn) {
            InputHelper::clearScreen();
            showStudentMenu();
            int choice = InputHelper::getInt();
            
            switch (choice) {
                case 1: handleStudentProfile(); break;
                case 2: handleUpdateEmail(); break;
                case 3: handleUpdateContact(); break;
                case 4: handleFileComplaint(); break;
                case 5: handleViewMyComplaints(); break;
                case 6: handleLogEntryExit(); break;
                case 7: handleResetPassword(); break;
                case 8: 
                    loggedIn = false;
                    std::cout << "\n✓ Logged out successfully!\n";
                    InputHelper::pause();
                    break;
                default: 
                    std::cout << "Invalid choice!\n";
                    InputHelper::pause();
            }
        }
    }
    
    // Admin flow after login
    void adminFlow() {
        bool loggedIn = true;
        while (loggedIn) {
            InputHelper::clearScreen();
            showAdminMenu();
            int choice = InputHelper::getInt();
            
            switch (choice) {
                case 1: 
                    dashboardManager.displayDashboard();
                    InputHelper::pause();
                    break;
                case 2: handleManageStudents(); break;
                case 3: handleViewAllComplaints(); break;
                case 4:
                    loggedIn = false;
                    std::cout << "\n✓ Logged out successfully!\n";
                    InputHelper::pause();
                    break;
                default:
                    std::cout << "Invalid choice!\n";
                    InputHelper::pause();
            }
        }
    }
    
public:
    HallVerseApp() 
        : studentManager(&fileHandler),
          complaintManager(&fileHandler),
          workerManager(&fileHandler),
          entryExitManager(&fileHandler),
          authManager(&fileHandler, &hasher),
          assignmentManager(&fileHandler, &complaintManager, &workerManager),
          dashboardManager(&studentManager, &complaintManager, &entryExitManager),
          roomManager(),
          isAdmin(false) {}
    
    void run() {
        bool running = true;
        
        while (running) {
            InputHelper::clearScreen();
            showWelcome();
            showMainMenu();
            int choice = InputHelper::getInt();
            
            switch (choice) {
                case 1:
                    if (performLogin(true)) {
                        adminFlow();
                    }
                    break;
                case 2:
                    if (performLogin(false)) {
                        studentFlow();
                    }
                    break;
                case 3:
                    running = false;
                    std::cout << "\n╔════════════════════════════════════╗\n";
                    std::cout << "║ Thank you for using HallVerse!     ║\n";
                    std::cout << "║ Developed by Team-14               ║\n";
                    std::cout << "╚════════════════════════════════════╝\n\n";
                    break;
                default:
                    std::cout << "Invalid choice!\n";
                    InputHelper::pause();
            }
        }
    }
};
int main() {
#ifdef _WIN32
    // Ensure Windows console uses UTF-8 so box-drawing characters render correctly
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    HallVerseApp app;
    app.run();
    return 0;
}
