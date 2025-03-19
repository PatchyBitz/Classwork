#include "people.h"
#include <string>
#include <iostream>
using namespace std;

	
string Name;
int AttributesID;
int Age;


	people::people(string name, int attribute, int age) {
		Name = name;
		AttributesID = attribute;
		Age = age;
	}

	people::people() {
		Name = "John";
		AttributesID = 0;
		Age = 20;
	}
	void people::print() {
		cout << "Name: " << Name << "\r\nAge: " << Age << "\r\nAttributesID: " << AttributesID;
	}
	
	int people::getID() {
		return AttributesID;
	}
	string people::getName() {
		return Name;
	}

	int people::getAge() {
		return Age;
	}

	void people::setID(int x) {
		AttributesID = x;
	}
	void people::setName(string x) {
		Name = x;
	}
	void people::setAge(int x) {
		Age = x;
	}