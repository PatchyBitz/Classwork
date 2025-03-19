#include <iostream>

using namespace std;

void printArray(int arr[]) {
	cout << "\n";
	for (int i = 0; i < 5; i++) {
		cout << arr[i] << "  ";
	}
	cout << "\n";
}

void changeArray(int arr[]) {
	cout << "\nchanging array values....";
	arr[0] = 42;
	arr[1] = 41;
}

int main() {
	int x = 0;
	double myArr[3] = { x, 2, 3 };
	//printArray(myArr);
	//changeArray(myArr);
	// 
	//printArray(myArr);

	// and just for fun....

	//cout <<   myArr << "\n";          // print the name of the array
	cout << & myArr[1] << "\n";    // print the address of the first element
	cout << & myArr[2] << "\n";
	cout << & myArr[3] << "\n";
	cout << & myArr[4] << "\n";
	cout << & myArr[5] << "\n";
	myArr[6] = 43;
	// and just for funsies, let's print the address of a variable
	cout << "variable x is stored at " << &x << " and its value is " << x;

	return 0;
}