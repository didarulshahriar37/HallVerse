#include "RoomManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

RoomManager::RoomManager() {
    loadRooms();
}

std::vector<std::string> RoomManager::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void RoomManager::loadRooms() {
    rooms.clear();
    std::ifstream file("data/rooms.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening rooms.csv\n";
        return;
    }
    
    std::string line;
    bool isHeader = true;
    
    while (std::getline(file, line)) {
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

void RoomManager::updateBedStatus(const std::string& hall, const std::string& room, 
                                   const std::string& bed, const std::string& status) {
    for (auto& r : rooms) {
        if (r.hallName == hall && r.roomNumber == room && r.bedNumber == bed) {
            r.status = status;
            break;
        }
    }
    
    // Write back to CSV
    std::ofstream file("data/rooms.csv");
    if (!file.is_open()) {
        std::cerr << "Error writing to rooms.csv\n";
        return;
    }
    
    file << "hallName,roomNumber,bedNumber,status\n";
    for (const auto& r : rooms) {
        file << r.hallName << "," << r.roomNumber << "," << r.bedNumber << "," << r.status << "\n";
    }
    
    file.close();
}

std::vector<RoomManager::Room> RoomManager::searchAvailableBeds(const std::string& hall, 
                                                                 const std::string& room) {
    std::vector<Room> results;
    
    for (const auto& r : rooms) {
        if (r.status == "free") {
            if (!hall.empty() && r.hallName != hall) continue;
            if (!room.empty() && r.roomNumber != room) continue;
            results.push_back(r);
        }
    }
    
    return results;
}
void RoomManager::displayBedAvailability(const std::string& hall, const std::string& room) {
    std::cout << "\n========== Bed Availability Report ==========\n";
    std::cout << "Hall: " << (hall.empty() ? "All" : hall) << " | ";
    std::cout << "Room: " << (room.empty() ? "All" : room) << "\n";
    std::cout << "=============================================\n";
    
    std::cout << std::left << std::setw(10) << "Hall" 
              << std::setw(10) << "Room" 
              << std::setw(8) << "Bed" 
              << "Status\n";
    std::cout << "---------------------------------------------\n";
    
    for (const auto& r : rooms) {
        if (!hall.empty() && r.hallName != hall) continue;
        if (!room.empty() && r.roomNumber != room) continue;
        
        std::cout << std::left << std::setw(10) << r.hallName 
                  << std::setw(10) << r.roomNumber 
                  << std::setw(8) << r.bedNumber 
                  << r.status << "\n";
    }
    
    std::cout << "=============================================\n";
}

void RoomManager::displayAllBeds() {
    displayBedAvailability("", "");
}

std::string RoomManager::getBedStatus(const std::string& hall, const std::string& room, 
                                       const std::string& bed) {
    for (const auto& r : rooms) {
        if (r.hallName == hall && r.roomNumber == room && r.bedNumber == bed) {
            return r.status;
        }
    }
    return "not found";
}