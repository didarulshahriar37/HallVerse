#include "Admin.h"
#include "../services/FileHandler.h"
#include <iostream>
#include <vector>

using namespace std;

// Admin can add students data to students.csv file
void Admin::addStudent(Student student){
    FileHandler fileHandler;
    vector<Student> students = fileHandler.readStudents();

    for(size_t i = 0; i < students.size(); i++){
        if(students[i].getStudentID() == student.getStudentID()){
            cout << "Student ID " << student.getStudentID() << " already exists." << endl;
            return;
        }
    }

    students.push_back(student);
    fileHandler.writeStudents(students);

    cout << "Student with ID " << student.getStudentID() << " added successfully" << endl;
}

// Admin can remove any students from students.csv file
void Admin::removeStudent(string studentID){
    FileHandler fileHandler;
    vector<Student> students = fileHandler.readStudents();

    for(size_t i = 0; i<students.size(); i++){
        if(students[i].getStudentID() == studentID){
            students.erase(students.begin() + i);
            fileHandler.writeStudents(students);

            cout << "Student with ID " << studentID << " removed successfully." << endl;
            return;
        }
    }

    cout << "Student with ID " << studentID << " doesn't exist in the system." << endl;
}

void Admin::verifyPayment(string studentID){

}

// Admin can view all the students stored in students.csv file
void Admin::viewAllStudents(){
    FileHandler fileHandler;
    vector<Student> students = fileHandler.readStudents();
    
    if(students.empty()){
        cout << "No Students Data Exists." << endl;
        return;
    }

    cout << "\n========== STUDENT LIST ==========" << endl;

    for(size_t i = 0; i<students.size(); i++){
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