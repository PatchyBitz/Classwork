#include "Student.h"
#include "people.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//string Name;
//int AttributesID;
//int Age;

int StudentID;
string Major;
float GPA;



void Student::printStudent() {
	cout << "\r\nName: " <<Name << "\r\nAttributesID: "<< AttributesID << "\r\nGPA: " << GPA  << "\r\nStudentID: " << StudentID << "\r\nMajor: " << Major;
}

Student::Student() {
	Name = "John";
	AttributesID = 0;
	Age = 20;
	GPA = 2;
	Major = "Unenrolled";
	StudentID = 0;
	
}

vector<Course> Transcript_Classes;
vector<float> Transcript_Grades;
vector<int> Transcript_Credits;

void Student::add_class(Course clas,float grade) {
	Transcript_Classes.push_back(clas);
	Transcript_Grades.push_back(grade);
	Transcript_Credits.push_back(clas.getCredits());
}

void Student::printTranscript() {
	float sum = 0;
	cout << "\n\r=====Transcript=====\n";
	for (int i = 0; i < Transcript_Classes.size(); i++) {
		cout << Transcript_Classes.at(i).getCourseTitle(); //Needs to return a string using a function or else COUT won't work.
		cout << "\nGrades: " << Transcript_Grades.at(i);
		cout << "\nCredits: " << Transcript_Classes.at(i).getCredits();
		cout << "\n\n";
		sum += Transcript_Grades.at(i);
	}
	cout << "\nAvg GPA: " << sum/Transcript_Classes.size() <<"\n";
}


Student::Student(string name, int attribute, int age,int studentid, string major, float gpa) {
	Name = name;
	AttributesID = attribute;
	Age = age;
	GPA = gpa;
	Major = major;
	StudentID = studentid;
}

int Student::getSID() {
	return StudentID;

}
void Student::setSID(int x) {
	StudentID = x;
}

float Student::getGPA() {
	return GPA;
}
void Student::setGPA(float x) {
	GPA = x;

}

string Student::getMajor() {
	return Major;
}
void Student::setMajor(string x) {
	Major = x;
}