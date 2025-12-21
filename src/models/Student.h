#include<string>
using namespace std;

class Student {

    private:
    string studentID;
    string name;
    string email;
    string emergencyContact;
    string roomNumber;
    double halldues;


    public:
    void viewProfile();
    void updateEmail(string email);
    void updateEmergencyContact(string contact);
    double checkHallDues();
    string getRoomNumber();
};