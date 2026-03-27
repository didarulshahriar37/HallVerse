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
    // Default constructor: Initializes an empty student object with default values
    // Features used: Student data initialization, hall management system
    Student();
    
    // Parameterized constructor: Creates a student with complete profile information
    // Parameters: studentID - unique student identifier
    //           name - full name of the student
    //           email - email address for communication
    //           emergencyContact - emergency contact number
    //           roomNumber - assigned room number
    //           bedNumber - assigned bed (A, B, C, or D)
    //           hallName - hall name (North/South)
    //           hallDues - outstanding dues amount
    // Features used: Student registration, room allocation, dues tracking, contact management
    Student(const string& studentID,
            const string& name,
            const string& email,
            const string& emergencyContact,
            const string& roomNumber,
            const string& bedNumber,
            const string& hallName,
            double hallDues);

    // Getters (const-correct)
    // Returns the unique student identifier
    // Features used: Student identification, authentication, record linking
    string getStudentID() const {
        return studentID;
    };
    
    // Returns the student's full name
    // Features used: Student profile display, identification
    string getName() const {
        return name;
    };
    
    // Returns the student's email address
    // Features used: Communication, password recovery, notifications
    string getEmail() const {
        return email;
    };
    
    // Returns the emergency contact number
    // Features used: Emergency contact management, safety protocols
    string getEmergencyContact() const {
        return emergencyContact;
    };
    
    // Returns the assigned room number
    // Features used: Room allocation, accommodation tracking
    string getRoomNumber() const {
        return roomNumber;
    };
    
    // Returns the assigned bed letter (A, B, C, or D)
    // Features used: Bed allocation, room sharing management
    string getBedNumber() const {
        return bedNumber;
    };
    
    // Returns the hall name (North or South)
    // Features used: Hall management, location-based services
    string getHallName() const {
        return hallName;
    };
    
    // Returns the current outstanding dues amount
    // Features used: Financial tracking, payment management
    double getHallDues() const {
        return hallDues;
    };
    
    // Returns the hashed password for authentication
    // Features used: Login security, password verification
    string getPasswordHash() const {
        return passwordHash;
    };

    // Setters
    // Updates the student's name
    // Features used: Profile management, student information updates
    void setName(const string& name) {
        this->name = name;
    };
    
    // Updates the student's email address
    // Features used: Communication updates, account management
    void setEmail(const string& email) {
        this->email = email;
    };
    
    // Updates the emergency contact number
    // Features used: Safety information updates
    void setEmergencyContact(const string& contact) {
        this->emergencyContact = contact;
    };
    
    // Updates the assigned room number
    // Features used: Room reassignment, accommodation changes
    void setRoomNumber(const string& roomNumber) {
        this->roomNumber = roomNumber;
    };
    
    // Updates the assigned bed letter
    // Features used: Bed reassignment, room management
    void setBedNumber(const string& bedNumber) {
        this->bedNumber = bedNumber;
    };
    
    // Updates the hall name
    // Features used: Hall transfers, location changes
    void setHallName(const string& hallName) {
        this->hallName = hallName;
    };
    
    // Updates the outstanding dues amount
    // Features used: Payment processing, fee management
    void setHallDues(double hallDues) {
        this->hallDues = hallDues;
    };
    
    // Updates the password hash
    // Features used: Password changes, security updates
    void setPasswordHash(const string& hash) {
        this->passwordHash = hash;
    };

    // Other Methods
    // Displays the complete student profile with all information and dues
    // Features used: Profile viewing, student dashboard
    void viewProfile();
    
    // Updates the student's email with validation
    // Parameters: email - new email address to set
    // Features used: Email validation, profile updates
    void updateEmail(const string& email);
    
    // Updates the emergency contact number with validation
    // Parameters: contact - new contact number to set
    // Features used: Contact validation, emergency information updates
    void updateEmergencyContact(const string& contact);
};

#endif
