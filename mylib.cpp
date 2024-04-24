#include <iostream>
#include <fstream>
#include "mylib.h"
#include <iomanip>

using namespace std;

struct clientData {
    int accNum;
    char name[25];
    char sur[25];
    float balance;	
};

void addRecord() {
    int i;
    clientData client;
    fstream file;
    file.open("data.dat", ios::app | ios::out | ios::binary);

    cout << "Enter account number from 1 - 100: " << endl;
    cin >> client.accNum;

    while (client.accNum != 0) {
        cout << "Enter Name Surname and Balance." << endl;
        cin >> client.name >> client.sur >> client.balance;
        file.seekp((client.accNum - 1) * sizeof(clientData));
        file.write((char*)&client, sizeof(clientData));
        cout << "Enter next client number (if you want to exit, press 0): ";
        cin >> client.accNum;	
    }
    file.close();	
}

void deleteRecord() {
    int del;	
    clientData client;
    fstream file;	
    file.open("data.dat", ios::in | ios::out | ios::binary);	
    cout << "Enter account number you want to delete: " << endl;
    cin >> del;
    while (file.read((char*)&client, sizeof(clientData))) {	
        if (client.accNum == del) {
            client.accNum = 0;
            file.seekp((client.accNum - 1) * sizeof(clientData), ios::cur);
            file.write((char*)&client.accNum, sizeof(client));
            cout << "Client deleted." << endl;
            break;
        }	
    }
    file.close();
}

void displayRecords() {
    clientData client;
    fstream file;	
    file.open("data.dat", ios::in | ios::binary);
    file.seekg((client.accNum - 1) * sizeof(clientData));
    cout << setw(10) << "Account" << setw(10) << "Name" << setw(10) << "Surname" << setw(10) << "Balance" << endl;
    while (file.read((char*)&client, sizeof(clientData))) {
        if (client.accNum != 0) {
            cout << setw(10) << client.accNum << setw(10) << client.name << setw(10) << client.sur << setw(10) << client.balance << endl;	
        }	
    }
    file.close();	
}

void findRecord() {
    int x;	
    clientData client;
    fstream file;	
    cout << "Enter client number you want to find: " << endl;
    cin >> x;
    file.open("data.dat", ios::in | ios::binary);
    while (file.read((char*)&client, sizeof(clientData))) {
        if (client.accNum == x) {
            cout << setw(10) << "Account" << setw(10) << "Name" << setw(10) << "Surname" << setw(10) << "Balance" << endl;	
            cout << setw(10) << client.accNum << setw(10) << client.name << setw(10) << client.sur << setw(10) << client.balance << endl;
            break;
        }
    }
    file.close();
}

void modifyBalance() {
    int x, b;	
    clientData client;
    fstream file;	
    cout << "Enter account number to modify balance: " << endl;
    cin >> x;
    cout << "Enter the amount you want to modify the balance by: " << endl;
    cin >> b;
    file.open("data.dat", ios::in | ios::out | ios::binary);	
    while (file.read((char*)&client, sizeof(clientData))) {
        if (client.accNum == x) {
            file.seekp(-sizeof(clientData), ios::cur);
            client.balance = client.balance + b;
            file.write((char*)&client, (sizeof(clientData)));
            cout << "Balance modified: " << client.balance << endl;
            break;	
        }		
    }
    file.close();
}

void displayDebtors() {
    clientData client;
    fstream file;
    file.open("data.dat", ios::in | ios::binary);
    cout << setw(10) << "Account" << setw(10) << "Name" << setw(10) << "Surname" << setw(10) << "Balance" << endl;	
    while (file.read((char*)&client, sizeof(clientData))) {
        if (client.balance < 0 && client.accNum != 0) {
            cout << setw(10) << client.accNum << setw(10) << client.name << setw(10) << client.sur << setw(10) << client.balance << endl;
        }	
    }
    file.close();	
}

void countRecords() {
    int sk = 0;	
    clientData client;
    fstream file;
    file.open("data.dat", ios::in | ios::binary);	
    while (file.read((char*)&client, sizeof(clientData))) {
        if (client.accNum != 0) {
            sk++;
        }	
    }
    cout << "Total bank records: " << sk << " records. " << endl;
    file.close();	
}

void createBackup() {
    char symbol;	
    fstream file("data.dat", ios::in | ios::binary);
    fstream file_copy("backup.dat", ios::out | ios::binary);

    file.get(symbol);
    while (file) {
        file_copy.put(symbol);
        file.get(symbol);	
    }
    file.close();
    file_copy.close();
}

void exitProgram() {
    cout << endl;
    cout << "You have successfully exited the bank database." << endl;	
}

