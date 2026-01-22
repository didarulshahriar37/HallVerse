#include "WorkAssignmentManager.h"
#include <iostream>
#include <sstream>

using namespace std;

WorkAssignmentManager::WorkAssignmentManager(ComplaintManager* complaintManager, WorkerManager* workerManager, FileHandler* fileHandler)
    : id("WAM_001"), complaintManager(complaintManager), workerManager(workerManager), fileHandler(fileHandler), nextAssignmentID(1) {
    loadAssignments();
}

void WorkAssignmentManager::loadAssignments() {
    assignments = fileHandler->readAssignments();
    if(!assignments.empty()) {
        string lastID = assignments.back().getAssignmentID();
        nextAssignmentID = stoi(lastID.substr(1)) + 1;
    }
}