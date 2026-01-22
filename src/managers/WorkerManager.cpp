#include "WorkerManager.h"
#include <iostream>
 
using namespace std;
WorkerManager::WorkerManager(FileHandler* fh) : fileHandler(fh) {
    loadWorkers();
}

void WorkerManager::loadWorkers() {
    workers = fileHandler->readWorkers();
}

std::vector<Worker> WorkerManager::getAllWorkers() {
    
    return workers;
}

Worker* WorkerManager::getAvailableWorkerByRole(const std::string& role) {
    
    return nullptr;
}
