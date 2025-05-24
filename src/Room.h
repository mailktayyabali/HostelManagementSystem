#ifndef ROOM_MANAGEMENT_H
#define ROOM_MANAGEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include "StudentManagement.h" // Link with Student system

using namespace std;

class Room {
public:
    int roomId;
    string roomType;  // "Single" or "Shared"
    int capacity;
    vector<int> occupants;

    bool isAvailable() const {
        return occupants.size() < capacity;
    }
};

class RoomManagement {
public:
    RoomManagement(StudentManagement& smRef);

    void addRoom(Room* room);
    void deleteRoom(int roomId);
    void assignStudentToRoom(int roomId, int studentId);
    void removeStudentFromRoom(int roomId, int studentId);
    void viewRooms();
    bool exists(int roomId) const;

private:
    vector<Room*> rooms;
    StudentManagement& studentManager;
};

#endif // ROOM_MANAGEMENT_H
