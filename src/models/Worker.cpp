#include "Worker.h"
 
using namespace std;
Worker::Worker() : isAvailable(true) {}

Worker::Worker(string id, string n, string r, bool avail, string contact)
    : workerID(id), name(n), role(r), isAvailable(avail), contactNumber(contact) {}

void Worker::markAvailable() {
    isAvailable = true;
}
void Worker::markUnavailable() {
    isAvailable = false;
}

bool Worker::checkAvailability() const {
    return isAvailable;
}