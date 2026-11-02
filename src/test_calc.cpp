/*
 * Bill Calculation Verification Test
 * Tests the slab-wise calculation logic for 5 unit values.
 * Author: Ayush Sharma
 */
#include <iostream>
#include <iomanip>
using namespace std;

const double RATE_SLAB1 = 3.0;
const double RATE_SLAB2 = 5.0;
const double RATE_SLAB3 = 7.0;
const double RATE_SLAB4 = 8.0;
const double FIXED      = 100.0;

double calcEnergy(double u) {
    double c = 0;
    if      (u <= 100) { c = u * 3; }
    else if (u <= 200) { c = 100*3 + (u-100)*5; }
    else if (u <= 300) { c = 100*3 + 100*5 + (u-200)*7; }
    else               { c = 100*3 + 100*5 + 100*7 + (u-300)*8; }
    return c;
}

int main() {
    double tests[] = {50, 100, 150, 250, 350};
    cout << string(52, '=') << "\n";
    cout << "  BILL CALCULATION VERIFICATION TEST\n";
    cout << string(52, '=') << "\n";
    cout << left << setw(8) << "Units"
         << setw(14) << "EnergyCharge"
         << setw(12) << "Fixed"
         << "TotalBill\n";
    cout << string(52, '-') << "\n";

    for (int i = 0; i < 5; i++) {
        double e = calcEnergy(tests[i]);
        double t = e + FIXED;
        cout << left
             << setw(8)  << tests[i]
             << "Rs. " << setw(10) << fixed << setprecision(2) << e
             << "Rs. " << setw(8)  << FIXED
             << "Rs. " << t << "\n";
    }

    cout << string(52, '=') << "\n";
    cout << "\nExpected Results:\n";
    cout << "  50  units: Energy=150,    Total=250\n";
    cout << "  100 units: Energy=300,    Total=400\n";
    cout << "  150 units: Energy=550,    Total=650\n";
    cout << "  250 units: Energy=1150,   Total=1250\n";
    cout << "  350 units: Energy=1900,   Total=2000\n";
    cout << string(52, '=') << "\n";
    return 0;
}
