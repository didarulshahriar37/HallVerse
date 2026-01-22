#ifndef WORKASSIGNMENT_H
#define WORKASSIGNMENT_H

#include<string>
using namespace std;

class WorkAssignment{
    
    private:
    std::string assignmentID;
    std::string status;
    std::string complaintID;
    std::string workerID;
    std::string report;
    
    public:
    WorkAssignment();
    WorkAssignment(std::string aID, std::string cID, std::string wID, 
                   std::string stat, std::string rep);
    
    void updateStatus(const std::string& newStatus);
    void addReport(const std::string& newReport);
    void markCompleted();
    
    std::string getAssignmentID() const { return assignmentID; }
    std::string getComplaintID() const { return complaintID; }
    std::string getWorkerID() const { return workerID; }
    std::string getStatus() const { return status; }
    std::string getReport() const { return report; }
};

#endif