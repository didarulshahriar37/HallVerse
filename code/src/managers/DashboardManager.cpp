#include "DashboardManager.h"
#include <iostream>
#include <iomanip>

using namespace std;
DashboardManager::DashboardManager(StudentManager *sm, ComplaintManager *cm, EntryExitManager *eem)
    : id("DM_001"), studentManager(sm), complaintManager(cm), entryExitManager(eem) {}

int DashboardManager::getTotalStudents()
{
    return studentManager->getAllStudents().size();
}

void DashboardManager::getComplaintSummary(int &pending, int &inProgress, int &resolved)
{
    pending = inProgress = resolved = 0;
    for (const auto &c : complaintManager->getAllComplaints())
    {
        if (c.getStatus() == "Pending")
            pending++;
        else if (c.getStatus() == "In-Progress")
            inProgress++;
        else if (c.getStatus() == "Resolved")
            resolved++;
    }
}
void DashboardManager::displayDashboard()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║        ADMIN DASHBOARD - HALLVERSE         ║\n";
    cout << "╠════════════════════════════════════════════╣\n";

    int total = getTotalStudents();
    cout << "║ Total Students: " << setw(23) << total << "    ║\n";

    // Calculate total dues
    double totalDues = 0.0;
    for (const auto &s : studentManager->getAllStudents())
    {
        totalDues += s.getHallDues();
    }
    cout << "║ Total Pending Dues: $" << std::setw(18) << std::fixed
         << setprecision(2) << totalDues << "    ║\n";

    int pending, inProgress, resolved;
    getComplaintSummary(pending, inProgress, resolved);
    cout << "║ Total Complaints: " << setw(21) << (pending + inProgress + resolved) << "    ║\n";
    cout << "║   - Pending: " << setw(26) << pending << "    ║\n";
    cout << "║   - In-Progress: " << setw(22) << inProgress << "    ║\n";
    cout << "║   - Resolved: " << setw(25) << resolved << "    ║\n";

    int totalEntries = 0, totalExits = 0;
    for (const auto &log : entryExitManager->getLogs())
    {
        if (log.getType() == "Entry")
            totalEntries++;
        else if (log.getType() == "Exit")
            totalExits++;
    }
    cout << "║ Total Entries: " << setw(24) << totalEntries << "    ║\n";
    cout << "║ Total Exits: " << setw(26) << totalExits << "    ║\n";

    cout << "╚════════════════════════════════════════════╝\n";
}