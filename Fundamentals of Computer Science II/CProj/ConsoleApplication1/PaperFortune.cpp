/*
Author: Yenshae
Assignment: Paper Fortune Teller
Class: Intro to Computer Science II
Professor: Melissa Holmes
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


string fortune() {
	int choice;
	cout << "\nPlease pick a number";
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
}
int ask() {
	cout << "\nPlease pick a number ";
	int answer;
	cin >> answer;
	return answer % 2;
}


int evenset[4] = {3,4,5,7}; /*Poorly named as they're not actually even or odd. The sets are determined by direction you open the teller first*/
int oddset[4] = {1,6,8,2};
int startset[4] = { 2,4,1,3 };

int main() {
	srand((unsigned) time(0));
	int a = rand() % 2; // This determines which direction the teller is opening first as that affects the set of numbers that will be shown.

	display(startset);

	if (a == 1){

		if (ask() == 0) {
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
		if (ask() == 0) {
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
	
	return 0;}


