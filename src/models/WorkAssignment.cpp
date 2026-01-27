#include "WorkAssignment.h"

using namespace std;
WorkAssignment::WorkAssignment() : status("Assigned") {}

WorkAssignment::WorkAssignment(string aID, string cID, string wID, 
                               string stat, string rep)
    : assignmentID(aID), complaintID(cID), workerID(wID), 
      status(stat), report(rep) {}

void WorkAssignment::updateStatus(const string& newStatus) {
    status = newStatus;
}

void WorkAssignment::addReport(const string& newReport) {
    report = newReport;
}

void WorkAssignment::markCompleted() {
    status = "Completed";
}