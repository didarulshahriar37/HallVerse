#ifndef COMPLAINT_H
#define COMPLAINT_H

#include<string>
using namespace std;

class Complaint{
    
    private:
    string complaintID;
    string category;
    string description;
    string status;
    string date;
    string studentID;

    public:
    void updateStatus(string status);
    void viewComplaintDetails();
};

#endif