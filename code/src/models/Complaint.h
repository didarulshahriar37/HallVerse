#ifndef COMPLAINT_H
#define COMPLAINT_H

#include<string>
using namespace std;

class Complaint{
    
    // Variables
    private:
    string complaintID;
    string category;
    string description;
    string status;
    string date;
    string studentID;

    // Constructors
    public:
    Complaint();
    Complaint(
        string complaintID,
        string category,
        string description,
        string status,
        string date,
        string studentID
    );
    
    // Getters
    string getComplaintID() const {
        return complaintID;
    };
    string getCategory() const {
        return category;
    };
    string getDescription() const {
        return description;
    };
    string getStatus() const {
        return status;
    };
    string getDate() const {
        return date;
    };
    string getStudentID() const {
        return studentID;
    };
    
    // other methods
    void updateStatus(const string& newStatus);
};

#endif