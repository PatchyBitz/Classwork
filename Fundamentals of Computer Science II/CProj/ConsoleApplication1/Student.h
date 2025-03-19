#pragma once
#include "people.h"
#include <vector>
#include "course.h"
#include <string>
using namespace std;

class Student : public people
{
public:

	int StudentID;
	string Major;
	float GPA;
	void add_class(Course clas, float grade);


	Student(string name, int attribute, int age, int studentid, string major, float gpa);

	Student();


	void setMajor(string x);
	void setGPA(float x);
	void setSID(int x);

	int getSID();
	float getGPA();
	string getMajor();


	vector<Course> Transcript_Classes;
	vector<float> Transcript_Grades;
	void printStudent();
	void printTranscript();

private:
};

