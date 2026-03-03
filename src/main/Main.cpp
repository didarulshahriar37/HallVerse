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

    string currentUserID;
    bool isAdmin;

    void showWelcome() {
        cout << "\n";
        cout << "╔═══════════════════════════════════════════╗\n";
        cout << "║                                           ║\n";
        cout << "║           WELCOME TO HALLVERSE            ║\n";
        cout << "║    Islamic University of Technology       ║\n";
        cout << "║                                           ║\n";
        cout << "╚═══════════════════════════════════════════╝\n";
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
        InputHelper::clearScreen();
        Student* student = studentManager.getStudent(currentUserID);
        if (student) {
            student->viewProfile();
        } else {
            cout << "Student profile not found.\n";
        }
        InputHelper::pause();
    }
    
    // Handles logging entry/exit
    void handleLogEntryExit() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::entryExitMenu();
            int choice = InputHelper::getInt();
            
            if (choice == 1) {
                entryExitManager.logEntry(currentUserID);
                InputHelper::pause();
            } else if (choice == 2) {
                entryExitManager.logExit(currentUserID);
                InputHelper::pause();
            } else if (choice == 3) {
                return;
            } else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    // Handles updating email
    void handleUpdateEmail() {
        InputHelper::clearScreen();
        Student* student = studentManager.getStudent(currentUserID);
        if (student) {
            cout << "\nCurrent Email: " << student->getEmail() << "\n";
            cout << "Enter new email: ";
            string email = InputHelper::getValidatedEmail();
            student->updateEmail(email);
            studentManager.updateStudent(*student);
        }
        InputHelper::pause();
    }

    // Handles updating emergency contact
    void handleUpdateContact() {
        InputHelper::clearScreen();
        Student* student = studentManager.getStudent(currentUserID);
        if (student) {
            cout << "\nCurrent Emergency Contact: " << student->getEmergencyContact() << "\n";
            cout << "Enter new contact: ";
            string contact = InputHelper::getLine();
            student->updateEmergencyContact(contact);
            studentManager.updateStudent(*student);
        }
        InputHelper::pause();
    }

    // Handles filing a complaint
    void handleFileComplaint() {
        InputHelper::clearScreen();
        MenuPrinter::filingComplaintMenu();
        int catChoice = InputHelper::getInt();
        if (catChoice == 6) return;

        string category;
        switch (catChoice) {
            case 1: category = "Electricity"; break;
            case 2: category = "Plumbing"; break;
            case 3: category = "Housekeeping"; break;
            case 4: category = "Internet"; break;
            case 5: category = "Other"; break;
            default: return;
        }

        cout << "Enter Description: ";
        string description = InputHelper::getLine();
        string cid = "C" + to_string(complaintManager.getAllComplaints().size() + 1);
        Complaint c(cid, category, description, "Pending", DateTimeHelper::getCurrentDate(), currentUserID);
        complaintManager.createComplaint(c);
        InputHelper::pause();
    }

    // Handles viewing student's own complaints
    void handleViewMyComplaints() {
        InputHelper::clearScreen();
        cout << "\n=== MY COMPLAINTS ===\n";
        auto comps = complaintManager.getComplaintsByStudent(currentUserID);
        if (comps.empty()) {
            cout << "You have no complaints filed.\n";
        } else {
            for (const auto& c : comps) {
                cout << "\nComplaint ID: " << c.getComplaintID() << "\n";
                cout << "Category: " << c.getCategory() << "\n";
                cout << "Description: " << c.getDescription() << "\n";
                cout << "Status: " << c.getStatus() << "\n";
                cout << "Date: " << c.getDate() << "\n";
            }
        }
        InputHelper::pause();
    }
    // ------------- Student side features ends here ----------------
    
    // Authentication handling
    bool performLogin(bool isAdminLogin) {
        InputHelper::clearScreen();
        cout << "\n========== " << (isAdminLogin ? "ADMIN" : "STUDENT") << " LOGIN ==========" << "\n";
        cout << "Username: ";
        string username = InputHelper::getLine();
        cout << "Password: ";
        string password = InputHelper::getPassword();
        
        if (authManager.login(username, password, isAdminLogin)) {
            currentUserID = username;
            isAdmin = isAdminLogin;
            cout << "\n\u2713 Login successful! Welcome, " << username << "\n";
            InputHelper::pause();
            return true;
        } else {
            cout << "\n\u2717 Invalid credentials!\n";
            InputHelper::pause();
            return false;
        }
    }
    
    // Login system
    void loginSystem() {
        while (true) {
            InputHelper::clearScreen();
            cout << "\n========== LOGIN ==========" << "\n";
            cout << "Username: ";
            string username = InputHelper::getLine();
            cout << "Password: ";
            string password = InputHelper::getPassword();
            
            if (authManager.login(username, password, true)) {
                currentUserID = username;
                isAdmin = true;
                adminFlow();
                return;
            }
            if (authManager.login(username, password, false)) {
                currentUserID = username;
                isAdmin = false;
                studentFlow();
                return;
            }
            cout << "\n\u2717 Invalid credentials!\n";
            cout << "1. Try Again\n";
            cout << "2. Go Back\n";
            cout << "Choice: ";
            int choice = InputHelper::getInt();
            if (choice == 2) {
                return;
            }
        }
    }
    
    // Handles managing students (admin)
    void handleManageStudents() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::manageStudentsMenu();
            int choice = InputHelper::getInt();
            
            if (choice == 1) {
                InputHelper::clearScreen();
                cout << "\n========== ALL STUDENTS ==========" << "\n";
                cout << left << setw(12) << "ID"
                          << setw(28) << "Name"
                          << setw(8) << "Room"
                          << setw(6) << "Bed"
                          << setw(10) << "Hall"
                          << right << setw(10) << "Dues" << "\n";
                cout << "────────────────────────────────────────────────────────────────────────────\n";
                for (const auto& s : studentManager.getAllStudents()) {
                    cout << left << setw(12) << s.getStudentID()
                              << setw(28) << s.getName()
                              << setw(8) << s.getRoomNumber()
                              << setw(6) << s.getBedNumber()
                              << setw(10) << s.getHallName();
                    cout << right << fixed << setprecision(2) << setw(10) << s.getHallDues() << "\n";
                }
                InputHelper::pause();
            }
            else if(choice == 2){
                InputHelper::clearScreen();
                cout << "\n========== ADD NEW STUDENT ==========\n";
                cout << left << setw(12) << "ID" << setw(28) << "Name" << setw(8) << "Room" << setw(6) << "Bed" << setw(10) << "Hall" << right << setw(10) << "Dues" << "\n";
                cout << "────────────────────────────────────────────────────────────────────────────\n";
                for(const auto& s : studentManager.getAllStudents()){
                    cout << left << setw(12) << s.getStudentID() << setw(28) << s.getName() << setw(8) << s.getRoomNumber() << setw(6) << s.getBedNumber() << setw(10) << s.getHallName();
                    cout << right << fixed << setprecision(2) << setw(10) << s.getHallDues() << "\n";
                }

                string id, name, email, contact;
                cout << "\nEnter Student ID: ";
                id = InputHelper::getLine();
                cout << "Enter Name: ";
                name = InputHelper::getLine();
                cout << "Enter Email: ";
                email = InputHelper::getValidatedEmail();
                cout << "Enter Emergency Contact: ";
                contact = InputHelper::getLine();
                cout << "Enter Hall Name (South/North) : ";
                string hall = InputHelper::getNormalizedHall();
                string room ;
                do{
                    cout << "Enter Room Number (e.g. 101): ";
                    room = InputHelper::getLine();
                    if(!InputHelper::isValidRoomForHall(hall, room)){
                        cout << "Invalid room for the selected hall. Try again.\n";
                    }
                } while(!InputHelper::isValidRoomForHall(hall, room));
                string bed;
                do{
                    cout << "Enter Bed Number (A/B/C/D): ";
                    bed = InputHelper::getLine();
                    if(!InputHelper::isValidBed(bed)){
                        cout << "Invalid Bed. Use A, B, C, D.\n";
                    }
                } while(!InputHelper::isValidBed(bed));

                bed[0] = toupper(bed[0]);
                cout << "Enter Hall Dues: ";
                double dues = InputHelper::getDouble();

                Student student(id, name, email, contact, room, bed, hall, dues);
                student.setPasswordHash(hasher.hash("password"));
                studentManager.addStudent(student);
                InputHelper::pause();
            }
            else if(choice == 3){
                InputHelper::clearScreen();
                cout << "Enter Student ID to remove: ";
                string id = InputHelper::getLine();
                studentManager.removeStudent(id);
                InputHelper::pause();
            }
            else if(choice == 4){
                InputHelper::clearScreen();
                cout << "\n========== VERIFY PAYMENT ==========\n";
                cout << "Enter Student ID: ";
                string id = InputHelper::getLine();
                Student* student = studentManager.getStudent(id);
                if(student){
                    cout << "\nStudent: " << student->getName() << "(" << student->getStudentID() << ")\n";
                    cout << "Hall: " << student->getHallName() << " (" << student->getRoomNumber()<< ", " << student->getBedNumber() << ")\n";
                    cout << "Current Due(s): $" << student->getHallDues() << "\n";
                    cout << "Clear all due(s)? (y/n): ";
                    string confirm = InputHelper::getLine();
                    if(confirm == "y" || confirm == "Y"){
                        student->setHallDues(0.0);
                        studentManager.updateStudent(*student);
                        cout << "✓ Payment verified and dues cleared!\n";
                    }
                }else{
                    cout << "Student not found!\n";
                }
                InputHelper::pause();
            }
            else if(choice == 5){
                return;
            }
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

        void handleCheckBed() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::bedAvailabilityMenu();
            int choice = InputHelper::getInt();
            
            if (choice == 1) {
                InputHelper::clearScreen();
                roomManager.displayAllBeds();
                InputHelper::pause();
            } else if (choice == 2) {
                InputHelper::clearScreen();
                string hall;
                cout << "Enter Hall Name (North/South): ";
                hall = InputHelper::getLine();
                roomManager.displayBedAvailability(hall);
                InputHelper::pause();
            } else if (choice == 3) {
                InputHelper::clearScreen();
                string hall, room;
                cout << "Enter Hall Name (North/South): ";
                hall = InputHelper::getLine();
                cout << "Enter Room Number: ";
                room = InputHelper::getLine();
                roomManager.displayBedAvailability(hall, room);
                InputHelper::pause();
            } else if (choice == 4) {
                InputHelper::clearScreen();
                cout << "\nCheck Specific Bed\n";
                cout << "Enter Hall Name (South/North): ";
                string hall = InputHelper::getNormalizedHall();
                string room;

                do {
                    cout << "Enter Room Number (e.g., 101): ";
                    room = InputHelper::getLine();
                    if (!InputHelper::isValidRoomForHall(hall, room)) {
                        cout << "Invalid room for the selected hall. Try again.\n";
                    }
                } while (!InputHelper::isValidRoomForHall(hall, room));
                string bed;
                do {
                    cout << "Enter Bed Number (A/B/C/D): ";
                    bed = InputHelper::getLine();
                    if (!InputHelper::isValidBed(bed)) {
                        cout << "Invalid bed. Use A, B, C or D.\n";
                    }
                } while (!InputHelper::isValidBed(bed));
                bed[0] = toupper(bed[0]);
                
                string status = roomManager.getBedStatus(hall, room, bed);
                cout << "\nBed Status: " << hall << " Hall, Room " << room << ", Bed " << bed << " is " << status << "\n";
                InputHelper::pause();
            } else if (choice == 5) {
                return;
            } else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    void handleChangeStudentRoom() {
        InputHelper::clearScreen();
        cout << "\n========== CHANGE STUDENT ROOM ==========\n";
        cout << "Enter Student ID: ";
        string studentID = InputHelper::getLine();
        
        Student* student = studentManager.getStudent(studentID);
        if (!student) {
            cout << "Student not found!\n";
            InputHelper::pause();
            return;
        }

        cout << "\nCurrent Room Assignment:\n";
        cout << "  Hall: " << student->getHallName() << "\n";
        cout << "  Room: " << student->getRoomNumber() << "\n";
        cout << "  Bed: " << student->getBedNumber() << "\n";
        

             // Select Hall
        string hall;
        do {
            cout << "\nSelect Hall:\n";
            cout << "  1. South\n";
            cout << "  2. North\n";
            cout << "Choose (1-2): ";
            int hallChoice = InputHelper::getInt();
            if (hallChoice == 1) {
                hall = "South";
            } else if (hallChoice == 2) {
                hall = "North";
            } else {
                std::cout << "Invalid choice. Try again.\n";
                continue;
            }
            break;
        } while (true);
        
        // Select Room
        string room;

            do {
            std::cout << "Enter Room Number (101-130 or 201-230): ";
            room = InputHelper::getLine();
            if (!InputHelper::isValidRoomForHall(hall, room)) {
                std::cout << "Invalid room for " << hall << " hall. Try again.\n";
            } else {
                break;
            }
        } while (true);
        
        // Select Bed
        std::string bed;
        do {
            cout << "Enter Bed Letter (A/B/C/D): ";
            bed = InputHelper::getLine();
            if (!InputHelper::isValidBed(bed)) {
                std::cout << "Invalid bed. Use A, B, C or D.\n";
            } else {
                bed[0] = std::toupper(bed[0]);
                break;
            }
        } while (true);
        
        // Check if bed is available
        if (studentManager.isBedOccupied(hall, room, bed)) {
            // Check if it's the same student's current bed
            Student* occupant = nullptr;
            for (auto& s : studentManager.getAllStudents()) {
                if (s.getHallName() == hall && s.getRoomNumber() == room && 
                    s.getBedNumber() == bed && s.getStudentID() != studentID) {
                    occupant = &s;
                    break;
                }
            }
            if (occupant) {
                cout << "\nError: Bed " << bed << " in Room " << room << " is already occupied by " 
                          << occupant->getName() << "!\n";
                InputHelper::pause();
                return;
            }
        }

            // Update student's room assignment
        string oldHall = student->getHallName();
        string oldRoom = student->getRoomNumber();
        string oldBed = student->getBedNumber();
        
        student->setHallName(hall);
        student->setRoomNumber(room);
        student->setBedNumber(bed);
        
        studentManager.updateStudent(*student);
        
        // Update room occupancy status in RoomManager
        roomManager.updateBedStatus(oldHall, oldRoom, oldBed, "Vacant");
        roomManager.updateBedStatus(hall, room, bed, "Occupied");
        
        cout << "\n✓ Room assignment updated successfully!\n";
        cout << "  Student: " << student->getName() << " (" << studentID << ")\n";
        cout << "  New Location: " << hall << " Hall, Room " << room << ", Bed " << bed << "\n";
        InputHelper::pause();
    
    }

    // Handles viewing all complaints (admin)
    void handleViewAllComplaints() {
        InputHelper::clearScreen();
        cout << "\n========== ALL COMPLAINTS ==========\n";
        auto& complaints = complaintManager.getAllComplaints();
        if (complaints.empty()) {
            cout << "No complaints found.\n";
        } else {
            for (const auto& c : complaints) {
                Student* s = studentManager.getStudent(c.getStudentID());
                cout << "\n┌─────────────────────────────────────┐\n";
                cout << "│ Complaint ID: " << c.getComplaintID() << "\n";
                cout << "│ Student: " << (s ? s->getName() : "Unknown") << "\n";
                cout << "│ Room: " << (s ? s->getRoomNumber() : "N/A") << "\n";
                cout << "│ Category: " << c.getCategory() << "\n";
                cout << "│ Description: " << c.getDescription() << "\n";
                cout << "│ Status: " << c.getStatus() << "\n";
                cout << "│ Date: " << c.getDate() << "\n";
                cout << "└─────────────────────────────────────┘\n";
            }
        }
        InputHelper::pause();
    }

    void handleEditHallDues() {
        InputHelper::clearScreen();
        cout << "\n=== EDIT HALL DUES ===\n";
        cout << "Enter Student ID: ";
        string id = InputHelper::getLine();
        Student* student = studentManager.getStudent(id);
        if (student) {
            cout << "Student: " << student->getName() << "\n";
            cout << "Current Dues: $" << student->getHallDues() << "\n";
            cout << "Enter new dues amount: ";
            double dues = InputHelper::getDouble();
            student->setHallDues(dues);
            studentManager.updateStudent(*student);
            cout << "\n✓ Hall dues updated!\n";
        } else {
            cout << "Student not found!\n";
        }
        InputHelper::pause();
    }

    // Handles resetting password
    void handleResetPassword() {
    InputHelper::clearScreen();
    cout << "\n========== RESET PASSWORD ==========\n";
    cout << "Enter current password: ";
    string currentPassword = InputHelper::getPassword();

    if (!authManager.login(currentUserID, currentPassword, false)) {
        cout << "\n✗ Current password is incorrect!\n";
        InputHelper::pause();
        return;
    }

    string newPassword, confirmPassword;

    while (true) {
        cout << "Enter new password: ";
        newPassword = InputHelper::getPassword();

        if (newPassword.length() < 8) {
            cout << "✗ Password must contain at least 8 characters!\n";
            continue;
        }

        cout << "Confirm new password: ";
        confirmPassword = InputHelper::getPassword();

        if (newPassword != confirmPassword) {
            cout << "✗ Passwords do not match!\n";
            continue;
        }

        break;
    }

    authManager.resetPassword(currentUserID, newPassword, false);
    cout << "\n✓ Password reset successfully!\n";
    InputHelper::pause();
}

 void handleUpdateComplaintStatus() {
        InputHelper::clearScreen();
        cout << "\n=== UPDATE COMPLAINT STATUS ===\n";
        cout << "Enter Complaint ID: ";
        string id = InputHelper::getLine();
        cout << "New Status:\n";
        cout << "  1. Pending\n";
        cout << "  2. In-Progress\n";
        cout << "  3. Resolved\n";
        cout << "Choose (1-3): ";
        int choice = InputHelper::getInt();
        
        string status;
        switch(choice) {
            case 1: status = "Pending"; break;
            case 2: status = "In-Progress"; break;
            case 3: status = "Resolved"; break;
            default: status = "Pending"; break;
        }
        
        complaintManager.updateComplaintStatus(id, status);
        InputHelper::pause();
    }
    
    void handleAssignWorker() {
        InputHelper::clearScreen();
        cout << "\n=== ASSIGN WORKER TO COMPLAINT ===\n";
        cout << "Enter Complaint ID: ";
        string complaintID = InputHelper::getLine();
        
        cout << "Worker Type:\n";
        cout << "  1. Electrician\n";
        cout << "  2. Plumber\n";
        cout << "  3. Carpenter\n";
        cout << "  4. General Maintenance\n";
        cout << "Choose (1-4): ";
        int choice = InputHelper::getInt();
        
        string role;
        switch(choice) {
            case 1: role = "Electrician"; break;
            case 2: role = "Plumber"; break;
            case 3: role = "Carpenter"; break;
            case 4: role = "General Maintenance"; break;
            default: role = "General Maintenance"; break;
        }
        
        assignmentManager.assignWorker(complaintID, role);
        InputHelper::pause();
    }
    
    void handleViewLogs() {
        InputHelper::clearScreen();
        cout << "\n========== ENTRY/EXIT LOGS ==========\n";
        auto& logs = entryExitManager.getLogs();
        if (logs.empty()) {
            cout << "No logs found.\n";
        } else {
            cout << "Record ID | Student ID   | Type  | Timestamp\n";
            cout << "──────────────────────────────────────────────────────\n";
            for (const auto& log : logs) {
                log.displayRecord();
            }
        }
        InputHelper::pause();
    }



    // Student flow after login
    void studentFlow() {
        bool loggedIn = true;
        while (loggedIn) {
            InputHelper::clearScreen();
            {
                Student* s = studentManager.getStudent(currentUserID);
                cout << "Welcome, " << (s ? s->getName() : currentUserID) << "\n";
            }
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
                    cout << "\n✓ Logged out successfully!\n";
                    InputHelper::pause();
                    break;
                default: 
                    cout << "Invalid choice!\n";
                    InputHelper::pause();
            }
        }
    }
    
    // Admin flow after login
    void adminFlow() {
        bool loggedIn = true;
        while (loggedIn) {
            InputHelper::clearScreen();
            cout << "Welcome, Admin\n";
            showAdminMenu();
            int choice = InputHelper::getInt();
            
            switch (choice) {
                case 1: 
                    InputHelper::clearScreen();
                    dashboardManager.displayDashboard();
                    InputHelper::pause();
                    break;
                case 2: handleManageStudents(); break;
                case 3: handleViewAllComplaints(); break;
                case 4: handleUpdateComplaintStatus(); break;
                case 5: handleAssignWorker(); break;
                case 6: handleViewLogs(); break;
                case 7: handleEditHallDues(); break;
                case 8: handleCheckBed(); break;
                case 9: handleChangeStudentRoom(); break;
                case 10:
                    loggedIn = false;
                    cout << "\n✓ Logged out successfully!\n";
                    InputHelper::pause();
                    break;
                default:
                    cout << "Invalid choice!\n";
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
                    loginSystem();
                    break;
                case 2:
                    running = false;
                    cout << "\n╔════════════════════════════════════╗\n";
                    cout << "║ Thank you for using HallVerse!     ║\n";
                    cout << "║      Developed by Team-14          ║\n";
                    cout << "╚════════════════════════════════════╝\n\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
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
