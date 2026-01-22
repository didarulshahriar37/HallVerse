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
