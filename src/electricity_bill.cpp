/*
 * ============================================================
 *  ELECTRICITY BILL CALCULATOR
 * ============================================================
 *  Project    : Electricity Bill Calculator
 *  Author     : Ayush Sharma
 *  Course     : BCA (Bachelor of Computer Applications)
 *  Subject    : Object-Oriented Programming (OOP) in C++
 *  University : Chandigarh University
 *
 *  NOTE: The electricity tariff rates used in this project
 *        are SAMPLE EDUCATIONAL RATES only. They do not
 *        represent any official government or utility tariff.
 * ============================================================
 *
 *  OOP CONCEPTS DEMONSTRATED:
 *  1. Classes and Objects
 *  2. Encapsulation (private data, public methods)
 *  3. Data Hiding
 *  4. Constructors (default + parameterized)
 *  5. Member Functions
 *  6. Inheritance (BillCalculator inherits from Customer)
 *  7. Function Overriding (virtual + override)
 *  8. Polymorphism (virtual functions)
 *
 *  STANDARD LIBRARIES USED:
 *  iostream  - for console input/output
 *  string    - for string data handling
 *  fstream   - for file read/write
 *  iomanip   - for output formatting (setw, fixed, precision)
 *  vector    - for storing multiple customer records
 *  limits    - for clearing invalid cin input
 *  sstream   - for string stream conversion
 * ============================================================
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

// ============================================================
// CONSTANTS - Tariff Rates (Sample Educational Rates Only)
// ============================================================
const double RATE_SLAB1     = 3.0;   // Rs. 3/unit  for   0-100 units
const double RATE_SLAB2     = 5.0;   // Rs. 5/unit  for 101-200 units
const double RATE_SLAB3     = 7.0;   // Rs. 7/unit  for 201-300 units
const double RATE_SLAB4     = 8.0;   // Rs. 8/unit  for 300+    units
const double FIXED_CHARGE   = 100.0; // Rs. 100 fixed monthly charge
const double LATE_FEE_RATE  = 0.02;  // 2% late payment surcharge

const string DATA_FILE      = "bills.txt"; // file to store saved records

// ============================================================
// UTILITY: Read a full line safely (handles cin/getline mix)
// Always use this instead of bare getline to avoid skipping.
// ============================================================
string readLine() {
    string line;
    getline(cin, line);
    return line;
}

// ============================================================
// CLASS: Customer
// PURPOSE : Stores basic information about a customer.
//           Demonstrates encapsulation and data hiding.
// ============================================================
class Customer {
private:
    // -- Private data members -- (Data Hiding)
    string name;
    string consumerID;
    double unitsConsumed;
    bool   hasLateFee;

public:
    // --------------------------------------------------------
    // DEFAULT CONSTRUCTOR
    // Called when we create a Customer without providing data.
    // --------------------------------------------------------
    Customer() {
        name          = "";
        consumerID    = "";
        unitsConsumed = 0.0;
        hasLateFee    = false;
    }

    // --------------------------------------------------------
    // PARAMETERIZED CONSTRUCTOR
    // Called when we already know all customer details.
    // --------------------------------------------------------
    Customer(const string& n, const string& id,
             double units, bool late) {
        name          = n;
        consumerID    = id;
        unitsConsumed = units;
        hasLateFee    = late;
    }

    // --------------------------------------------------------
    // SETTER FUNCTIONS (Mutators) - controlled write access
    // --------------------------------------------------------
    void setName(const string& n)  { name          = n;    }
    void setConsumerID(const string& id) { consumerID = id; }
    void setUnitsConsumed(double u){ unitsConsumed  = u;    }
    void setHasLateFee(bool late)  { hasLateFee     = late; }

    // --------------------------------------------------------
    // GETTER FUNCTIONS (Accessors) - controlled read access
    // --------------------------------------------------------
    string getName()          const { return name;          }
    string getConsumerID()    const { return consumerID;    }
    double getUnitsConsumed() const { return unitsConsumed; }
    bool   getHasLateFee()    const { return hasLateFee;    }

    // --------------------------------------------------------
    // VIRTUAL FUNCTION: displayInfo()
    // Base-class version prints basic customer info.
    // 'virtual' keyword enables runtime polymorphism —
    // the correct version is picked at runtime based on
    // the actual object type, not the pointer/reference type.
    // --------------------------------------------------------
    virtual void displayInfo() const {
        cout << left << setw(22) << "  Customer Name"
             << ": " << name << "\n";
        cout << left << setw(22) << "  Consumer ID"
             << ": " << consumerID << "\n";
        cout << left << setw(22) << "  Units Consumed"
             << ": " << fixed << setprecision(2)
             << unitsConsumed << " units\n";
        cout << left << setw(22) << "  Late Fee Applied"
             << ": " << (hasLateFee ? "Yes" : "No") << "\n";
    }

    // Virtual destructor - good practice with inheritance
    virtual ~Customer() {}
};

// ============================================================
// CLASS: BillCalculator
// PURPOSE : Inherits from Customer. Adds bill calculation.
//           Demonstrates INHERITANCE and FUNCTION OVERRIDING.
// ============================================================
class BillCalculator : public Customer {
private:
    double energyCharge;   // cost based on units consumed
    double lateFeeAmount;  // late payment surcharge amount
    double totalBill;      // final amount to be paid

    // --------------------------------------------------------
    // PRIVATE HELPER: calculateEnergyCharge()
    // Applies PROGRESSIVE SLAB RATES.
    //
    // Example: 250 units
    //   First  100 units -> 100 x Rs.3 = Rs. 300
    //   Next   100 units -> 100 x Rs.5 = Rs. 500
    //   Last    50 units ->  50 x Rs.7 = Rs. 350
    //   Total Energy Charge            = Rs.1150
    // --------------------------------------------------------
    double calculateEnergyCharge(double units) const {
        double charge = 0.0;

        if (units <= 100) {
            charge = units * RATE_SLAB1;
        }
        else if (units <= 200) {
            charge  = 100 * RATE_SLAB1;
            charge += (units - 100) * RATE_SLAB2;
        }
        else if (units <= 300) {
            charge  = 100 * RATE_SLAB1;
            charge += 100 * RATE_SLAB2;
            charge += (units - 200) * RATE_SLAB3;
        }
        else {
            charge  = 100 * RATE_SLAB1;
            charge += 100 * RATE_SLAB2;
            charge += 100 * RATE_SLAB3;
            charge += (units - 300) * RATE_SLAB4;
        }

        return charge;
    }

public:
    // --------------------------------------------------------
    // DEFAULT CONSTRUCTOR
    // --------------------------------------------------------
    BillCalculator() : Customer() {
        energyCharge  = 0.0;
        lateFeeAmount = 0.0;
        totalBill     = 0.0;
    }

    // --------------------------------------------------------
    // PARAMETERIZED CONSTRUCTOR
    // Uses constructor initializer list (:) to call the
    // base class (Customer) constructor first.
    // --------------------------------------------------------
    BillCalculator(const string& n, const string& id,
                   double units, bool late)
        : Customer(n, id, units, late)
    {
        energyCharge  = 0.0;
        lateFeeAmount = 0.0;
        totalBill     = 0.0;
        computeBill();
    }

    // --------------------------------------------------------
    // computeBill()
    // Calculates energy charge, optional late fee, total bill.
    // --------------------------------------------------------
    void computeBill() {
        energyCharge  = calculateEnergyCharge(getUnitsConsumed());
        lateFeeAmount = 0.0;

        double subtotal = energyCharge + FIXED_CHARGE;

        if (getHasLateFee()) {
            lateFeeAmount = subtotal * LATE_FEE_RATE;
        }

        totalBill = subtotal + lateFeeAmount;
    }

    // --------------------------------------------------------
    // GETTER FUNCTIONS for bill components
    // --------------------------------------------------------
    double getEnergyCharge()  const { return energyCharge;  }
    double getLateFeeAmount() const { return lateFeeAmount; }
    double getTotalBill()     const { return totalBill;     }

    // --------------------------------------------------------
    // OVERRIDDEN FUNCTION: displayInfo()
    // 'override' keyword (C++11) ensures we are correctly
    // overriding the base class virtual function.
    // --------------------------------------------------------
    void displayInfo() const override {
        Customer::displayInfo();   // call base class version first
        cout << left << setw(22) << "  Energy Charge"
             << ": Rs. " << fixed << setprecision(2) << energyCharge << "\n";
        cout << left << setw(22) << "  Fixed Charge"
             << ": Rs. " << fixed << setprecision(2) << FIXED_CHARGE << "\n";
        if (getHasLateFee()) {
            cout << left << setw(22) << "  Late Fee (2%)"
                 << ": Rs. " << fixed << setprecision(2) << lateFeeAmount << "\n";
        }
        cout << left << setw(22) << "  TOTAL PAYABLE"
             << ": Rs. " << fixed << setprecision(2) << totalBill << "\n";
    }

    // --------------------------------------------------------
    // printReceipt()
    // Prints a formatted electricity bill receipt to console.
    // --------------------------------------------------------
    void printReceipt() const {
        string border(56, '=');
        string dashes(56, '-');
        double units = getUnitsConsumed();

        cout << "\n" << border << "\n";
        cout << setw(42) << right << "ELECTRICITY BILL RECEIPT\n";
        cout << "       ** SAMPLE EDUCATIONAL RATES - NOT OFFICIAL **\n";
        cout << border << "\n";

        cout << left << setw(22) << "  Customer Name"
             << ": " << getName() << "\n";
        cout << left << setw(22) << "  Consumer ID"
             << ": " << getConsumerID() << "\n";
        cout << dashes << "\n";
        cout << left << setw(22) << "  Units Consumed"
             << ": " << fixed << setprecision(2) << units << " units\n";
        cout << "\n  Slab-wise Charge Breakdown:\n";

        // --- Breakdown per slab ---
        if (units > 0) {
            double u1 = (units >= 100) ? 100.0 : units;
            cout << "    0-100 units    : "
                 << fixed << setprecision(2) << u1
                 << " x Rs." << RATE_SLAB1
                 << " = Rs." << (u1 * RATE_SLAB1) << "\n";
        }
        if (units > 100) {
            double u2 = (units >= 200) ? 100.0 : (units - 100.0);
            cout << "    101-200 units  : "
                 << fixed << setprecision(2) << u2
                 << " x Rs." << RATE_SLAB2
                 << " = Rs." << (u2 * RATE_SLAB2) << "\n";
        }
        if (units > 200) {
            double u3 = (units >= 300) ? 100.0 : (units - 200.0);
            cout << "    201-300 units  : "
                 << fixed << setprecision(2) << u3
                 << " x Rs." << RATE_SLAB3
                 << " = Rs." << (u3 * RATE_SLAB3) << "\n";
        }
        if (units > 300) {
            double u4 = units - 300.0;
            cout << "    Above 300 units: "
                 << fixed << setprecision(2) << u4
                 << " x Rs." << RATE_SLAB4
                 << " = Rs." << (u4 * RATE_SLAB4) << "\n";
        }

        cout << dashes << "\n";
        cout << left << setw(22) << "  Energy Charges"
             << ": Rs. " << fixed << setprecision(2) << energyCharge << "\n";
        cout << left << setw(22) << "  Fixed Charges"
             << ": Rs. " << fixed << setprecision(2) << FIXED_CHARGE << "\n";

        if (getHasLateFee()) {
            cout << left << setw(22) << "  Late Fee (2%)"
                 << ": Rs. " << fixed << setprecision(2) << lateFeeAmount << "\n";
        }

        cout << dashes << "\n";
        cout << left << setw(22) << "  TOTAL PAYABLE"
             << ": Rs. " << fixed << setprecision(2) << totalBill << "\n";
        cout << border << "\n";
        cout << "         Thank you for using our service!\n";
        cout << border << "\n\n";
    }

    // --------------------------------------------------------
    // toFileString()
    // Converts bill data to a plain-text string for saving.
    // --------------------------------------------------------
    string toFileString() const {
        ostringstream oss;
        oss << fixed << setprecision(2);
        oss << "---RECORD---\n";
        oss << "Name:"         << getName()           << "\n";
        oss << "ConsumerID:"   << getConsumerID()      << "\n";
        oss << "Units:"        << getUnitsConsumed()   << "\n";
        oss << "LateFee:"      << (getHasLateFee() ? "1" : "0") << "\n";
        oss << "EnergyCharge:" << energyCharge         << "\n";
        oss << "LateFeeAmt:"   << lateFeeAmount         << "\n";
        oss << "TotalBill:"    << totalBill             << "\n";
        return oss.str();
    }
};

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void printLine(char ch = '-', int w = 56) {
    cout << string(w, ch) << "\n";
}

void printBanner() {
    printLine('=');
    cout << setw(44) << right << "ELECTRICITY BILL CALCULATOR\n";
    cout << setw(42) << right << "BCA OOP Project - C++ | CU\n";
    cout << setw(44) << right << "Author: Ayush Sharma\n";
    printLine('=');
    cout << "  Sample Educational Tariff (Not Official Rates):\n";
    cout << "    0  - 100 units : Rs. 3 per unit\n";
    cout << "    101 - 200 units: Rs. 5 per unit\n";
    cout << "    201 - 300 units: Rs. 7 per unit\n";
    cout << "    Above 300 units: Rs. 8 per unit\n";
    cout << "    Fixed Charge   : Rs. 100 per month\n";
    printLine('=');
    cout << "\n";
}

void printMenu() {
    printLine('=');
    cout << setw(36) << right << "MAIN MENU\n";
    printLine('=');
    cout << "  1. Add New Customer\n";
    cout << "  2. Calculate & Display Bill\n";
    cout << "  3. View All Customers\n";
    cout << "  4. Search Customer by Consumer ID\n";
    cout << "  5. Save All Bills to File\n";
    cout << "  6. View Bills from File\n";
    cout << "  7. Clear All Records (Current Session)\n";
    cout << "  8. Exit\n";
    printLine('-');
    cout << "  Enter your choice (1-8): ";
}

void pauseScreen() {
    cout << "\n  Press Enter to return to menu...";
    readLine();
}

// ============================================================
// VALIDATED INPUT HELPERS
// All input is read as a full line (string) then parsed,
// so getline/cin mixing issues are completely avoided.
// ============================================================

// Read an integer in [minVal, maxVal]. Loops until valid.
int getValidInt(int minVal, int maxVal) {
    while (true) {
        string line = readLine();
        if (line.empty()) {
            cout << "  [!] Please enter a number between "
                 << minVal << " and " << maxVal << ": ";
            continue;
        }
        istringstream iss(line);
        int val;
        char extra;
        if ((iss >> val) && !(iss >> extra)) {
            if (val >= minVal && val <= maxVal) return val;
        }
        cout << "  [!] Invalid input. Please enter a number between "
             << minVal << " and " << maxVal << ": ";
    }
}

// Read a double >= minVal. Loops until valid.
double getValidDouble(double minVal) {
    while (true) {
        string line = readLine();
        if (line.empty()) {
            cout << "  [!] Please enter a valid number >= "
                 << minVal << ": ";
            continue;
        }
        istringstream iss(line);
        double val;
        char extra;
        if ((iss >> val) && !(iss >> extra)) {
            if (val >= minVal) return val;
        }
        cout << "  [!] Invalid input. Enter a positive number >= "
             << minVal << ": ";
    }
}

// Read a non-empty, non-whitespace-only string.
string getValidString(const string& prompt) {
    while (true) {
        cout << prompt;
        string val = readLine();
        // Trim leading/trailing spaces
        size_t s = val.find_first_not_of(" \t\r\n");
        size_t e = val.find_last_not_of(" \t\r\n");
        if (s == string::npos) {
            cout << "  [!] Input cannot be empty. Try again.\n";
            continue;
        }
        return val.substr(s, e - s + 1);
    }
}

// ============================================================
// CLASS: BillManager
// PURPOSE : Manages a vector of BillCalculator objects.
//           Handles add, display, search, save, load.
// ============================================================
class BillManager {
private:
    vector<BillCalculator> customers;

    // Returns true if a Consumer ID already exists
    bool isDuplicateID(const string& id) const {
        for (size_t i = 0; i < customers.size(); i++) {
            if (customers[i].getConsumerID() == id) return true;
        }
        return false;
    }

    // Finds index of a customer by ID; returns -1 if not found
    int findByID(const string& id) const {
        for (size_t i = 0; i < customers.size(); i++) {
            if (customers[i].getConsumerID() == id) return (int)i;
        }
        return -1;
    }

public:

    // --------------------------------------------------------
    // addCustomer()
    // Gets input from user and adds a new BillCalculator.
    // --------------------------------------------------------
    void addCustomer() {
        printLine('=');
        cout << setw(36) << right << "ADD NEW CUSTOMER\n";
        printLine('=');

        // Get name
        string name = getValidString("  Enter Customer Name      : ");

        // Get unique Consumer ID
        string id;
        while (true) {
            id = getValidString("  Enter Consumer ID        : ");
            if (isDuplicateID(id)) {
                cout << "  [!] ID '" << id
                     << "' already exists. Use a different ID.\n";
            } else {
                break;
            }
        }

        // Get units consumed
        cout << "  Enter Units Consumed      : ";
        double units = getValidDouble(0.0);

        // Late fee?
        cout << "  Apply Late Fee? (1=Yes / 0=No): ";
        bool lateFee = (getValidInt(0, 1) == 1);

        // Create object and store
        BillCalculator bill(name, id, units, lateFee);
        customers.push_back(bill);

        cout << "\n  [OK] Customer added successfully!\n";
        cout << "       Name: " << name << "  |  ID: " << id << "\n";
        printLine('-');
    }

    // --------------------------------------------------------
    // calculateAndDisplay()
    // Search by ID and print full bill receipt.
    // --------------------------------------------------------
    void calculateAndDisplay() {
        if (customers.empty()) {
            cout << "\n  [!] No records found. Add a customer first.\n";
            return;
        }
        printLine('=');
        cout << setw(44) << right << "CALCULATE & DISPLAY BILL\n";
        printLine('=');

        string id = getValidString("  Enter Consumer ID: ");
        int idx = findByID(id);

        if (idx == -1) {
            cout << "\n  [!] Consumer ID '" << id << "' not found.\n";
            return;
        }

        customers[idx].computeBill();
        customers[idx].printReceipt();
    }

    // --------------------------------------------------------
    // viewAllCustomers()
    // Shows a summary table of all loaded customers.
    // --------------------------------------------------------
    void viewAllCustomers() const {
        if (customers.empty()) {
            cout << "\n  [!] No customer records found.\n";
            return;
        }
        printLine('=');
        cout << setw(40) << right << "ALL CUSTOMER RECORDS\n";
        printLine('=');

        cout << left
             << setw(5)  << "No."
             << setw(18) << "Name"
             << setw(14) << "Consumer ID"
             << setw(10) << "Units"
             << "Total Bill\n";
        printLine('-');

        for (size_t i = 0; i < customers.size(); i++) {
            cout << left
                 << setw(5)  << (i + 1)
                 << setw(18) << customers[i].getName()
                 << setw(14) << customers[i].getConsumerID()
                 << setw(10) << fixed << setprecision(2)
                              << customers[i].getUnitsConsumed()
                 << "Rs. " << fixed << setprecision(2)
                 << customers[i].getTotalBill() << "\n";
        }
        printLine('-');
        cout << "  Total Records: " << customers.size() << "\n";
    }

    // --------------------------------------------------------
    // searchCustomer()
    // Finds a customer by ID and prints full receipt.
    // --------------------------------------------------------
    void searchCustomer() const {
        if (customers.empty()) {
            cout << "\n  [!] No records found.\n";
            return;
        }
        printLine('=');
        cout << setw(42) << right << "SEARCH BY CONSUMER ID\n";
        printLine('=');

        string id = getValidString("  Enter Consumer ID to search: ");
        int idx = findByID(id);

        if (idx == -1) {
            cout << "\n  [!] Consumer ID '" << id << "' not found.\n";
            return;
        }

        cout << "\n  [OK] Customer Found!\n";
        customers[idx].printReceipt();
    }

    // --------------------------------------------------------
    // saveToFile()
    // Writes all customer records to bills.txt.
    // File handling: ios::out | ios::trunc
    //   ios::out   = open for writing
    //   ios::trunc = clear file before writing (overwrite)
    // --------------------------------------------------------
    void saveToFile() const {
        if (customers.empty()) {
            cout << "\n  [!] No records to save.\n";
            return;
        }

        ofstream outFile(DATA_FILE.c_str(), ios::out | ios::trunc);

        if (!outFile.is_open()) {
            cout << "\n  [ERROR] Cannot open file: " << DATA_FILE << "\n";
            return;
        }

        outFile << "ELECTRICITY BILL CALCULATOR - SAVED RECORDS\n";
        outFile << "Author: Ayush Sharma | Course: BCA | CU\n";
        outFile << string(56, '=') << "\n";

        for (size_t i = 0; i < customers.size(); i++) {
            outFile << customers[i].toFileString();
        }

        outFile << "---END---\n";
        outFile.close();

        cout << "\n  [OK] " << customers.size()
             << " record(s) saved to '" << DATA_FILE << "'.\n";
    }

    // --------------------------------------------------------
    // viewFromFile()
    // Reads and displays saved records from bills.txt.
    // File handling: ios::in = open for reading
    // --------------------------------------------------------
    void viewFromFile() const {
        ifstream inFile(DATA_FILE.c_str(), ios::in);

        if (!inFile.is_open()) {
            cout << "\n  [!] File '" << DATA_FILE
                 << "' not found. Save records first (Option 5).\n";
            return;
        }

        printLine('=');
        cout << setw(42) << right << "SAVED BILLS FROM FILE\n";
        printLine('=');

        string line;
        while (getline(inFile, line)) {
            cout << "  " << line << "\n";
        }

        inFile.close();
        printLine('-');
    }

    // --------------------------------------------------------
    // clearAllRecords()
    // Clears in-memory records (does NOT delete saved file).
    // --------------------------------------------------------
    void clearAllRecords() {
        if (customers.empty()) {
            cout << "\n  [!] No records to clear.\n";
            return;
        }

        cout << "\n  Are you sure you want to clear all "
             << customers.size() << " record(s) from this session?\n";
        cout << "  (The saved file '" << DATA_FILE
             << "' will NOT be deleted.)\n";
        cout << "  Type YES to confirm: ";

        string confirm = readLine();

        if (confirm == "YES") {
            customers.clear();
            cout << "  [OK] All session records cleared.\n";
        } else {
            cout << "  [--] Operation cancelled.\n";
        }
    }

    int getCount() const { return (int)customers.size(); }
};

// ============================================================
// MAIN FUNCTION - Program entry point
// ============================================================
int main() {

    printBanner();

    BillManager manager;

    while (true) {
        printMenu();

        int choice = getValidInt(1, 8);
        cout << "\n";

        switch (choice) {

            case 1:
                manager.addCustomer();
                pauseScreen();
                break;

            case 2:
                manager.calculateAndDisplay();
                pauseScreen();
                break;

            case 3:
                manager.viewAllCustomers();
                pauseScreen();
                break;

            case 4:
                manager.searchCustomer();
                pauseScreen();
                break;

            case 5:
                manager.saveToFile();
                pauseScreen();
                break;

            case 6:
                manager.viewFromFile();
                pauseScreen();
                break;

            case 7:
                manager.clearAllRecords();
                pauseScreen();
                break;

            case 8:
                printLine('=');
                cout << setw(40) << right << "Thank you!\n";
                cout << setw(48) << right << "Electricity Bill Calculator\n";
                cout << setw(42) << right << "Ayush Sharma | BCA | CU\n";
                printLine('=');
                cout << "\n";
                return 0;

            default:
                cout << "  [!] Invalid choice. Select 1-8.\n";
                pauseScreen();
                break;
        }

        cout << "\n";
    }

    return 0;
}
