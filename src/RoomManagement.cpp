#include "Room.h"

RoomManagement::RoomManagement(StudentManagement& smRef) : studentManager(smRef) {}

void RoomManagement::addRoom(Room* room) {
    if (exists(room->roomId)) {
        cout << "Room already exists!" << endl;
        return;
    }
    rooms.push_back(room);
    roomHeap.push(room); // Add to min heap
    cout << "Room added successfully!" << endl;
}

void RoomManagement::deleteRoom(int roomId) {
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i]->roomId == roomId) {
            delete rooms[i];
            rooms.erase(rooms.begin() + i);
            cout << "Room deleted successfully!" << endl;

            // Rebuild min heap after deletion
            roomHeap.clear();
            for (Room* r : rooms) {
                roomHeap.push(r);
            }

            return;
        }
    }
    cout << "Room not found!" << endl;
}

void RoomManagement::assignStudentToRoom(int roomId, int studentId) {
    if (!studentManager.exists(studentId)) {
        cout << "Cannot assign: Student ID " << studentId << " is not registered!" << endl;
        return;
    }

    for (Room* room : rooms) {
        if (room->roomId == roomId) {
            if (!room->isAvailable()) {
                cout << "Room is full!" << endl;
                return;
            }

            // Check if student is already in the room
            for (int id : room->occupants) {
                if (id == studentId) {
                    cout << "Student already assigned to this room." << endl;
                    return;
                }
            }

            room->occupants.push_back(studentId);
            cout << "Student assigned to room!" << endl;

            // Rebuild the heap since occupancy has changed
            roomHeap.clear();
            for (Room* r : rooms) {
                roomHeap.push(r);
            }

            return;
        }
    }

    cout << "Room not found!" << endl;
}

void RoomManagement::removeStudentFromRoom(int roomId, int studentId) {
    for (Room* room : rooms) {
        if (room->roomId == roomId) {
            bool found = false;
            for (size_t i = 0; i < room->occupants.size(); ++i) {
                if (room->occupants[i] == studentId) {
                    room->occupants.erase(room->occupants.begin() + i);
                    cout << "Student removed from room!" << endl;
                    found = true;

                    // Rebuild heap after occupancy update
                    roomHeap.clear();
                    for (Room* r : rooms) {
                        roomHeap.push(r);
                    }

                    break;
                }
            }
            if (!found) {
                cout << "Student not found in room!" << endl;
            }
            return;
        }
    }

    cout << "Room not found!" << endl;
}

void RoomManagement::viewRooms() {
    if (rooms.empty()) {
        cout << "No rooms available." << endl;
        return;
    }

    // Optional: View rooms in increasing order of occupancy using Min Heap
    cout << "--- Rooms (Sorted by Least Occupied) ---" << endl;
    RoomMinHeap tempHeap = roomHeap; // make a copy to avoid modifying original

    while (!tempHeap.empty()) {
        Room* room = tempHeap.top();
        tempHeap.getHeap()[0] = tempHeap.getHeap().back();
        tempHeap.getHeap().pop_back();
        tempHeap.rebuild();

        cout << "Room ID: " << room->roomId << endl;
        cout << "Type: " << room->roomType << endl;
        cout << "Capacity: " << room->capacity << endl;
        cout << "Occupied: " << room->occupants.size() << "/" << room->capacity << endl;
        cout << "Occupants: ";
        for (int id : room->occupants) {
            cout << id << " ";
        }
        cout << endl << "------------------------" << endl;
    }
}

bool RoomManagement::exists(int roomId) const {
    for (const Room* room : rooms) {
        if (room->roomId == roomId) {
            return true;
        }
    }
    return false;
}
