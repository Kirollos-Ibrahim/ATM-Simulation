# ATM Simulation

A **ATM Simulation** developed in **C++** as a console-based application. The project simulates common ATM and banking operations, including user authentication, balance management, deposits, withdrawals, PIN changes, and administrative account management.

The project focuses on applying **Object-Oriented Programming (OOP)** concepts, input validation, authentication logic, and account state management in C++.

---

## Project Objectives

- Apply Object-Oriented Programming concepts using C++.
- Simulate common ATM operations.
- Implement user and administrator authentication.
- Practice account and balance management.
- Handle invalid user input and transaction conditions.
- Implement PIN validation and account locking.
- Develop a collaborative team project using C++.

---

## Features

### User Authentication

Users can access their accounts using:

- Account number
- PIN

The system validates the entered credentials before granting access to the ATM menu.

### PIN Security

The system includes basic PIN protection:

- Failed PIN attempts are tracked.
- An account is locked after three consecutive failed attempts.
- Locked accounts cannot be accessed until unlocked by an administrator.
- Users can change their PIN after successful authentication.

### Account Operations

Authenticated users can perform:

- Check account balance
- Deposit money
- Withdraw money
- Change PIN
- Exit the account menu

### Deposit

Users can deposit money into their account.

The system validates the entered amount and rejects invalid or non-positive values.

### Withdrawal

Users can withdraw money if sufficient funds are available.

The system checks:

- Whether the entered amount is valid.
- Whether the account has sufficient funds.

### Administrator Operations

Administrators have access to a separate menu that allows them to:

- Create new accounts
- Delete accounts
- View all accounts
- Unlock locked accounts

---

## System Structure

The application is implemented around an `Account` class responsible for account data and ATM operations.

```text
ATM Simulation
│
├── User Authentication
│   ├── Account Number
│   └── PIN Validation
│
├── User Menu
│   ├── Check Balance
│   ├── Deposit Money
│   ├── Withdraw Money
│   ├── Change PIN
│   └── Exit
│
└── Admin Menu
    ├── Create Account
    ├── Delete Account
    ├── View Accounts
    ├── Unlock Account
    └── Exit
```
---
