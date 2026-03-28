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

    public:
    // Constructors
    // Default constructor: Initializes an empty entry/exit record
    // Features used: Basic object initialization for entry/exit tracking system
    EntryExitRecord();
    
    // Parameterized constructor: Creates a record with specific details
    // Features used: Entry/exit logging, student identification, timestamp recording
    EntryExitRecord(string recordID, string studentID, string type, string timestamp);

    // Getters
    // Returns the unique record identifier
    // Features used: Record identification in entry/exit logs
    string getRecordID() const {
        return recordID;
    };
    
    // Returns the student ID associated with this record
    // Features used: Student identification, linking records to students
    string getStudentID() const {
        return studentID;
    };
    
    // Returns the type of record ("Entry" or "Exit")
    // Features used: Entry/exit status tracking, hall access monitoring
    string getType() const {
        return type;
    };
    
    // Returns the timestamp when the entry/exit occurred
    // Features used: Time-based logging, chronological record keeping
    string getTimestamp() const {
        return timestamp;
    };

    // Other Methods
    // Displays the record in a formatted manner (pipe-delimited)
    // Features used: Record display, log viewing functionality
    void displayRecord() const;
};

#endif