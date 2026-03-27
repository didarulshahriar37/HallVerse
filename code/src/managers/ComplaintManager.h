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
    // Constructor: Initialize persistence service and load existing complaints
    ComplaintManager(FileHandler* fh);

    // Create a new complaint and save it on disk
    void createComplaint(const Complaint& complaint);

    // Get all complaints filed by a specific student
    vector<Complaint> getComplaintsByStudent(const string& studentID);

    // Return reference to all complaints in memory
    vector<Complaint>& getAllComplaints() { return complaints; }

    // Update complaint status (Pending, In-Progress, Resolved)
    void updateComplaintStatus(const string& complaintID, const string& status);

    // Load complaints from file into memory
    void loadComplaints();
};

#endif
