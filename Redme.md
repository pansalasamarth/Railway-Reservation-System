# 🚆 Railway Reservation System (C Language)

## 📌 Objective
To design and implement a **C-based Railway Reservation System** that simulates the basic operations of a real-world railway booking system. The program manages train schedules, passenger information, seat allocation, and ticket status using appropriate data structures and control logic.

---

## 🧩 Problem Description
The Railway Reservation System is a **menu-driven, console-based simulation program** written in the C programming language. It allows users to perform railway ticket booking–related operations such as viewing available trains, booking tickets, canceling tickets, and displaying passenger details.

The system maintains records of trains and passengers, checks seat availability, allocates seats upon successful booking, and updates ticket status accordingly. The program runs continuously until the user explicitly chooses to exit.

---

## 🏗️ System Overview
The Railway Reservation System simulates basic railway booking operations using:
- Structures to model real-world entities
- Arrays for runtime data storage
- Files for persistent data storage
- Functions for modular program design

---

## 🧱 Key Entities and Data Modeling

### 1️⃣ Train Information
Each train stores both static and dynamic information.

**Train Structure Fields:**
- Train Number (unique identifier)
- Train Name
- Source Station
- Destination Station
- Total Seats
- Available Seats

**Purpose:**
- Display train schedules
- Check seat availability during booking
- Update seat count during booking and cancellation

---

### 2️⃣ Passenger Information
Passenger data represents a ticket booking transaction.

**Passenger Structure Fields:**
- Passenger Name
- Age
- Gender
- Train Number
- Seat Number
- Ticket Status

**Ticket Status Types:**
- Confirmed
- Waiting
- Canceled

**Purpose:**
- Track booking details
- Display ticket status
- Manage cancellations

---

## 💾 Data Storage Strategy

### Arrays and File Backup
- Arrays of structures are used for fast runtime access
- Files are used to preserve data across program executions

**Files Used:**
- `trains.dat` — stores train information
- `passengers.dat` — stores passenger booking records

### Program Startup
- Load data from files into arrays
- Initialize counters based on file contents

### Data Updates
After every operation that modifies data (booking, cancellation):
- Update the corresponding file

**Benefit:**
- Prevents data loss after program exit

---

## 🧠 Functional Decomposition

### Main Menu
The main menu provides the following options:
1. Display Available Trains  
2. Book Ticket  
3. Cancel Ticket  
4. Display Passenger Details  
5. Exit  

The menu is implemented using a loop and a `switch-case` statement to handle user choices.

---

### Display Available Trains
**Responsibilities:**
- Traverse the train array
- Display:
  - Train Number
  - Train Name
  - Source → Destination
  - Available Seats

**Validation:**
- Display a message if no trains are available

---

### Ticket Booking Logic
**Steps:**
1. Accept train number from user
2. Validate train existence
3. Check available seats
4. Collect passenger details
5. Allocate seat automatically

**Seat Allocation Rules:**
- If seats are available:
  - Assign next seat number
  - Ticket status set to **Confirmed**
  - Available seats reduced
- If seats are full:
  - Seat number set to `-1`
  - Ticket status set to **Waiting**

**Constraints:**
- No overbooking allowed
- Automatic seat allocation only

---

### Ticket Cancellation Logic
**Steps:**
1. Accept passenger name or booking reference
2. Validate passenger record
3. Check ticket status
4. Update ticket status to **Canceled**

**Rules:**
- Confirmed tickets restore seat count
- Waiting tickets do not affect seat count
- Passenger records are not deleted

**Optional Enhancement:**
- Promote a waiting passenger when a seat becomes available

---

### Display Passenger and Ticket Details
**Responsibilities:**
- Traverse passenger array
- Display:
  - Passenger Name
  - Train Number
  - Seat Number (if confirmed)
  - Ticket Status

**Validation:**
- Handle empty passenger list
- Clearly display canceled tickets

---

## 🎫 Ticket Status Management
Ticket status is managed using:
- Enumeration (`enum`) OR
- Predefined status strings

**Recommended Enumeration:**
- CONFIRMED
- WAITING
- CANCELED

**Rules:**
- Confirmed tickets always have a seat
- Waiting tickets do not reduce available seats
- Canceled tickets free seats only if previously confirmed

---

## ⚠️ Input Validation and Error Handling
The system validates:
- Menu choices
- Train number existence
- Passenger age (must be greater than zero)
- Gender input
- Seat availability

**Error Messages Include:**
- Invalid menu choice
- Invalid train number
- No seats available
- Ticket not found

---

## 🔁 Program Flow Control
- The program runs inside a loop
- Returns to the main menu after every operation
- Terminates only when the user selects the exit option

---

## 🧑‍💻 Coding Guidelines

### Program Structure
- Structure definitions at the top
- Constants and macros before `main()`
- Function prototypes before `main()`
- Function implementations after `main()`

---

### Naming Conventions
- Use meaningful variable names
- Use consistent naming style (camelCase or snake_case)
- Avoid generic names like `x`, `y`, `z`

---

### Constants and Macros
Use macros instead of magic numbers:
- Maximum trains
- Maximum passengers

---

### Modular Programming
- One function per responsibility
- Avoid placing all logic inside `main()`

---

### Booking Rules
- Prevent overbooking
- Seat count must never go below zero
- Automatic seat allocation only

---

### Cancellation Rules
- Only confirmed tickets restore seats
- Waiting tickets do not affect seat count
- Passenger records remain for history

---

## 📝 Commenting Guidelines
- Use function header comments
- Comment logical blocks
- Avoid obvious comments

---

## 🧪 Testing Guidelines
Before final submission, test:
- Booking until all seats are full
- Ticket cancellation
- Invalid user inputs
- Waiting list scenarios

---

## 📌 Conclusion
The Railway Reservation System demonstrates:
- Structured and modular programming in C
- Effective use of structures, enums, arrays, and files
- Real-world simulation of a railway booking system
- Clean, readable, and maintainable design