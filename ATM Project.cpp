// ============= ** Team 32 ** ============= //

#include <bits/stdc++.h>
using namespace std;

class Account {
private:
    // Members for managing all accounts
    static vector<Account> accounts;
    static Account* currentAccount;
    static const string ADMIN_PIN;

    // Account instance members
    string account_number;
    string pin;
    double balance;
    int failed_attempts;
    bool locked;

public:
    // Constructor
    Account(string acc_no, string pin_no, double initial_balance) 
    : account_number(acc_no), pin(pin_no), balance(initial_balance), failed_attempts(0), locked(false) {}

    // Initialize accounts
    static void initializeAccounts() {
        accounts.push_back(Account("1234", "0000", 1000.0));
        accounts.push_back(Account("5678", "1111", 2000.0));
        accounts.push_back(Account("9012", "2222", 3000.0));
    }

    // Getters
    double getBalance() const { return balance; }
    
    // ============= Main ATM functions ============= //
    static void start() {
        while (true) {
            cout << "\n=== Welcome to the ATM ===" << endl;
            cout << "1. User Login" << endl;
            cout << "2. Admin Login" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    if (login()) {
                        main_menu();
                        currentAccount = nullptr;
                    }
                    break;
                case 2:
                    if (admin_login()) {
                        admin_menu();
                    }
                    break;
                case 3:
                    cout << "\nThank you for using our ATM. Goodbye!" << endl;
                    return;
                default:
                    cout << "Invalid choice." << endl;
            }
        }
    }

    // ============= login and pin validation ============= //
    static bool login() {
        string accNum, pin;
        cout << "Enter account number: ";
        cin >> accNum;

        for (auto& account : accounts) {
            if (account.account_number == accNum) {
                cout << "Enter PIN: ";
                cin >> pin;
                if (account.validatePIN(pin)) {
                    currentAccount = &account;
                    return true;
                }
                cout << "Invalid PIN. Try again." << endl;
                return false;
            }
        }
        cout << "Account not found." << endl;
        return false;
    }

    bool validatePIN(const string& inputPin) {
        if (locked) {
            cout << "Account is locked. Please contact bank support." << endl;
            return false;
        } else if (pin == inputPin) {
            failed_attempts = 0;
            return true;
        } else {
            failed_attempts++;
            if (failed_attempts >= 3) {
                locked = true;
                cout << "Too many failed attempts. Account has been locked." << endl;
            }
            return false;
        }
    }

    // ============= Main menu ============= //
    static void main_menu() {
        while (true) {
            display_menu();
            int choice;
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
            switch (choice) {
                case 1:
                    currentAccount->check_balance();
                    break;
                case 2:
                    currentAccount->deposit();
                    break;
                case 3:
                    currentAccount->withdraw();
                    break;
                case 4:
                    currentAccount->change_PIN();
                    break;
                case 5:
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    static void display_menu() {
        cout << "\n=== ATM Menu ===" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Change PIN" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void check_balance() {
        cout << "\nCurrent Balance: $" << currentAccount->getBalance() << endl;
    }

    void deposit() {
        double money;
        cout << "Enter amount of money to deposit: $";
        cin >> money;
        if (cin.fail() || money <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount." << endl;
            return;
        }
        balance += money;
        cout << "Successfully deposited $" << money << endl;
        cout << "New balance: $" << balance << endl;
    }

    void withdraw() {
        double money;
        cout << "Enter amount to withdraw: $";
        cin >> money;
        if (cin.fail() || money <= 0 || money > balance) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount or insufficient funds." << endl;
            return;
        }
        balance -= money;
        cout << "Please take your cash." << endl;
        cout << "New balance: $" << balance << endl;
    }

    void change_PIN() {
        string oldPin, newPin;
        cout << "Enter current PIN: ";
        cin >> oldPin;
        if (pin != oldPin) {
            cout << "Incorrect current PIN." << endl;
            return;
        }
        cout << "Enter new PIN (4 digits): ";
        cin >> newPin;
        if (newPin.length() != 4) {
            cout << "PIN must be 4 digits." << endl;
        } else {
            pin = newPin;
            cout << "PIN successfully changed." << endl;
        }
    }

    // ============= Admin section and menu ============= //
    static bool admin_login() {
        string pin;
        cout << "Enter Admin PIN: ";
        cin >> pin;
        if (pin == ADMIN_PIN) {
            return true;
        }
        cout << "Invalid Admin PIN." << endl;
        return false;
    }

    static void admin_menu() {
        while (true) {
            display_admin_menu();
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    create_account();
                    break;
                case 2:
                    delete_account();
                    break;
                case 3:
                    view_accounts();
                    break;
                case 4:
                    unlock_account();
                    break;
                case 5:
                    return;
                default:
                    cout << "Invalid choice." << endl;
            }
        }
    }

    static void display_admin_menu() {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Delete Account" << endl;
        cout << "3. View All Accounts" << endl;
        cout << "4. Unlock Account" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "Enter choice: ";
    }

    static void create_account() {
        string acc_num, pin;
        double balance;

        cout << "Enter new account number: ";
        cin >> acc_num;

        for (const auto& acc : accounts) {
            if (acc.account_number == acc_num) {
                cout << "Account number already exists." << endl;
                return;
            }
        }

        cout << "Enter PIN (4 digits): ";
        cin >> pin;
        if (pin.length() != 4) {
            cout << "PIN must be 4 digits." << endl;
            return;
        }

        cout << "Enter initial balance: ";
        cin >> balance;
        if (balance < 0) {
            cout << "Initial balance cannot be negative." << endl;
            return;
        }

        accounts.push_back(Account(acc_num, pin, balance));
        cout << "Account created successfully." << endl;
    }

    static void delete_account() {
        string acc_num;
        cout << "Enter account number to delete: ";
        cin >> acc_num;

        for (auto acc = accounts.begin(); acc != accounts.end(); ++acc) {
            if (acc->account_number == acc_num) {
                accounts.erase(acc);
                cout << "Account deleted successfully." << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    static void view_accounts() {
        cout << "\nAccount List:" << endl;
        cout << setw(15) << "Account" << setw(15) << "Balance" << setw(15) << "Status" << endl;
        cout << string(45, '-') << endl;

        for (const auto& acc : accounts) {
            cout << setw(15) << acc.account_number 
                 << setw(15) << fixed << setprecision(3) << acc.balance
                 << setw(15) << (acc.locked ? "Locked" : "Active") << endl;
        }
    }

    static void unlock_account() {
        string acc_num;
        cout << "Enter account number to unlock: ";
        cin >> acc_num;

        for (auto& acc : accounts) {
            if (acc.account_number == acc_num) {
                acc.locked = false;
                cout << "Account unlocked successfully." << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    
};

// Initialize static members
vector<Account> Account::accounts;
Account* Account::currentAccount = nullptr;
const string Account::ADMIN_PIN = "admin";

int main() {
    Account::initializeAccounts();
    Account::start();
    return 0;
}
