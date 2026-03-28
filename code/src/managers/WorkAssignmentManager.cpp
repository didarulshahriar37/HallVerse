#include "WorkAssignmentManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
 
using namespace std;
WorkAssignmentManager::WorkAssignmentManager(FileHandler* fh, ComplaintManager* cm, WorkerManager* wm)
    : id("W-001"), complaintManager(cm), workerManager(wm), fileHandler(fh), nextAssignmentID(1) {
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
    // Use smart workload-balanced selection: pick worker with fewest resolved complaints
    Worker* worker = workerManager->findLeastLoadedWorker(role);
    if (worker) {
        stringstream ss;
        ss << "A" << nextAssignmentID;
        WorkAssignment assignment(ss.str(), complaintID, worker->getWorkerID(), "Assigned", "");
        workAssignments.push_back(assignment);
        fileHandler->writeAssignments(workAssignments);
        // Mark worker as unavailable
        workerManager->updateWorkerStatus(worker->getWorkerID(), false);
        // Automatically set complaint to In-Progress
        complaintManager->updateComplaintStatus(complaintID, "In-Progress");
        nextAssignmentID++;
        cout << "\n✓ Worker assigned successfully!\n";
        cout << "  ┌─────────────────────────────────────────┐\n";
        cout << "  │ Worker ID  : " << left << setw(27) << worker->getWorkerID()  << "│\n";
        cout << "  │ Name       : " << left << setw(27) << worker->getName()      << "│\n";
        cout << "  │ Role       : " << left << setw(27) << role                   << "│\n";
        cout << "  │ Contact    : " << left << setw(27) << worker->getContactNumber() << "│\n";
        cout << "  │ Complaint  : " << left << setw(27) << complaintID            << "│\n";
        cout << "  └─────────────────────────────────────────┘\n";
        cout << "  → Complaint status set to In-Progress\n";
    } else {
        cout << "\n✗ No worker found for role: " << role << "\n";
    }
}

void WorkAssignmentManager::completeWork(const string& assignmentID) {
    for (auto& a : workAssignments) {
        if (a.getAssignmentID() == assignmentID) {
            a.markCompleted();
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

vector<WorkAssignment> WorkAssignmentManager::getAssignmentsByWorker(const string& workerID) {
    vector<WorkAssignment> result;
    for (const auto& a : workAssignments) {
        if (a.getWorkerID() == workerID) {
            result.push_back(a);
        }
    }
    return result;
}
