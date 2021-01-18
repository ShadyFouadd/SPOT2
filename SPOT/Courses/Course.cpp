#include "Course.h"
#include "../GUI/GUI.h"
#include <iostream>
using namespace std;
Course::Course(Course_Code r_code, string r_title, int crd):code(r_code),Title(r_title)
{
	credits = crd;
}

void Course::setPreReq(list<Course_Code> pr)
{
	this->PreReq = pr;
}

void Course::setCoReq(list<Course_Code> cr)
{
	this->CoReq = cr;
}

Course::~Course()
{
}

Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}

//return course credits
int Course::getCredits() const
{
	return credits;
}


string Course::getPreReqAsString() const
{
	string tempString = "";
	//Review for understanding.
	for (std::list<std::string>::const_iterator i = PreReq.begin(); i != PreReq.end(); ++i)
	{
		tempString = tempString + (*i);
		//if it's not the last element of that iterate then add , 
		if (i != PreReq.end())
			tempString = tempString + ", ";
	}
	if (tempString == "")
		return "None";
	//if by the end of the sentence and still not returned None then add . 
	tempString = tempString + ". ";

	return tempString;
}

string Course::getCoReqAsString() const
{
	string tempString = "";
	//Understand little more why that here
	for (std::list<std::string>::const_iterator i = CoReq.begin(); i != CoReq.end(); ++i)
	{
		tempString = tempString + (*i);
		//if it's not the last element of that iterate then add , 
		if (i != CoReq.end())
			tempString = tempString + ", ";
	}
	if (tempString == "")
		return "None";
	//if by the end of the sentence and still not returned None then add . 
	tempString = tempString + ". ";
	return tempString;
}

list<Course_Code> Course::getPreReq() const
{
	return PreReq;
}

list<Course_Code> Course::getCoReq() const
{
	return CoReq;
}

void Course::addPreReq(string preReq)
{
	this->PreReq.push_back(preReq);
}


void Course::addCoReq(string CoReq)
{
	this->CoReq.push_back(CoReq);
}

void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}

bool Course::operator=(const Course& anotherCourse)
{
	if (this->getCode() == anotherCourse.getCode())
		return true;
	return false;
}
void Course::DrawCourseDeps(GUI* pGUI, int x1, int y1, int x2, int y2, depTypte dType) const
{
	pGUI->DrawDeps(x1, y1, x2, y2, dType);
}
/*
Course* Course::getCourseByCode(this->code) const
{
	
}
*/