#include "WorkerManager.h"

#include "../models/Worker.h"
#include "../services/FileHandler.h"

WorkerManager::WorkerManager(FileHandler* fileHandler) {
    this->fileHandler = fileHandler;
}

void WorkerManager::loadWorkers() {
}

void WorkerManager::addWorker(const Worker& worker) {
    
}

void WorkerManager::updateWorkerStatus(const std::string& workerID, const std::string& newStatus) {
    
}

std::vector<Worker> WorkerManager::getAllWorkers() {
    
    return workers;
}

Worker* WorkerManager::getAvailableWorkerByRole(const std::string& role) {
    
    return nullptr;
}
