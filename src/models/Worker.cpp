#include "Worker.h"
 
using namespace std;
Worker::Worker() : isAvailable(true) {}

Worker::Worker(std::string id, std::string n, std::string r, bool avail, std::string contact)
    : workerID(id), name(n), role(r), isAvailable(avail), contactNumber(contact) {}

void Worker::markAvailable() {
    isAvailable = true;
}