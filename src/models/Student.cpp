#include "Student.h"

// Default constructor
Student::Student() {
    hallDues = 0.0;
}

// Parameterized constructor
Student::Student(const std::string& studentID,
                 const std::string& name,
                 const std::string& email,
                 const std::string& emergencyContact,
                 const std::string& roomNumber,
                 double hallDues) {
    this->studentID = studentID;
    this->name = name;
    this->email = email;
    this->emergencyContact = emergencyContact;
    this->roomNumber = roomNumber;
    this->hallDues = hallDues;
}

// Getters
std::string Student::getStudentID() const {
    return studentID;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getEmail() const {
    return email;
}

std::string Student::getEmergencyContact() const {
    return emergencyContact;
}

std::string Student::getRoomNumber() const {
    return roomNumber;
}

double Student::getHallDues() const {
    return hallDues;
}

// Setters
void Student::setName(const std::string& name) {
    this->name = name;
}

void Student::setEmail(const std::string& email) {
    this->email = email;
}

void Student::setEmergencyContact(const std::string& contact) {
    this->emergencyContact = contact;
}

void Student::setRoomNumber(const std::string& roomNumber) {
    this->roomNumber = roomNumber;
}

void Student::setHallDues(double dues) {
    this->hallDues = dues;
}
