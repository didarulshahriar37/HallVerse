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
        WorkAssignment assignment(ss.str(), complaintID, worker->getWorkerID(), "Assigned", "");
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

void WorkAssignmentManager::completeWork(const string& assignmentID, const string& report) {
    for(auto& assignment : assignments){
        if(assignment.getAssignmentID() == assignmentID){
            assignment.markCompleted();
            assignment.addReport(report);
            fileHandler->writeAssignment(assignments);
            workerManager->updateWorkerStatus(assignment.getWorkerID(), true);
            complaintManager->updateComplaintStatus(assignment.getComplaintID(), "Resolved");
            cout << "Work assignment " << assignmentID << " marked as completed.\n";
            return;
        }
    }
    cout << "Assignment ID " << assignmentID << " not found or already completed.\n";
}

std::vector<WorkAssignment> WorkAssignmentManager::getAssignmentsByComplaint(const std::string& complaintID) {
    std::vector<WorkAssignment> result;
    for(const auto& assignment : assignments){
        if(assignment.getComplaintID() == complaintID){
            result.push_back(assignment);
        }
    }
    return result;
}