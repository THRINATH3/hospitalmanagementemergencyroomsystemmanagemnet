#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Patient {
public:
    string name;
    int age;
    char gender;
    string address;
    string guardian;
    string disease;
    int roomNumber;

    Patient(string name, int age, char gender, string address, string guardian, string disease)
        : name(name), age(age), gender(gender), address(address), guardian(guardian), disease(disease), roomNumber(-1) {}

    bool operator<(const Patient& other) const {
        if ((other.disease == "cancer") && (disease != "cancer"))
            return true;
        else if ((other.disease == "kidney disease") && (disease != "cancer") && (disease != "kidney disease"))
            return true;
        else if ((other.disease == "liver disease") && (disease != "cancer") && (disease != "kidney disease") && (disease != "liver disease"))
            return true;
        else if ((other.disease == "stomach pain") && (disease != "cancer") && (disease != "kidney disease") && (disease != "liver disease") && (disease != "stomach pain"))
            return true;
        return false;
    }
};

class Room {
public:
    Patient patient;
    Room* next;

    Room(Patient p) : patient(p), next(nullptr) {}
};

class RoomList {
private:
    Room* head;
    int totalRooms;
    int maxRooms;

public:
    RoomList(int maxRooms) : head(nullptr), totalRooms(0), maxRooms(maxRooms) {}

    void addRoom(Patient& patient) {
        if (totalRooms >= maxRooms) {
            cout << "All rooms are full.sorry for not allocation of room to you" << endl;
            return;
        }
        Room* newRoom = new Room(patient);
        if (!head)
        {
            head = newRoom;
        }
        else
        {
            Room* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newRoom;
        }
        totalRooms++;
    }
    void displayRooms()
    {
        int roomNumber = 0;
        Room* temp = head;
        while (temp) {
            cout << "-------------------------" << endl;
            cout << "Room Number: " << roomNumber << endl;
            cout << "Name: " << temp->patient.name << endl;
            cout << "Age: " << temp->patient.age << endl;
            cout << "Gender: " << temp->patient.gender << endl;
            cout << "Address: " << temp->patient.address << endl;
            cout << "Guardian: " << temp->patient.guardian << endl;
            cout << "Disease: " << temp->patient.disease << endl;
            cout << "-------------------------" << endl;
            temp->patient.roomNumber = roomNumber;
            temp = temp->next;
            roomNumber++;
        }
    }
};

int main()
 {
    int numRooms;
    cout << "Enter number of rooms: ";
    cin >> numRooms;

    priority_queue<Patient> patientqueue;
    RoomList roomList(numRooms);

    auto addPatient = [&](string name, int age, char gender, string address, string guardian, string disease) {
        Patient patient(name, age, gender, address, guardian, disease);
        patientqueue.push(patient);
    };

    int numPatients;
    cout << "Enter number of patients: ";
    cin >> numPatients;
    cin.ignore();

    for (int i = 0; i < numPatients; i++) {
        string name, address, guardian, disease;
        int age;
        char gender;

        cout << "Enter details for patient " << i + 1 << ":" << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Age: ";
        cin >> age;
        cout << "Gender (M/F): ";
        cin >> gender;
        cout << "Address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Guardian: ";
        getline(cin, guardian);
        cout << "Disease: ";
        getline(cin, disease);
        addPatient(name, age, gender, address, guardian, disease);
    }

    while (!patientqueue.empty()) {
        Patient patient = patientqueue.top();
        patientqueue.pop();
        roomList.addRoom(patient);
    }

    roomList.displayRooms();
    return 0;
}
