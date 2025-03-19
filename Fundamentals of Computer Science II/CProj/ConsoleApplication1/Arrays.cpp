#include <iostream>
#include <random>
#include <time.h>
using namespace std;


int TwoD[5][5];
void randomize(int a[5][5]) { //Loops through each column then each element in each row and sets them to a random number
	for (int i = 0; i < 5; i++) {
		for (int y = 0; y < 5; y++)
			a[i][y] = rand() % 99 + 1;
	}
}

void display(int a[5][5]) { //Loops through each column then each element in each row. Print's out each element.
	for (int i = 0; i < 5; i++) {
		cout << "\n";
		for (int y = 0; y < 5;  y++)
			if (a[i][y] >= 10) { // checks whether the number is greater than 10, if so, skips adding a leading space for padding
				cout << a[i][y] << " ";
			}
			else if (a[i][y] < 0) {
				cout << a[i][y] << " ";
			}
			else {
				cout << " " << a[i][y] << " ";
			}
	}
}

void sumrow(int a[5][5]) { //Same as previous display code, but adds a counter variable that is displayed at the end of each outer loop (columns)
	int sum = 0;		// Yes I realized late that the entire program has the rows and columns backwards, but this is corrected where needed.
	for (int i = 0; i < 5; i++) {
		cout << "\n";
		sum = 0;
		for (int y = 0; y < 5; y++){
			if (a[i][y] >= 10) {
				cout << a[i][y] << " ";
			}
			else {
				cout << " " << a[i][y] << " ";
			}
		sum += a[i][y];}
		cout << " Sum: " << sum;

	}
}

void sumall(int a[5][5]) { //Simply stops reseting the sum at the beginning of each column loop so the sum is total for the entire array, and then outputs it.
	int sum = 0;
	for (int i = 0; i < 5; i++) {
		cout << "\n";
		//sum = 0;
		for (int y = 0; y < 5; y++) {
			if (a[i][y] >= 10) {
				cout << a[i][y] << " ";
			}
			else {
				cout << " " << a[i][y] << " ";
			}
			sum += a[i][y];
		}

	}
	cout << " Sum: " << sum;
}

void fullarr(int a[5][5]) { // Does all of the previous but uses a second portion to sum and display the column sums. Also gives each character 3 spaces for display for alignment reasons.
	int sum = 0;
	int sumr = 0;
	int sumc = 0;
	cout << "\n                     Sum of Row";
	for (int x = 0; x < 5; x++) {
		cout << "\n";
		sumr = 0;
		for (int y = 0; y < 5; y++) {
			if (a[x][y] < 10) {
				cout << a[x][y] << "   ";
			}
			else {
				cout << "" << a[x][y] << "  ";
			}
			sumr += a[x][y];
			sum += a[x][y];
		}
		cout << " " << sumr;
	}
	cout << "\n";
	for (int y = 0; y < 5; y++) {

		sumc = 0;
		for (int x = 0; x < 5; x++) {
			/*if (a[x][y] > 10) {
				cout << a[x][y] << " ";
			}
			else {
				cout << " " << a[x][y] << " ";
			}*/
			sumc += a[x][y];
		}
		cout << sumc << " ";
	}
	cout << " Sum of Columns";
	cout << "\nTotal Sum: " << sum;
}

void spread(int y,int x,int b[5][5]) { //Doesn't take from previous functions as we're given the coordinates directly and can use that.
	x = x - 1; //Subtracts one to make desgination more natural since the array goes from 0 to 4, but people would select from 1-5 
	y = y - 1;
	//Various checks on the input incase it is outside the bounds of the array which my cause issues.
	if (x < 0) {
		cout << "Warning X is less than zero, shifting to positive.\n";
		x = x * -1;
	}
	if (y < 0) {
		cout << "Warning X is less than zero, shifting to positive.\n";
		y = y * -1;
	}

	if (x > 5) {
		cout << "Warning X is greater than size of array. Overflowing to other side\n";
		x = x % 5; 
	}
	else if (y > 5) {
		cout << "Warning Y is greater than size of array. Overflowing to other side\n";
		x = y % 5;
	}
	cout << "Original array:";
	display(b);
	b[x][y] = -1;
	//Block for checking if the designated spot is on the edge, and therefore won't roll over the -1 infection to the other side or tries to write to outside of array.
	if ((x - 1) >= 0) {   //Two conditions to check for the edges
		b[x - 1][y] = -1;
		
	}
	if ((x + 1) <= 4) {
		b[x + 1][y] = -1;
	}

	if ((y - 1) >= 0) {
		b[x][y-1] = -1;
		
	} 
	if ((y + 1) <= 4) {
		b[x][y+1] = -1;
	}

	if (x + 1 <= 4 and y + 1 <= 4) {
		b[x + 1][y + 1] = -1;
	}
	if (x + 1 <= 4 and y - 1 >= 0) {
		b[x + 1][y - 1] = -1;
	}

	if (x - 1 >= 0 and y + 1 <= 4) {
		b[x - 1][y + 1] = -1;
	}
	if (x - 1 >= 0 and y - 1 >= 0) {
		b[x - 1][y - 1] = -1;
	}


	cout << "\nNew array:";
	display(b);

}


int main() {
	//Main execution and presentation block
	int xinp;
	int yinp;
	cout << "Beginning Question 1-3: ";
	srand(time(NULL));
	randomize(TwoD);
	display(TwoD);
	cout << "\n\nBeginning Question 4: Write a function that calculates and returns the sum for each row.";
	sumrow(TwoD);
	cout << "\n\nBeginning Question 5: Write a function that calculates and returns the sum for the entire array.";
	sumall(TwoD);
	cout << "\n\nBeginning Question 6: Write a function, or a small collection of functions, that prints the array as rows and columns,\n\ralong with the sum of each row at the end of the row, and the sum of each column below the columns";
	fullarr(TwoD);
	cout << "\n\nBeginning Question 7: Spread Sim";
	cout << "\nPlease input x (Between 1 and 5)";
	cin >> xinp;
	cout << "\nPlease input y (Between 1 and 5)";
	cin >> yinp;
	spread(xinp, yinp, TwoD);
	return 0;
}