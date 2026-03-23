// Student Name: Obadiah Goodnews Chukwu
// School Project


#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct Passenger {
    string route; // S, L, C
    int boarding_time;
};

void processTaxiData(const string& fileName);

int main() {
    string fileName = "C:\\Data\\taxiData.txt"; // To make sure the file path is correct
    try {
        processTaxiData(fileName);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}

void processTaxiData(const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw runtime_error("Could not open file: " + fileName);
    }

    queue<Passenger> shortDistanceQueue;
    queue<Passenger> longDistanceQueue;
    queue<Passenger> cityRouteQueue;

    int timeStep = 0;  // Time step counter
    string line;

    // Header for the table format
    cout << setw(4) << "T" << setw(10) << "next" << setw(8) << "S" << setw(8) << "L" << setw(8) << "C"
        << setw(10) << "WQS" << setw(10) << "WQL" << setw(10) << "WQC"
        << setw(8) << "CS" << setw(8) << "CL" << setw(8) << "CC" << endl;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string timeCount, route, boardingTime;
        getline(ss, timeCount, ',');
        getline(ss, route, ',');
        getline(ss, boardingTime);

        Passenger newPassenger = { route, stoi(boardingTime) };

        // Putiing the new passenger on queue based on their route type
        if (route == "S") {
            shortDistanceQueue.push(newPassenger);
        }
        else if (route == "L") {
            longDistanceQueue.push(newPassenger);
        }
        else if (route == "C") {
            cityRouteQueue.push(newPassenger);
        }

        // Checking if taxi is full before departure (5 passengers)
        if (shortDistanceQueue.size() > 5) {
            shortDistanceQueue.pop();  // Taxi departure after it is full
        }
        if (longDistanceQueue.size() > 5) {
            longDistanceQueue.pop();
        }
        if (cityRouteQueue.size() > 5) {
            cityRouteQueue.pop();
        }

        // Calculate the waiting queues
        int waitingQS = max(0, (int)shortDistanceQueue.size() - 1);
        int waitingQL = max(0, (int)longDistanceQueue.size() - 1);
        int waitingQC = max(0, (int)cityRouteQueue.size() - 1);

        // Calculate the remaining space in the taxi (capacity)
        int taxiCap_S = max(0, 5 - (int)shortDistanceQueue.size());
        int taxiCap_L = max(0, 5 - (int)longDistanceQueue.size());
        int taxiCap_C = max(0, 5 - (int)cityRouteQueue.size());

        // Print the output of each time step in a table format
        cout << setw(4) << timeStep++
            << setw(10) << timeCount + " " + route + "(" + boardingTime + ")"
            << setw(8) << shortDistanceQueue.size()
            << setw(8) << longDistanceQueue.size()
            << setw(8) << cityRouteQueue.size()
            << setw(10) << waitingQS
            << setw(10) << waitingQL
            << setw(10) << waitingQC
            << setw(8) << taxiCap_S
            << setw(8) << taxiCap_L
            << setw(8) << taxiCap_C << endl;
    }
    inputFile.close();
}
