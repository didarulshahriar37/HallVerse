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
    DashboardManager(StudentManager* sm, ComplaintManager* cm, EntryExitManager* eem);
    int getTotalStudents();
    void getComplaintSummary(int& pending, int& inProgress, int& resolved);
    void displayDashboard();
};

#endif