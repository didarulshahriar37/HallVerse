#ifndef WORKASSIGNMENT_H
#define WORKASSIGNMENT_H

#include<string>
using namespace std;

class WorkAssignment{
    
    private:
    string assignmentID;
    string status;
    string complaintID;
    string workerID;
    string report;
    
    public:
    WorkAssignment();
    WorkAssignment(string aID, string cID, string wID,
                   string stat, string rep);
    
    void updateStatus(const string& newStatus);
    void addReport(const string& newReport);
    void markCompleted();
    
    string getAssignmentID() const { return assignmentID; }
    string getComplaintID() const { return complaintID; }
    string getWorkerID() const { return workerID; }
    string getStatus() const { return status; }
    string getReport() const { return report; }
};

#endif