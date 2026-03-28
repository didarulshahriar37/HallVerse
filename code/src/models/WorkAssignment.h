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
    
    public:
    WorkAssignment();
    WorkAssignment(string aID, string cID, string wID, 
                   string stat);
    
    void updateStatus(const string& newStatus);
    
    string getAssignmentID() const { return assignmentID; }
    string getComplaintID() const { return complaintID; }
    string getWorkerID() const { return workerID; }
    string getStatus() const { return status; }
    // string getReport() const { return report; }
};

#endif