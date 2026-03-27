#include <iostream>
#include <iomanip>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#endif
#include <string>
#include <sstream>
#include <vector>
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
        InputHelper::clearScreen();
        pair<bool, string> status = entryExitManager.getCurrentStatus(currentUserID);
        bool isLoggedIn = status.first;
        string lastTimestamp = status.second;
        MenuPrinter::conditionalEntryExitMenu(isLoggedIn, lastTimestamp);
        int choice = InputHelper::getInt();
        
        if (choice == 1) {
            if (isLoggedIn) {
                entryExitManager.logExit(currentUserID);
            } else {
                entryExitManager.logEntry(currentUserID);
            }
            InputHelper::pause();
        } else if (choice == 2) {
            // Go back, do nothing
        } else {
            cout << "Invalid choice!\n";
            InputHelper::pause();
        }
        // After action or invalid, return to student menu
    }

    // Handles updating student email
    void handleUpdateEmail() {
        InputHelper::clearScreen();
        Student* student = studentManager.getStudent(currentUserID);
        if (student) {
            cout << "\nCurrent Email: " << student->getEmail() << "\n";
            cout << "Enter new email: ";
            string email = InputHelper::getValidateEmail();
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
            string contact = InputHelper::getNumericLine();
            student->updateEmergencyContact(contact);
            studentManager.updateStudent(*student);
        }
        InputHelper::pause();
    }

    // Parent handler: Update Information sub-menu
    void handleUpdateInfo() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::updateInfoMenu();
            int choice = InputHelper::getInt();
            if (choice == 1)      handleUpdateEmail();
            else if (choice == 2) handleUpdateContact();
            else if (choice == 3) return;
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    // Handles filing a complaint
    void handleFileComplaint() {
        while (true) {
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
                default: continue;
            }

            cout << "Enter Description: ";
            string description = InputHelper::getLine();
            string cid = "C" + to_string(complaintManager.getAllComplaints().size() + 1);
            Complaint c(cid, category, description, "Pending", DateTimeHelper::getCurrentDate(), currentUserID);
            complaintManager.createComplaint(c);
            InputHelper::pause();
            return;
        }
    }

    // Handles viewing student's own complaints (with worker info for In-Progress/Resolved)
    void handleViewMyComplaintsByStatus(const string& statusFilter) {
        InputHelper::clearScreen();
        auto comps = complaintManager.getComplaintsByStudent(currentUserID);
        
        // Count matching complaints
        int count = 0;
        for (const auto& c : comps) {
            if (statusFilter == "" || c.getStatus() == statusFilter) count++;
        }

        string label = (statusFilter == "") ? "ALL" : statusFilter;
        cout << "\n╔══════════════════════════════════════════════════╗\n";
        cout << "║  MY COMPLAINTS — " << left << setw(32) << label << "║\n";
        cout << "║  Total in this section: " << left << setw(25) << count << "║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";

        if (count == 0) {
            cout << "\n  No " << label << " complaints found.\n";
            InputHelper::pause();
            return;
        }

        if (statusFilter == "Resolved") {
            cout << "\n  " << string(105, '-') << "\n";
            cout << "  " << left
                 << setw(12) << "ID"
                 << setw(16) << "Category"
                 << setw(14) << "Date"
                 << setw(25) << "Worker Name"
                 << setw(20) << "Service Role"
                 << "Contact No" << "\n";
            cout << "  " << string(105, '-') << "\n";
            
            for (const auto& c : comps) {
                if (c.getStatus() != "Resolved") continue;
                
                string workerName = "N/A", workerRole = "N/A", workerContact = "N/A";
                auto& assignments = assignmentManager.getAssignmentsByComplaint(c.getComplaintID());
                if (!assignments.empty()) {
                    const WorkAssignment& wa = assignments.back();
                    workerName = wa.getWorkerID();
                    for (auto& w : workerManager.getAllWorkers()) {
                        if (w.getWorkerID() == wa.getWorkerID()) {
                            workerName = w.getName();
                            workerRole = w.getRole();
                            workerContact = w.getContactNumber();
                            break;
                        }
                    }
                }
                
                string dispWorker = workerName;
                if (dispWorker.length() > 23) dispWorker = dispWorker.substr(0, 20) + "...";
                
                cout << "  " << left
                     << setw(12) << c.getComplaintID()
                     << setw(16) << (c.getCategory().length() > 15 ? c.getCategory().substr(0,12) + "..." : c.getCategory())
                     << setw(14) << c.getDate()
                     << setw(25) << dispWorker
                     << setw(20) << (workerRole.length() > 19 ? workerRole.substr(0,16) + "..." : workerRole)
                     << workerContact << "\n";
            }
            cout << "  " << string(105, '-') << "\n";
        } else {
            int idx = 0;
            for (const auto& c : comps) {
                if (statusFilter != "" && c.getStatus() != statusFilter) continue;
                idx++;
                cout << "\n  [" << idx << "/" << count << "]\n";
                cout << "  ┌──────────────────────────────────────────┐\n";
                cout << "  │ Complaint ID : " << left << setw(27) << c.getComplaintID()   << "│\n";
                cout << "  │ Category     : " << left << setw(27) << c.getCategory()       << "│\n";
                cout << "  │ Status       : " << left << setw(27) << c.getStatus()         << "│\n";
                cout << "  │ Date         : " << left << setw(27) << c.getDate()           << "│\n";
                cout << "  │ Description  : " << left << setw(27) << c.getDescription().substr(0,27) << "│\n";

                // Show worker info for In-Progress
                if (c.getStatus() == "In-Progress") {
                    auto& assignments = assignmentManager.getAssignmentsByComplaint(c.getComplaintID());
                    if (!assignments.empty()) {
                        const WorkAssignment& wa = assignments.back();
                        Worker* worker = nullptr;
                        for (auto& w : workerManager.getAllWorkers()) {
                            if (w.getWorkerID() == wa.getWorkerID()) {
                                worker = &w;
                                break;
                            }
                        }
                        cout << "  ├──────────────────────────────────────────┤\n";
                        cout << "  │ ── Assigned Worker ──                     │\n";
                        cout << "  │ Worker Name  : " << left << setw(27) << (worker ? worker->getName() : wa.getWorkerID()) << "│\n";
                        cout << "  │ Service Type : " << left << setw(27) << (worker ? worker->getRole() : "N/A") << "│\n";
                        cout << "  │ Work Status  : " << left << setw(27) << wa.getStatus() << "│\n";
                        cout << "  │ Contact No.  : " << left << setw(27) << (worker ? worker->getContactNumber() : "N/A") << "│\n";
                    }
                }
                cout << "  └──────────────────────────────────────────┘\n";
            }
        }
        InputHelper::pause();
    }

    void handleViewMyComplaints() {
        while (true) {
            InputHelper::clearScreen();
            
            auto comps = complaintManager.getComplaintsByStudent(currentUserID);
            int pending = 0, inProgress = 0, resolved = 0;
            for (const auto& c : comps) {
                if (c.getStatus() == "Pending") pending++;
                else if (c.getStatus() == "In-Progress") inProgress++;
                else if (c.getStatus() == "Resolved") resolved++;
            }
            
            MenuPrinter::studentViewComplaintsMenu(pending, inProgress, resolved);
            
            int choice = InputHelper::getInt();
            if (choice == 1) handleViewMyComplaintsByStatus("Pending");
            else if (choice == 2) handleViewMyComplaintsByStatus("In-Progress");
            else if (choice == 3) handleViewMyComplaintsByStatus("Resolved");
            else if (choice == 4) return;
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    // Parent handler: File/View Complaints sub-menu
    void handleFileViewComplaints() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::fileViewComplaintsMenu();
            int choice = InputHelper::getInt();
            if (choice == 1) handleFileComplaint();
            else if (choice == 2) handleViewMyComplaints();
            else if (choice == 3) return;
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }
    // ------------- Student side features ends here ----------------
    
    // Authentication handling
    // Performs login for admin or student
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
        // Pre-compute default password hashes for comparison
        const string studentDefaultHash = hasher.hash("password");
        const string workerDefaultHash  = hasher.hash("worker");

        while (true) {
            InputHelper::clearScreen();
            cout << "\n========== LOGIN ==========" << "\n";
            cout << "Username: ";
            string username = InputHelper::getLine();
            cout << "Password: ";
            string password = InputHelper::getPassword();

            // ── Admin login (no first-login check needed) ──
            if (authManager.login(username, password, true)) {
                currentUserID = username;
                isAdmin = true;
                adminFlow();
                return;
            }

            // ── Student login ──
            if (authManager.login(username, password, false)) {
                currentUserID = username;
                isAdmin = false;

                // Detect default password — force change before menu access
                if (hasher.hash(password) == studentDefaultHash) {
                    forcedStudentPasswordChange();
                }

                studentFlow();
                return;
            }

            // ── Worker login ──
            if (workerManager.loginWorker(username, password)) {
                currentUserID = username;
                isAdmin = false;

                // Detect default password — force change before menu access
                if (hasher.hash(password) == workerDefaultHash) {
                    forcedWorkerPasswordChange();
                }

                workerFlow();
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

                string id, name, email, contact;
                bool backToMenu = false;
                while (true) {
                    cout << "\nEnter Student ID: ";
                    id = InputHelper::getNumericLine();
                    if (studentManager.getStudent(id) != nullptr) {
                        cout << "✗ Error: Student already exists!\n";
                        cout << "1. Try Again\n";
                        cout << "2. Go Back\n";
                        cout << "Choice: ";
                        int idChoice = InputHelper::getInt();
                        if (idChoice == 2) {
                            backToMenu = true;
                            break;
                        }
                        continue;
                    }
                    break;
                }
                if (backToMenu) continue;
                cout << "Enter Name: ";
                name = InputHelper::getLine();
                cout << "Enter Email: ";
                email = InputHelper::getValidateEmail();
                cout << "Enter Emergency Contact: ";
                contact = InputHelper::getNumericLine();
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
                double dues = InputHelper::getNonNegativeDouble();

                Student student(id, name, email, contact, room, bed, hall, dues);
                student.setPasswordHash(hasher.hash("password"));
                studentManager.addStudent(student);
                InputHelper::pause();
            }
            else if(choice == 3){
                InputHelper::clearScreen();
                cout << "\n========== REMOVE STUDENT ==========\n";
                cout << left << setw(12) << "ID" << setw(28) << "Name" << setw(8) << "Room" << setw(6) << "Bed" << setw(10) << "Hall" << right << setw(10) << "Dues" << "\n";
                cout << "────────────────────────────────────────────────────────────────────────────\n";
                for(const auto& s : studentManager.getAllStudents()){
                    cout << left << setw(12) << s.getStudentID() << setw(28) << s.getName() << setw(8) << s.getRoomNumber() << setw(6) << s.getBedNumber() << setw(10) << s.getHallName();
                    cout << right << fixed << setprecision(2) << setw(10) << s.getHallDues() << "\n";
                }

                cout << "\nEnter Student ID to remove: ";
                string id = InputHelper::getNumericLine();
                // locate student to free their bed before deletion
                Student* target = studentManager.getStudent(id);
                if (target) {
                    // Update bed status to vacant in room manager
                    roomManager.updateBedStatus(
                        target->getHallName(),
                        target->getRoomNumber(),
                        target->getBedNumber(),
                        "Vacant"
                    );
                }
                studentManager.removeStudent(id);
                InputHelper::pause();
            }
            else if(choice == 4){
                handleViewLogs();
            }
            else if(choice == 5){
                handleResetStudentPassword();
            }
            else if(choice == 6){
                // reset all student passwords to default
                cout << "\nAre you sure you want to reset ALL student passwords to default? (y/n): ";
                string confirm = InputHelper::getLine();
                if (confirm == "y" || confirm == "Y") {
                    string defaultHash = hasher.hash("password");
                    studentManager.resetAllPasswords(defaultHash);
                    InputHelper::pause();
                }
            }
            else if(choice == 7){
                return;
            }
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    void handleResetStudentPassword() {
        InputHelper::clearScreen();
        cout << "\n========== RESET STUDENT PASSWORD ==========\n";
        cout << left << setw(12) << "ID" << setw(28) << "Name" << setw(8) << "Room" << setw(6) << "Bed" << setw(10) << "Hall" << right << setw(10) << "Dues" << "\n";
        cout << "────────────────────────────────────────────────────────────────────────────\n";
        for(const auto& s : studentManager.getAllStudents()){
            cout << left << setw(12) << s.getStudentID() << setw(28) << s.getName() << setw(8) << s.getRoomNumber() << setw(6) << s.getBedNumber() << setw(10) << s.getHallName();
            cout << right << fixed << setprecision(2) << setw(10) << s.getHallDues() << "\n";
        }

        cout << "\nEnter Student ID (or 'q' to go back): ";
        string studentID = InputHelper::getLine();
        if (studentID == "q" || studentID == "Q") {
            return;
        }

        Student* student = studentManager.getStudent(studentID);
        if (!student) {
            cout << "\n✗ Student not found!\n";
            InputHelper::pause();
            return;
        }

        string defaultPassword = "password";
        authManager.resetPassword(studentID, defaultPassword, false);
        cout << "\n✓ Password reset successfully!\n";
        cout << "Student: " << student->getName() << "\n";
        cout << "New Password: " << defaultPassword << "\n";
        InputHelper::pause();
    }

        void handleCheckBed() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::bedAvailabilityMenu();
            int choice = InputHelper::getInt();
            
            if (choice == 1) {
                // Filter sub-menu for View All Beds
                while (true) {
                    InputHelper::clearScreen();
                    MenuPrinter::viewAllBedsMenu();
                    int filterChoice = InputHelper::getInt();
                    if (filterChoice == 1) {
                        InputHelper::clearScreen();
                        roomManager.displayBedsByStatus("");          // All beds
                        InputHelper::pause();
                    } else if (filterChoice == 2) {
                        InputHelper::clearScreen();
                        roomManager.displayBedsByStatus("Occupied");  // Occupied only
                        InputHelper::pause();
                    } else if (filterChoice == 3) {
                        InputHelper::clearScreen();
                        roomManager.displayBedsByStatus("Vacant");    // Vacant only
                        InputHelper::pause();
                    } else if (filterChoice == 4) {
                        break;                                         // Go Back to bed availability menu
                    } else {
                        cout << "  Invalid choice!\n";
                        InputHelper::pause();
                    }
                }

            } else if (choice == 2) {
                InputHelper::clearScreen();
                string hall;
                cout << "Enter Hall Name (North/South): ";
                hall = InputHelper::getLine();
                roomManager.displayBedAvailability(hall);
                InputHelper::pause();
            } else if (choice == 3) {
                InputHelper::clearScreen();
                cout << "Enter Hall Name (North/South): ";
                string hall = InputHelper::getNormalizedHall();
                string room;
                do {
                    cout << "Enter Room Number (e.g., 101): ";
                    room = InputHelper::getLine();
                    if (!InputHelper::isValidRoomForHall(hall, room)) {
                        cout << "Invalid room for the selected hall. Try again.\n";
                    }
                } while (!InputHelper::isValidRoomForHall(hall, room));
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
        
        // Select Room: show only rooms that have available beds
        string room;
        {
            auto roomsList = roomManager.getAvailableRooms(hall);

            if (roomsList.empty()) {
                cout << "\nNo available rooms in " << hall << " hall.\n";
                InputHelper::pause();
                return;
            }

            cout << "\nAvailable Rooms in " << hall << " Hall:\n";
            for (size_t i = 0; i < roomsList.size(); ++i) {
                cout << "  " << (i+1) << ". " << roomsList[i] << "\n";
            }

            int choice = -1;
            do {
                cout << "Choose Room (1-" << roomsList.size() << "): ";
                choice = InputHelper::getInt();
                if (choice < 1 || choice > (int)roomsList.size()) {
                    cout << "Invalid choice. Try again.\n";
                }
            } while (choice < 1 || choice > (int)roomsList.size());

            room = roomsList[choice-1];
        }

        // Select Bed: show only vacant beds for the chosen room
        string bed;
        {
            auto bedLetters = roomManager.getAvailableBeds(hall, room);

            if (bedLetters.empty()) {
                cout << "\nNo available beds in Room " << room << " of " << hall << " hall.\n";
                InputHelper::pause();
                return;
            }

            cout << "\nAvailable Beds in Room " << room << ":\n";
            for (size_t i = 0; i < bedLetters.size(); ++i) {
                cout << "  " << (i+1) << ". " << bedLetters[i] << "\n";
            }

            int bchoice = -1;
            do {
                cout << "Choose Bed (1-" << bedLetters.size() << "): ";
                bchoice = InputHelper::getInt();
                if (bchoice < 1 || bchoice > (int)bedLetters.size()) {
                    cout << "Invalid choice. Try again.\n";
                }
            } while (bchoice < 1 || bchoice > (int)bedLetters.size());

            bed = bedLetters[bchoice-1];
        }
        
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

    // Handles viewing filtered complaints by status (admin)
    void handleViewAllComplaints(const string& statusFilter = "") {
        InputHelper::clearScreen();

        auto& complaints = complaintManager.getAllComplaints();

        // Count matching complaints for the subsection header
        int count = 0;
        for (const auto& c : complaints) {
            if (statusFilter == "" || c.getStatus() == statusFilter) count++;
        }

        // Subsection header banner
        string label = (statusFilter == "") ? "ALL" : statusFilter;
        cout << "\n╔══════════════════════════════════════════════════╗\n";
        cout << "║  COMPLAINTS — " << left << setw(35) << label          << "║\n";
        cout << "║  Total in this section: " << left << setw(25) << count << "║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";

        if (count == 0) {
            cout << "\n  No " << label << " complaints found.\n";
            InputHelper::pause();
            return;
        }

        int idx = 0;
        for (const auto& c : complaints) {
            if (statusFilter != "" && c.getStatus() != statusFilter) continue;
            idx++;
            Student* s = studentManager.getStudent(c.getStudentID());
            cout << "\n  [" << idx << "/" << count << "]";
            cout << "\n  ┌──────────────────────────────────────────┐\n";
            cout << "  │ Complaint ID : " << left << setw(27) << c.getComplaintID()                  << "│\n";
            cout << "  │ Student      : " << left << setw(27) << (s ? s->getName() : "Unknown")      << "│\n";
            cout << "  │ Room         : " << left << setw(27) << (s ? s->getRoomNumber() : "N/A")    << "│\n";
            cout << "  │ Category     : " << left << setw(27) << c.getCategory()                     << "│\n";
            cout << "  │ Status       : " << left << setw(27) << c.getStatus()                       << "│\n";
            cout << "  │ Date         : " << left << setw(27) << c.getDate()                         << "│\n";
            cout << "  │ Description  : " << left << setw(27) << c.getDescription().substr(0,27)     << "│\n";

                // Show assigned worker info for In-Progress or Resolved complaints
                if (c.getStatus() == "In-Progress" || c.getStatus() == "Resolved") {
                    auto& assignments = assignmentManager.getAssignmentsByComplaint(c.getComplaintID());
                    if (!assignments.empty()) {
                        const WorkAssignment& wa = assignments.back();
                        Worker* worker = nullptr;
                        for (auto& w : workerManager.getAllWorkers()) {
                            if (w.getWorkerID() == wa.getWorkerID()) {
                                worker = &w;
                                break;
                            }
                        }
                        cout << "  ├──────────────────────────────────────────┤\n";
                        cout << "  │ ── Assigned Worker ──                     │\n";
                        cout << "  │ Worker Name  : " << left << setw(27) << (worker ? worker->getName() : wa.getWorkerID()) << "│\n";
                        cout << "  │ Service Type : " << left << setw(27) << (worker ? worker->getRole() : "N/A")          << "│\n";
                        cout << "  │ Work Status  : " << left << setw(27) << wa.getStatus()                                 << "│\n";
                    }
                }
            cout << "  └──────────────────────────────────────────┘\n";
        }
        InputHelper::pause();
    }


    void handleVerifyPayment() {
        while (true) {
            InputHelper::clearScreen();
            cout << "\n========== VERIFY PAYMENT ==========\n";
            cout << "Enter Student ID (or 'q' to go back): ";
            string id = InputHelper::getLine();
            if (id == "q" || id == "Q") return;

            Student* s = studentManager.getStudent(id);
            if (!s) {
                cout << "Student not found!\n";
                InputHelper::pause();
                continue;
            }

            while (true) {
                cout << "\nStudent: " << s->getName() << " (" << id << ")\n";
                cout << "Current Dues: $" << s->getHallDues() << "\n";
                cout << "Enter payment amount: ";
                double amount = InputHelper::getNonNegativeDouble();

                if (amount > s->getHallDues()) {
                    cout << "\n✗ Error: Payment amount exceeds current dues!\n";
                    cout << "1. Try Again\n";
                    cout << "2. Back to Dues Menu\n";
                    cout << "Choice: ";
                    int choice = InputHelper::getInt();
                    if (choice == 1) continue;
                    return;
                }

                s->setHallDues(s->getHallDues() - amount);
                studentManager.updateStudent(*s);
                cout << "\n✓ Payment of $" << amount << " verified. New dues: $" << s->getHallDues() << "\n";
                InputHelper::pause();
                return;
            }
        }
    }

    void handleAddPenalty() {
        InputHelper::clearScreen();
        cout << "\n========== ADD PENALTY ==========\n";
        cout << "Enter Student ID: ";
        string id = InputHelper::getLine();
        Student* s = studentManager.getStudent(id);
        if (s) {
            cout << "Current Dues: $" << s->getHallDues() << "\n";
            cout << "Enter penalty amount: ";
            double penalty = InputHelper::getNonNegativeDouble();
            s->setHallDues(s->getHallDues() + penalty);
            studentManager.updateStudent(*s);
            cout << "\n✓ Penalty added. New dues: $" << s->getHallDues() << "\n";
        } else {
            cout << "Student not found!\n";
        }
        InputHelper::pause();
    }

    void handleAddHallFee() {
        InputHelper::clearScreen();
        cout << "\n========== ADD HALL FEE (ALL STUDENTS) ==========\n";
        cout << "Enter hall fee amount to add to all students: ";
        double fee = InputHelper::getNonNegativeDouble();
        
        cout << "Are you sure? (y/n): ";
        string confirm = InputHelper::getLine();
        if (confirm == "y" || confirm == "Y") {
            for (auto& s : studentManager.getAllStudents()) {
                s.setHallDues(s.getHallDues() + fee);
            }
            studentManager.saveAll();
            cout << "\n✓ Hall fee added to all students!\n";
        } else {
            cout << "Action cancelled.\n";
        }
        InputHelper::pause();
    }

    void handleManageDues() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::manageDuesMenu();
            int choice = InputHelper::getInt();
            if (choice == 1) handleVerifyPayment();
            else if (choice == 2) handleAddPenalty();
            else if (choice == 3) handleAddHallFee();
            else if (choice == 4) return;
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    // Handles resetting password
    void handleResetPassword() {
        while (true) {
            InputHelper::clearScreen();
            cout << "\n========== UPDATE PASSWORD ==========\n";
            cout << "Enter current password: ";
            string currentPassword = InputHelper::getPassword();

            if (!authManager.login(currentUserID, currentPassword, false)) {
                cout << "\n✗ Current password is incorrect!\n";
                cout << "1. Try Again\n";
                cout << "2. Go Back\n";
                cout << "Choice: ";
                int choice = InputHelper::getInt();
                if (choice == 1) continue;
                return;
            }

            string newPassword, confirmPassword;
            while (true) {
                cout << "Enter new password: ";
                newPassword = InputHelper::getPassword();

                if (newPassword == currentPassword) {
                    cout << "✗ This password is already in use by you! Please use a new one.\n";
                    continue;
                }

                if (newPassword == "password") {
                    cout << "✗ Password cannot be set as the default password ('password').\n";
                    continue;
                }

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
            cout << "\n✓ Password updated successfully!\n";
            InputHelper::pause();
            return;
        }
    }

    // ── Forced password change on first student login ──────────────────────
    // Returns true if the user successfully changed their password,
    // false only if the user somehow exits (should not happen — loop is infinite).
    bool forcedStudentPasswordChange() {
        InputHelper::clearScreen();
        cout << "\n╔══════════════════════════════════════════════════════════╗\n";
        cout << "║          ⚠  MANDATORY PASSWORD CHANGE  ⚠                ║\n";
        cout << "╠══════════════════════════════════════════════════════════╣\n";
        cout << "║  You are using the default password.                     ║\n";
        cout << "║  For your security you MUST set a new password           ║\n";
        cout << "║  before you can access the system.                       ║\n";
        cout << "╚══════════════════════════════════════════════════════════╝\n";

        const string defaultPassword = "password";

        while (true) {
            string newPassword, confirmPassword;

            cout << "\nEnter new password (min 8 chars): ";
            newPassword = InputHelper::getPassword();

            if (newPassword.length() < 8) {
                cout << "\n✗ Password must be at least 8 characters. Try again.\n";
                continue;
            }

            if (newPassword == defaultPassword) {
                cout << "\n✗ New password cannot be the same as the default password ('" << defaultPassword << "'). Choose a different password.\n";
                continue;
            }

            cout << "Confirm new password: ";
            confirmPassword = InputHelper::getPassword();

            if (newPassword != confirmPassword) {
                cout << "\n✗ Passwords do not match. Try again.\n";
                continue;
            }

            // Commit the new password
            authManager.resetPassword(currentUserID, newPassword, false);
            studentManager.loadStudents();
            InputHelper::clearScreen();
            cout << "\n✓ Password changed successfully! You may now access the system.\n";
            InputHelper::pause();
            return true;
        }
    }

    // ── Forced password change on first worker login ───────────────────────
    bool forcedWorkerPasswordChange() {
        InputHelper::clearScreen();
        cout << "\n╔══════════════════════════════════════════════════════════╗\n";
        cout << "║          ⚠  MANDATORY PASSWORD CHANGE  ⚠                ║\n";
        cout << "╠══════════════════════════════════════════════════════════╣\n";
        cout << "║  You are using the default password.                     ║\n";
        cout << "║  For your security you MUST set a new password           ║\n";
        cout << "║  before you can access the system.                       ║\n";
        cout << "╚══════════════════════════════════════════════════════════╝\n";

        const string defaultPassword = "worker";

        while (true) {
            string newPassword, confirmPassword;

            cout << "\nEnter new password (min 8 chars): ";
            newPassword = InputHelper::getPassword();

            if (newPassword.length() < 8) {
                cout << "\n✗ Password must be at least 8 characters. Try again.\n";
                continue;
            }

            if (newPassword == defaultPassword) {
                cout << "\n✗ New password cannot be the same as the default password ('" << defaultPassword << "'). Choose a different password.\n";
                continue;
            }

            cout << "Confirm new password: ";
            confirmPassword = InputHelper::getPassword();

            if (newPassword != confirmPassword) {
                cout << "\n✗ Passwords do not match. Try again.\n";
                continue;
            }

            // Commit the new password
            workerManager.updateWorkerPassword(currentUserID, newPassword);
            InputHelper::clearScreen();
            cout << "\n✓ Password changed successfully! You may now access the system.\n";
            InputHelper::pause();
            return true;
        }
    }

    void handleAssignWorker() {
        while (true) {
            InputHelper::clearScreen();
            cout << "\n╔══════════════════════════════════════════════╗\n";
            cout << "║       ASSIGN WORKER TO COMPLAINT             ║\n";
            cout << "╚══════════════════════════════════════════════╝\n";

            // Collect only Pending complaints
            auto& allComplaints = complaintManager.getAllComplaints();
            vector<Complaint> pending;
            for (const auto& c : allComplaints) {
                if (c.getStatus() == "Pending") {
                    pending.push_back(c);
                }
            }

            // Sort by date ascending (oldest first) — date is stored as YYYY-MM-DD string
            sort(pending.begin(), pending.end(), [](const Complaint& a, const Complaint& b) {
                return a.getDate() < b.getDate();
            });

            if (pending.empty()) {
                cout << "\n  No pending complaints to assign.\n";
                InputHelper::pause();
                return;
            }

            // Display pending complaints table
            cout << "\n  Pending Complaints (oldest first):\n";
            cout << "  " << string(72, '-') << "\n";
            cout << "  " << left
                 << setw(8)  << "ID"
                 << setw(16) << "Date"
                 << setw(16) << "Category"
                 << setw(14) << "Student"
                 << "Description" << "\n";
            cout << "  " << string(72, '-') << "\n";
            for (const auto& c : pending) {
                Student* s = studentManager.getStudent(c.getStudentID());
                string desc = c.getDescription();
                if (desc.length() > 20) desc = desc.substr(0, 17) + "...";
                cout << "  " << left
                     << setw(8)  << c.getComplaintID()
                     << setw(16) << c.getDate()
                     << setw(16) << c.getCategory()
                     << setw(14) << (s ? s->getName().substr(0, 12) : "Unknown")
                     << desc << "\n";
            }
            cout << "  " << string(72, '-') << "\n";

            cout << "\n  Enter Complaint ID to assign (or 'q' to go back): ";
            string complaintID = InputHelper::getLine();
            if (complaintID == "q" || complaintID == "Q") return;

            // Find the selected complaint
            Complaint* selected = nullptr;
            for (auto& c : allComplaints) {
                if (c.getComplaintID() == complaintID && c.getStatus() == "Pending") {
                    selected = &c;
                    break;
                }
            }
            if (!selected) {
                cout << "\n  ✗ Complaint not found or not Pending. Please try again.\n";
                InputHelper::pause();
                continue;
            }

            // Auto-determine worker role from complaint category
            string category = selected->getCategory();
            string role;
            if      (category == "Electricity")  role = "Electrician";
            else if (category == "Plumbing")      role = "Plumber";
            else if (category == "Housekeeping")  role = "Carpenter";
            else                                  role = "General Maintenance";

            cout << "\n  Category  : " << category << "\n";
            cout << "  Auto-role : " << role << "\n";
            cout << "  Confirm assignment? (y/n): ";
            string confirm = InputHelper::getLine();
            if (confirm != "y" && confirm != "Y") {
                cout << "  Assignment cancelled.\n";
                InputHelper::pause();
                continue;
            }

            assignmentManager.assignWorker(complaintID, role);
            InputHelper::pause();
        }
    }
    
    void handleViewLogs() {
        while (true) {
            InputHelper::clearScreen();
            auto& logs = entryExitManager.getLogs();

            // Header
            cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
            cout << "║                   ENTRY / EXIT LOGS                         ║\n";
            cout << "║  Total Records : " << left << setw(44) << logs.size()       << "║\n";
            cout << "╚══════════════════════════════════════════════════════════════╝\n";

            if (logs.empty()) {
                cout << "\n  No logs recorded yet.\n";
                InputHelper::pause();
                return;
            }

            // Search prompt
            cout << "\n  Enter Student ID to filter  (or press Enter to show all): ";
            string filterID = InputHelper::getLine();

            // Trim leading/trailing spaces from input
            size_t start = filterID.find_first_not_of(" \t");
            size_t end   = filterID.find_last_not_of(" \t");
            filterID = (start == string::npos) ? "" : filterID.substr(start, end - start + 1);

            // If a filter is provided, validate the student exists
            if (!filterID.empty()) {
                Student* s = studentManager.getStudent(filterID);
                if (!s) {
                    cout << "\n  ✗ Student ID \"" << filterID << "\" not found. Showing all logs instead.\n";
                    filterID = "";
                    InputHelper::pause();
                    // Fall through and show all
                } else {
                    cout << "\n  Filtering by: " << filterID << " — " << s->getName() << "\n";
                }
            }

            // Count matching records
            int matchCount = 0;
            for (const auto& log : logs) {
                if (filterID.empty() || log.getStudentID() == filterID) matchCount++;
            }

            // Sub-header
            cout << "\n  ";
            if (filterID.empty())
                cout << "Showing all " << matchCount << " record(s).\n";
            else
                cout << matchCount << " record(s) found for Student ID: " << filterID << "\n";

            if (matchCount == 0) {
                cout << "\n  No matching logs found.\n";
                InputHelper::pause();
                // Ask if admin wants to search again or go back
                cout << "\n  1. Search again\n  2. Go Back\n  Choice: ";
                int c = InputHelper::getInt();
                if (c == 1) continue;
                return;
            }

            // Table header
            cout << "\n  " << string(72, '-') << "\n";
            cout << "  " << left
                 << setw(10) << "Record ID"
                 << setw(14) << "Student ID"
                 << setw(22) << "Student Name"
                 << setw(10) << "Type"
                 << "Timestamp" << "\n";
            cout << "  " << string(72, '-') << "\n";

            // Table rows
            for (const auto& log : logs) {
                if (!filterID.empty() && log.getStudentID() != filterID) continue;
                Student* s = studentManager.getStudent(log.getStudentID());
                string name = s ? s->getName() : "Unknown";
                if (name.length() > 20) name = name.substr(0, 17) + "...";
                cout << "  " << left
                     << setw(10) << log.getRecordID()
                     << setw(14) << log.getStudentID()
                     << setw(22) << name
                     << setw(10) << log.getType()
                     << log.getTimestamp() << "\n";
            }
            cout << "  " << string(72, '-') << "\n";

            InputHelper::pause();

            // After viewing, ask if admin wants to search again
            cout << "\n  1. Search again\n  2. Go Back\n  Choice: ";
            int choice = InputHelper::getInt();
            if (choice != 1) return;
        }
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
                case 2: handleUpdateInfo(); break;
                case 3: handleFileViewComplaints(); break;
                case 4: handleLogEntryExit(); break;
                case 5: handleResetPassword(); break;
                case 6:
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
    
    void handleAddRooms() {
        InputHelper::clearScreen();
        cout << "\n╔══════════════════════════════════════════════════╗\n";
        cout << "║               ADD ROOMS (BULK)                   ║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";
        cout << "  Each room will be created with 4 beds: A, B, C, D\n";
        cout << "  Existing rooms will be skipped automatically.\n\n";

        // Select hall
        string hall = InputHelper::getNormalizedHall();

        // Start room number
        int startRoom = 0;
        while (true) {
            cout << "  Enter Starting Room Number: ";
            startRoom = InputHelper::getInt();
            if (startRoom > 0) break;
            cout << "  ✗ Room number must be a positive integer.\n";
        }

        // End room number
        int endRoom = 0;
        while (true) {
            cout << "  Enter Ending Room Number  : ";
            endRoom = InputHelper::getInt();
            if (endRoom >= startRoom) break;
            cout << "  ✗ Ending room must be >= starting room (" << startRoom << ").\n";
        }

        // Preview
        int totalRooms = endRoom - startRoom + 1;
        int totalBeds  = totalRooms * 4;
        cout << "\n  Preview:\n";
        cout << "  ┌──────────────────────────────────┐\n";
        cout << "  │ Hall         : " << left << setw(18) << hall        << "│\n";
        cout << "  │ Room range   : " << left << setw(18) << (to_string(startRoom) + " → " + to_string(endRoom)) << "│\n";
        cout << "  │ Rooms to add : " << left << setw(18) << totalRooms  << "│\n";
        cout << "  │ Beds to add  : " << left << setw(18) << totalBeds   << " (max, excl. duplicates)│\n";
        cout << "  └──────────────────────────────────┘\n";

        cout << "\n  Confirm? (y/n): ";
        string confirm = InputHelper::getLine();
        if (confirm != "y" && confirm != "Y") {
            cout << "  Operation cancelled.\n";
            InputHelper::pause();
            return;
        }

        roomManager.addRooms(hall, startRoom, endRoom);
        InputHelper::pause();
    }

    void handleManageRooms() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::manageRoomsMenu();
            int choice = InputHelper::getInt();
            if (choice == 1) handleCheckBed();
            else if (choice == 2) handleChangeStudentRoom();
            else if (choice == 3) handleAddRooms();
            else if (choice == 4) return;
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    void handleViewComplaints() {
        while (true) {
            InputHelper::clearScreen();
            int pending = 0, inProgress = 0, resolved = 0;
            auto& complaints = complaintManager.getAllComplaints();
            for (const auto& c : complaints) {
                if (c.getStatus() == "Pending") pending++;
                else if (c.getStatus() == "In-Progress") inProgress++;
                else if (c.getStatus() == "Resolved") resolved++;
            }
            MenuPrinter::viewComplaintsMenu(pending, inProgress, resolved);
            int choice = InputHelper::getInt();
            if (choice == 1) handleViewAllComplaints("Pending");
            else if (choice == 2) handleViewAllComplaints("In-Progress");
            else if (choice == 3) handleViewAllComplaints("Resolved");
            else if (choice == 4) return;
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    void handleManageComplaints() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::manageComplaintsMenu();
            int choice = InputHelper::getInt();
            if (choice == 1) handleViewComplaints();
            else if (choice == 2) handleAssignWorker();
            else if (choice == 3) return;
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    // ─── Worker flow after login ─────────────────────────────────────────────

    // Worker dashboard: shows count of tasks by status
    void handleWorkerDashboard() {
        InputHelper::clearScreen();
        auto myAssignments = assignmentManager.getAssignmentsByWorker(currentUserID);

        int pending = 0, inProgress = 0, resolved = 0;
        for (const auto& a : myAssignments) {
            // Map assignment status to complaint status categories
            if (a.getStatus() == "Assigned")   pending++;
            else if (a.getStatus() == "In-Progress") inProgress++;
            else if (a.getStatus() == "Completed")   resolved++;
        }

        // Also account for complaint statuses tied to this worker
        // Recount by reading from complaint statuses for robustness
        pending = 0; inProgress = 0; resolved = 0;
        for (const auto& a : myAssignments) {
            // Find the associated complaint
            for (const auto& c : complaintManager.getAllComplaints()) {
                if (c.getComplaintID() == a.getComplaintID()) {
                    if (c.getStatus() == "Pending")      pending++;
                    else if (c.getStatus() == "In-Progress") inProgress++;
                    else if (c.getStatus() == "Resolved")    resolved++;
                    break;
                }
            }
        }

        Worker* w = workerManager.findWorkerByID(currentUserID);
        cout << "\n╔══════════════════════════════════════════════════╗\n";
        cout << "║                 WORKER DASHBOARD                 ║\n";
        cout << "╠══════════════════════════════════════════════════╣\n";
        cout << "║  Worker   : " << left << setw(37) << (w ? w->getName() : currentUserID) << "║\n";
        cout << "║  Role     : " << left << setw(37) << (w ? w->getRole() : "N/A")         << "║\n";
        cout << "║  Contact  : " << left << setw(37) << (w ? w->getContactNumber() : "N/A") << "║\n";
        cout << "╠══════════════════════════════════════════════════╣\n";
        cout << "║   Pending Tasks    : " << left << setw(27) << pending    << " ║\n";
        cout << "║   In-Progress Tasks: " << left << setw(27) << inProgress << " ║\n";
        cout << "║   Resolved Tasks   : " << left << setw(27) << resolved   << " ║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";
        InputHelper::pause();
    }

    // Shows complaints assigned to this worker filtered by status
    void handleWorkerViewComplaintsByStatus(const string& statusFilter) {
        InputHelper::clearScreen();
        auto myAssignments = assignmentManager.getAssignmentsByWorker(currentUserID);

        // Gather complaints matching the status filter
        struct WorkerComplaintEntry {
            Complaint complaint;
            WorkAssignment assignment;
        };
        vector<WorkerComplaintEntry> entries;

        for (const auto& a : myAssignments) {
            for (const auto& c : complaintManager.getAllComplaints()) {
                if (c.getComplaintID() == a.getComplaintID()) {
                    if (statusFilter == "" || c.getStatus() == statusFilter) {
                        entries.push_back({c, a});
                    }
                    break;
                }
            }
        }

        string label = (statusFilter == "") ? "ALL" : statusFilter;
        cout << "\n╔══════════════════════════════════════════════════╗\n";
        cout << "║  MY COMPLAINTS — " << left << setw(32) << label << "║\n";
        cout << "║  Total: " << left << setw(41) << entries.size()  << "║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";

        if (entries.empty()) {
            cout << "\n  No " << label << " complaints assigned to you.\n";
            InputHelper::pause();
            return;
        }

        // --- Resolved: tabular layout ---
        if (statusFilter == "Resolved") {
            const int COL_W = 75;
            cout << "\n  " << string(COL_W, '-') << "\n";
            cout << "  " << left
                 << setw(14) << "Complaint ID"
                 << setw(18) << "Service Type"
                 << setw(16) << "Student ID"
                 << setw(14) << "Date"
                 << "Status" << "\n";
            cout << "  " << string(COL_W, '-') << "\n";
            for (const auto& e : entries) {
                const Complaint& c = e.complaint;
                string svcType = c.getCategory();
                if (svcType.length() > 16) svcType = svcType.substr(0, 13) + "...";
                cout << "  " << left
                     << setw(14) << c.getComplaintID()
                     << setw(18) << svcType
                     << setw(16) << c.getStudentID()
                     << setw(14) << c.getDate()
                     << c.getStatus() << "\n";
            }
            cout << "  " << string(COL_W, '-') << "\n";
        }
        // --- Pending / In-Progress: box layout ---
        else {
            int idx = 0;
            for (const auto& e : entries) {
                idx++;
                const Complaint& c = e.complaint;
                const WorkAssignment& a = e.assignment;
                cout << "\n  [" << idx << "/" << entries.size() << "]\n";
                cout << "  ┌──────────────────────────────────────────┐\n";
                cout << "  │ Complaint ID  : " << left << setw(27) << c.getComplaintID()  << "│\n";
                cout << "  │ Category      : " << left << setw(27) << c.getCategory()      << "│\n";
                cout << "  │ Status        : " << left << setw(27) << c.getStatus()        << "│\n";
                cout << "  │ Date          : " << left << setw(27) << c.getDate()          << "│\n";
                string desc = c.getDescription();
                if (desc.length() > 27) desc = desc.substr(0, 24) + "...";
                cout << "  │ Description   : " << left << setw(27) << desc                << "│\n";
                cout << "  │ Student ID    : " << left << setw(27) << c.getStudentID()    << "│\n";
                cout << "  │ Assignment ID : " << left << setw(27) << a.getAssignmentID() << "│\n";
                cout << "  └──────────────────────────────────────────┘\n";
            }
        }
        InputHelper::pause();
    }

    // Worker updates the status of one of their assigned complaints (Pending/In-Progress only)
    void handleWorkerUpdateStatus() {
        InputHelper::clearScreen();
        auto myAssignments = assignmentManager.getAssignmentsByWorker(currentUserID);

        // Collect only non-Resolved complaints
        struct UpdatableEntry { string complaintID; string category; string status; string date; };
        vector<UpdatableEntry> updatable;
        for (const auto& a : myAssignments) {
            for (const auto& c : complaintManager.getAllComplaints()) {
                if (c.getComplaintID() == a.getComplaintID() && c.getStatus() != "Resolved") {
                    updatable.push_back({c.getComplaintID(), c.getCategory(), c.getStatus(), c.getDate()});
                    break;
                }
            }
        }

        if (updatable.empty()) {
            cout << "\n  No complaints available to update.\n";
            InputHelper::pause();
            return;
        }

        // Show only updatable complaints
        cout << "\n=== UPDATE COMPLAINT STATUS ===\n";
        cout << "  Complaints available to update (Pending / In-Progress):\n";
        cout << "  " << string(60, '-') << "\n";
        cout << "  " << left << setw(14) << "Complaint ID" << setw(16) << "Category" << setw(16) << "Status" << "Date\n";
        cout << "  " << string(60, '-') << "\n";
        for (const auto& e : updatable) {
            string cat = e.category;
            if (cat.length() > 14) cat = cat.substr(0, 13);
            cout << "  " << left << setw(14) << e.complaintID
                 << setw(16) << cat
                 << setw(16) << e.status
                 << e.date << "\n";
        }
        cout << "  " << string(60, '-') << "\n";

        cout << "\n  Enter Complaint ID to update (or 'q' to go back): ";
        string cid = InputHelper::getLine();
        if (cid == "q" || cid == "Q") return;

        // Verify this complaint is in the updatable list
        bool belongs = false;
        for (const auto& e : updatable) {
            if (e.complaintID == cid) { belongs = true; break; }
        }
        if (!belongs) {
            cout << "\n  ✗ Complaint not found, not assigned to you, or already Resolved.\n";
            InputHelper::pause();
            return;
        }

        MenuPrinter::statusUpdateMenu();
        int choice = InputHelper::getInt();
        if (choice == 4) return;

        string status;
        switch (choice) {
            case 1: status = "Pending";     break;
            case 2: status = "In-Progress"; break;
            case 3: status = "Resolved";    break;
            default:
                cout << "  Invalid choice!\n";
                InputHelper::pause();
                return;
        }

        complaintManager.updateComplaintStatus(cid, status);
        complaintManager.loadComplaints();
        cout << "\n  ✓ Status updated to '" << status << "' successfully!\n";
        InputHelper::pause();
    }

    // Worker updates their own password
    void handleWorkerUpdatePassword() {
        while (true) {
            InputHelper::clearScreen();
            cout << "\n========== UPDATE PASSWORD ==========\n";
            cout << "Enter current password: ";
            string currentPassword = InputHelper::getPassword();

            if (!workerManager.verifyWorkerPassword(currentUserID, currentPassword)) {
                cout << "\n✗ Current password is incorrect!\n";
                cout << "1. Try Again\n";
                cout << "2. Go Back\n";
                cout << "Choice: ";
                int choice = InputHelper::getInt();
                if (choice == 1) continue;
                return;
            }

            string newPassword, confirmPassword;
            while (true) {
                cout << "Enter new password: ";
                newPassword = InputHelper::getPassword();

                if (newPassword == currentPassword) {
                    cout << "✗ This password is already in use by you! Please use a new one.\n";
                    continue;
                }

                if (newPassword == "password" || newPassword == "worker") {
                    cout << "✗ Password cannot be set as default.\n";
                    continue;
                }

                if (newPassword.length() < 8) {
                    cout << "✗ Password must be at least 8 characters!\n";
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

            workerManager.updateWorkerPassword(currentUserID, newPassword);
            cout << "\n✓ Password updated successfully!\n";
            InputHelper::pause();
            return;
        }
    }

    // Worker: Manage Complaints menu with status-based sub-views
    void handleWorkerManageComplaints() {
        while (true) {
            InputHelper::clearScreen();
            // Compute counts for this worker's complaints
            auto myAssignments = assignmentManager.getAssignmentsByWorker(currentUserID);
            int pending = 0, inProgress = 0, resolved = 0;
            for (const auto& a : myAssignments) {
                for (const auto& c : complaintManager.getAllComplaints()) {
                    if (c.getComplaintID() == a.getComplaintID()) {
                        if (c.getStatus() == "Pending")      pending++;
                        else if (c.getStatus() == "In-Progress") inProgress++;
                        else if (c.getStatus() == "Resolved")    resolved++;
                        break;
                    }
                }
            }
            MenuPrinter::workerManageComplaintsMenu(pending, inProgress, resolved);
            int choice = InputHelper::getInt();
            if      (choice == 1) handleWorkerViewComplaintsByStatus("Pending");
            else if (choice == 2) handleWorkerViewComplaintsByStatus("In-Progress");
            else if (choice == 3) handleWorkerViewComplaintsByStatus("Resolved");
            else if (choice == 4) {
                // Update Status sub-option
                handleWorkerUpdateStatus();
            }
            else if (choice == 5) return;
            else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    // Worker: Update phone number
    void handleWorkerUpdateInfo() {
        while (true) {
            InputHelper::clearScreen();
            MenuPrinter::workerUpdateInfoMenu();
            int choice = InputHelper::getInt();
            if (choice == 1) {
                InputHelper::clearScreen();
                Worker* w = workerManager.findWorkerByID(currentUserID);
                if (w) {
                    cout << "\nCurrent Phone Number: " << w->getContactNumber() << "\n";
                    cout << "Enter new phone number: ";
                    string phone = InputHelper::getNumericLine();
                    workerManager.updateContactNumber(currentUserID, phone);
                    cout << "\n✓ Phone number updated successfully!\n";
                } else {
                    cout << "Worker profile not found.\n";
                }
                InputHelper::pause();
            } else if (choice == 2) {
                return;
            } else {
                cout << "Invalid choice!\n";
                InputHelper::pause();
            }
        }
    }

    // Worker flow after login
    void workerFlow() {
        bool loggedIn = true;
        bool firstLogin = true;
        while (loggedIn) {
            InputHelper::clearScreen();
            Worker* w = workerManager.findWorkerByID(currentUserID);
            cout << "Welcome, " << (w ? w->getName() : currentUserID)
                 << " [" << (w ? w->getRole() : "Worker") << "]\n";

            // Auto-show dashboard on first entry after login
            if (firstLogin) {
                firstLogin = false;
                auto myAssignments = assignmentManager.getAssignmentsByWorker(currentUserID);
                int pending = 0, inProgress = 0, resolved = 0;
                for (const auto& a : myAssignments) {
                    for (const auto& c : complaintManager.getAllComplaints()) {
                        if (c.getComplaintID() == a.getComplaintID()) {
                            if (c.getStatus() == "Pending")          pending++;
                            else if (c.getStatus() == "In-Progress") inProgress++;
                            else if (c.getStatus() == "Resolved")    resolved++;
                            break;
                        }
                    }
                }
                cout << "\n╔══════════════════════════════════════════════════╗\n";
                cout << "║              YOUR COMPLAINTS SUMMARY             ║\n";
                cout << "╠══════════════════════════════════════════════════╣\n";
                cout << "║   Pending     : " << left << setw(31) << pending    << "║\n";
                cout << "╠══════════════════════════════════════════════════╣\n";
                cout << "║   In-Progress : " << left << setw(31) << inProgress << "║\n";
                cout << "╠══════════════════════════════════════════════════╣\n";
                cout << "║   Resolved    : " << left << setw(31) << resolved   << "║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                cout << "\nPress Enter to continue to the menu...";
                cin.ignore();
            }

            InputHelper::clearScreen();
            cout << "Welcome, " << (w ? w->getName() : currentUserID)
                 << " [" << (w ? w->getRole() : "Worker") << "]\n";

            // Auto-show dashboard summary once immediately after login
            if (firstLogin) {
                firstLogin = false;
                auto myAssignments = assignmentManager.getAssignmentsByWorker(currentUserID);
                int pending = 0, inProgress = 0, resolved = 0;
                for (const auto& a : myAssignments) {
                    for (const auto& c : complaintManager.getAllComplaints()) {
                        if (c.getComplaintID() == a.getComplaintID()) {
                            if (c.getStatus() == "Pending")          pending++;
                            else if (c.getStatus() == "In-Progress") inProgress++;
                            else if (c.getStatus() == "Resolved")    resolved++;
                            break;
                        }
                    }
                }
                cout << "\n╔══════════════════════════════════════════════════╗\n";
                cout << "║           YOUR COMPLAINTS SUMMARY                ║\n";
                cout << "╠══════════════════════════════════════════════════╣\n";
                cout << "║   Pending     : " << left << setw(31) << pending    << "║\n";
                cout << "╠══════════════════════════════════════════════════╣\n";
                cout << "║   In-Progress : " << left << setw(31) << inProgress << "║\n";
                cout << "╠══════════════════════════════════════════════════╣\n";
                cout << "║   Resolved    : " << left << setw(31) << resolved   << "║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                InputHelper::pause();
                InputHelper::clearScreen();
                cout << "Welcome, " << (w ? w->getName() : currentUserID)
                     << " [" << (w ? w->getRole() : "Worker") << "]\n";
            }

            MenuPrinter::showWorkerMenu();
            int choice = InputHelper::getInt();
            switch (choice) {
                case 1: {
                    // Manage Complaints — show sub-menu with update option too
                    while (true) {
                        InputHelper::clearScreen();
                        auto myAssignments = assignmentManager.getAssignmentsByWorker(currentUserID);
                        int pending = 0, inProgress = 0, resolved = 0;
                        for (const auto& a : myAssignments) {
                            for (const auto& c : complaintManager.getAllComplaints()) {
                                if (c.getComplaintID() == a.getComplaintID()) {
                                    if (c.getStatus() == "Pending")      pending++;
                                    else if (c.getStatus() == "In-Progress") inProgress++;
                                    else if (c.getStatus() == "Resolved")    resolved++;
                                    break;
                                }
                            }
                        }
                        cout << "\n========== MANAGE MY COMPLAINTS ==========\n";
                        cout << "1. View Pending     (" << pending    << ")\n";
                        cout << "2. View In-Progress (" << inProgress << ")\n";
                        cout << "3. View Resolved    (" << resolved   << ")\n";
                        cout << "4. Update Status\n";
                        cout << "5. Go Back\n";
                        cout << "Choice: ";
                        int sub = InputHelper::getInt();
                        if      (sub == 1) handleWorkerViewComplaintsByStatus("Pending");
                        else if (sub == 2) handleWorkerViewComplaintsByStatus("In-Progress");
                        else if (sub == 3) handleWorkerViewComplaintsByStatus("Resolved");
                        else if (sub == 4) handleWorkerUpdateStatus();
                        else if (sub == 5) break;
                        else { cout << "Invalid choice!\n"; InputHelper::pause(); }
                    }
                    break;
                }
                case 2: handleWorkerUpdateInfo(); break;
                case 3: handleWorkerUpdatePassword(); break;
                case 4:
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

    // ─────────────────────────────────────────────────────────────────────────
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
                case 3: handleManageRooms(); break;
                case 4: handleManageComplaints(); break;
                case 5: handleManageDues(); break;
                case 6:
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
    // Constructor: Initializes all managers and services
    HallVerseApp() 
        : studentManager(&fileHandler),
          complaintManager(&fileHandler),
          workerManager(&fileHandler, &hasher),
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
// Main entry point: Sets up console and starts the application
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
