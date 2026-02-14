#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <string>
#include <vector>

using namespace std;

class RoomManager {
private:
    struct Room {
        string hallName;
        string roomNumber;
        string bedNumber;
        string status;
    };

    vector<Room> rooms;
    
    vector<string> split(const string& str, char delimiter);
public:
    RoomManager();
    void loadRooms();
    void updateBedStatus(const string& hall, const string& room, const string& bed, const string& status);
    vector<Room> searchAvailableBeds(const string& hall = "", const string& room = "");
    void displayBedAvailability(const string& hall, const string& room = "");
    void displayAllBeds();
    string getBedStatus(const string& hall, const string& room, const string& bed);
};
#endif