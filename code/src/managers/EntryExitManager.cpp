#include "EntryExitManager.h"
#include "../utils/DateTimeHelper.h"
#include <iostream>
#include <sstream>
#include <utility>
 
using namespace std;

// EntryExitManager manages the entry/exit logs for students, persisting and querying.
EntryExitManager::EntryExitManager(FileHandler* fh) : fileHandler(fh), nextRecordID(1) {
    loadLogs();
}

// Loads entry/exit CSV logs into memory and initializes next log ID.
void EntryExitManager::loadLogs() {
    logs = fileHandler->readEntryExitLogs();
    if (!logs.empty()) {
        string lastID = logs.back().getRecordID();
        nextRecordID = stoi(lastID.substr(1)) + 1;
    }
}

// Creates a new 'Entry' log record for the given student.
void EntryExitManager::logEntry(const string& studentID) {
    stringstream ss;
    ss << "R" << nextRecordID;
    string timestamp = DateTimeHelper::getCurrentDateTime();
    EntryExitRecord record(ss.str(), studentID, "Entry", timestamp);
    logs.push_back(record);
    fileHandler->writeEntryExitLogs(logs);
    nextRecordID++;
    cout << "Entry logged successfully at " << timestamp << "\n";
}

// Creates a new 'Exit' log record for the given student.
void EntryExitManager::logExit(const string& studentID) {
    stringstream ss;
    ss << "R" << nextRecordID;
    string timestamp = DateTimeHelper::getCurrentDateTime();
    EntryExitRecord record(ss.str(), studentID, "Exit", timestamp);
    logs.push_back(record);
    fileHandler->writeEntryExitLogs(logs);
    nextRecordID++;
    cout << "Exit logged successfully at " << timestamp << "\n";
}

// Returns pair<logged_in, last_timestamp> for a student. Consults logs in reverse order.
pair<bool, string> EntryExitManager::getCurrentStatus(const string& studentID) {
    string lastTimestamp = "";
    bool isLoggedIn = false;
    for (auto it = logs.rbegin(); it != logs.rend(); ++it) {
        if (it->getStudentID() == studentID) {
            lastTimestamp = it->getTimestamp();
            isLoggedIn = (it->getType() == "Entry");
            break;
        }
    }
    return {isLoggedIn, lastTimestamp};
}