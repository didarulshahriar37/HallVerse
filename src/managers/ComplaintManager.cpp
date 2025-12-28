#include "ComplaintManager.h"

#include "../models/Complaint.h"
#include "../services/FileHandler.h"

ComplaintManager::ComplaintManager(FileHandler* fileHandler) {
    this->fileHandler = fileHandler;
}

void ComplaintManager::loadComplaints() {
}

void ComplaintManager::addComplaint(const Complaint& complaint) {
}

std::vector<Complaint>
ComplaintManager::getComplaintsByStudent(const std::string& studentID) {
    
    return std::vector<Complaint>();
}

std::vector<Complaint>
ComplaintManager::getAllComplaints() {
    return complaints;
}

void ComplaintManager::updateComplaintStatus(const std::string& complaintID, const std::string& newStatus) {
}

Complaint* ComplaintManager::getComplaintByID(const std::string& complaintID) {
    
    return nullptr;
}
