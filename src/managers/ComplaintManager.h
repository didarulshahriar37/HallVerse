#ifndef COMPLAINT_MANAGER_H
#define COMPLAINT_MANAGER_H

#include <vector>
#include <string>

class Complaint;
class FileHandler;

class ComplaintManager {
private:
    FileHandler* fileHandler;
    std::vector<Complaint> complaints;

public:
    ComplaintManager(FileHandler* fileHandler);

    void loadComplaints();

    void addComplaint(const Complaint& complaint);
    std::vector<Complaint> getComplaintsByStudent(const std::string& studentID);

    std::vector<Complaint> getAllComplaints();
    void updateComplaintStatus(const std::string& complaintID, const std::string& newStatus);

    Complaint* getComplaintByID(const std::string& complaintID);
};

#endif
