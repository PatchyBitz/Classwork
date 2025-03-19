/*
Author: Yenshae
Assignment: Paper Fortune Teller V2
Class: Intro to Computer Science II
Professor: Melissa Holmes
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int evenset[4] = {3,4,5,7}; /*Poorly named as they're not actually even or odd. The sets are determined by direction you open the teller first*/
int oddset[4] = {1,6,8,2};
string colors[4] = { "White","Green","Blue","Orange" }; // Array of string colors, easier since I could just tweak my display function
int play = 0;
//int startset[4] = {2,4,1,3};
string userInp;



// Functions
string fortune() {
	int choice;
	cout << "\nPlease pick a number ";
	cin >> choice;

	switch (choice) {
	case 3: 
	case 4:
		return "Fortune 1";
	case 1:
	case 2:
		return "Fortune 2";
	case 6:
	case 8:
		return "Fortune 3";
	case 7:
	case 5:
		return "Fortune 4";

	}

}
void display(int set[4]) {
	cout << set[0] << "  " << set[1];
	cout <<'\n' << set[3] << "  " << set[2];
} // Displays the choices
void displayc(string set[4]) {
	cout << set[0] << "  " << set[1];
	cout << '\n' << set[3] << "  " << set[2];
} 
//Asks for choice
int ask() {
	cout << "\nPlease pick a number ";
	int answer;
	cin >> answer;
	return answer % 2;
}
int askc() {
	cout << "\nPlease pick a color ";
	string answerc;
	int answer;
	cin >> answerc;
	answer = answerc.length();
	return answer % 2;
} 
void playask() {
	cin >> userInp;
	string cleanInp;
	for (int i = 0; i < userInp.length(); i++) {
		cleanInp += tolower(userInp[i]);
	}
	if (cleanInp == "yes" || cleanInp == "y") {
		play = 1;

	}
	else if (cleanInp == "no" || cleanInp == "n") {
		cout << "Goodbye";
		play = 0;
	}
} // Asks to play and sets flag


int main() {
	srand((unsigned)time(0));
	cout <<  "Welcome to the fortune picker! Would you like to pick your fortune? ";
	playask();
	while (play==1) {
		int a = rand() % 2; // This determines which direction the teller is opening first as that affects the set of numbers that will be shown.
		//display(startset);
		displayc(colors);
		if (a == 1) {

			if (askc() == 0) {
				display(evenset);
			}
			else {
				display(oddset);
			}


			if (ask() == 0) {
				display(evenset);
			}
			else {
				display(oddset);
			}
			cout << fortune();
		}


		else {
			if (askc() == 0) {
				display(oddset);
			}
			else {
				display(evenset);
			}

			if (ask() == 0) {
				display(oddset);
			}
			else {
				display(evenset);
			}
			cout << fortune();
		}
		cout << "\nWould you like to play again? ";
		playask();
	}
	
	return 0;}


