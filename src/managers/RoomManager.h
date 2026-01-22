#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <string>
#include <vector>

class RoomManager {
private:
    struct Room {
        std::string hallName;
        std::string roomNumber;
        std::string bedNumber;
        std::string status;
    };

    std::vector<Room> rooms;
    
    std::vector<std::string> split(const std::string& str, char delimiter);
public:
    RoomManager();
    void loadRooms();
    void updateBedStatus(const std::string& hall, const std::string& room, const std::string& bed, const std::string& status);
    std::vector<Room> searchAvailableBeds(const std::string& hall = "", const std::string& room = "");
    void displayBedAvailability(const std::string& hall, const std::string& room = "");
    void displayAllBeds();
    std::string getBedStatus(const std::string& hall, const std::string& room, const std::string& bed);
};
#endif