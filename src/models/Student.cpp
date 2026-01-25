#include "Student.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Default constructor
Student::Student() {
    bedNumber = "";
    hallName = "";
    hallDues = 0.0;
    passwordHash = "";
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
    this->passwordHash = "";
}

// View Profile Method
void Student::viewProfile(){
    std::cout << "\n============= STUDENT PROFILE =============\n";
    std::cout << "Student Id: " << studentID << "\n";
    std::cout << "Student Name: " << name << "\n";
    std::cout << "Student Email: " << email << "\n";
    std::cout << "Emergency Contact: " << emergencyContact << "\n";
    std::cout << "Room Number: " << roomNumber << "\n";
    std::cout << "Bed Number: " << bedNumber << "\n";
    std::cout << "Hall Name: " << hallName << "\n";
    std::cout << "Hall Due: $ " << std::fixed << std::setprecision(2) << hallDues << "\n";
    std::cout << "===========================================\n";   
}

// Update Methods
// Update Email
void Student::updateEmail(const std::string& newEmail){
    if(newEmail.empty()){
        std::cout << "You must provide an email address !\n";
        return;
    }
    email = newEmail;
    std::cout << "Email updated to: " << email << "\n";
}

// Update Emergency Contact
void Student::updateEmergencyContact(const std::string& newEmergencyContact){
    if(newEmergencyContact.empty()){
        std::cout << "You must provide an emergency contact !\n";
        return;
    }
    emergencyContact = newEmergencyContact;
    std::cout << "Emergency Contact updated to: " << emergencyContact << "\n";
}