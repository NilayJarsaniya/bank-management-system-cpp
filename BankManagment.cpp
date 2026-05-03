#include <iostream>
#include <fstream>
using namespace std;

class Account {
public:
    int accNo;
    char name[50];
    float balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void display() {
        cout << "Acc No: " << accNo 
             << " | Name: " << name 
             << " | Balance: " << balance << endl;
    }
};

// Create Account
void createAccount() {
    Account a;
    ofstream file("accounts.dat", ios::binary | ios::app);

    a.createAccount();
    file.write((char*)&a, sizeof(a));

    file.close();
    cout << "Account Created!\n";
}

// Deposit
void deposit() {
    Account a;
    int acc;
    float amt;

    cout << "Enter Account Number: ";
    cin >> acc;
    cout << "Enter Amount to Deposit: ";
    cin >> amt;

    fstream file("accounts.dat", ios::binary | ios::in | ios::out);

    while(file.read((char*)&a, sizeof(a))) {
        if(a.accNo == acc) {
            a.balance += amt;

            file.seekp(-sizeof(a), ios::cur);
            file.write((char*)&a, sizeof(a));

            cout << "Amount Deposited!\n";
            return;
        }
    }

    cout << "Account not found\n";
    file.close();
}

// Withdraw
void withdraw() {
    Account a;
    int acc;
    float amt;

    cout << "Enter Account Number: ";
    cin >> acc;
    cout << "Enter Amount to Withdraw: ";
    cin >> amt;

    fstream file("accounts.dat", ios::binary | ios::in | ios::out);

    while(file.read((char*)&a, sizeof(a))) {
        if(a.accNo == acc) {
            if(a.balance >= amt) {
                a.balance -= amt;

                file.seekp(-sizeof(a), ios::cur);
                file.write((char*)&a, sizeof(a));

                cout << "Amount Withdrawn!\n";
            } else {
                cout << "Insufficient Balance\n";
            }
            return;
        }
    }

    cout << "Account not found\n";
    file.close();
}

// Check Balance
void checkBalance() {
    Account a;
    int acc;

    cout << "Enter Account Number: ";
    cin >> acc;

    ifstream file("accounts.dat", ios::binary);

    while(file.read((char*)&a, sizeof(a))) {
        if(a.accNo == acc) {
            cout << "Balance: " << a.balance << endl;
            return;
        }
    }

    cout << "Account not found\n";
    file.close();
}

// Display All
void displayAll() {
    Account a;
    ifstream file("accounts.dat", ios::binary);

    while(file.read((char*)&a, sizeof(a))) {
        a.display();
    }

    file.close();
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n1. Create Account";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: displayAll(); break;
        }

    } while(choice != 6);

    return 0;
}
