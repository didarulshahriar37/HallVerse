#ifndef WORK_ASSIGNMENT_MANAGER_H
#define WORK_ASSIGNMENT_MANAGER_H

using namespace std;

#include <string>
#include <vector>
#include "../services/FileHandler.h"
#include "../models/WorkAssignment.h"
#include "ComplaintManager.h"
#include "WorkerManager.h"

class WorkAssignmentManager {
    private:
    string id;
    ComplaintManager* complaintManager;
    WorkerManager* workerManager;
    FileHandler* fileHandler;
    vector<WorkAssignment> workAssignments;
    int nextAssignmentID;

    public:
    // Constructor: set dependencies and load assignment history
    WorkAssignmentManager(FileHandler* fileHandler, ComplaintManager* complaintManager, WorkerManager* workerManager);

    // Assign a worker to a complaint (creates assignment and updates complaint/worker states)
    void assignWorker(const string& complaintID, const string& role);

    // Complete assignment and optionally store a report
    void completeWork(const string& assignmentID, const string& report);

    // Get assignments for a particular complaint by ID
    vector<WorkAssignment>& getAssignmentsByComplaint(const string& complaintID);

    // Get assignments for a particular worker by ID
    vector<WorkAssignment> getAssignmentsByWorker(const string& workerID);

    // Return all assignments
    vector<WorkAssignment>& getAllAssignments() { return workAssignments; }

    // Load assignments from file into memory
    void loadAssignments();
};

#endif