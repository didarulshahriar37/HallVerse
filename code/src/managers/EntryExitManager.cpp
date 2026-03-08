#include "EntryExitManager.h"
#include "../utils/DateTimeHelper.h"
#include <iostream>
#include <sstream>
#include <utility>
 
using namespace std;
EntryExitManager::EntryExitManager(FileHandler* fh) : fileHandler(fh), nextRecordID(1) {
    loadLogs();
}

void EntryExitManager::loadLogs() {
    logs = fileHandler->readEntryExitLogs();
    if (!logs.empty()) {
        string lastID = logs.back().getRecordID();
        nextRecordID = stoi(lastID.substr(1)) + 1;
    }
}

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