#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

struct Customer {
    int id;
    string name;
    string phone;
};

struct Package {
    int id;
    string name;
    string destination;
    double price;
};

struct Booking {
    int id;
    int customerId;
    int packageId;
    int travelers;
    double totalCost;
};

const int MAX = 50;
Customer customers[MAX];
Package packages[MAX];
Booking bookings[MAX];

int custCount = 0, pkgCount = 0, bookCount = 0;
int nextCustId = 1, nextPkgId = 1, nextBookId = 1;

// Function declarations
void mainMenu();
void addCustomer();
void viewCustomers();
void addPackage();
void viewPackages();
void makeBooking();
void viewBookings();
void loadData();
void saveData();
void pause();

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void loadData() {
    // Load customers
    ifstream cf("customers.txt");
    if (cf.is_open()) {
        while (custCount < MAX && cf >> customers[custCount].id) {
            cf.ignore();
            getline(cf, customers[custCount].name, ',');
            getline(cf, customers[custCount].phone);
            if (customers[custCount].id >= nextCustId)
                nextCustId = customers[custCount].id + 1;
            custCount++;
        }
        cf.close();
    }

    // Load packages
    ifstream pf("packages.txt");
    if (pf.is_open()) {
        while (pkgCount < MAX && pf >> packages[pkgCount].id) {
            pf.ignore();
            getline(pf, packages[pkgCount].name, ',');
            getline(pf, packages[pkgCount].destination, ',');
            pf >> packages[pkgCount].price;
            pf.ignore();
            if (packages[pkgCount].id >= nextPkgId)
                nextPkgId = packages[pkgCount].id + 1;
            pkgCount++;
        }
        pf.close();
    }

    // Load bookings
    ifstream bf("bookings.txt");
    if (bf.is_open()) {
        while (bookCount < MAX && bf >> bookings[bookCount].id) {
            bf.ignore();
            bf >> bookings[bookCount].customerId;
            bf.ignore();
            bf >> bookings[bookCount].packageId;
            bf.ignore();
            bf >> bookings[bookCount].travelers;
            bf.ignore();
            bf >> bookings[bookCount].totalCost;
            bf.ignore();
            if (bookings[bookCount].id >= nextBookId)
                nextBookId = bookings[bookCount].id + 1;
            bookCount++;
        }
        bf.close();
    }
}

void saveData() {
    // Save customers
    ofstream cf("customers.txt");
    for (int i = 0; i < custCount; i++) {
        cf << customers[i].id << "," << customers[i].name << ","
            << customers[i].phone << endl;
    }
    cf.close();

    // Save packages
    ofstream pf("packages.txt");
    for (int i = 0; i < pkgCount; i++) {
        pf << packages[i].id << "," << packages[i].name << ","
            << packages[i].destination << "," << packages[i].price << endl;
    }
    pf.close();

    // Save bookings
    ofstream bf("bookings.txt");
    for (int i = 0; i < bookCount; i++) {
        bf << bookings[i].id << "," << bookings[i].customerId << ","
            << bookings[i].packageId << "," << bookings[i].travelers << ","
            << bookings[i].totalCost << endl;
    }
    bf.close();
}

void addCustomer() {
    if (custCount >= MAX) {
        cout << "Customer limit reached!" << endl;
        pause();
        return;
    }

    Customer c;
    c.id = nextCustId++;

    cout << "\n=== ADD CUSTOMER ===" << endl;
    cout << "Customer ID: " << c.id << " (auto)" << endl;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, c.name);
    cout << "Enter Phone: ";
    getline(cin, c.phone);

    customers[custCount++] = c;
    saveData();

    cout << "\nCustomer added successfully!" << endl;
    pause();
}

void viewCustomers() {
    cout << "\n=== ALL CUSTOMERS ===" << endl;
    if (custCount == 0) {
        cout << "No customers found." << endl;
    }
    else {
        cout << left << setw(8) << "ID" << setw(25) << "Name"
            << setw(15) << "Phone" << endl;
        cout << string(48, '-') << endl;
        for (int i = 0; i < custCount; i++) {
            cout << left << setw(8) << customers[i].id
                << setw(25) << customers[i].name
                << setw(15) << customers[i].phone << endl;
        }
    }
    pause();
}

void addPackage() {
    if (pkgCount >= MAX) {
        cout << "Package limit reached!" << endl;
        pause();
        return;
    }

    Package p;
    p.id = nextPkgId++;

    cout << "\n=== ADD PACKAGE ===" << endl;
    cout << "Package ID: " << p.id << " (auto)" << endl;
    cout << "Enter Package Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Destination: ";
    getline(cin, p.destination);
    cout << "Enter Price (per person): ";
    cin >> p.price;

    packages[pkgCount++] = p;
    saveData();

    cout << "\nPackage added successfully!" << endl;
    pause();
}

void viewPackages() {
    cout << "\n=== ALL PACKAGES ===" << endl;
    if (pkgCount == 0) {
        cout << "No packages found." << endl;
    }
    else {
        cout << left << setw(8) << "ID" << setw(25) << "Name"
            << setw(20) << "Destination" << setw(12) << "Price" << endl;
        cout << string(65, '-') << endl;
        cout << fixed << setprecision(2);
        for (int i = 0; i < pkgCount; i++) {
            cout << left << setw(8) << packages[i].id
                << setw(25) << packages[i].name
                << setw(20) << packages[i].destination
                << "Rs " << packages[i].price << endl;
        }
    }
    pause();
}

void makeBooking() {
    if (bookCount >= MAX) {
        cout << "Booking limit reached!" << endl;
        pause();
        return;
    }

    if (custCount == 0) {
        cout << "No customers available. Add customers first." << endl;
        pause();
        return;
    }

    if (pkgCount == 0) {
        cout << "No packages available. Add packages first." << endl;
        pause();
        return;
    }

    Booking b;
    b.id = nextBookId++;

    cout << "\n=== NEW BOOKING ===" << endl;
    cout << "Booking ID: " << b.id << " (auto)" << endl;

    // Show customers
    cout << "\nAvailable Customers:" << endl;
    cout << left << setw(8) << "ID" << setw(25) << "Name" << endl;
    cout << string(33, '-') << endl;
    for (int i = 0; i < custCount; i++) {
        cout << left << setw(8) << customers[i].id
            << setw(25) << customers[i].name << endl;
    }

    cout << "\nEnter Customer ID: ";
    cin >> b.customerId;

    bool validCust = false;
    for (int i = 0; i < custCount; i++) {
        if (customers[i].id == b.customerId) {
            validCust = true;
            break;
        }
    }

    if (!validCust) {
        cout << "Invalid Customer ID!" << endl;
        pause();
        return;
    }

    // Show packages
    cout << "\nAvailable Packages:" << endl;
    cout << left << setw(8) << "ID" << setw(25) << "Name"
        << setw(20) << "Destination" << setw(12) << "Price" << endl;
    cout << string(65, '-') << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < pkgCount; i++) {
        cout << left << setw(8) << packages[i].id
            << setw(25) << packages[i].name
            << setw(20) << packages[i].destination
            << "Rs " << packages[i].price << endl;
    }

    cout << "\nEnter Package ID: ";
    cin >> b.packageId;

    double pkgPrice = 0;
    bool validPkg = false;
    for (int i = 0; i < pkgCount; i++) {
        if (packages[i].id == b.packageId) {
            validPkg = true;
            pkgPrice = packages[i].price;
            break;
        }
    }

    if (!validPkg) {
        cout << "Invalid Package ID!" << endl;
        pause();
        return;
    }

    cout << "Enter Number of Travelers: ";
    cin >> b.travelers;

    b.totalCost = pkgPrice * b.travelers;

    cout << "\nTotal Cost: Rs " << fixed << setprecision(2)
        << b.totalCost << endl;

    bookings[bookCount++] = b;
    saveData();

    cout << "\nBooking created successfully!" << endl;
    pause();
}

void viewBookings() {
    cout << "\n=== ALL BOOKINGS ===" << endl;
    if (bookCount == 0) {
        cout << "No bookings found." << endl;
    }
    else {
        cout << left << setw(8) << "ID" << setw(20) << "Customer"
            << setw(20) << "Package" << setw(12) << "Travelers"
            << setw(15) << "Total Cost" << endl;
        cout << string(75, '-') << endl;
        cout << fixed << setprecision(2);

        for (int i = 0; i < bookCount; i++) {
            string custName = "Unknown";
            string pkgName = "Unknown";

            for (int j = 0; j < custCount; j++) {
                if (customers[j].id == bookings[i].customerId) {
                    custName = customers[j].name;
                    break;
                }
            }

            for (int j = 0; j < pkgCount; j++) {
                if (packages[j].id == bookings[i].packageId) {
                    pkgName = packages[j].name;
                    break;
                }
            }

            cout << left << setw(8) << bookings[i].id
                << setw(20) << custName
                << setw(20) << pkgName
                << setw(12) << bookings[i].travelers
                << "Rs " << bookings[i].totalCost << endl;
        }
    }
    pause();
}

void mainMenu() {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "   TRAVEL MANAGEMENT SYSTEM" << endl;
        cout << "========================================" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. View All Customers" << endl;
        cout << "3. Add Package" << endl;
        cout << "4. View All Packages" << endl;
        cout << "5. Make Booking" << endl;
        cout << "6. View All Bookings" << endl;
        cout << "0. Exit" << endl;
        cout << "========================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addCustomer(); break;
        case 2: viewCustomers(); break;
        case 3: addPackage(); break;
        case 4: viewPackages(); break;
        case 5: makeBooking(); break;
        case 6: viewBookings(); break;
        case 0: cout << "\nThank you for using the system!" << endl; break;
        default:
            cout << "Invalid choice!" << endl;
            pause();
        }
    } while (choice != 0);
}

int main() {
    loadData();

    cout << "\n========================================" << endl;
    cout << "      WELCOME TO TRAVEL SYSTEM" << endl;
    cout << "========================================" << endl;

    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "admin" && password == "admin") {
        cout << "\nLogin Successful!" << endl;
        mainMenu();
    }
    else {
        cout << "\nInvalid credentials!" << endl;
    }

    return 0;
}