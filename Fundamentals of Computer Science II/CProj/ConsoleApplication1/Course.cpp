#include "Course.h"
#include <string>
#include <iostream>
using namespace std;

int CourseNum;
string CourseTitle;
string Semester;
int Credits;

Course::Course() {
	CourseNum = 0;
	CourseTitle = "None";
	Semester = "None";
	Credits = 0;
}
Course::Course(int coursenum,string coursetitle,string semester,int creds) {
	CourseNum = coursenum;
	CourseTitle = coursetitle;
	Semester = semester;
	Credits = creds;
};

void Course::printCourse() {
	cout << "\n\rCourseNumber: " << CourseNum << "\n\rCourseTitle: " << CourseTitle << "\n\rSemester: " << Semester << "\n\rCredits: " << Credits;
}

string Course::getCourseTitle() {
	return CourseTitle;
}
int Course::getCourseNum() {
	return CourseNum;
}

string Course::getSemester() {
	return Semester;
}

int Course::getCredits() {
	return Credits;
}

void Course::setCredits(int creds) {
	Credits = creds;
}

void Course::setSemester(string Semester) {
	Semester;
}

void Course::setCourseNum(int coursenum) {
	CourseNum = coursenum;
}

void Course::setCourseTitle(string coursetitle) {
	CourseTitle = coursetitle;
}


