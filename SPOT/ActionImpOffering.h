#pragma once
#include "Actions//Action.h"
#include "Rules.h"
#include "DEFs.h"
#include <vector>
#include <map>
class ActionImpOffering :
	public Action
{
public:
	ActionImpOffering(Registrar*);
	bool virtual Execute();
	virtual ~ActionImpOffering();
	map<Course_Code, SEMESTER> OfferingCourses;
	bool checkOffering(Course_Code, SEMESTER);
};