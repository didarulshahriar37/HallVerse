#ifndef DASHBOARDMANAGER_H
#define DASHBOARDMANAGER_H
using namespace std;
#include "StudentManager.h"
#include "ComplaintManager.h"
#include "EntryExitManager.h" 
class DashboardManager {
private:
    string id;
    StudentManager* studentManager;
    ComplaintManager* complaintManager;
    EntryExitManager* entryExitManager;
    
public:
    // Constructor: initialize references to each manager used for dashboard data
    DashboardManager(StudentManager* sm, ComplaintManager* cm, EntryExitManager* eem);

    // Get number of registered students
    int getTotalStudents();

    // Fill counts of complaints in different statuses
    void getComplaintSummary(int& pending, int& inProgress, int& resolved);

    // Print formatted dashboard summary (students, complaints, entry-exit)
    void displayDashboard();
};

#endif