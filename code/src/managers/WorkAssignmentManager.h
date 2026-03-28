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
    WorkAssignmentManager(FileHandler* fileHandler, ComplaintManager* complaintManager, WorkerManager* workerManager);

    void assignWorker(const string& complaintID, const string& role);
    void completeWork(const string& assignmentID);
    vector<WorkAssignment>& getAssignmentsByComplaint(const string& complaintID);
    vector<WorkAssignment> getAssignmentsByWorker(const string& workerID);
    vector<WorkAssignment>& getAllAssignments() { return workAssignments; }
    void loadAssignments();
};

#endif