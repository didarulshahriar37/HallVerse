#include "Worker.h"
#include <algorithm>
#include <iostream>

using namespace std;

// constructors
Worker::Worker()
    : workerID(""), name(""), role(""), contactNumber(""), isAvailable(true),
      activeComplaints(0), resolvedComplaints(0), assignedComplaintIDs() {}

Worker::Worker(const string &id,
               const string &n,
               const string &r,
               bool avail,
               const string &contact,
               const string &pwdHash)
    : workerID(id), name(n), role(r), contactNumber(contact), isAvailable(avail),
      passwordHash(pwdHash), activeComplaints(0), resolvedComplaints(0), assignedComplaintIDs() {}

// availability control
void Worker::markAvailable()
{
    isAvailable = true;
}

void Worker::markUnavailable()
{
    isAvailable = false;
}

bool Worker::checkAvailability() const
{
    return isAvailable;
}

// complaint workflow
void Worker::assignComplaint(const string &complaintID)
{
    // avoid duplicates
    if (find(assignedComplaintIDs.begin(), assignedComplaintIDs.end(), complaintID) == assignedComplaintIDs.end())
    {
        assignedComplaintIDs.push_back(complaintID);
        ++activeComplaints;
        if (activeComplaints > 0)
            markUnavailable();
    }
}

void Worker::completeComplaint(const string &complaintID)
{
    auto it = find(assignedComplaintIDs.begin(), assignedComplaintIDs.end(), complaintID);
    if (it != assignedComplaintIDs.end())
    {
        assignedComplaintIDs.erase(it);
        if (activeComplaints > 0)
            --activeComplaints;
        ++resolvedComplaints;
        if (activeComplaints == 0)
            markAvailable();
    }
    else
    {
        // complaint not assigned; ignore or log
        cerr << "Warning: complaint " << complaintID << " not found for worker " << name << "\n";
    }
}

void Worker::updateComplaintStatus(const string &complaintID, const string &status)
{
    cout << "Worker " << name << " updating complaint " << complaintID << " to status '"
         << status << "'" << endl;
}

// getters
int Worker::getActiveComplaints() const
{
    return activeComplaints;
}

int Worker::getResolvedComplaints() const
{
    return resolvedComplaints;
}

vector<string> Worker::getAssignedComplaints() const
{
    return assignedComplaintIDs;
}

// basic attribute getters
string Worker::getWorkerID() const
{
    return workerID;
}

string Worker::getName() const
{
    return name;
}

string Worker::getRole() const
{
    return role;
}

string Worker::getContactNumber() const
{
    return contactNumber;
}

bool Worker::getIsAvailable() const
{
    return isAvailable;
}

string Worker::getPasswordHash() const
{
    return passwordHash;
}

void Worker::setPasswordHash(const string& hash)
{
    passwordHash = hash;
}

void Worker::setContactNumber(const string& contact)
{
    contactNumber = contact;
}
