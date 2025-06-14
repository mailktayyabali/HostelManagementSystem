#ifndef ROOM_MANAGEMENT_H
#define ROOM_MANAGEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Database/json.hpp" // JSON header
#include "StudentManagement.h"

using namespace std;
using json = nlohmann::json;

class Room {
public:
    int roomId;
    string roomType;
    int capacity;
    vector<int> occupants;

    bool isAvailable() const {
        return occupants.size() < capacity;
    }

    json toJson() const {
        return json{
            {"roomId", roomId},
            {"roomType", roomType},
            {"capacity", capacity},
            {"occupants", occupants}
        };
    }

    void fromJson(const json& j) {
        roomId = j.at("roomId").get<int>();
        roomType = j.at("roomType").get<string>();
        capacity = j.at("capacity").get<int>();
        occupants = j.at("occupants").get<vector<int>>();
    }
};

class RoomMinHeap {
private:
    vector<Room*> heap;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void push(Room* room);
    void rebuild();
    Room* top();
    void clear();
    vector<Room*>& getHeap();
    bool empty() const;
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
    void saveRoomsToFile(const string& filename);
    void loadRoomsFromFile(const string& filename);
    void updateRoomInFile(const string& filename, int roomId);
    void deleteRoomFromFile(const string& filename, int roomId);

private:
    vector<Room*> rooms;
    StudentManagement& studentManager;
    RoomMinHeap roomHeap;
};

#endif // ROOM_MANAGEMENT_H
