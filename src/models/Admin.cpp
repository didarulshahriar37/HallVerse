#include "Admin.h"
#include <iostream>

using namespace std;

static Student students[100];
static int studentCount = 0; 

void Admin::addStudent(Student student){
    if(studentCount >= 100){
        cout << "Student limit reached." << endl;
        return;
    }

    for(int i = 0; i < studentCount; i++){
        if(students[i].getStudentID() == student.getStudentID()){
            cout << "Student ID " << student.getStudentID() << " already exists." << endl;
            return;
        }
    }

    students[studentCount] = student;
    studentCount++;

    cout << "Student with ID " << student.getStudentID() << " added successfully" << endl;
}

void Admin::removeStudent(string studentID){
    for(int i = 0; i<studentCount; i++){
        if(students[i].getStudentID() == studentID){
            for(int j = i; j<studentCount - 1; j++){
                students[j] = students[j + 1];
            }

            studentCount--;
            cout << "Student with ID " << studentID << " removed successfully." << endl;
            return;
        }
    }

    cout << "Student with ID " << studentID << " doesn't exist in the system." << endl;
}

void Admin::verifyPayment(string studentID){

}

void Admin::viewAllStudents(){
    if(studentCount == 0){
        cout << "No Students Data Exists." << endl;
        return;
    }

    cout << "========== STUDENT LIST ==========" << endl;

    for(int i = 0; i<studentCount; i++){
        cout << "Student ID          : " << students[i].getStudentID() << endl;
        cout << "Student Name        : " << students[i].getName() << endl;
        cout << "Email               : " << students[i].getEmail() << endl;
        cout << "Emergency Contact   : " << students[i].getEmergencyContact() << endl;
        cout << "Room No.            : " << students[i].getRoomNumber() << endl;
        cout << "Hall Due            : " << students[i].getHallDues() << endl;
        cout << "--------------------------------------------" << endl;
    }
}

void Admin::viewAllComplaints(){

}

void Admin::updateComplaintStatus(string complaintID, string status){
    
}