//Author: Yenshae
//Class: Fundamentals of Computer Science II
//Professor Melissa Holme
//Project: Class Part3
//Date: 2 / 19 / 2025


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "people.h"
#include "student.h"
using namespace std;

	int main() {
		vector<Student> Roster;

		Student Person1("John",50,20,90,"Computer Science",4.0);
		Person1.printStudent();
		Person1.setSID(9);

		Course class1(12, "Intro to Computer Science", "Fall", 3);
		Course class2(13, "Psychology 101", "Fall", 3);

		Person1.add_class(class1, 100);
		Person1.add_class(class2, 100);
		Person1.printTranscript();

		Student Person2("Jane", 40, 20, 81, "Mechanical Engineering", 4.0);
		
		Course class3(15, "Stress Mechanics", "Fall", 3);
		Course class4(16, "Streess Mechanics Lab", "Fall", 3);
		

		Person2.add_class(class3, 100);
		Person2.add_class(class4, 100);
		
		Roster.push_back(Person1);
		Roster.push_back(Person2);

		cout << "Roster:";
		for (int i = 0; i < Roster.size(); i++) {
			cout << Roster.at(i).getName() << " ";
		}

		return 0;
	}