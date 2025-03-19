//Author: Yenshae
//Class: Fundamentals of Computer Science II
//Professor Melissa Holme
//Project: Class Part2
//Date: 2 / 19 / 2025


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;


class people {
private:
	string Name;
	int AttributesID;
	int Age;
public:
	void print() {
		cout << "Name: " << Name << "\r\nAge: " << Age << "\r\nAttributesID: " << AttributesID;
	}


	int getID() {
		return AttributesID;
	}
	string getName() {
		return Name;
	}

	int getAge() {
		return Age;
	}

	void setID(int x) {
		AttributesID = x;
	}
	void setName(string x) {
		Name = x;
	}
	void setAge(int x) {
		Age = x;
	}
};

class student : public people {
private:
	int StudentID;
	string Major;
	float GPA;
public:
	void printStudent() {
		cout << "\r\nStudentID: " << StudentID << "\r\nMajor " << Major << "\r\nGPA: " << GPA;
	}
	int getSID() {
		return StudentID;

	}
	void setSID(int x) {
		StudentID = x;
	}

	float getGPA() {
		return GPA;
	}
	void setGPA(float x) {
		GPA = x;
			
	}
	string getMajor() {
		return Major;
	}
	void setMajor(string x) {
		Major = x;
	}

};


int main() {
	student Person1;
	Person1.setAge(20);
	Person1.setName("John");
	Person1.setID(12312241);
	Person1.setSID(123123);
	Person1.setGPA(3.2);
	Person1.setMajor("Comp Sci");
	Person1.print();
	Person1.printStudent();
	cout << "\r\nGet Tests: \r\nName: " << Person1.getName() << "\r\nMajor: " << Person1.getMajor() << "\r\nGPA: " << Person1.getGPA();
	return 0;


}