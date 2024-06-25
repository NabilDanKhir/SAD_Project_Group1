#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "register.cpp"
#include "mainPage.cpp"

using namespace std;

void header();
void login();
bool loadUserData(vector<string>& ids, vector<string>& passwords, vector<string>& names);
bool validateCredentials(const vector<string>& ids, const vector<string>& passwords, vector<string>& names, const string& id, const string& pass, string& userName);

const string USER_DATA_FILE = "idnum.dat";
const string PASS_DATA_FILE = "password.dat";
const string NAME_DATA_FILE = "username.dat";

int main() {
    int opt;
    bool input_ok;

    while (true) {
        header();
        cout << endl;
        cout << "\tWelcome to Online Voting System (OVS). An Initiative to Simplify and Optimise the Process." << endl << endl;
        cout << "Please Login or Register an Account to Start: " << endl;

        cout << "1) Login" << endl;
        cout << "2) Register" << endl;
        cout << "3) See Current Result" << endl;
        cout << "4) Exit" << endl << endl;

        do {
            cout << "Option: ";
            cin >> opt;

            if (opt < 1 || opt > 4) {
                cout << endl;
                cout << "Error: Input is out of bounds. Please re-enter." << endl;
                input_ok = false;
            }
            else if (cin.fail()) {
                cout << endl;
                cout << "Error: Input is not an integer. Please re-enter." << endl;
                input_ok = false;
            }
            else {
                input_ok = true;
            }

            cin.clear();
            cin.ignore();
            cout << endl;

        } while (!input_ok);

        switch (opt) {
        case 1:
            system("cls");
            login();
            break;
        case 2:
            system("cls");
            registerAcc();
            break;
        case 3:
            system("cls");
            displayResult();
            cout << endl;
            system("pause");
            break;
        case 4:
            cout << endl << "Thank you for using our Online Voting System! Goodbye!" << endl << endl;
            return 0;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }

        system("cls");
    }

    return 0;
}

void header() {
    cout << "           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%-===-#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%=-%%%=-%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%%%%  %%%%%%%%%%%%%%%====-#%%%%%%%%%%%%%*  %%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%=--  ----------------: ----------------:  --+%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%*++  +++++++++++=:++.   .=+.-++++++++++=  ++*%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%*::=-%%%%%%%%%%%#-%%%+:*%%%.*%%%%%%%%%%#-=::*%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%- =%%**%%%%%%%%%%==%%+.+%%-+%%%%%%%%%%#*%%* =%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%%=..-*%%%%%%%%%%%%*=-   :-#%%%%%%%%%%%%+-. =%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%%+:.=%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#:.:=%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%-=#-+:#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%:#:*+=%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%-*%#-%#:*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*:#%:*%+=%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%:*%%#-%%%-+%%%%%%%%%%%%%%%%%%%%%%%%%%%+:%%%:*%%+:#%%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%#:*%%%#-%%%%=+%%%%%%%%%%%%%%%%%%%%%%%%%==%%%%:*%%%#:#%%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%+:#%%%%#-%%%%%=-%%%%%%%%%%%%%%%%%%%%%%%==%%%%%:*%%%%%-#%%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%+=%%%%%%#-%%%%%%+:#%%%%%%%%%%%%%%%%%%%#-+%%%%%%:*%%%%%#:*%%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%+=%%%%%%%#-%%%%%%%#:%%%%%%%%%%%%%%%%%%*:#%%%%%%%:*%%%%%%%-=%%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%=-%%%%%%%%#-%%%%%%%%*:#%%%%%%%%%%%%%%%*:#%%%%%%%%:*%%%%%%%%=-%%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%-+%%%%%%%%%#-%%%%%%%%%#:*%%%%%%%%%%%%%*-%%%%%%%%%%:*%%%%%%%%%*-%%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%-#%%%%%%%%%%#-%%%%%%%%%%%-=%%%%%%%%%%%+:%%%%%%%%%%%:*%%%%%%%%%%*-%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%#:*%%%%%%%%%%%#-%%%%%%%%%%%%+=%%%%%%%%%-=%%%%%%%%%%%%:*%%%%%%%%%%%*:#%%%%%%%%" << endl;
    cout << "           %%%%%%%*:#%%%%%%%%%%%%#-%%%%%%%%%%%%%+-%%%%%%%-*%%%%%%%%%%%%%:*%%%%%%%%%%%%#:*%%%%%%%" << endl;
    cout << "           %%%%%%%. .............. .............. +%%%%%* ..............  ..............-%%%%%%%" << endl;
    cout << "           %%%%%%%+                              .%%%%%%%.                              +%%%%%%%" << endl;
    cout << "           %%%%%%%%*:                           -%%%%%%%%#-                           :+%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%#=-::::::::::::::::::::-=+%%%%%%%%%%%%%*=:::::::::::::::::::::-+#%%%%%%%%%%" << endl;
    cout << "           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << endl << endl;
    cout << "#    #    ##    ######    #      #   #    ### #            ### #  #   #     ### #  ######    ### #   #   #" << endl;
    cout << "##   #   ## #     #      ##     ##   #   ##  #            ##  #   #   ##   ##  #     #      ##  #   ### ##" << endl;
    cout << "##   #  ##   #   ##      ##     ###  #  ##                ##      ##  ##   ##       ##     ##       ######" << endl;
    cout << "##  ##  ##   #   ##      ##     #### #  ## ####            ####    #####    ####    ##     ####     ## # #" << endl;
    cout << " ## #   ##   #   ##      ##     ## ###  ##   #               ###      ##      ###   ##     ##       ##   #" << endl;
    cout << " ####   ##   #   ##  #   ##     ##  ##  ##   #            #   ##  #   ##   #   ##   ##  #  ##   #   ##   #" << endl;
    cout << "  ##     ## #    ### #   #      #    #  ### ##            ## ###  ## ###   ## ###   ### #  ### ##   #    #" << endl;
    cout << "  ##      ##      ###   #      #     #   #### #          # ####    ####   # ####     ###    #### # #    ###" << endl;
}

void login() {
    string id, pass, userName;
    vector<string> uID, uPass, uName;

    if (!loadUserData(uID, uPass, uName)) {
        return;
    }

    cout << "ID Num (e.g. 010101101111): ";
    cin >> id;
    cout << "Password: ";
    cin >> pass;

    if (validateCredentials(uID, uPass, uName, id, pass, userName)) {
        cout << endl << endl;
        cout << "Login Successful! Welcome, " << userName << "." << endl;
        system("pause");
        system("cls");
        cout << "Press your fingerprint to verify.........." << endl;
        system("pause");
        system("cls");
        home(id);
    }
    else {
        cout << "Invalid ID or Password. Please retry." << endl;
        system("pause");
        system("cls");
    }
}

bool loadUserData(vector<string>& ids, vector<string>& passwords, vector<string>& names) {
    ifstream userDetail(USER_DATA_FILE);
    ifstream passDetail(PASS_DATA_FILE);
    ifstream nameDetail(NAME_DATA_FILE);

    if (!userDetail.is_open()) {
        cerr << "Error opening user data file: " << USER_DATA_FILE << endl;
        return false;
    }
    if (!passDetail.is_open()) {
        cerr << "Error opening password data file: " << PASS_DATA_FILE << endl;
        return false;
    }
    if (!nameDetail.is_open()) {
        cerr << "Error opening name data file: " << NAME_DATA_FILE << endl;
        return false;
    }

    string id, pass, name;
    while (userDetail >> id && passDetail >> pass && nameDetail >> name) {
        ids.push_back(id);
        passwords.push_back(pass);
        names.push_back(name);
    }

    userDetail.close();
    passDetail.close();
    nameDetail.close();
    return true;
}

bool validateCredentials(const vector<string>& ids, const vector<string>& passwords, vector<string>& names, const string& id, const string& pass, string& userName) {
    for (size_t i = 0; i < ids.size(); ++i) {
        if (ids[i] == id && passwords[i] == pass) {
            userName = names[i];
            return true;
        }
    }
    return false;
}
