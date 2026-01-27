#include "WorkerManager.h"
#include <iostream>
 
using namespace std;
WorkerManager::WorkerManager(FileHandler* fh) : fileHandler(fh) {
    loadWorkers();
}

void WorkerManager::loadWorkers() {
    workers = fileHandler->readWorkers();
}

Worker* WorkerManager::findAvailableWorker(const string& role) {
    for (auto& w : workers) {
        if (w.getRole() == role && w.checkAvailability()) {
            return &w;
        }
    }
    return nullptr;
}

void WorkerManager::updateWorkerStatus(const string& workerID, bool availability) {
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
            cout << "Worker status updated!\n";
            return;
        }
    }
    cout << "Worker not found!\n";
}
