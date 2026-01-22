#include "EntryExitManager.h"
#include "../utils/DateTimeHelper.h"
#include <iostream>
#include <sstream>
 
using namespace std;
EntryExitManager::EntryExitManager(FileHandler* fh) : fileHandler(fh), nextRecordID(1) {
    loadLogs();
}

void EntryExitManager::loadLogs() {
    logs = fileHandler->readEntryExitLogs();
    if (!logs.empty()) {
        std::string lastID = logs.back().getRecordID();
        nextRecordID = std::stoi(lastID.substr(1)) + 1;
    }
}

void EntryExitManager::logEntry(const std::string& studentID) {
    std::stringstream ss;
    ss << "R" << nextRecordID;
    std::string timestamp = DateTimeHelper::getCurrentDateTime();
    EntryExitRecord record(ss.str(), studentID, "Entry", timestamp);
    logs.push_back(record);
    fileHandler->writeEntryExitLogs(logs);
    nextRecordID++;
    std::cout << "Entry logged successfully at " << timestamp << "\n";
}

void EntryExitManager::logExit(const std::string& studentID) {
    std::stringstream ss;
    ss << "R" << nextRecordID;
    std::string timestamp = DateTimeHelper::getCurrentDateTime();
    EntryExitRecord record(ss.str(), studentID, "Exit", timestamp);
    logs.push_back(record);
    fileHandler->writeEntryExitLogs(logs);
    nextRecordID++;
    std::cout << "Exit logged successfully at " << timestamp << "\n";
}