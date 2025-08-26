# My-First-OOP-Bank-Project
Full Banking System Project in C++
The project is built entirely from scratch without any external libraries (except vector), fully leveraging Object-Oriented Programming (OOP) principles.


Features & Capabilities:

Client Management
 • Add, edit, delete, search, and display clients
 • Each client is linked to a bank account with a PIN
 • Track balances and manage account transactions directly

Bank Accounts Management
 • Deposit, withdraw, and transfer funds between clients
 • Automatic balance updates after each transaction
 • Each transfer is logged in a separate file

User Management
 • Multiple system users with unique Username/Password
 • Role-Based Access Control (RBAC) defines accessible screens for each user (implemented using binary enum and bitwise AND checks)
 • Edit, delete, and display users

Currency Management
 • Store currency data and exchange rates
 • Manual currency updates
 • Search for a specific currency
 • Currency conversion with dynamic value calculation

Logging & Monitoring
 • Record all transfer operations in TransferLog.txt
 • Track login attempts and sessions in LoginRegister.txt
 • Monitor who accessed the system and their actions

Security
 • Passwords are encrypted, not stored in plain text
 • Global user variable tracks current user and permissions
 • Unauthorized access to sensitive screens is blocked

File-Based Database Simulation
 • Use text files (Clients.txt, Users.txt, Currencies.txt, TransferLog.txt, LoginRegister.txt) as a full database
 • All modifications are immediately saved; the system reads and writes directly from files
 • clsString class provides Split & Join for data parsing and storage

Screens Layer
 • Each operation has a separate class inheriting from clsScreen
 • Modular and extensible design
 • Screens for Clients, Users, Currencies, Transfers, and Logs
 • clsMainScreen links all screens

Utilities & Helpers
 • clsDate → handle dates
 • clsString → split & join for file storage
 • clsInputValidate → input validation
 • clsUtil → general helper functions

OOP Design
 • Inheritance: all screens inherit from clsScreen
 • Polymorphism & Abstraction: applied especially in screen classes
 • Encapsulation: data protection inside classes

Project Overview:
A complete simulation of a real banking system: client management, accounts, currencies, users, transfers, login & permissions, security, data storage, and interactive screens—all built from scratch in C++ using OOP principles.

Future Enhancements:
 • Integrate with SQL database instead of text files
 • Add a GUI interface
 • Implement report generation for transactions and permissions
 • Unit testing for system stability
