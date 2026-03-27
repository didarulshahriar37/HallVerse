#include "EntryExitRecord.h"
#include <iostream>
using namespace std;

// Default constructor implementation: Initializes an empty entry/exit record
// Features used: Basic object initialization for entry/exit tracking system
EntryExitRecord::EntryExitRecord(){}

// Parameterized constructor implementation: Creates a record with specific details
// Parameters: recordID - unique identifier for the record
//           studentID - ID of the student making entry/exit
//           type - "Entry" or "Exit"
//           timestamp - date/time of the event
// Features used: Entry/exit logging, student identification, timestamp recording
EntryExitRecord::EntryExitRecord(
    string recordID,
    string studentID,
    string type,
    string timestamp
){
    this->recordID = recordID;
    this->studentID = studentID;
    this->type = type;
    this->timestamp = timestamp;
}

// Displays the record in a formatted manner (pipe-delimited)
// Features used: Record display, log viewing functionality
void EntryExitRecord::displayRecord() const {
    cout << recordID << " | " << studentID << " | " << type << " | " << timestamp << "\n";
}