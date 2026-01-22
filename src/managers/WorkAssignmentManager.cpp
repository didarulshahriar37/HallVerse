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

void WorkAssignmentManager::assignWorker(const string& complaintID, const string& role) {
    Worker* worker = workerManager->findAvailableWorker(role);
    if(worker){
        stringstream ss;
        ss << "A" << nextAssignmentID;
        workAssignment assignment(ss.str(), complaintID, worker->getWorkerID(), "Assigned", "");
        assignments.push_back(assignment);
        fileHandler->writeAssignment(assignments);
        workerManager->updateWorkerStatus(worker->getWorkerID(), false);
        nextAssignmentID++;
        cout << "Worker " << worker->getName() << " assigned to complaint " << complaintID << "\n";
    }
    else{
        cout << "No available worker found for role: " << role << "\n";
    }
}