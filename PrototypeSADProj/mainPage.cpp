#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "result.cpp"

using namespace std;

void options();
int menu();
void candidateFill(vector<string>&);

const int arraySize = 6;
int opt = -1;
vector<string> candDate;

void home(string id) {
    options();
    opt = menu();
    if (opt > 0 && opt <= arraySize) {
        pollRes(opt, id, candDate);
        cout << endl;
    }
}

void options() {
    candidateFill(candDate);
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "\t\tCANDIDATE OPTIONS" << endl;
    cout << "--------------------------------------------------------------------------" << endl << endl;
    for (int i = 0; i < arraySize; i++) {
        if (i < candDate.size()) {
            cout << "\t" << i + 1 << ". | \t" << candDate[i] << endl << endl;
        }
    }
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "Press 0 to Leave and Log Out" << endl << endl;
}

void candidateFill(vector<string>& cName) {
    const string CAND_DATA_FILE = "candidate.dat";
    fstream candFile;
    candFile.open(CAND_DATA_FILE, ios::in);

    if (!candFile.is_open()) {
        cerr << "Error opening user data file: " << CAND_DATA_FILE << endl;
        return;
    }

    string candidate;
    while (getline(candFile, candidate)) {
        cName.push_back(candidate);
    }

    candFile.close();
}

int menu() {
    int choice;
    bool input_ok = false;
    char verif = 'n';

    while (!input_ok) {
        cout << "Enter your chosen option: ";
        cin >> choice;

        if (cin.fail()) {
            cout << endl;
            cout << "Error: Input is not an integer. Please re-enter." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (choice < 0 || choice > arraySize) {
            cout << endl;
            cout << "Error: Input is out of bounds. Please re-enter." << endl;
        }
        else {
            input_ok = true;
        }

        cout << endl;
    }

    do {
        cout << "Are you sure of your choice? (Y/N): ";
        cin >> verif;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (verif == 'n' || verif == 'N');

    return choice;
}