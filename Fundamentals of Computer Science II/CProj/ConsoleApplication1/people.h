#pragma once
#include <string>
using namespace std;

class people
{
public:
	people();
	people(string name, int attribute, int age);

	string Name;
	int AttributesID;
	int Age;


	void print();
	int getID();
	string getName();

	int getAge();
	void setID(int x);
	void setName(string x);
	void setAge(int x);



private:
};




