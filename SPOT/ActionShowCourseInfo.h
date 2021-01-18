#pragma once
#include "Actions/Action.h"
#include "Courses/Course.h"
#include "StudyPlan/StudyPlan.h"

//#include "DEFs.h"
class ActionShowCourseInfo
	:public Action
{
	Course* crsClicked;
	StudyPlan* pS;
	GUI* pGUI;
public:
	ActionShowCourseInfo(Registrar*,Course* crsClicked);
	bool virtual Execute();
	virtual ~ActionShowCourseInfo();
};

