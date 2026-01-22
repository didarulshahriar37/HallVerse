#include "Student.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Default constructor
Student::Student() {
    bedNumber = "";
    hallName = "";
    hallDues = 0.0;
}

// Parameterized constructor
Student::Student(const std::string& studentID,
                 const std::string& name,
                 const std::string& email,
                 const std::string& emergencyContact,
                 const std::string& roomNumber,
                 const std::string& bedNumber,
                 const std::string& hallName,
                 double hallDues) {
    this->studentID = studentID;
    this->name = name;
    this->email = email;
    this->emergencyContact = emergencyContact;
    this->roomNumber = roomNumber;
    this->bedNumber = bedNumber;
    this->hallName = hallName;
    this->hallDues = hallDues;
}

// View Profile
void Student::viewProfile(){
    std::cout << "\n============= STUDENT PROFILE =============\n";
    std::cout << "Student Id: " << studentID << endl;
    std::cout << "Student Name: " << name << endl;
    std::cout << "Student Email: " << email << endl;
    std::cout << "Emergency Contact: " << emergencyContact << endl;
    std::cout << "Room Number: " << roomNumber << endl;
    std::cout << "Bed Number: " << bedNumber << endl;
    std::cout << "Hall Name: " << hallName << endl;
    std::cout << "Hall Due: $ " << std::fixed << std::setprecision(2) << hallDues << endl;
    std::cout << "===========================================\n";   
}