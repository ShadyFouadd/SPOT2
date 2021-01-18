#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
#include <map>
#include<string>

//A full study plan for as student
class StudyPlan:public Drawable
{
	


	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	vector<AcademicYear*>* plan= new vector<AcademicYear*>;	//plan is a list of academic years

	string PlanNotes;
	void instantiatePlan();
	map<int, FILTERS> credProblemMap;
	map<Course*, int> offeringProblemMap;
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	bool DeleteCourse(Course* pC, int year, SEMESTER sem,int orderOfCourse);
	void DeleteAll();
	void virtual DrawMe(GUI*) const;
	AcademicYear* getAcadamicYearAt(int year);
	//This function will determine topLeft and bottom right of each cours and academicyEAR
	void calculateGraphicsInfoForEachItem(int lastY);
	Course* getCourseAtGraphicsInfo(graphicsInfo point);
	Course* getCourseAtGraphicsInfo(graphicsInfo point, SEMESTER& deletedSemester, int& deletedYear, int& orderOfCourse);
	void getSemAndYearForPoint(int x, int y, SEMESTER& sem,int& year);
	virtual ~StudyPlan();
	////
	bool virtual checkCReqS();
	bool virtual checkCReqD();
	void virtual drawCourseDependencies(GUI* pGUI, depTypte dType);
	void virtual drawCourseDependencies(GUI* pGUI, depTypte dType, Course*);
	Course* getCourseByCode(Course_Code code) const;
	bool stringIsEqual(string& f, string& s) const;
	////
	void setMap(int, FILTERS);
	void setMap(Course*, int);
};

