#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"
#include "Student.h"

//The maestro class for the application
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;
	Student* pSignedStudent;
	void loadRules();

	Action* getActionsForClickingOnDrawArea(Action* RequiredAction, ActionData actData);
public:
	Registrar();
	GUI* getGUI() const;
	void setOfferingRules(Rules);
	void setRules(Rules);
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	Rules getRules()const;
	Student* getSignedStudest();
	void loadNewDefaultPlan();
	void Run();
	void checkOfferingR(Course* c, SEMESTER& sem);
	~Registrar();
};

