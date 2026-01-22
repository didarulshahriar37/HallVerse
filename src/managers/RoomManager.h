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
};
#endif