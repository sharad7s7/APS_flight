#include <bits/stdc++.h>
using namespace std;

const int PASSWORD = 123;
const int INF = numeric_limits<int>::max();
const int AIRPORTS = 5;

string airportNames[AIRPORTS] = {"DELHII", "MUMBAI", "CHENNAI", "KOLKATA", "BENGALURU"};
unordered_map<string, int> airportIndex = {
    {"DELHI", 0}, {"MUMBAI", 1}, {"CHENNAI", 2}, {"KOLKATA", 3}, {"BENGALURU", 4}
};

int fareGraph[AIRPORTS][AIRPORTS] = {
    {0,3000,9000,4000,3500},
    {3000,0,4500,3000,2000}, 
    {9000,4500,0,1000,2800}, 
    {4000,3000,1000,0,4000}, 
    {3500,2000,2800,4000,0}
};

class Passenger {
public:
    string passport;
    string name;
    long long number;
    string mail;
    int seat;
};

class FlightInfo {
public:
    int fno;
    int fare;
};

class Complaint {
public:
    string user;
    string complaintText;
    int token;
};

void intro() {
    cout << "\t***********************************************************************************\n";
    cout << "\t*                             WELCOME TO MAKE MY DAY                              *\n";
    cout << "\t***********************************************************************************\n";
}

void inface() {
    cout << "\n\n\n |---> Please enter your choices from 1-4\n\n ";
    cout << " 1. RESERVATION\n";
    cout << " 2. CANCEL RESERVATION\n";
    cout << " 3. COMPLAINT\n";
    cout << " 4. QUIT\n\n";
    cout << "\t-----------------------------------------\n";
    cout << "\t\tFEEL FREE TO CONTACT\n\t\tCONTACT NUMBER: 8882747035\n";
    cout << "\t-----------------------------------------\n";
}

void hppj() {
    cout << "\t################################################################\n";
    cout << "\t#                                                              #\n";
    cout << "\t#                        HAPPY JOURNEY                         #\n";
    cout << "\t#                                                              #\n";
    cout << "\t################################################################\n";
}

void tickcan() {
    cout << "\t################################################################\n";
    cout << "\t#                                                              #\n";
    cout << "\t#               TICKETS CANCELLED SUCCESSFULLY                 #\n";
    cout << "\t#                                                              #\n";
    cout << "\t################################################################\n";
}

void dijkstra(int start, int end, vector<int>& path, int& cost) {
    vector<int> dist(AIRPORTS, INF), prev(AIRPORTS, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int curr = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        for (int i = 0; i < AIRPORTS; i++) {
            if (fareGraph[curr][i] && d + fareGraph[curr][i] < dist[i]) {
                dist[i] = d + fareGraph[curr][i];
                prev[i] = curr;
                pq.push({dist[i], i});
            }
        }
    }

    cost = dist[end];
    for (int at = end; at != -1; at = prev[at])
        path.insert(path.begin(), at);
}

void reservation() {
    int pass, date, book = 0, month, password;
    string airport, dest, user;

    cout << "\nLOGIN TO YOUR ACCOUNT:\n";
    cout << "Enter user name: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> password;

    if (password == PASSWORD) {
        cout << "\n\n\t\t\t\t\t\t\t\t\t RESERVATION\n\n\n";
        Passenger c[10];
        cout << "Enter number of passengers: ";
        cin >> pass;
        cout << "Enter date: ";
        cin >> date;
        cout << "Enter month: ";
        cin >> month;
        cout << "Enter nearest airport (DELHI/MUMBAI/CHENNAI/KOLKATA/BENGALURU): ";
        cin >> airport;
        cout << "Enter destination (DELHI/MUMBAI/CHENNAI/KOLKATA/BENGALURU): ";
        cin >> dest;

        if (airportIndex.count(airport) == 0 || airportIndex.count(dest) == 0) {
            cout << "Invalid airport name.\n";
            return;
        }

        vector<int> path;
        int cost;
        dijkstra(airportIndex[airport], airportIndex[dest], path, cost);

        cout << "\nCheapest Route from " << airport << " to " << dest << ":\n";
        for (int i = 0; i < path.size(); i++) {
            cout << airportNames[path[i]];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal Fare per person: " << cost << "\nTotal Fare for " << pass << " passengers: " << cost * pass << "\n";

        cout << "\nDo you want to book tickets? (1 = Yes, 0 = No): ";
        cin >> book;

        if (book == 1) {
            for (int i = 0; i < pass; i++) {
                cout << "Passenger " << i + 1 << " Name: ";
                cin >> c[i].name;
                cout << "Passport: ";
                cin >> c[i].passport;
                cout << "Contact Number: ";
                cin >> c[i].number;
                cout << "Email: ";
                cin >> c[i].mail;
                cout << "Seat: ";
                cin >> c[i].seat;
            }
            cout << "\nBooking successful!\n";
            hppj();
        } else {
            cout << "\nThanks for visiting!\n";
        }
    } else {
        cout << "\t\t\t\t\t\t\t\tWRONG PASSWORD!!!!!\n";
    }
}

void cancel() {
    int date, month, pass, password;
    string airport, dest, user;

    cout << "\nLOGIN TO YOUR ACCOUNT:\n";
    cout << "Enter user name: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> password;

    if (password == PASSWORD) {
        Passenger c[10];
        cout << "\n\n\t\t\t\t\t\t\t\t\t CANCEL\n\n\n";
        cout << "Enter details of booked tickets.\n\n";
        cout << "Enter date: ";
        cin >> date;
        cout << "Enter month: ";
        cin >> month;
        cout << "Enter boarding place: ";
        cin >> airport;
        cout << "Enter destination: ";
        cin >> dest;

        cout << "Enter number of passengers: ";
        cin >> pass;
        for (int i = 0; i < pass; i++) {
            cout << "Passenger " << i + 1 << " Name: ";
            cin >> c[i].name;
            cout << "Passport: ";
            cin >> c[i].passport;
        }
        tickcan();
    } else {
        cout << "\t\t\t\t\t\t\t\tWRONG PASSWORD!!!!!\n";
    }
}

void complaint() {
    Complaint comp;
    int password;
    srand(time(0));
    comp.token = rand() % 100000;

    cout << "LOGIN TO YOUR ACCOUNT:\n";
    cout << "Enter user name: ";
    cin >> comp.user;
    cout << "Enter password: ";
    cin >> password;

    if (password == PASSWORD) {
        cout << "\n\n\t\t\t\t\t\t\t\t\t COMPLAINT\n";
        cout << "We sincerely apologize for the inconvenience that has caused you.\n";
        cout << "Create your complaint here: ";
        cin.ignore();
        getline(cin, comp.complaintText);

        cout << "Your complaint will be resolved within 24 hours.\n";
        cout << "Your complaint token code is " << comp.token << "\n";
        cout << "\t\t\t\t\tTHANKS FOR VISITING\n";
    } else {
        cout << "\t\t\t\t\tWRONG PASSWORD!!!\n";
    }
}

int main() {
    intro();
    int choice;
    do {
        inface();
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: reservation(); break;
            case 2: cancel(); break;
            case 3: complaint(); break;
            case 4: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
    return 0;
}
