#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;
int quest1[20];
int quest2[20];
int quest3[20];
int quest4[20];
int quest5[20];
int quest6[20];
int test;
void randoms(int a[],int size,int maxsize) { // Takes array and size of array and fills that many elements with random numbers between 0 and 9
	for (int i  = 0; i < size; i++) {
		a[i] = (rand() % maxsize) + 1;
	}
}
void knowns(int a[],int size, int known) { // Takes array and size of array and fills that many elements an array of known numbers between 0 and 9
	for (int i = 0; i < size; i++) {
		a[i] = (known) ;
	}
}
void disp(int a[], int size) {   // Found out from this that you must have the size of an array passed in as arrays passed into functions are just pointers and therefore have no size associated.
	for (int i = 0; i < size; i++) {
		cout << a[i];
		if (i < size - 1) { //Prevents trailing comma
		cout << ",";}
	}
}
void dispvect(vector<int> dis) { //Only used for one function that returns a vector as the answer
	int counter = 0;
	for (int i : dis) {
		cout << i;
		counter ++;
		if (counter < dis.size()) { //Prevents trailing comma
			cout << ",";}
	}
}
int largest(int a[], int size) { //Simply iterates through the list and if it finds a larger number, replaces buffer with it. 
	int large;
	large = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] > large){
			large = a[i];
		}
	}
	return large;
}
int linsearch(int a[], int size, int search){ //I wasn't in the lab for this one, but since python's index function also only returns the first index and I assumed this was Ok
	int flag = -1;
	for (int i = 0; i < size; i++) {
		if (a[i] == search){
			flag = i;
			break;
		}
	}
	return flag;
}
int seclargest(int a[], int size) { //Uses a stack of two. Uses the following rule: If number is greater than position 1 , move position 1's value to position 2, if not: check if larger than position two, if so, replace position 2, if none, iterate.
	int buf[2];
	buf[1] = 0;
	buf[0] = 0;
	for (int i = 0; i <= size; i++) {
		if (a[i] > buf[1]){
			buf[0] = buf[1];
			buf[1] = a[i];
		
		}
		else if (a[i] == buf[1]){
			// Intentionally blank like a pass statement
		}
		else if (a[i] > buf[0]){
			buf[0] = a[i];
		}
	}
	return buf[0];
}
bool comp(int a, int b){
	return a > b; 
}
vector<int> klargest(int a[],int size, int k){ // I could have done something similiar to my previous seclargest function, but I didn't want to use vectors yet. Moreover, due to k, time complexity gets wonky if I use my other method.
	sort(a, a + size,comp);					  // I also couldn't think of a better form to return the answer in.
	vector<int> answer;
	for (int i = 0; i < k; i++ ){
		answer.push_back(a[i]);
	}
	return answer;
}
bool even(int a){
	return a % 2 ==0;
}
void evenodd(int a[],int size){ // Taken from geeks for geeks. Doesn't retain order
	for (int i = 0; i < size; i++ ){
		if (a[i] % 2 == 0){
			a[i] = a[i] * -1;
		} 
	}
	sort(a,a+size);
	for (int i = 0; i < size; i++ ){
		if (a[i] < 0 ){
			a[i] = a[i] * -1;
		} 
	}
}

void reverse(int a[],int size){ //Swaps starting from both ends, doesn't use a vector which would be faster.

	for (int i = 0; i < size/2; i++ ){
		swap(a[i],a[size-i - 1 ]);
	} 
	}

int main() {
int inp = 0;

cout << "Beginning Question 1 - Largest number\n";
randoms(quest1,20,50);
disp(quest1,20);
cout << "\nLargest number in array is: " << largest(quest1,20);

cout << "\n\nBeginning Question 2 - Searching Array\n";
randoms(quest1,20,10);
disp(quest1,20);
cout << "\nPlease type in a number 1 - 10 and we'll search for it in the array: \n";
cin >> inp;
cout << inp << " was found at index: " << linsearch(quest1,20,inp);

cout << "\n\nBeginning Question 3 - Second Largest number\n";
randoms(quest1,20,90);
disp(quest1,20);
cout << "\nThe second largest number in the array is: " << seclargest(quest1,20);

cout << "\n\nBeginning Question 4 - K Largest number\n";
randoms(quest1,20,90);
disp(quest1,20);
cout << "\nPlease input how many of the largest numbers you'd like to find: ";
cin >> inp;
cout << "\nYour " << inp << " largest numbers are: ";
dispvect(klargest(quest1,20,inp));

cout << "\n\nBeginning Question 5 - Even and odds \n";
randoms(quest1,20,10);
disp (quest1, 20);
cout << "\nSorting...\n";
evenodd(quest1,20);
disp(quest1,20);

cout << "\n\nBeginning Question 6 - Reversing order \n";
randoms(quest1,20,10);
disp(quest1,20);
cout << "\nReversing...\n";
reverse(quest1,20);
disp(quest1,20);


}
