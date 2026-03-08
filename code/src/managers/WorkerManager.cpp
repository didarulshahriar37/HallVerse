#include "WorkerManager.h"
#include <iostream>
 
using namespace std;

WorkerManager::WorkerManager(FileHandler* fh, Hasher* h) : fileHandler(fh), hasher(h) {
    loadWorkers();
}

void WorkerManager::loadWorkers() {
    workers = fileHandler->readWorkers();
}

void WorkerManager::saveWorkers() {
    fileHandler->writeWorkers(workers);
}

bool WorkerManager::loginWorker(const string& workerID, const string& password) {
    string hash = hasher->hash(password);
    return fileHandler->checkWorkerCredentials(workerID, hash);
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

Worker* WorkerManager::findWorkerByID(const string& workerID) {
    for (auto& w : workers) {
        if (w.getWorkerID() == workerID) {
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

void WorkerManager::updateContactNumber(const string& workerID, const string& newContact) {
    for (auto& w : workers) {
        if (w.getWorkerID() == workerID) {
            w.setContactNumber(newContact);
            fileHandler->updateWorkerContact(workerID, newContact);
            // Reload to keep in-memory data in sync
            loadWorkers();
            return;
        }
    }
}

bool WorkerManager::verifyWorkerPassword(const string& workerID, const string& password) {
    string hash = hasher->hash(password);
    return fileHandler->checkWorkerCredentials(workerID, hash);
}

void WorkerManager::updateWorkerPassword(const string& workerID, const string& newPassword) {
    string hash = hasher->hash(newPassword);
    fileHandler->updateWorkerPassword(workerID, hash);
    loadWorkers();
}
