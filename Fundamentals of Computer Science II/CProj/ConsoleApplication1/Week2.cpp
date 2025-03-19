#include <iostream>
using namespace std;

string uName;
int uYear, uNum1, uNum2,sNum,eNum,eSum,pairs,uInp,uSum;
long BigNum;


int main(){
	cout << "Beginning Question 1 \n\n";
	cout << "Please enter your name. \n"; // Solution to Question 1
	cin >> uName;
	cout << "Hello " << uName;

	cout << "\n\nBeginning Question 2 \n\n"; 
	cout << "What year where you born?: ";  // Solution to Question 2
	cin >> uYear;
	cout << "You are " << (2024 - uYear) << " years old";

	cout << "\n\nBeginning Question 3 \n\n"; // Solution to Question 3
	cout << "Please enter your first number: ";
	cin >> uNum1;
	cout << "Please enter your second number: ";
	cin >> uNum2;
	if (uNum1 == uNum2) {
		cout << "The numbers are equal";
	}
	else {
		cout << "The numbers are not equal";
}															
	cout << "\n\nBeginning Question 4 \n\n"; // Solution to Question 5 
	eNum = 101;                              // I wanted to create a solution that could pick any two numbers and get the sum of evens but I didn't need to and i'm too tired.
	sNum = 1;                                // This process finds how many pairs there are then iterates up till the pairs while multiplying by 2 and summing it.
	cout << "Start number is "
		<< sNum
		<< " End Number is "
		<< eNum
		<< "\n Summing even numbers...";
	if (eNum % 2 == 0) {
		pairs = eNum / 2;
	}
	else {
		pairs = (eNum + 1) / 2;
	}

	int counter = 0;

	while (counter < pairs) { 
		eSum += (2*counter);
		counter++;
	}
	cout << "\n The sum of evens between " << sNum << " and " << eNum << " is " << eSum;


	cout << "\n\nBeginning Question 5 \n";
	do {
		cout << "Please enter an integer to add to the pile or -999 to exit ";
		cin >> uInp;
		uSum += uInp;
	} while (uInp != -999 );
	cout << "Your final sum is: " << uSum;

	return 0;

}