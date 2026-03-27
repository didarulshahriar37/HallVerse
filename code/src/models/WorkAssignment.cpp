#include "WorkAssignment.h"

using namespace std;
// Default constructor: Initializes with "Assigned" status
WorkAssignment::WorkAssignment() : status("Assigned") {}

// Parameterized constructor: Creates assignment with all details
WorkAssignment::WorkAssignment(string aID, string cID, string wID, 
                               string stat)
    : assignmentID(aID), complaintID(cID), workerID(wID), 
      status(stat) {}

// Updates assignment status
void WorkAssignment::updateStatus(const string& newStatus) {
    status = newStatus;
}
