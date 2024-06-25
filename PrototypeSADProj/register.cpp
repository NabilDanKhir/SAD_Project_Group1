#include <iostream>
#include <fstream>
using namespace std;

void inputFunction();

int accountCount = 0;
const int idSize = 50;

struct UserID {
	
	string userName;
	string user[idSize];
	string id;
	string UserIDNum[idSize];
	string passWord;
	string pass[50];
};

UserID regUser;

bool registerAcc() {

	fstream nameFile;
	fstream passFile;
	fstream idFile;
	nameFile.open("username.dat", ios::app | ios::in | ios::out);
	passFile.open("password.dat", ios::app | ios::in | ios::out);
	idFile.open("idnum.dat", ios::app | ios::in | ios::out);


	cout << endl << endl;
	cout << "-----------------------------------------------------REGISTER-------------------------------------------------------" << endl;


	inputFunction();

	if (accountCount > idSize) {
		cout << "The system is currently overloaded. Please re-try in another hour" << endl;
		return false;
	}
	else {
		for (int i = 0; i < accountCount; ++i) {
			while (regUser.user[i] == regUser.userName && regUser.UserIDNum[i] == regUser.id) {
				cout << "Username / ID already exist" << endl;
				inputFunction();
				
			}  
		}
	}

	regUser.user[accountCount] = regUser.userName;
	nameFile << regUser.user[accountCount] << endl;
	regUser.pass[accountCount] = regUser.passWord;
	passFile << regUser.pass[accountCount] << endl;
	regUser.UserIDNum[accountCount] = regUser.id;
	idFile << regUser.UserIDNum[accountCount] << endl;
	accountCount++;
	cout << endl << endl;
	cout << "Account registered successfully" << endl << endl << endl;
	system("pause");
	nameFile.close();
	passFile.close();
	idFile.close();

}

void inputFunction() {

	cout << "Enter your username: ";
	cin >> regUser.userName;
	cout << "Enter your password: ";
	cin >> regUser.passWord;
	cout << "ID Num (e.g. 010101101111): ";
	cin >> regUser.id;
}