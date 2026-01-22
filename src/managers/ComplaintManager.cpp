#include "ComplaintManager.h"
#include <iostream>
 
using namespace std;
ComplaintManager::ComplaintManager(FileHandler* fh) : fileHandler(fh), nextComplaintID(1) {
    loadComplaints();
}

void ComplaintManager::loadComplaints() {
    complaints = fileHandler->readComplaints();
    if (!complaints.empty()) {
        std::string lastID = complaints.back().getComplaintID();
        nextComplaintID = std::stoi(lastID.substr(1)) + 1;
    }
}

void ComplaintManager::createComplaint(const Complaint& complaint) {
    complaints.push_back(complaint);
    fileHandler->writeComplaints(complaints);
    nextComplaintID++;
    std::cout << "Complaint submitted successfully! ID: " << complaint.getComplaintID() << "\n";
}

std::vector<Complaint> ComplaintManager::getComplaintsByStudent(const std::string& studentID) {
    std::vector<Complaint> result;
    for (const auto& c : complaints) {
        if (c.getStudentID() == studentID) {
            result.push_back(c);
        }
    }
    return result;
}

void ComplaintManager::updateComplaintStatus(const std::string& complaintID, const std::string& status) {
    for (auto& c : complaints) {
        if (c.getComplaintID() == complaintID) {
            c.updateStatus(status);
            fileHandler->writeComplaints(complaints);
            std::cout << "Complaint status updated to: " << status << "\n";
            return;
        }
    }
    std::cout << "Complaint not found!\n";
}
