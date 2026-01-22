#ifndef ENTRYEXITMANAGER_H
#define ENTRYEXITMANAGER_H

#include <vector>
#include "../models/EntryExitRecord.h"
#include "../services/FileHandler.h"

class EntryExitManager {
private:
    FileHandler* fileHandler;
    std::vector<EntryExitRecord> logs;
    int nextRecordID;
    
public:
    EntryExitManager(FileHandler* fh);
    void logEntry(const std::string& studentID);
    void logExit(const std::string& studentID);
    std::vector<EntryExitRecord>& getLogs() { return logs; }
    void loadLogs();
};

#endif