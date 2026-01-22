#include "WorkerManager.h"
#include <iostream>
 
using namespace std;
WorkerManager::WorkerManager(FileHandler* fh) : fileHandler(fh) {
    loadWorkers();
}

void WorkerManager::loadWorkers() {
    workers = fileHandler->readWorkers();
}

Worker* WorkerManager::findAvailableWorker(const std::string& role) {
    for (auto& w : workers) {
        if (w.getRole() == role && w.checkAvailability()) {
            return &w;
        }
    }
    return nullptr;
}

void WorkerManager::updateWorkerStatus(const std::string& workerID, bool availability) {
    for (auto& w : workers) {
        if (w.getWorkerID() == workerID) {
            if (availability) {
                w.markAvailable();
            } else {
                w.markUnavailable();
            }
            fileHandler->writeWorkers(workers);
            // Reload workers from file to ensure consistency
            loadWorkers();
            std::cout << "Worker status updated!\n";
            return;
        }
    }
    std::cout << "Worker not found!\n";
}
