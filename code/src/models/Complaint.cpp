#include "Complaint.h"
using namespace std;

// Default constructor: Initializes complaint with "Pending" status
Complaint::Complaint() {
    status = "Pending";
}

// Parameterized constructor: Creates complaint with all details
Complaint::Complaint(
    string complaintID,
    string category,
    string description,
    string status,
    string date,
    string studentID
) {
    this->complaintID = complaintID;
    this->category = category;
    this->description = description;
    this->status = status;
    this->date = date;
    this->studentID = studentID;
}

// Updates complaint status (Pending → In-Progress → Resolved)
void Complaint::updateStatus(const string& newStatus){
    status = newStatus;
}