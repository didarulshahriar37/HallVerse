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

