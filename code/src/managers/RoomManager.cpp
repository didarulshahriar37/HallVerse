#include "RoomManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;
RoomManager::RoomManager() {
    loadRooms();
}

vector<string> RoomManager::split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void RoomManager::loadRooms() {
    rooms.clear();
    ifstream file("data/rooms.csv");
    if (!file.is_open()) {
        cerr << "Error opening rooms.csv\n";
        return;
    }
    
    string line;
    bool isHeader = true;
    
    while (getline(file, line)) {
        if (isHeader) {
            isHeader = false;
            continue;
        }
        
        auto parts = split(line, ',');
        if (parts.size() >= 4) {
            Room room;
            room.hallName = parts[0];
            room.roomNumber = parts[1];
            room.bedNumber = parts[2];
            room.status = parts[3];
            rooms.push_back(room);
        }
    }
    
    file.close();
}

void RoomManager::updateBedStatus(const string& hall, const string& room, 
                                   const string& bed, const string& status) {
    for (auto& r : rooms) {
        if (r.hallName == hall && r.roomNumber == room && r.bedNumber == bed) {
            r.status = status;
            break;
        }
    }
    
    // Write back to CSV
    ofstream file("data/rooms.csv");
    if (!file.is_open()) {
        cerr << "Error writing to rooms.csv\n";
        return;
    }
    
    file << "hallName,roomNumber,bedNumber,status\n";
    for (const auto& r : rooms) {
        file << r.hallName << "," << r.roomNumber << "," << r.bedNumber << "," << r.status << "\n";
    }
    
    file.close();
}

// Adds rooms in bulk for a given hall from startRoom to endRoom (inclusive).
// Each room gets 4 beds: A, B, C, D. Duplicate beds are silently skipped.
void RoomManager::addRooms(const string& hall, int startRoom, int endRoom) {
    const string beds[] = {"A", "B", "C", "D"};
    int added = 0;
    int skipped = 0;

    for (int r = startRoom; r <= endRoom; r++) {
        string roomNum = to_string(r);
        for (const string& bed : beds) {
            // Duplicate check: skip if this hall+room+bed already exists
            bool exists = false;
            for (const auto& existing : rooms) {
                if (existing.hallName == hall &&
                    existing.roomNumber == roomNum &&
                    existing.bedNumber == bed) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                skipped++;
                continue;
            }
            Room newRoom;
            newRoom.hallName   = hall;
            newRoom.roomNumber = roomNum;
            newRoom.bedNumber  = bed;
            newRoom.status     = "Vacant";
            rooms.push_back(newRoom);
            added++;
        }
    }

    // Persist to CSV
    ofstream file("data/rooms.csv");
    if (!file.is_open()) {
        cerr << "Error writing to rooms.csv\n";
        return;
    }
    file << "hallName,roomNumber,bedNumber,status\n";
    for (const auto& rm : rooms) {
        file << rm.hallName << "," << rm.roomNumber << "," << rm.bedNumber << "," << rm.status << "\n";
    }
    file.close();

    cout << "\n✓ Room addition complete!\n";
    cout << "  Beds added   : " << added   << "\n";
    cout << "  Beds skipped : " << skipped << " (already existed)\n";
}


vector<RoomManager::Room> RoomManager::searchAvailableBeds(const string& hall, 
                                                                 const string& room) {
    vector<Room> results;
    
    for (const auto& r : rooms) {
        // treat both "free" and "vacant" as available
        string st = r.status;
        for (auto &c : st) c = tolower(c);
        if (st == "free" || st == "vacant") {
            if (!hall.empty() && r.hallName != hall) continue;
            if (!room.empty() && r.roomNumber != room) continue;
            results.push_back(r);
        }
    }
    
    return results;
}

vector<string> RoomManager::getAvailableRooms(const string& hall) {
    vector<string> roomsList;
    for (const auto& r : rooms) {
        string st = r.status;
        for (auto &c : st) c = tolower(c);
        if (st == "free" || st == "vacant") {
            if (!hall.empty() && r.hallName != hall) continue;
            if (find(roomsList.begin(), roomsList.end(), r.roomNumber) == roomsList.end()) {
                roomsList.push_back(r.roomNumber);
            }
        }
    }
    return roomsList;
}

vector<string> RoomManager::getAvailableBeds(const string& hall, const string& room) {
    vector<string> bedList;
    for (const auto& r : rooms) {
        string st = r.status;
        for (auto &c : st) c = tolower(c);
        if (st == "free" || st == "vacant") {
            if (!hall.empty() && r.hallName != hall) continue;
            if (!room.empty() && r.roomNumber != room) continue;
            bedList.push_back(r.bedNumber);
        }
    }
    return bedList;
}
void RoomManager::displayBedAvailability(const string& hall, const string& room) {
    cout << "\n========== Bed Availability Report ==========\n";
    cout << "Hall: " << (hall.empty() ? "All" : hall) << " | ";
    cout << "Room: " << (room.empty() ? "All" : room) << "\n";
    cout << "=============================================\n";
    
    cout << left << setw(10) << "Hall" 
              << setw(10) << "Room" 
              << setw(8) << "Bed" 
              << "Status\n";
    cout << "---------------------------------------------\n";
    
    for (const auto& r : rooms) {
        if (!hall.empty() && r.hallName != hall) continue;
        if (!room.empty() && r.roomNumber != room) continue;
        
        cout << left << setw(10) << r.hallName 
                  << setw(10) << r.roomNumber 
                  << setw(8) << r.bedNumber 
                  << r.status << "\n";
    }
    
    cout << "=============================================\n";
}

void RoomManager::displayAllBeds() {
    displayBedAvailability("", "");
}

// Displays beds filtered by status ("Occupied", "Vacant", or "" for all).
void RoomManager::displayBedsByStatus(const string& statusFilter) {
    auto isStatusMatch = [](const string& recordStatus, const string& filter) {
        if (filter.empty()) return true;
        
        string rs = recordStatus;
        string f = filter;
        // Convert to lowercase for robust comparison
        for(auto& c : rs) c = tolower(c);
        for(auto& c : f) c = tolower(c);
        
        if (f == "vacant") {
            return (rs == "vacant" || rs == "free");
        } else if (f == "occupied") {
            return (rs == "occupied");
        }
        return rs == f;
    };

    // Count matching beds first for the header
    int matchCount = 0;
    for (const auto& r : rooms) {
        if (isStatusMatch(r.status, statusFilter)) matchCount++;
    }

    string label = statusFilter.empty() ? "All Beds" : statusFilter + " Beds";
    cout << "\n╔══════════════════════════════════════════════════╗\n";
    cout << "║  BED VIEW — " << left << setw(37) << label            << "║\n";
    cout << "║  Matching Beds: " << left << setw(32) << matchCount   << "║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    if (matchCount == 0) {
        cout << "\n  No " << label << " found.\n";
        return;
    }

    // Table header
    cout << "\n  " << string(52, '-') << "\n";
    cout << "  " << left
         << setw(12) << "Hall"
         << setw(10) << "Room"
         << setw(8)  << "Bed"
         << "Status" << "\n";
    cout << "  " << string(52, '-') << "\n";

    for (const auto& r : rooms) {
        if (!isStatusMatch(r.status, statusFilter)) continue;
        cout << "  " << left
             << setw(12) << r.hallName
             << setw(10) << r.roomNumber
             << setw(8)  << r.bedNumber
             << r.status << "\n";
    }
    cout << "  " << string(52, '-') << "\n";
}


string RoomManager::getBedStatus(const string& hall, const string& room, 
                                       const string& bed) {
    for (const auto& r : rooms) {
        if (r.hallName == hall && r.roomNumber == room && r.bedNumber == bed) {
            return r.status;
        }
    }
    return "not found";
}