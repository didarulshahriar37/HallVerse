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
    void updateStatus(string status);
    void addReport(string report);
    void markCompleted();
};

#endif