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
Student::Student(const string& studentID,
                 const string& name,
                 const string& email,
                 const string& emergencyContact,
                 const string& roomNumber,
                 const string& bedNumber,
                 const string& hallName,
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
    cout << "\n============= STUDENT PROFILE =============\n";
    cout << "Student Id: " << studentID << "\n";
    cout << "Student Name: " << name << "\n";
    cout << "Student Email: " << email << "\n";
    cout << "Emergency Contact: " << emergencyContact << "\n";
    cout << "Hall Name: " << hallName << "\n";
    cout << "Room Number: " << roomNumber << "\n";
    cout << "Bed Number: " << bedNumber << "\n";
    cout << "Total Due(s): $ " << fixed << setprecision(2) << hallDues << "\n";
    cout << "===========================================\n";   
}

// Update Methods
// Update Email
void Student::updateEmail(const string& newEmail){
    if(newEmail.empty()){
        cout << "You must provide an email address !\n";
        return;
    }
    email = newEmail;
    cout << "Email updated to: " << email << "\n";
}

// Update Emergency Contact
void Student::updateEmergencyContact(const string& newEmergencyContact){
    if(newEmergencyContact.empty()){
        cout << "You must provide an emergency contact !\n";
        return;
    }
    emergencyContact = newEmergencyContact;
    cout << "Emergency Contact updated to: " << emergencyContact << "\n";
}