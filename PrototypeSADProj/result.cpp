#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int candidateAmount = 6;
int candRes[candidateAmount] = { 0 };
const string RESULT_FILE = "result.dat";
const string VOTED_USERS_FILE = "voted_users.dat";

bool hasVoted(const string&);
void recordVote(const string&);
void displayResult();
void saveResult(vector<string>&);
void pollRes(int, string, vector<string>&);

bool hasVoted(const string& userID) {
    ifstream votedFile(VOTED_USERS_FILE);
    if (!votedFile.is_open()) {
        cerr << "Error opening voted users file." << endl;
        return true;
    }

    string line;
    while (getline(votedFile, line)) {
        if (line == userID) {
            votedFile.close();
            return true; 
        }
    }

    votedFile.close();
    return false;
}

void recordVote(const string& userID) {
    ofstream votedFile(VOTED_USERS_FILE, ios::app);
    if (!votedFile.is_open()) {
        cerr << "Error opening voted users file for recording." << endl;
        return;
    }

    votedFile << userID << endl;
    votedFile.close();
}

void saveResult(vector<string>& nama) {
    ofstream resultFile(RESULT_FILE);
    if (!resultFile.is_open()) {
        cerr << "Error opening result file for writing." << endl;
        return;
    }

    for (int i = 0; i < candidateAmount; i++) {
        resultFile << "Candidate " << i+1 << ": " << candRes[i] << "\t" << nama[i] << endl;
    }

    resultFile.close();

    cout << endl << endl;
}

void displayResult() {
    ifstream resultFile(RESULT_FILE);
    if (!resultFile.is_open()) {
        cerr << "Error opening result file." << endl;
        return;
    }

    string line;
    while (getline(resultFile, line)) {
        cout << line << endl;
    }

    resultFile.close();
}

void pollRes(int result, string uID, vector<string>& name) {
    if (result > 0 && result <= candidateAmount) {
        string current_user_id = uID;

        if (hasVoted(current_user_id)) {
            cout << "You have already voted. You cannot vote again." << endl;
        }
        else {
            candRes[result - 1] += 1;

            saveResult(name);

            displayResult();

            recordVote(current_user_id);
        }
    }
    else {
        cout << "Invalid candidate selection." << endl;
    }

    system("pause");
}