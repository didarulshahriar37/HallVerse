#ifndef ENTRYEXITRECORD_H
#define ENTRYEXITRECORD_H

#include<string>
using namespace std;

class EntryExitRecord{

    // Variables
    private:
    string recordID;
    string studentID;
    string type;
    string timestamp;

    // Constructors
    public:
    EntryExitRecord();
    EntryExitRecord(string recordID, string studentID, string type, string timestamp);

    // Getters
    string getRecordID() const {
        return recordID;
    };
    string getStudentID() const {
        return studentID;
    };
    string getType() const {
        return type;
    };
    string getTimestamp() const {
        return timestamp;
    };

    // Other Methods
    void displayRecord() const;
};

#endif