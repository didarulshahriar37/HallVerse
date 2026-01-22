#ifndef COMPLAINTMANAGER_H
#define COMPLAINTMANAGER_H

#include <vector>
#include "../models/Complaint.h"
#include "../services/FileHandler.h"

class ComplaintManager {
private:
    FileHandler* fileHandler;
    std::vector<Complaint> complaints;
    int nextComplaintID;
    
public:
    ComplaintManager(FileHandler* fh);
    void createComplaint(const Complaint& complaint);
    std::vector<Complaint> getComplaintsByStudent(const std::string& studentID);
    std::vector<Complaint>& getAllComplaints() { return complaints; }
    void updateComplaintStatus(const std::string& complaintID, const std::string& status);
    void loadComplaints();
};

#endif
