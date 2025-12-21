#include<string>
#include "Student.h"
using namespace std;

class Admin{
    
    private:
    string adminID;
    string name;

    public:
    void addStudent(Student student);
    void removeStudent(string studentID);
    void verifyPayment(string studentID);
    void viewAllStudents();
    void viewAllComplaints();
    void updateComplaintStatus(string complaintID, string status);
};