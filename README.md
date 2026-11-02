# Electricity Bill Calculator

> **A C++ Console Application demonstrating Object-Oriented Programming concepts**

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/Standard-C%2B%2B11-green.svg)](https://en.cppreference.com/w/cpp/11)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Course](https://img.shields.io/badge/Course-BCA%20OOP-orange.svg)]()

---

## 📌 Project Description

**Electricity Bill Calculator** is a menu-driven console application built in **C++** that calculates and manages electricity bills for multiple customers. The project is developed as an academic OOP project for BCA 2nd year at Chandigarh University.

> ⚠️ **Disclaimer:** The electricity tariff rates used in this project are **sample educational rates only**. They do **not** represent any official government or utility provider tariff.

---

## ✨ Features

- ✅ Add multiple customer records
- ✅ Slab-wise progressive electricity bill calculation
- ✅ Fixed monthly charge included
- ✅ Optional late payment surcharge (2%)
- ✅ Detailed bill receipt with slab-wise breakdown
- ✅ View all customers in a summary table
- ✅ Search customer by Consumer ID
- ✅ Save all bills to a text file (`bills.txt`)
- ✅ Load and display saved bills from file
- ✅ Duplicate Consumer ID prevention
- ✅ Robust input validation (no crashes on invalid input)
- ✅ Clean, formatted console interface

---

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C++ (C++11 standard) | Core application language |
| `iostream` | Console input/output |
| `string` | String data handling |
| `fstream` | File read/write operations |
| `iomanip` | Output formatting (alignment, decimals) |
| `vector` | Dynamic list of customer records |
| `sstream` | String stream for parsing & formatting |
| g++ compiler | Compilation |

**No external libraries or frameworks used.**

---

## 🎓 OOP Concepts Demonstrated

| Concept | Where Used |
|---|---|
| **Classes & Objects** | `Customer`, `BillCalculator`, `BillManager` classes |
| **Encapsulation** | Private data with public getters/setters |
| **Data Hiding** | All data members are `private` |
| **Constructors** | Default and parameterized constructors in both classes |
| **Member Functions** | `computeBill()`, `printReceipt()`, `addCustomer()`, etc. |
| **Inheritance** | `BillCalculator` inherits from `Customer` |
| **Function Overriding** | `displayInfo()` overridden using `virtual` and `override` |
| **Polymorphism** | Virtual function dispatch at runtime |

---

## ⚡ Electricity Tariff (Sample Educational Rates)

| Units Consumed | Rate per Unit |
|---|---|
| 0 – 100 units | ₹ 3.00 |
| 101 – 200 units | ₹ 5.00 |
| 201 – 300 units | ₹ 7.00 |
| Above 300 units | ₹ 8.00 |
| **Fixed Charge** | **₹ 100.00 per month** |
| **Late Fee** | **2% of (Energy + Fixed) — optional** |

### 📊 Sample Calculation (250 units)

```
First 100 units  : 100 × Rs.3 = Rs. 300
Next  100 units  : 100 × Rs.5 = Rs. 500
Last   50 units  :  50 × Rs.7 = Rs. 350
                   ─────────────────────
Energy Charge    :             Rs.1150
Fixed Charge     :             Rs. 100
                   ─────────────────────
TOTAL PAYABLE    :             Rs.1250
```

---

## 📁 Project Structure

```
Electricity-Bill-Calculator/
│
├── src/
│   ├── electricity_bill.cpp    ← Main application source code
│   └── test_calc.cpp           ← Bill calculation verification test
│
├── screenshots/                ← Add your program screenshots here
│
├── README.md                   ← Project documentation (this file)
├── .gitignore                  ← Files to exclude from Git
└── LICENSE                     ← MIT License
```

---

## 🚀 Installation & Setup

### Prerequisites

- A C++ compiler supporting C++11 (g++ recommended)
- Windows / Linux / macOS

### Check if g++ is installed

```bash
g++ --version
```

If not installed:
- **Windows:** Install [MinGW-w64](https://www.mingw-w64.org/) or use [Code::Blocks](https://www.codeblocks.org/)
- **Linux:** `sudo apt install g++`
- **macOS:** `xcode-select --install`

---

## 🔨 How to Compile

Open your terminal/command prompt in the project root folder:

```bash
# Windows (Command Prompt or PowerShell)
g++ -std=c++11 -Wall -o electricity_bill.exe src/electricity_bill.cpp

# Linux / macOS
g++ -std=c++11 -Wall -o electricity_bill src/electricity_bill.cpp
```

---

## ▶️ How to Run

```bash
# Windows
electricity_bill.exe

# Linux / macOS
./electricity_bill
```

---

## 🖥️ Sample Output

```
========================================================
                       ELECTRICITY BILL CALCULATOR
                         BCA OOP Project - C++ | CU
                           Author: Ayush Sharma
========================================================
  Sample Educational Tariff (Not Official Rates):
    0  - 100 units : Rs. 3 per unit
    101 - 200 units: Rs. 5 per unit
    201 - 300 units: Rs. 7 per unit
    Above 300 units: Rs. 8 per unit
    Fixed Charge   : Rs. 100 per month
========================================================

========================================================
                               MAIN MENU
========================================================
  1. Add New Customer
  2. Calculate & Display Bill
  3. View All Customers
  4. Search Customer by Consumer ID
  5. Save All Bills to File
  6. View Bills from File
  7. Clear All Records (Current Session)
  8. Exit
--------------------------------------------------------
  Enter your choice (1-8): 2

========================================================
                        ELECTRICITY BILL RECEIPT
       ** SAMPLE EDUCATIONAL RATES - NOT OFFICIAL **
========================================================
  Customer Name          : Rahul Kumar
  Consumer ID            : C001
--------------------------------------------------------
  Units Consumed         : 250.00 units

  Slab-wise Charge Breakdown:
    0-100 units    : 100.00 x Rs.3 = Rs.300.00
    101-200 units  : 100.00 x Rs.5 = Rs.500.00
    201-300 units  :  50.00 x Rs.7 = Rs.350.00
--------------------------------------------------------
  Energy Charges         : Rs. 1150.00
  Fixed Charges          : Rs.  100.00
--------------------------------------------------------
  TOTAL PAYABLE          : Rs. 1250.00
========================================================
         Thank you for using our service!
========================================================
```

---

## 🧪 Test Cases Verified

| Units | Energy Charge | Fixed | Total |
|-------|--------------|-------|-------|
| 50    | Rs. 150      | Rs. 100 | Rs. 250  |
| 100   | Rs. 300      | Rs. 100 | Rs. 400  |
| 150   | Rs. 550      | Rs. 100 | Rs. 650  |
| 250   | Rs. 1150     | Rs. 100 | Rs. 1250 |
| 350   | Rs. 1900     | Rs. 100 | Rs. 2000 |

---

## 🔮 Future Improvements

- [ ] Add monthly bill history per customer
- [ ] Export bill as PDF using a library
- [ ] GUI interface using Qt or SFML
- [ ] Database integration (SQLite)
- [ ] Login system for admin access
- [ ] Support for multiple tariff zones
- [ ] Bill due date tracking

---

## 👤 Author

| Field | Details |
|---|---|
| **Name** | Ayush Sharma |
| **Course** | BCA (Bachelor of Computer Applications) |
| **Subject** | Object-Oriented Programming in C++ |
| **University** | Chandigarh University |

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 🏷️ Suggested GitHub Repository Topics

`cpp` `oop` `electricity-bill` `console-application` `bca-project` `chandigarh-university` `beginner-cpp` `file-handling` `inheritance` `encapsulation`

---

*Developed as an academic OOP project. Sample tariff rates are for educational demonstration only.*
