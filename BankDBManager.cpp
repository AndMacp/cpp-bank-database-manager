#include <iostream>
#include <fstream>
#include "mylib.h"

using namespace std;

struct clientData {
    int accNum;
    char name[25];
    char sur[25];
    float balance;	
};

int main() {
    int i;
    clientData blankClient = {0, "", "", 0};
    fstream file;
    file.open("data.dat", ios::app | ios::out | ios::binary);
    for (i = 0; i < 100; i++) {
        file.write((char*)&blankClient, sizeof(clientData));
    }
    file.close();	
	
    int x;	
    while (x != 9) {
        cout << "Bank database." << endl;
        cout << endl;
        cout << "1. Add a record." << endl;
        cout << "2. Delete a record." << endl;
        cout << "3. Display all records." << endl;
        cout << "4. Find a record." << endl;
        cout << "5. Modify account balance." << endl;
        cout << "6. Display debtors." << endl;
        cout << "7. Count records." << endl;
        cout << "8. Create a DB backup." << endl;
        cout << "9. Exit." << endl;
        cout << endl;
        cin >> x;	

        switch(x) {
            case 1: addRecord();
                    break;
            case 2: deleteRecord();
                    break;
            case 3: displayRecords();
                    break;	
            case 4: findRecord();
                    break;
            case 5: modifyBalance();
                    break;
            case 6: displayDebtors();
                    break;
            case 7: countRecords();
                    break;
            case 8: createBackup();
                    break;
            case 9: exitProgram();
                    break;
        }	
    }
}

