#include "EntryExitRecord.h"
#include <iostream>
using namespace std;

EntryExitRecord::EntryExitRecord(){}
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

void EntryExitRecord::displayRecord() const {
    cout << recordID << " | " << studentID << " | " << type << " | " << timestamp << "\n";
}