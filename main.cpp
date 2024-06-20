#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

class Room {
public:
    int roomNumber;
    std::string host;
    std::time_t startTime;
    std::time_t endTime;
    int chairCapacity;

    // Default constructor
    Room() : roomNumber(-1), host(""), startTime(0), endTime(0), chairCapacity(0) {}

    // Parameterized constructor
    Room(int number, const std::string &hostName, std::time_t start, std::time_t end, int chairs)
        : roomNumber(number), host(hostName), startTime(start), endTime(end), chairCapacity(chairs) {}
};

class RoomManager {
private:
    std::unordered_map<int, Room> rooms;

public:
    void bookRoom(int roomNumber, const std::string &host, std::time_t start, std::time_t end, int chairCapacity) {
        if (rooms.find(roomNumber) != rooms.end()) {
            std::cout << "Room " << roomNumber << " is already booked.\n";
        } else {
            rooms[roomNumber] = Room(roomNumber, host, start, end, chairCapacity);
            std::cout << "Room " << roomNumber << " booked successfully.\n";
        }
    }

    void checkRoomStatus(int roomNumber) {
        if (rooms.find(roomNumber) != rooms.end()) {
            Room &room = rooms[roomNumber];
            std::cout << "Room " << roomNumber << " is booked by " << room.host << ".\n";
            std::cout << "Start time: " << std::put_time(std::localtime(&room.startTime), "%F %T") << "\n";
            std::cout << "End time: " << std::put_time(std::localtime(&room.endTime), "%F %T") << "\n";
            std::cout << "Chair capacity: " << room.chairCapacity << "\n";
        } else {
            std::cout << "Room " << roomNumber << " is available.\n";
        }
    }
};

std::time_t parseTime(const std::string &timeStr) {
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::mktime(&tm);
}

int main() {
    RoomManager manager;
    int choice;
    do {
        std::cout << "1. Book a room\n";
        std::cout << "2. Check room status\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int roomNumber, chairCapacity;
            std::string host, startStr, endStr;
            std::cout << "Enter room number: ";
            std::cin >> roomNumber;
            std::cin.ignore();
            std::cout << "Enter host name: ";
            std::getline(std::cin, host);
            std::cout << "Enter start time (YYYY-MM-DD HH:MM:SS): ";
            std::getline(std::cin, startStr);
            std::cout << "Enter end time (YYYY-MM-DD HH:MM:SS): ";
            std::getline(std::cin, endStr);
            std::cout << "Enter chair capacity: ";
            std::cin >> chairCapacity;

            std::time_t startTime = parseTime(startStr);
            std::time_t endTime = parseTime(endStr);

            manager.bookRoom(roomNumber, host, startTime, endTime, chairCapacity);
            break;
        }
        case 2: {
            int roomNumber;
            std::cout << "Enter room number: ";
            std::cin >> roomNumber;
            manager.checkRoomStatus(roomNumber);
            break;
        }
        case 3:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
