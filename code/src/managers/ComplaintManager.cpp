#include "ComplaintManager.h"
#include <iostream>
 
using namespace std;

// Constructor: Load complaint list and initialize next complaint ID
ComplaintManager::ComplaintManager(FileHandler* fh) : fileHandler(fh), nextComplaintID(1) {
    loadComplaints();
}

// Read complaint records from storage and update ID counter
void ComplaintManager::loadComplaints() {
    complaints = fileHandler->readComplaints();
    if (!complaints.empty()) {
        string lastID = complaints.back().getComplaintID();
        nextComplaintID = stoi(lastID.substr(1)) + 1;
    }
}

// Creates a new complaint
void ComplaintManager::createComplaint(const Complaint& complaint) {
    complaints.push_back(complaint);
    fileHandler->writeComplaints(complaints);
    nextComplaintID++;
    cout << "Complaint submitted successfully! ID: " << complaint.getComplaintID() << "\n";
}

// retuurns the complaint made by a particular student
vector<Complaint> ComplaintManager::getComplaintsByStudent(const string& studentID) {
    vector<Complaint> result;
    for (const auto& c : complaints) {
        if (c.getStudentID() == studentID) {
            result.push_back(c);
        }
    }
    return result;
}

// updates the status of a complaint
void ComplaintManager::updateComplaintStatus(const string& complaintID, const string& status) {
    for (auto& c : complaints) {
        if (c.getComplaintID() == complaintID) {
            c.updateStatus(status);
            fileHandler->writeComplaints(complaints);
            cout << "Complaint status updated to: " << status << "\n";
            return;
        }
    }
    cout << "Complaint not found!\n";
}
