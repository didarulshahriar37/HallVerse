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
        std::string lastID = workAssignments.back().getAssignmentID();
        nextAssignmentID = std::stoi(lastID.substr(1)) + 1;
    }
}

void WorkAssignmentManager::assignWorker(const std::string& complaintID, const std::string& role) {
    Worker* worker = workerManager->findAvailableWorker(role);
    if (worker) {
        std::stringstream ss;
        ss << "A" << nextAssignmentID;
        WorkAssignment assignment(ss.str(), complaintID, worker->getWorkerID(), "Assigned", "");
        workAssignments.push_back(assignment);
        fileHandler->writeAssignments(workAssignments);
        workerManager->updateWorkerStatus(worker->getWorkerID(), false);
        nextAssignmentID++;
        std::cout << "Worker assigned successfully!\n";
    } else {
        std::cout << "No available worker found for role: " << role << "\n";
    }
}

void WorkAssignmentManager::completeWork(const std::string& assignmentID, const std::string& report) {
    for (auto& a : workAssignments) {
        if (a.getAssignmentID() == assignmentID) {
            a.markCompleted();
            a.addReport(report);
            fileHandler->writeAssignments(workAssignments);
            workerManager->updateWorkerStatus(a.getWorkerID(), true);
            complaintManager->updateComplaintStatus(a.getComplaintID(), "Resolved");
            std::cout << "Work completed successfully!\n";
            return;
        }
    }
    std::cout << "Assignment not found!\n";
}

std::vector<WorkAssignment>& WorkAssignmentManager::getAssignmentsByComplaint(const std::string& complaintID) {
    static std::vector<WorkAssignment> result;
    result.clear();
    for (const auto& a : workAssignments) {
        if (a.getComplaintID() == complaintID) {
            result.push_back(a);
        }
    }
    return result;
}
