#pragma once
#include <string>
#include <iostream>
using namespace std;

class Course
{

public:
	int CourseNum;
	int Credits;
	string CourseTitle;
	string Semester ;

	Course();
	Course(int coursenum, string coursetitle, string semester, int creds);


	void printCourse();


	string getCourseTitle();
	int getCourseNum();
	string getSemester();
	int getCredits();

	void setCredits(int creds);
	void setSemester(string semester);
	void setCourseNum(int coursenum);
	void setCourseTitle(string coursetitle);

};

