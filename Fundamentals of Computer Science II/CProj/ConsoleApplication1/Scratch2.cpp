#include <iostream>
#include <string>
using namespace std;
int main() {
	string fullName;
	cout << "Type your full name: ";
	// comment and uncomment the next two lines to test
	//getline (cin, fullName);
	cin >> fullName;
	cout << "Your name is: " << fullName;
	return 0;
}