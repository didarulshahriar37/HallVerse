#ifndef COMPLAINTMANAGER_H
#define COMPLAINTMANAGER_H

#include <vector>
#include "../models/Complaint.h"
#include "../services/FileHandler.h"
using namespace std;

class ComplaintManager {
private:
    FileHandler* fileHandler;
    vector<Complaint> complaints;
    int nextComplaintID;
    
public:
    ComplaintManager(FileHandler* fh);
    void createComplaint(const Complaint& complaint);
    vector<Complaint> getComplaintsByStudent(const string& studentID);
    vector<Complaint>& getAllComplaints() { return complaints; }
    void updateComplaintStatus(const string& complaintID, const string& status);
    void loadComplaints();
};

#endif
