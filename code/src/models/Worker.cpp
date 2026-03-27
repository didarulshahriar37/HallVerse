#include "Worker.h"
#include <algorithm>
#include <iostream>

using namespace std;

// constructors
// Default constructor: Initializes unavailable worker with no assignments
Worker::Worker()
    : workerID(""), name(""), role(""), contactNumber(""), isAvailable(true),
      activeComplaints(0), resolvedComplaints(0), assignedComplaintIDs() {}

// Parameterized constructor: Creates worker with full details
Worker::Worker(const string &id,
               const string &n,
               const string &r,
               bool avail,
               const string &contact,
               const string &pwdHash)
    : workerID(id), name(n), role(r), contactNumber(contact), isAvailable(avail),
      passwordHash(pwdHash), activeComplaints(0), resolvedComplaints(0), assignedComplaintIDs() {}

// availability control
// Sets worker availability to available
void Worker::markAvailable()
{
    isAvailable = true;
}

// Sets worker availability to unavailable
void Worker::markUnavailable()
{
    isAvailable = false;
}

// Returns true if worker is available
bool Worker::checkAvailability() const
{
    return isAvailable;
}

// complaint workflow
// Assigns complaint to worker, marks unavailable if active complaints > 0
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

// Removes complaint from worker, marks available if no more active complaints
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

// Updates complaint status (logging only in current implementation)
void Worker::updateComplaintStatus(const string &complaintID, const string &status)
{
    cout << "Worker " << name << " updating complaint " << complaintID << " to status '"
         << status << "'" << endl;
}

// getters
// Returns number of active complaints assigned to worker
int Worker::getActiveComplaints() const
{
    return activeComplaints;
}

// Returns number of resolved complaints by worker
int Worker::getResolvedComplaints() const
{
    return resolvedComplaints;
}

// Returns list of assigned complaint IDs
vector<string> Worker::getAssignedComplaints() const
{
    return assignedComplaintIDs;
}

// basic attribute getters
// Returns worker's unique ID
string Worker::getWorkerID() const
{
    return workerID;
}

// Returns worker's name
string Worker::getName() const
{
    return name;
}

// Returns worker's role (Electrician, Plumber, etc.)
string Worker::getRole() const
{
    return role;
}

// Returns worker's contact number
string Worker::getContactNumber() const
{
    return contactNumber;
}

// Returns worker's availability status
bool Worker::getIsAvailable() const
{
    return isAvailable;
}

// Returns worker's password hash
string Worker::getPasswordHash() const
{
    return passwordHash;
}

// Updates worker's password hash
void Worker::setPasswordHash(const string& hash)
{
    passwordHash = hash;
}

// Updates worker's contact number
void Worker::setContactNumber(const string& contact)
{
    contactNumber = contact;
}
