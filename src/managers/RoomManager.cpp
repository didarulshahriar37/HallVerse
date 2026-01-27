#include "RoomManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
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

vector<RoomManager::Room> RoomManager::searchAvailableBeds(const string& hall, 
                                                                 const string& room) {
    vector<Room> results;
    
    for (const auto& r : rooms) {
        if (r.status == "free") {
            if (!hall.empty() && r.hallName != hall) continue;
            if (!room.empty() && r.roomNumber != room) continue;
            results.push_back(r);
        }
    }
    
    return results;
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

string RoomManager::getBedStatus(const string& hall, const string& room, 
                                       const string& bed) {
    for (const auto& r : rooms) {
        if (r.hallName == hall && r.roomNumber == room && r.bedNumber == bed) {
            return r.status;
        }
    }
    return "not found";
}