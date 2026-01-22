#include "Complaint.h"
using namespace std;

Complaint::Complaint() {
    status = "Pending";
}

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

void Complaint::updateStatus(const string& newStatus){
    status = newStatus;
}