#include "WorkAssignment.h"

using namespace std;
WorkAssignment::WorkAssignment() : status("Assigned") {}

WorkAssignment::WorkAssignment(std::string aID, std::string cID, std::string wID, 
                               std::string stat, std::string rep)
    : assignmentID(aID), complaintID(cID), workerID(wID), 
      status(stat), report(rep) {}

void WorkAssignment::updateStatus(const std::string& newStatus) {
    status = newStatus;
}

void WorkAssignment::addReport(const std::string& newReport) {
    report = newReport;
}

void WorkAssignment::markCompleted() {
    status = "Completed";
}