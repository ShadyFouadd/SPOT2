#pragma once
#include <string>
#include <list>
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"

//Base class for all types of courses
class Course : public Drawable
{
	const Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	const string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	string type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course_Code> CoReq;	//list of prerequisites
public:
	Course(Course_Code r_code,string r_title, int crd);
	void setPreReq(list<Course_Code>);
	void setCoReq(list<Course_Code>);
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	string getPreReqAsString() const;
	string getCoReqAsString() const;
	list<Course_Code> getPreReq()const;
	list<Course_Code> getCoReq()const;
	//Course* getCourseByCode(code) const;
	void DrawCourseDeps(GUI*, int x1, int y1, int x2, int y2, depTypte dType) const;
	void addPreReq(string preReq);
	void addCoReq(string CoReq);
	void DrawMe(GUI*) const;
	bool operator=(const Course& anotherCourse);
	virtual ~Course();

};
