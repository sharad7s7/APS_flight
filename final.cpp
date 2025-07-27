#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <string>
#include <sstream>
#include <iomanip>
#include <climits>
#include <limits>
#include <cstring>
#include <cassert>
#include <bitset>
using namespace std;  
const int PASSWORD = 123;
const int INF = numeric_limits<int>::max();
const int AIRPORTS = 5;

string airportNames[AIRPORTS] = {"DELHI", "MUMBAI", "CHENNAI", "KOLKATA", "BENGALURU"};
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
void printBanner(const string& title) {
    cout << "\n=====================================" << endl;
    cout << "     " << title << endl;
    cout << "=====================================\n" << endl;
}

void printLine() {
    cout << "-------------------------------------\n";
}

// ------------------- HOTEL BOOKING SYSTEM -------------------
class Guest {
public:
    string name;
    int id;
    int roomNumber;
    string checkInTime;
    Guest() {}
    Guest(string n, int i, int r, string time) : name(n), id(i), roomNumber(r), checkInTime(time) {}
};

unordered_map<int, Guest> guestMap;
unordered_map<int, bool> roomAvailability;
vector<int> allRooms = {101, 102, 103, 201, 202, 301, 302};

// ------------------- TIME HELPER -------------------
string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

// ------------------- GREEDY ROOM ALLOCATION -------------------
int allocateRoom() {
    for (int room : allRooms) {
        if (!roomAvailability[room]) {
            roomAvailability[room] = true;
            return room;
        }
    }
    return -1;
}

// ------------------- BACKTRACKING FOR VIP UPGRADE -------------------
bool vipUpgrade(vector<int>& rooms, int index, int target, vector<int>& path) {
    if (target == 0) return true;
    if (index >= rooms.size() || target < 0) return false;
    path.push_back(rooms[index]);
    if (vipUpgrade(rooms, index + 1, target - rooms[index], path)) return true;
    path.pop_back();
    return vipUpgrade(rooms, index + 1, target, path);
}

// ------------------- DYNAMIC PROGRAMMING FOR DISCOUNT SCHEDULING -------------------
int dpSchedule(vector<int>& discounts) {
    int n = discounts.size();
    if (n == 0) return 0;
    if (n == 1) return discounts[0];
    vector<int> dp(n+1, 0);
    dp[1] = discounts[0];
    for (int i = 2; i <= n; ++i) {
        dp[i] = max(dp[i-1], dp[i-2] + discounts[i-1]);
    }
    return dp[n];
}

// ------------------- CHECK-IN -------------------
void checkIn() {
    printBanner("Guest Check-In");
    string name;
    int id;
    cout << "Enter guest name: ";
    cin >> name;
    cout << "Enter guest ID: ";
    cin >> id;

    if (guestMap.find(id) != guestMap.end()) {
        cout << "Guest with this ID already exists.\n";
        return;
    }

    int room = allocateRoom();
    if (room == -1) {
        cout << "No rooms available for " << name << endl;
        return;
    }

    string checkInTime = getCurrentTime();
    guestMap[id] = Guest(name, id, room, checkInTime);
    cout << name << " checked into room " << room << " at " << checkInTime << endl;
    printLine();
}

// ------------------- CHECK-OUT -------------------
void checkOut() {
    printBanner("Guest Check-Out");
    int id;
    cout << "Enter guest ID to check out: ";
    cin >> id;

    if (guestMap.find(id) == guestMap.end()) {
        cout << "Guest not found.\n";
        return;
    }
    int room = guestMap[id].roomNumber;
    roomAvailability[room] = false;
    cout << guestMap[id].name << " checked out from room " << room << endl;
    guestMap.erase(id);
    printLine();
}

// ------------------- DISPLAY GUEST LIST -------------------
void displayGuests() {
    printBanner("Current Guest List");
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Room" << "Check-in Time" << endl;
    printLine();
    for (auto& entry : guestMap) {
        cout << left << setw(10) << entry.first << setw(15) << entry.second.name << setw(10) << entry.second.roomNumber << entry.second.checkInTime;
    }
    printLine();
}

// ------------------- DISPLAY ROOM STATUS -------------------
void displayRooms() {
    printBanner("Room Availability");
    for (int room : allRooms) {
        cout << "Room " << room << ": " << (roomAvailability[room] ? "Occupied" : "Available") << endl;
    }
    printLine();
}

// ------------------- DISPLAY HELP -------------------
void displayHelp() {
    printBanner("Help Menu");
    cout << "1: Book a room for a new guest.\n";
    cout << "2: Check out a guest using their ID.\n";
    cout << "3: View list of currently checked-in guests.\n";
    cout << "4: View room availability status.\n";
    cout << "5: Try VIP room upgrades.\n";
    cout << "6: Calculate best combination of discounts.\n";
    cout << "0: Exit the system.\n";
    printLine();
}
struct passenger
{
    char name[20];
    int age;
    int adh;
};

struct dataq {
    int trainno;
    float fare;
};

//data
// Greedy: Assign the lowest available seat number to each passenger
vector<int> assignSeatsGreedy(int numPassengers, vector<int>& availableSeats) {
    sort(availableSeats.begin(), availableSeats.end());
    vector<int> assignedSeats;
    for(int i = 0; i < numPassengers && i < (int)availableSeats.size(); ++i) {
        assignedSeats.push_back(availableSeats[i]);
    }
    return assignedSeats;
}

// DP: Minimum fare to reach the last station (example fares)
int minFareDP(const vector<int>& fares) {
    int n = fares.size();
    vector<int> dp(n, INT_MAX);
    dp[0] = fares[0];
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            if(dp[j] != INT_MAX)
                dp[i] = min(dp[i], dp[j] + fares[i]);
        }
    }
    return dp[n-1];
}

// Searching: Binary search for a train number in sorted train list
int binarySearchTrain(const vector<dataq>& trains, int trainno) {
    int left = 0, right = (int)trains.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(trains[mid].trainno == trainno) return mid;
        else if(trains[mid].trainno < trainno) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Sorting: Bubble sort trains by fare
void bubbleSortByFare(vector<dataq>& trains) {
    int n = (int)trains.size();
    for(int i = 0; i < n-1; ++i) {
        for(int j = 0; j < n-i-1; ++j) {
            if(trains[j].fare > trains[j+1].fare) {
                swap(trains[j], trains[j+1]);
            }
        }
    }
}

// Function definitions translated from C to C++
int reservation1()
{
    char a[20],b[20];
    // Use std::vector for dynamic array of structs
    vector<dataq> s(15); // Note: C code used s[1] to s[14], C++ vector is 0-indexed. Adjusting loop and access.
    int c,d,i;

    // Initialize train data (Indices 1 to 14 as in C)
    // C++ vectors are 0-indexed, so size 15 means indices 0-14.
    // We will populate indices 1-14 to match the C logic exactly.
    for(i=1; i<=14; i++)
    {
        s[i].trainno = rand() % 100000 + 1;
        s[i].fare = rand() % 10000 + 1;
    }

    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\n                                                                            WELCOME TO RAILWAY RESERVATION                            \n";
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\nPLEASE ENTER THE NUMBER OF PASSENGERS :-";
    cin >> d;

    // Use std::vector for dynamic array of passengers
    vector<passenger> st(d); // Creates a vector of size d

    cout << "\nPLEASE ENTER BOARDING PLACE :- ";
    cin >> a; // Reads into char array a
    cout << "\nPLEASE ENTER THE DESTINATION:- ";
    cin >> b; // Reads into char array b
    cout << "\nENTER THE DATE :- ";
    cin >> c;

    // Sort trains by fare before displaying (Sorting algorithm)
    bubbleSortByFare(s);

    cout << "\n TRAINS AVAILABLE ARE ";
    cout << "\n----------------------";
    cout << "\n\nTRAIN NUMBER            TRAIN NAME                  DATE                DURATION                  FARE     SEAT AVAILIBILITY ";

    // Display first 7 trains (indices 1 to 7)
    for(i=1; i<=7; i++) {
        cout << "\n\n" << s[i].trainno << "                  TRAIN " << i << "                  " << c << "/11/2023          2 HOUR " << (10 + i*5) << " MINUTES           " << s[i].fare << "              " << rand()%10+1;
    }

    int df;
    cout << "\n\nIF YOU WANT TO BOOK A TICKET PLEASE PRESS 1 OR 0 TO EXIT :-";
    cin >> df;

    // Exit if user chooses 0
    if (df == 0) {
        cout << "\nExiting reservation process.\n";
        return 0; // Exit the function
    }

    int f,e,g,h = 0,sa,fd,far = 0,fj; // Initialize h and far
    cout << "\nPLEASE ENTER THE TRAIN NUMBER YOU WANT TO BOOK :- ";
    cin >> f;

    h = d * s[0].fare;
    far = h;

    cout << "\nDO YOU WANT A RETURN TICKET IF YES PLEASE ENTER 1 OR 0 FOR NO :- ";
    cin >> e;

    if(e == 1) {
        cout << "\nPLEASE ENTER THE RETURNING DATE ";
        cin >> g;
        cout << "\n TRAINS AVAILABLE ARE ";
        cout << "\n----------------------";
        cout << "\n\nTRAIN NUMBER            TRAIN NAME                  DATE                DURATION                  FARE     ";

        // Display trains 8 to 14 for return
        for(i=8; i<=14; i++) {
            cout << "\n\n" << s[i].trainno << "                  TRAIN " << i << "                  " << g << "/11/2023          2 HOUR " << (10 + (i-7)*5) << " MINUTES           " << s[i].fare << "       ";
        }

        cout << "\n\nPLEASE ENTER THE TRAIN NUMBER YOU WANT TO BOOK :- ";
        cin >> sa;

        // Add return fare
        h = h + d * s[0].fare;

        // Get passenger details
        for(i=0; i<d; i++)
        {
            cout << "\nENTER THE NAME OF " << i+1 << " PASSENGER :- ";
            cin >> st[i].name; // Read into char array in struct
            cout << "\n\nENTER THE AGE OF " << i+1 << " PASSENGER :- ";
            cin >> st[i].age;
            cout << "\n\nENTER THE ADHAAR NUMBER OF " << i+1 << " PASSENGER :- ";
            cin >> st[i].adh;
        }

        // Greedy seat assignment example
        vector<int> availableSeats = {1,2,3,4,5,6,7,8,9,10};
        vector<int> assignedSeats = assignSeatsGreedy(d, availableSeats);
        cout << "\n\nAssigned seats (Greedy): ";
        for(int seat : assignedSeats) cout << seat << " ";
        cout << "\n";

        cout << "\n\nNAME                  AGE                 ADHAAR NUMBER ";
        for(i=0; i<d; i++)
        {
            cout << "\n\n" << st[i].name << "                    " << st[i].age << "                  " << st[i].adh;
        }

        // Dynamic Programming example: minimum fare calculation from fares of first 7 trains
        vector<int> fares;
        for(i=1; i<=7; ++i) fares.push_back(s[i].fare);
        int minFare = minFareDP(fares);
        cout << "\n\nMinimum possible fare (DP) for route: " << minFare;

        float gs = (h * 18.0) / 100.0; // Use 18.0 for floating point division
        cout << "\n\nTAX ON THE TICKET IS " << gs;
        cout << "\n\n******************************************";
        cout << "\n*  YOUR TOTAL FARE IS " << h << " + " << gs << " = " << h + gs << " ";
        cout << "\n******************************************";
        cout << "\nPRESS 1 WHEN YOU COMPLETED THE PAYMENT ";
        cin >> fd;
        if(fd == 1) {
            cout << "\n\n\n   PAYMENT RECEIVED ";
            cout << "\n\nYOUR PNR NUMBER IS " << rand() % 1000000 + 1;
        } else {
             cout << "\n\nPayment not confirmed. Booking cancelled.\n";
             return 0; // Exit if payment not confirmed
        }
    }
    else // No return ticket
    {
        // Get passenger details
        for(i=0; i<d; i++)
        {
            cout << "\nENTER THE NAME OF " << i+1 << " PASSENGER :- ";
            cin >> st[i].name; // Read into char array in struct
            cout << "\n\nENTER THE AGE OF " << i+1 << " PASSENGER :- ";
            cin >> st[i].age;
            cout << "\n\nENTER THE ADHAAR NUMBER OF " << i+1 << " PASSENGER :- ";
            cin >> st[i].adh;
        }

        // Greedy seat assignment example
        vector<int> availableSeats = {1,2,3,4,5,6,7,8,9,10};
        vector<int> assignedSeats = assignSeatsGreedy(d, availableSeats);
        cout << "\n\nAssigned seats (Greedy): ";
        for(int seat : assignedSeats) cout << seat << " ";
        cout << "\n";

        cout << "\n\nNAME                  AGE                 ADHAAR NUMBER ";
        for(i=0; i<d; i++)
        {
            cout << "\n" << st[i].name << "                    " << st[i].age << "                  " << st[i].adh;
        }

        // Dynamic Programming example: minimum fare calculation from fares of first 7 trains
        vector<int> fares;
        for(i=1; i<=7; ++i) fares.push_back(s[i].fare);
        int minFare = minFareDP(fares);
        cout << "\n\nMinimum possible fare (DP) for route: " << minFare;

        float gs1 = (far * 18.0) / 100.0; // Use far (one-way fare) and 18.0
        cout << "\n\nTAX ON THE TICKET IS " << gs1; // Added newline
        cout << "\n\n******************************************";
        cout << "\n* YOUR TOTAL FARE IS " << 2300 << " + " << gs1 << " = " << h + gs1 << " *";
        cout << "\n******************************************";
        cout << "\nPRESS 1 WHEN YOU COMPLETED THE PAYMENT ";
        cin >> fj;

        if (fj == 1) { // Check if payment is completed
            cout << "\n   PAYMENT RECEIVED \n";
            cout << "\nYOUR PNR NUMBER IS " << rand() % 1000000 + 1 << " \n\n";
        } else {
             cout << "\n\nPayment not confirmed. Booking cancelled.\n";
             return 0; // Exit if payment not confirmed
        }
        cout << "\n\n\nFOR ANY FURTHER ENQUIRY PLEASE CONTACT 325323222";
    }

    cout << "\n\n                                                                           --------------------------------                           \n"; // Added newline for spacing
    cout << "\n                                                                             HAVE A SAFE JOURNEY 🤗🤗🤗🤗                           \n";
    cout << "\n                                                                           --------------------------------                           \n";
    return 0;
}

int status()
{
    int a;
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\n                                                                                   CHECK PNR STATUS                             \n";
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\nPLEASE ENTER YOU PNR NUMBER :- ";
    cin >> a;
    if(a % 3 == 0)
    {
        cout << "\n\nYOUR TICKET IS STILL NOT CONFIRMED AND IS AT WAITING NUMBER " << rand() % 10 + 1;
    }
    else if(a % 7 == 0)
    {
        cout << "\n\nYOUR TICKET IS STILL CANCELLED DUE TO CANCELLATION OF TRAIN";
    }
    else
    {
        cout << "\n\nYOUR TICKET IS CONFIRMED AND IT IS SCHEDULED IN " << rand() % 10 + 1 << " HOURS ";
    }
    cout << "\n\n\nFOR ANY FURTHER ENQUIRY PLEASE CONTACT 325323222";
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\n                                                                             HAVE A SAFE JOURNEY 🤗🤗🤗🤗                           \n";
    cout << "\n                                                                           --------------------------------                           \n";
    return 0;
}

int trainstatus()
{
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\n                                                                                  CHECK TRAIN STATUS                             \n";
    cout << "\n                                                                           --------------------------------                           \n";
    int a;
    cout << "\nENTER THE TRAIN NUMBER :- ";
    cin >> a;
    if(a % 3 == 0)
    {
        cout << "\n\nTRAIN NUMBER\t\t\t\t\tTRAIN NAME\t\t\t\t\tRUNNING STATUS\t\t\t\t\tLAST STATION";
        cout << "\n\n" << a << "\t\t\t\t\t\tAJMER EXPRESS\t\t\t\t\tLATE BY " << rand() % 10 + 1 << "HRS\t\t\t\t\tAGRA";
    }
    else if(a % 7 == 0)
    {
        cout << "\n\nTRAIN NUMBER\t\t\t\t\tTRAIN NAME\t\t\t\t\tRUNNING STATUS\t\t\t\t\tLAST STATION";
        cout << "\n\n" << a << "\t\t\t\t\t\tSHATABDI EXPRESS\t\t\t\t\tEARLY BY " << rand() % 10 + 1 << "HRS\t\t\t\t\tAJMER";
    }
    else
    {
        cout << "\n\nTRAIN NUMBER\t\t\t\t\tTRAIN NAME\t\t\t\t\tRUNNING STATUS\t\t\t\t\tLAST STATION";
        cout << "\n\n" << a << "\t\t\t\t\t\tRAJHDANI EXPRESS\t\t\t\t\tON TIME \t\t\t\t\tGHAZIABAD";
    }
    cout << "\n\n\nFOR ANY FURTHER ENQUIRY PLEASE CONTACT 325323222";
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\n                                                                             HAVE A SAFE JOURNEY 🤗🤗🤗🤗                           \n";
    cout << "\n                                                                           --------------------------------                           \n";
    return 0;
}

int modify()
{
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\n                                                                                 MODIFY TRAIN TICKET                             \n";
    cout << "\n                                                                           --------------------------------                           \n";
    int a,b,f,g,x;
    cout << "\nENTER 1 FOR MODIFYING TICKET ";
    cout << "\n\nENTER 0 FOR CANCELLING THE TICKET ";
    cout << "\n\nENTER YOUR CHOICE :- ";
    cin >> a;
    if(a == 1)
    {
        cout << "\nENTER THE PNR NUMBER :- ";
        cin >> b;
        int c, d = rand() % 10 + 1; // Ensure date is at least 1
        int e = rand() % 10000 + 1;
        cout << "\nAS PER TICKET THE CURRENT RESERVATION DATE IS " << d << "/11/2023 ";
        cout << "\n\nENTER THE NEW DATE FOR BOARDING :- ";
        cin >> c;
        if(c - d >= 5)
        {
            cout << "\n\n AS THE CHANGE IN DAYS IS MORE THAN 5 HENCE 20 PERCENT OF FARE WILL BE CHARGED ";
            cout << "\n\n PRESS 1 TO CONTINUE ";
            cin >> f;
            if(f == 1)
            {
                cout << "\nNEW DATE IS " << c << "/11/2023 ";
                cout << "\n\nYOUR NEW FARE IS " << e + (e / 5); // Integer division matches C behavior
                cout << "\nPLEASE PAY THE EXTRA FARE WITHIN 2 WORKING DAYS OR ELSE TICKET WILL BE CANCELLED "; // Added newline
                cout << "\n\nYOUR UPDATED TICKET WILL BE MAILED TO YOUR GMAIL ACCOUNT AFTER PAYMENT";
            } else {
                 cout << "\nModification cancelled.\n";
            }
        }
        else if (c > d) // Only charge if the new date is later, handle c<=d case? Original didn't.
        {
            cout << "\n\n AS THE CHANGE IN DAYS IS LESS THAN 5 HENCE 50 PERCENT OF FARE WILL BE CHARGED ";
            cout << "\n\n PRESS 1 TO CONTINUE ";
            cin >> g;
            if(g == 1)
            {
                cout << "\nNEW DATE IS " << c << "/11/2023 ";
                cout << "\n\nYOUR NEW FARE IS " << e + (e / 2); // Integer division matches C behavior
                cout << "\nPLEASE PAY THE EXTRA FARE WITHIN 2 WORKING DAYS OR ELSE TICKET WILL BE CANCELLED "; // Added newline
                cout << "\n\nYOUR UPDATED TICKET WILL BE MAILED TO YOUR GMAIL ACCOUNT AFTER PAYMENT";
            } else {
                 cout << "\nModification cancelled.\n";
            }
        }
         else { // c <= d case
             cout << "\nNew date must be later than the current date. Modification cancelled.\n";
         }
    }
    else if (a == 0) // Check specifically for 0 for cancellation
    {
        int pn, dx = rand() % 10000 + 1;
        cout << "\nENTER THE PNR NUMBER :- ";
        cin >> pn;
        cout << "\nAS PER THE TERMS AND CONDITIONS THE CANCELLATION OF TICKET WILL ONLY REFUND 50 PERCENT OF THE FARE ";
        cout << "\n\nPRESS 1 TO CONTINUE ";
        cin >> x;
        if(x == 1)
        {
            cout << "\nYOUR TICKET HAS BEEN SUCCESSFULLY CANCELED ";
            cout << "\n\nYOUR REFUND OF AMOUNT " << (dx / 2) << " WILL BE CREDITED IN YOUR ACCOUNT WITH 4-5 WORKING DAYS "; // Integer division
        } else {
             cout << "\nCancellation aborted.\n";
        }
    } else {
        cout << "\nInvalid choice.\n";
    }
    return 0;
}

int query()
{
    int a;
    int d = rand() % 100000 + 1;
    // Use larger char arrays as in C, potential buffer overflow exists if input is larger
    char b[100], c_query[100]; // Renamed c to c_query to avoid conflict with char c[10] in train()
    cout << "\nENTER 1 FOR COMPLAINT ";
    cout << "\n\nENTER 2 FOR QUERY ";
    cin >> a;
    if(a == 1)
    {
        cout << "\nPLEASE ENTER YOUR COMPLAINT :- ";
        cin >> b;
        cout << "\nYOUR COMPLAINT WILL BE RESOLVED WITHIN 2 WORKING DAYS ";
        cout << "\n\nYOUR COMPLAIN TOKEN IS " << d;
    }
    else if(a == 2)
    {
        cout << "\nPLEASE ENTER YOUR QUERY :- ";
        cin >> c_query;
        cout << "\nYOUR QUERY WILL BE ANSWERED WITHIN 2 WORKING DAYS ";
        cout << "\n\nYOUR QUERY TOKEN IS " << d;
    } else {
        cout << "\nInvalid choice.\n";
    }
    return 0;
}

int train()
{
    
    srand(time(0));

    char b[20],c[10];
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\n                                                                              WELCOME TO RAILWAY SERVICES                            \n";
    cout << "\n                                                                           --------------------------------                           \n";
    cout << "\n\nWe're thrilled to have you here. Whether you're a first-time visitor or a returning friend, we extend a warm welcome to our online home.\n";
    cout << "\n\nLOGIN TO YOUR ACCOUNT \n";
    cout << "\nEMAIL ID :- ";
    cin >> b; // Reads into char array b
    cout << "\nPASSWORD :- ";
    cin >> c; // Reads into char array c
    cout << "\n\nYOU HAVE SUCCESSFULLY LOGGED IN ";
    cout << "\n\nPRESS 1 FOR TRAIN RESERVATION \n";
    cout << "\nPRESS 2 FOR CHECKING YOUR PNR STATUS \n";
    cout << "\nPRESS 3 FOR TRAIN RUNNING STATUS \n";
    cout << "\nPRESS 4 FOR TRAIN TICKET MODIFFICATION AND CANCELLATION \n";
    cout << "\nPRESS 5 FOR COMPLAINTS OR QUERY";
    int a;
    cout << "\n\nPLEASE ENTER YOUR CHOICE :- ";
    cin >> a;
    if(a == 1)
    {
        reservation1();
    }
    else if(a == 2)
    {
        status();
    }
    else if(a == 3)
    {
        trainstatus();
    }
    else if(a == 4)
    {
        modify();
    }
    else if(a == 5)
    {
        query();
    }
     else {
        cout << "\nInvalid choice. Exiting.\n"; // Handle invalid choice
    }
    return 0;
}

struct User {
    string username;
    string password;
};

struct Bus {
    string busNumber;
    string origin;
    string destination;
    int departureHour;
    int departureMinute;
    int seatsAvailable;
};

class BusSystem {
    vector<User> users;
    vector<Bus> buses;
    vector<string> stops;
    vector<vector<int>> graph;
    map<string, vector<string>> bookings;
    string loggedInUser;

public:
    void registerUser() {
        string uname, pass;
        cout << "Enter new username: ";
        cin >> uname;
        cout << "Enter new password: ";
        cin >> pass;
        for (auto& u : users) {
            if (u.username == uname) {
                cout << "Username already exists.\n";
                return;
            }
        }
        users.push_back({uname, pass});
        cout << "Registration successful.\n";
    }

    bool loginUser() {
        string uname, pass;
        cout << "Enter username: ";
        cin >> uname;
        cout << "Enter password: ";
        cin >> pass;
        for (auto& u : users) {
            if (u.username == uname && u.password == pass) {
                loggedInUser = uname;
                cout << "Login successful.\n";
                return true;
            }
        }
        cout << "Invalid credentials.\n";
        return false;
    }

    void addBus(Bus bus) {
        buses.push_back(bus);
    }

    void setupStops(vector<string> s) {
        stops = s;
        graph = vector<vector<int>>(s.size(), vector<int>(s.size(), 0));
    }

    void addRoute(string from, string to, int dist) {
        int i = getIndex(from), j = getIndex(to);
        if (i != -1 && j != -1) {
            graph[i][j] = dist;
            graph[j][i] = dist;
        }
    }

    void displayBuses() {
        for (auto& b : buses) {
            cout << "Bus No: " << b.busNumber << ", From: " << b.origin
                 << ", To: " << b.destination << ", Departure: "
                 << b.departureHour << ":" << b.departureMinute
                 << ", Seats: " << b.seatsAvailable << endl;
        }
    }

    void selectionSortByDeparture() {
        int n = buses.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < n; ++j) {
                if (timeCompare(buses[j], buses[minIdx]))
                    minIdx = j;
            }
            swap(buses[i], buses[minIdx]);
        }
    }

    bool timeCompare(Bus& a, Bus& b) {
        if (a.departureHour != b.departureHour)
            return a.departureHour < b.departureHour;
        return a.departureMinute < b.departureMinute;
    }

    void searchBus(string busNumber) {
        selectionSortByNumber();
        int index = binarySearch(busNumber);
        if (index == -1)
            cout << "Bus not found.\n";
        else {
            Bus& b = buses[index];
            cout << "Found - Bus No: " << b.busNumber << ", From: " << b.origin
                 << ", To: " << b.destination << ", Departure: "
                 << b.departureHour << ":" << b.departureMinute
                 << ", Seats: " << b.seatsAvailable << endl;
        }
    }

    void selectionSortByNumber() {
        int n = buses.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < n; ++j) {
                if (buses[j].busNumber < buses[minIdx].busNumber)
                    minIdx = j;
            }
            swap(buses[i], buses[minIdx]);
        }
    }

    int binarySearch(string busNumber) {
        int l = 0, r = buses.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (buses[m].busNumber == busNumber)
                return m;
            else if (buses[m].busNumber < busNumber)
                l = m + 1;
            else
                r = m - 1;
        }
        return -1;
    }

    void dijkstra(string start, string end) {
        int n = stops.size();
        vector<int> dist(n, numeric_limits<int>::max());
        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        int src = getIndex(start), dst = getIndex(end);
        dist[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, src});
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (visited[u]) continue;
            visited[u] = true;
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    pq.push({dist[v], v});
                    parent[v] = u;
                }
            }
        }
        if (dist[dst] == numeric_limits<int>::max()) {
            cout << "No route found.\n";
            return;
        }
        vector<string> path;
        for (int at = dst; at != -1; at = parent[at])
            path.push_back(stops[at]);
        reverse(path.begin(), path.end());
        cout << "Shortest path (" << dist[dst] << " km): ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }

    int getIndex(string name) {
        for (int i = 0; i < stops.size(); ++i)
            if (stops[i] == name) return i;
        return -1;
    }

    void bookTicket(string busNumber) {
        int idx = binarySearch(busNumber);
        if (idx == -1 || buses[idx].seatsAvailable <= 0) {
            cout << "Bus not available.\n";
            return;
        }
        buses[idx].seatsAvailable--;
        bookings[loggedInUser].push_back(busNumber);
        cout << "Ticket booked successfully.\n";
    }

    void viewMyBookings() {
        if (bookings[loggedInUser].empty()) {
            cout << "No bookings found.\n";
            return;
        }
        cout << "Your Booked Buses:\n";
        for (auto& b : bookings[loggedInUser]) {
            cout << b << endl;
        }
    }
};
void busMaster(){
    cout << "\n===========================================================\n";
    cout << "         WELCOME TO METRO BUS SYSTEM!        \n";
    cout << "=============================================\n";
    cout << "     Efficient | Reliable | Convenient       \n";
    cout << "---------------------------------------------\n";
    cout << "  Book your journey across Delhi NCR with us!\n";
    cout << "=============================================\n\n";
    
    BusSystem system;
    system.setupStops({"Delhi", "Noida", "Meerut", "Rewari", "Ghaziabad"});

    system.addRoute("Delhi", "Noida", 5);
    system.addRoute("Noida", "Meerut", 7);
    system.addRoute("Meerut", "Rewari", 4);
    system.addRoute("Rewari", "Ghaziabad", 6);
    system.addRoute("Delhi", "Meerut", 10);
    system.addRoute("Noida", "Rewari", 8);
    
    system.addBus({"B101", "Delhi", "Noida", 9, 30, 10});
    system.addBus({"B102", "Noida", "Meerut", 10, 15, 8});
    system.addBus({"B103", "Meerut", "Rewari", 11, 45, 12});
    system.addBus({"B104", "Delhi", "Rewari", 12, 20, 6});
    system.addBus({"B105", "Rewari", "Ghaziabad", 14, 0, 7});

  
    int choice;
    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose: ";
        cin >> choice;
        if (choice == 1) {
            system.registerUser();
        } else if (choice == 2) {
            if (!system.loginUser()) continue;
            int opt;
            while (true) {
                cout << "\n--- User Dashboard ---\n";
                cout << "1. View Buses\n2. Search Bus\n3. Sort by Departure\n";
                cout << "4. Book Ticket\n5. View Bookings\n6. Shortest Route\n7. Logout\nChoose: ";
                cin >> opt;
                if (opt == 1) system.displayBuses();
                else if (opt == 2) {
                    string bno; cout << "Enter Bus Number: "; cin >> bno;
                    system.searchBus(bno);
                }
                else if (opt == 3) {
                    system.selectionSortByDeparture();
                    system.displayBuses();
                }
                else if (opt == 4) {
                    string bno; cout << "Enter Bus Number to Book: "; cin >> bno;
                    system.bookTicket(bno);
                }
                else if (opt == 5) system.viewMyBookings();
                else if (opt == 6) {
                    string src, dst;
                    cout << "From: "; cin >> src;
                    cout << "To: "; cin >> dst;
                    system.dijkstra(src, dst);
                }
                else if (opt == 7) break;
                else cout << "Invalid option.\n";
            }
        } else if (choice == 3) break;
        else cout << "Invalid choice.\n";
    }
   }

   void hotelMaster(){
    int choice;
    printBanner(" Hotel Booking ");

    do {
        cout << "\n1. Book a Room\n2. Check Out\n3. Display Guest List\n4. Display Room Status\n5. VIP Upgrade\n6. Calculate Discounts\n7. Help\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                checkIn();
                break;
            case 2:
                checkOut();
                break;
            case 3:
                displayGuests();
                break;
            case 4:
                displayRooms();
                break;
            case 5: {
                vector<int> prices = {50, 100, 150};
                vector<int> upgradePath;
                cout << "\nVIP Upgrade for 150: ";
                if (vipUpgrade(prices, 0, 150, upgradePath)) {
                    for (int p : upgradePath) cout << p << " ";
                    cout << endl;
                } else cout << "No upgrade path found\n";
                break;
            }
            case 6: {
                vector<int> discountOptions = {10, 20, 30, 40};
                int maxDiscount = dpSchedule(discountOptions);
                cout << "\nMaximum Discount Value: " << maxDiscount << endl;
                break;
            }
            case 7:
                displayHelp();
                break;
            case 0:
                printBanner("Exiting system. Goodbye!");
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
   }
  
   void flightMaster(){
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
   }


int main() {

    cout << setw(70) << "===============================================\n";
    cout << setw(70) << "         WELCOME TO TRAVEL MANAGEMENT SYSTEM   \n";
    cout << setw(70) << "===============================================\n";
    cout << setw(70) << "          Your Journey, Our Responsibility      \n";
    cout << setw(70) << "-----------------------------------------------\n";
    cout << setw(70) << "         Flights    Hotels    Buses    Trains      \n";
    cout << setw(70) << "-----------------------------------------------\n";
    cout << setw(70) << "   Explore. Book. Travel — All in one place!   \n";
    cout << setw(70) << "===============================================\n";

    cout << "\n\nReady to begin your adventure? Let's go!\n\n";

    cout<<"WELCOME TO TARVELLING MANAGEMENT SYSTEM "<<endl;
    int choiceMain;
    while(true){
        cout << "\n 1.Hotel Booking\n2. Train Booking\n3. Bus Booking \n4. Flight Booking \nChoose: ";
        cin>>choiceMain;
        if(choiceMain==1){
         hotelMaster();
        }
        if(choiceMain==2){
            train();
        }
        if(choiceMain==3){
           busMaster();
        }
        if(choiceMain==4){
         flightMaster();
        }
        else {
            cout<<"Enter the correct NUMBER ..";
        }
    }

    return 0;
}
 