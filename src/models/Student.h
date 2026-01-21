#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string studentID;
    std::string name;
    std::string email;
    std::string emergencyContact;
    std::string roomNumber;
    std::string bedNumber;
    std::string hallName;
    double hallDues;

public:
    // Constructors
    Student();
    Student(const std::string& studentID,
            const std::string& name,
            const std::string& email,
            const std::string& emergencyContact,
            const std::string& roomNumber,
            const std::string& bedNumber,
            const std::string& hallName,
            double hallDues);

    // Getters (const-correct)
    std::string getStudentID() const {
        return studentID;
    };
    std::string getName() const {
        return name;
    };
    std::string getEmail() const {
        return email;
    };
    std::string getEmergencyContact() const {
        return emergencyContact;
    };
    std::string getRoomNumber() const {
        return roomNumber;
    };
    std::string getBedNumber() const {
        return bedNumber;
    };
    std::string getHallName() const {
        return hallName;
    };
    double getHallDues() const {
        return hallDues;
    };

    // Setters
    void setName(const std::string& name) {
        this->name = name;
    };
    void setEmail(const std::string& email) {
        this->email = email;
    };
    void setEmergencyContact(const std::string& contact) {
        this->emergencyContact = contact;
    };
    void setRoomNumber(const std::string& roomNumber) {
        this->roomNumber = roomNumber;
    };
    void setBedNumber(const std::string& bedNumber) {
        this->bedNumber = bedNumber;
    };
    void setHallName(const std::string& hallName) {
        this->hallName = hallName;
    };
    void setHallDues(double hallDues) {
        this->hallDues = hallDues;
    };

    // Other Methods
    void viewProfile();
    void updateEmail(const std::string& email);
    void updateEmergencyContact(const std::string& contact);
};

#endif
