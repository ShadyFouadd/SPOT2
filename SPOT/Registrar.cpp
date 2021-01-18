#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "ActionImportCourseCatalog.h"
#include "ActionImportRules.h"
#include "EmptyAction.h"
#include <iostream>
#include "EmptyAction.h"
#include "ActionImportDefaulPlan.h"
#include "ActionImpOffering.h"
#include "ActionImpReq.h"
#include "ActionDeleteCourse.h"
#include "ActionShowCourseInfo.h"
#include  "Student.h"
#include"ActionAddNotes.h"
#include"ActionShowNotes.h"
#include "ActionChangeByCode.h"
#include "ActionDragAndDropCrs.h"
#include "ActionSignUserUp.h"
#include "ActionDisplayFilters.h"

using namespace std;
Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	pSignedStudent = new Student();
}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//Sets the courses offering data
void Registrar::setOfferingRules(Rules newRules)
{
	for (int i = 0; i < 5; i++)
	{
		RegRules.OffringsList[i] = newRules.OffringsList[i];
	}

}

//sets the Rules 
void Registrar::setRules(Rules newRules)
{
	RegRules.TotalCredits = newRules.TotalCredits;
	RegRules.SemMinCredit = 12;
	RegRules.SemMaxCredit = 18;
	RegRules.ReqUnivCredits = newRules.ReqUnivCredits;
	RegRules.ReqTrackCredits = newRules.ReqTrackCredits;
	RegRules.ReqMajorCredits = newRules.ReqMajorCredits;
	RegRules.ConcentrationsNumber = newRules.ConcentrationsNumber;
	RegRules.ReqConcentrationCredits = newRules.ReqConcentrationCredits;
	RegRules.UnivCompulsory = newRules.UnivCompulsory;
	RegRules.UnivElective = newRules.UnivElective;
	RegRules.TrackCompulsory = newRules.TrackCompulsory;
	//RegRules.TrackElective = newRules.TrackElective; //commented to see if it will be in the file or not
	RegRules.MajorCompulsory = newRules.MajorCompulsory;
	RegRules.MajorElective = newRules.MajorElective;
	RegRules.ConcentrationsCompulsory = newRules.ConcentrationsCompulsory;
	RegRules.ConcentrationsElective = newRules.ConcentrationsElective;


}


//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}

Rules Registrar::getRules() const
{
	return this->RegRules;
}

Student* Registrar::getSignedStudest()
{
	return pSignedStudent;
}

void Registrar::loadNewDefaultPlan()
{
	pSPlan->DeleteAll();
	Action* acc = new  ActionImportDefaulPlan(this);
	acc->Execute();
}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		break;

	
	case CHANGE_BY_CODE:	//add_course action
		RequiredAction = new ActionChangeByCode(this);
		break;
	
	case DEL_CRS:
		//RequiredAction = new ActionDeleteCourse(this);
		RequiredAction = new ActionDeleteCourse(this);
		break;

	case REORDER:	//add_course action
		RequiredAction = new ActionDragAndDropCrs(this);
		break;

	
	case ADD_NOTES:
		RequiredAction = new ActionAddNotes(this);
		break;
	case SHOW_NOTES:
		RequiredAction = new ActionShowNotes(this);
		break;
	
	case SETTINGS:
		RequiredAction = new ActionSignUserUp(this);
		break;
	case SHOW_FILTERS:
		RequiredAction = new ActionDisplayFilters(this);
		break;
	case DRAW_AREA:	
		RequiredAction = getActionsForClickingOnDrawArea(RequiredAction, actData);
		cout << (RequiredAction == nullptr);
		break;
	case DEF_VIEW:
		pGUI->UpdateInterface();
		UpdateInterface();
		break;
	case SHOW_PREQS:
		//RequiredAction = new ActionShowPreReqs(this);
		pSPlan->drawCourseDependencies(pGUI, PREQ);
		//pSPlan->DrawMe(pGUI);
		break;
	case SHOW_COREQS:
		pSPlan->drawCourseDependencies(pGUI, COREQ);
		//pSPlan->DrawMe(pGUI);
		break;
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	if (!pSignedStudent->isUserSigned())
	{
		Action* sign = new ActionSignUserUp(this);
		sign->Execute();
	}
	//cout << "Reg" << pSignedStudent->getMajor() << endl;

	loadRules();
	
	//import rules on program runs
	//Action* pOffering = new ActionImpOffering(this);

	Action* pReq = new ActionImpReq(this);
	//ExecuteAction(pOffering);
	ExecuteAction(pReq);
	//cout <<"Size: "<<RegRules.CourseCatalog->size();
	Action* acc =new  ActionImportDefaulPlan(this);
	acc->Execute();
	//cout <<"Psplan: "<<pSPlan->getAcadamicYearAt(1)[FALL].sizeOfYearCourses();
	
	//this is made essentialy to stop bliking while it's not needed, if the action can handle the drawing; then no need to draw all courses from scratch./
	bool isUpdateInterface = true;
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		if(isUpdateInterface)
			UpdateInterface();
		isUpdateInterface = false;

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			isUpdateInterface = ExecuteAction(pAct);
		}
	}
}


void Registrar::UpdateInterface()
{
	//pSPlan->drawCourseDependencies(pGUI);
	pGUI->UpdateInterface();	//update interface items
	//pSPlan->drawCourseDependencies(pGUI);
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
	if (pSignedStudent->isNanoSingle())
	{
		bool check = new bool;
		check = pSPlan->checkCReqS();
		if (check)
			pGUI->drawConcentrationIssue();
	}
	else if (pSignedStudent->isNanoDouble())
	{
		bool check = new bool;
		check = pSPlan->checkCReqD();
		if (check)
			pGUI->drawConcentrationIssue();
	}
	
}

void Registrar::loadRules()
{

	Action* acc = new ActionImportRules(this);
	acc->Execute();
	//delete acc;
}

Action* Registrar::getActionsForClickingOnDrawArea(Action* RequiredAction, ActionData actData)
{
	graphicsInfo tempGI;
	tempGI.x = actData.x;
	tempGI.y = actData.y;
	try
	{
		cout << "drawArea" << endl;
		Course* crsClicked = pSPlan->getCourseAtGraphicsInfo(tempGI);
		cout << "drawArea" << endl;

		//then course found if it doesn't throw an exception
		return new ActionShowCourseInfo(this, crsClicked);

		cout << "drawArea"<<endl;

	}
	catch (const char* msg)
	{
		return new EmptyAction(this);
	}
}
void Registrar::checkOfferingR(Course* c, SEMESTER& sem)
{
	Action* pOfferingg = new ActionImpOffering(this);
	//ExecuteAction(pOfferingg);
	bool check = new bool;
	static_cast<ActionImpOffering*>(pOfferingg)->Execute();
	check = static_cast<ActionImpOffering*>(pOfferingg)->checkOffering(" " + c->getCode(), sem);
	if (!check)
	{
		pGUI->drawOfferingWarning(c->getCode(), sem);
		pSPlan->setMap(c, sem);
	}
}
Registrar::~Registrar()
{
	delete pGUI;
}
