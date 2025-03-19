//Author: Yenshae
//Class: Fundamentals of Computer Science II
//Professor Melissa Holme
//Project: Class Part1
//Date: 2 / 19 / 2025


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;


class people {
public:
	string Name;
	int AttributesID;
	int Age;
	void print() {
		cout << "Name: " << Name << "\r\nAge: " << Age << "\r\nAttributesID: " << AttributesID;
	}




};

class student : public people {
public:
	int StudentID;
	string Major;
	float GPA;
	void printStudent() {
		cout << "\r\nStudentID: " << StudentID << "\r\nMajor " << Major << "\r\nGPA: " << GPA;
	}


};


int main() {
	student Person1;
	Person1.Age = 20;
	Person1.Name = "John";
	Person1.AttributesID = 12312241;
	Person1.StudentID = 123123;
	Person1.Major = "Comp Sci";
	Person1.GPA = 3.2;
	Person1.print();
	Person1.printStudent();
	return 0;


}