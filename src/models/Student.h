#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;
class Student {
private:
    string studentID;
    string name;
    string email;
    string emergencyContact;
    string roomNumber;
    string bedNumber;
    string hallName;
    double hallDues;
    string passwordHash;

public:
    // Constructors
    Student();
    Student(const string& studentID,
            const string& name,
            const string& email,
            const string& emergencyContact,
            const string& roomNumber,
            const string& bedNumber,
            const string& hallName,
            double hallDues);

    // Getters (const-correct)
    string getStudentID() const {
        return studentID;
    };
    string getName() const {
        return name;
    };
    string getEmail() const {
        return email;
    };
    string getEmergencyContact() const {
        return emergencyContact;
    };
    string getRoomNumber() const {
        return roomNumber;
    };
    string getBedNumber() const {
        return bedNumber;
    };
    string getHallName() const {
        return hallName;
    };
    double getHallDues() const {
        return hallDues;
    };
    string getPasswordHash() const {
        return passwordHash;
    };

    // Setters
    void setName(const string& name) {
        this->name = name;
    };
    void setEmail(const string& email) {
        this->email = email;
    };
    void setEmergencyContact(const string& contact) {
        this->emergencyContact = contact;
    };
    void setRoomNumber(const string& roomNumber) {
        this->roomNumber = roomNumber;
    };
    void setBedNumber(const string& bedNumber) {
        this->bedNumber = bedNumber;
    };
    void setHallName(const string& hallName) {
        this->hallName = hallName;
    };
    void setHallDues(double hallDues) {
        this->hallDues = hallDues;
    };
    void setPasswordHash(const string& hash) {
        this->passwordHash = hash;
    };

    // Other Methods
    void viewProfile();
    void updateEmail(const string& email);
    void updateEmergencyContact(const string& contact);
};

#endif
