#include "DashboardManager.h"
#include <iostream>
#include <iomanip>
 
using namespace std;
DashboardManager::DashboardManager(StudentManager* sm, ComplaintManager* cm, EntryExitManager* eem)
    : id("DM_001"), studentManager(sm), complaintManager(cm), entryExitManager(eem) {}

int DashboardManager::getTotalStudents() {
    return studentManager->getAllStudents().size();
}

void DashboardManager::getComplaintSummary(int& pending, int& inProgress, int& resolved) {
    pending = inProgress = resolved = 0;
    for (const auto& c : complaintManager->getAllComplaints()) {
        if (c.getStatus() == "Pending") pending++;
        else if (c.getStatus() == "In-Progress") inProgress++;
        else if (c.getStatus() == "Resolved") resolved++;
    }
}

void DashboardManager::displayDashboard() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════╗\n";
    std::cout << "║        ADMIN DASHBOARD - HALLVERSE         ║\n";
    std::cout << "╠════════════════════════════════════════════╣\n";
    
    int total = getTotalStudents();
    std::cout << "║ Total Students: " << std::setw(23) << total << " ║\n";
    
    // Calculate total dues
    double totalDues = 0.0;
    for (const auto& s : studentManager->getAllStudents()) {
        totalDues += s.getHallDues();
    }
    std::cout << "║ Total Pending Dues: $" << std::setw(18) << std::fixed 
              << std::setprecision(2) << totalDues << " ║\n";
    
    int pending, inProgress, resolved;
    getComplaintSummary(pending, inProgress, resolved);
    std::cout << "║ Total Complaints: " << std::setw(21) << (pending + inProgress + resolved) << " ║\n";
    std::cout << "║   - Pending: " << std::setw(26) << pending << " ║\n";
    std::cout << "║   - In-Progress: " << std::setw(22) << inProgress << " ║\n";
    std::cout << "║   - Resolved: " << std::setw(25) << resolved << " ║\n";
    
    int totalEntries = 0, totalExits = 0;
    for (const auto& log : entryExitManager->getLogs()) {
        if (log.getType() == "Entry") totalEntries++;
        else if (log.getType() == "Exit") totalExits++;
    }
    std::cout << "║ Total Entries: " << std::setw(24) << totalEntries << " ║\n";
    std::cout << "║ Total Exits: " << std::setw(26) << totalExits << " ║\n";
    
    std::cout << "╚════════════════════════════════════════════╝\n";
}