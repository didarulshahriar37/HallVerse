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

// Finds the worker of the given role with the fewest resolved complaints.
// This balances workload by preferring the least-experienced (least-loaded) worker.
// Falls back to nullptr if no worker of that role exists.
Worker* WorkerManager::findLeastLoadedWorker(const string& role) {
    Worker* best = nullptr;
    for (auto& w : workers) {
        if (w.getRole() == role) {
            if (best == nullptr || w.getResolvedComplaints() < best->getResolvedComplaints()) {
                best = &w;
            }
        }
    }
    return best;
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
