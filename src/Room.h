#ifndef ROOM_MANAGEMENT_H
#define ROOM_MANAGEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include "StudentManagement.h"

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

// ✅ Custom Min Heap to maintain least-occupied room ordering
class RoomMinHeap {
private:
    vector<Room*> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)]->occupants.size() > heap[index]->occupants.size()) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
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

public:
    void push(Room* room) {
        heap.push_back(room);
        heapifyUp(heap.size() - 1);
    }

    void rebuild() {
        for (int i = heap.size() / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    Room* top() {
        if (heap.empty()) return nullptr;
        return heap[0];
    }

    void clear() {
        heap.clear();
    }

    vector<Room*>& getHeap() {
        return heap;
    }

    bool empty() const {
        return heap.empty();
    }
};

class RoomManagement {
public:
    RoomManagement(StudentManagement& smRef);

    void addRoom(Room* room);
    void deleteRoom(int roomId);
    void assignStudentToRoom(int roomId, int studentId);  // manual assignment
    void removeStudentFromRoom(int roomId, int studentId);
    void viewRooms();
    bool exists(int roomId) const;

private:
    vector<Room*> rooms;
    StudentManagement& studentManager;
    RoomMinHeap roomHeap; // ✅ used internally to manage least-filled room ordering
};

#endif // ROOM_MANAGEMENT_H
