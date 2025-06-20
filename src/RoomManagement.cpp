#include "Room.h"

void RoomMinHeap::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)]->occupants.size() > heap[index]->occupants.size()) {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

void RoomMinHeap::heapifyDown(int index) {
    int smallest = index;
    int l = left(index);
    int r = right(index);

    if (l < heap.size() && heap[l]->occupants.size() < heap[smallest]->occupants.size())
        smallest = l;
    if (r < heap.size() && heap[r]->occupants.size() < heap[smallest]->occupants.size())
        smallest = r;

    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

void RoomMinHeap::push(Room* room) {
    heap.push_back(room);
    heapifyUp(heap.size() - 1);
}

void RoomMinHeap::rebuild() {
    for (int i = heap.size() / 2 - 1; i >= 0; i--)
        heapifyDown(i);
}

Room* RoomMinHeap::top() {
    return heap.empty() ? nullptr : heap[0];
}

void RoomMinHeap::clear() {
    heap.clear();
}

vector<Room*>& RoomMinHeap::getHeap() {
    return heap;
}

bool RoomMinHeap::empty() const {
    return heap.empty();
}

RoomManagement::RoomManagement(StudentManagement& smRef) : studentManager(smRef) {}

void RoomManagement::addRoom(Room* room) {
    if (exists(room->roomId)) {
        cout << "Room already exists!" << endl;
        return;
    }
    rooms.push_back(room);
    roomHeap.push(room);
    cout << "Room added successfully!" << endl;
}

void RoomManagement::deleteRoom(int roomId) {
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i]->roomId == roomId) {
            delete rooms[i];
            rooms.erase(rooms.begin() + i);
            roomHeap.clear();
            for (Room* r : rooms) roomHeap.push(r);
            cout << "Room deleted successfully!" << endl;
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

            if (find(room->occupants.begin(), room->occupants.end(), studentId) != room->occupants.end()) {
                cout << "Student already assigned to this room." << endl;
                return;
            }

            room->occupants.push_back(studentId);
            roomHeap.clear();
            for (Room* r : rooms) roomHeap.push(r);
            cout << "Student assigned to room!" << endl;
            return;
        }
    }

    cout << "Room not found!" << endl;
}

void RoomManagement::removeStudentFromRoom(int roomId, int studentId) {
    for (Room* room : rooms) {
        if (room->roomId == roomId) {
            auto it = find(room->occupants.begin(), room->occupants.end(), studentId);
            if (it != room->occupants.end()) {
                room->occupants.erase(it);
                roomHeap.clear();
                for (Room* r : rooms) roomHeap.push(r);
                cout << "Student removed from room!" << endl;
            } else {
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

    cout << "======================================================" << endl;
    cout << "                      Room List" << endl;
    cout << "======================================================" << endl;
    RoomMinHeap tempHeap = roomHeap;

    while (!tempHeap.empty()) {
        Room* room = tempHeap.top();
        tempHeap.getHeap()[0] = tempHeap.getHeap().back();
        tempHeap.getHeap().pop_back();
        tempHeap.rebuild();

        cout << "Room ID:   | " << room->roomId << endl;
        cout << "Type:      | " << room->roomType << endl;
        cout << "Capacity:  | " << room->capacity << endl;
        cout << "Occupied:  | " << room->occupants.size() << "/" << room->capacity << endl;
        cout << "Occupants: | ";
        for (int id : room->occupants) cout << id << " ";
        cout << "======================================================" << endl;
    }
}

bool RoomManagement::exists(int roomId) const {
    for (const Room* room : rooms) {
        if (room->roomId == roomId) return true;
    }
    return false;
}

void RoomManagement::saveRoomsToFile(const string& filename) {
    json jArray = json::array();
    for (const Room* room : rooms) jArray.push_back(room->toJson());

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << jArray.dump(4);
        outFile.close();
        cout << "Rooms saved to " << filename << endl;
    } else {
        cout << "Failed to save rooms!" << endl;
    }
}

void RoomManagement::loadRoomsFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "No saved room data found." << endl;
        return;
    }

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (const auto& j : jArray) {
        Room* room = new Room();
        room->fromJson(j);
        rooms.push_back(room);
        roomHeap.push(room);
    }

    cout << "Rooms loaded from " << filename << endl;
}

// 🔥 Update room record in file
void RoomManagement::updateRoomInFile(const string& filename, int roomId) {
    ifstream inFile(filename);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (auto& j : jArray) {
        if (j["roomId"] == roomId) {
            for (Room* r : rooms) {
                if (r->roomId == roomId) {
                    j = r->toJson();
                    break;
                }
            }
            break;
        }
    }

    ofstream outFile(filename);
    outFile << setw(4) << jArray;
    outFile.close();
    cout << "Room " << roomId << " updated in file." << endl;
}

// 🔥 Delete room record from file
void RoomManagement::deleteRoomFromFile(const string& filename, int roomId) {
    ifstream inFile(filename);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    json updatedArray = json::array();
    for (const auto& j : jArray) {
        if (j["roomId"] != roomId)
            updatedArray.push_back(j);
    }

    ofstream outFile(filename);
    outFile << setw(4) << updatedArray;
    outFile.close();
    cout << "Room " << roomId << " removed from file." << endl;
}
