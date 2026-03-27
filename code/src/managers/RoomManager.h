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
    // Constructor: load room data from CSV
    RoomManager();

    // Load rooms from file into memory
    void loadRooms();

    // Update status of one specific bed (Occupied/Vacant)
    void updateBedStatus(const string& hall, const string& room, const string& bed, const string& status);

    // Add rooms and beds in bulk to the inventory
    void addRooms(const string& hall, int startRoom, int endRoom);

    // Find available beds optionally filtered by hall and/or room
    vector<Room> searchAvailableBeds(const string& hall = "", const string& room = "");

    // Get list of rooms with at least one free bed
    vector<string> getAvailableRooms(const string& hall);

    // Get specific available bed letters within a room
    vector<string> getAvailableBeds(const string& hall, const string& room);

    // Print bed availability table filtered by hall/room
    void displayBedAvailability(const string& hall, const string& room = "");

    // Display all rooms and bed states
    void displayAllBeds();

    // Display beds matching a specific status (Occupied/Vacant)
    void displayBedsByStatus(const string& statusFilter);

    // Return status string for one bed
    string getBedStatus(const string& hall, const string& room, const string& bed);
};
#endif