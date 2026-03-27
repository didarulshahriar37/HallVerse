#include "WorkAssignment.h"

using namespace std;
// Default constructor: Initializes with "Assigned" status
WorkAssignment::WorkAssignment() : status("Assigned") {}

// Parameterized constructor: Creates assignment with all details
WorkAssignment::WorkAssignment(string aID, string cID, string wID, 
                               string stat, string rep)
    : assignmentID(aID), complaintID(cID), workerID(wID), 
      status(stat), report(rep) {}

// Updates assignment status
void WorkAssignment::updateStatus(const string& newStatus) {
    status = newStatus;
}

// Adds completion report
void WorkAssignment::addReport(const string& newReport) {
    report = newReport;
}

// Sets status to "Completed"
void WorkAssignment::markCompleted() {
    status = "Completed";
}