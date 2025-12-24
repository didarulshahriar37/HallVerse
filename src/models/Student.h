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
    double hallDues;

public:
    // Constructors
    Student();
    Student(const std::string& studentID,
            const std::string& name,
            const std::string& email,
            const std::string& emergencyContact,
            const std::string& roomNumber,
            double hallDues);

    // Getters (const-correct)
    std::string getStudentID() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getEmergencyContact() const;
    std::string getRoomNumber() const;
    double getHallDues() const;

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setEmergencyContact(const std::string& contact);
    void setRoomNumber(const std::string& roomNumber);
    void setHallDues(double dues);
};

#endif
