#include "WorkAssignmentManager.h"
#include <iostream>
#include <sstream>
 
using namespace std;
WorkAssignmentManager::WorkAssignmentManager(FileHandler* fh, ComplaintManager* cm, WorkerManager* wm)
    : id("WAM_001"), complaintManager(cm), workerManager(wm), fileHandler(fh), nextAssignmentID(1) {
    loadAssignments();
}

void WorkAssignmentManager::loadAssignments() {
    workAssignments = fileHandler->readAssignments();
    if (!workAssignments.empty()) {
        string lastID = workAssignments.back().getAssignmentID();
        nextAssignmentID = stoi(lastID.substr(1)) + 1;
    }
}

void WorkAssignmentManager::assignWorker(const string& complaintID, const string& role) {
    Worker* worker = workerManager->findAvailableWorker(role);
    if (worker) {
        stringstream ss;
        ss << "A" << nextAssignmentID;
        WorkAssignment assignment(ss.str(), complaintID, worker->getWorkerID(), "Assigned", "");
        workAssignments.push_back(assignment);
        fileHandler->writeAssignments(workAssignments);
        workerManager->updateWorkerStatus(worker->getWorkerID(), false);
        nextAssignmentID++;
        cout << "Worker assigned successfully!\n";
    } else {
        cout << "No available worker found for role: " << role << "\n";
    }
}

void WorkAssignmentManager::completeWork(const string& assignmentID, const string& report) {
    for (auto& a : workAssignments) {
        if (a.getAssignmentID() == assignmentID) {
            a.markCompleted();
            a.addReport(report);
            fileHandler->writeAssignments(workAssignments);
            workerManager->updateWorkerStatus(a.getWorkerID(), true);
            complaintManager->updateComplaintStatus(a.getComplaintID(), "Resolved");
            cout << "Work completed successfully!\n";
            return;
        }
    }
    cout << "Assignment not found!\n";
}

vector<WorkAssignment>& WorkAssignmentManager::getAssignmentsByComplaint(const string& complaintID) {
    static vector<WorkAssignment> result;
    result.clear();
    for (const auto& a : workAssignments) {
        if (a.getComplaintID() == complaintID) {
            result.push_back(a);
        }
    }
    return result;
}
