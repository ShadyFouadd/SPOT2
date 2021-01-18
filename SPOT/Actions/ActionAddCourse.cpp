#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "..\DEFs.h"
#include <iostream>
#include "..\ActionChangeMenuItemTo.h"
#include "..\ActionMenuBar.h"
//#include "\C++Final\SPOT-main\SPOT - CIE202 Project Code Framework\SPOT\ActionImpOffering.h"

ActionAddCourse::ActionAddCourse(Registrar* p) :ActionMenuBar(p, GUI::ITM_ADD)
{
	//actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_ADD, "GUI\\Images\\Menu\\Add_borderd.jpg");
	actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_ADD);



}

bool ActionAddCourse::Execute()
{
	actionChangeMenuItemTo->Execute();

	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();

	//TODO: add input validation


	ActionData actData = pGUI->GetUserAction("Select a semester to add coures to");
	//TODO: add input validation

	//Checking if user want to deselect Add Action.
	if (isClose(actData.x, actData.y))
	{
		actionChangeMenuItemTo->reverseExcute();
		delete actionChangeMenuItemTo;
		return false;
	}
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		StudyPlan* pS = pReg->getStudyPlay();
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		graphicsInfo gInfo{ x, y };
		graphicsInfo g2info{ x + CRS_WIDTH,y + CRS_HEIGHT };
		graphicsInfoComprehensive gcomprehensive{ gInfo,g2info };
		//create a course and set its graphics info by x,y
		string Title = "Test101";
		int crd = 4;
		Course* pC = new Course(code, Title, crd);
		pC->setGfxInfo(gInfo);
		pC->setGfxInfoComp(gcomprehensive);

		//constants needed for detecting which semester
		int sH = pGUI->getStatusBarHeight();
		int wH = pGUI->getWindHeight();
		int d = VERTICAL_SPACE_BETWEEN_YEARS;
		int semH = CRS_HEIGHT + 2 * VERTICAL_SPACE_BETWEEN_SEMESTER_;
		int yH = 3 * semH;
		SEMESTER sem;

		for (int i = 0; i <= 5; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (y <= wH - sH - (d + yH) * i - d - semH * j && y > wH - sH - (d + yH) * i - d - semH * (j + 1))
				{
					sem = static_cast<SEMESTER>(j);
					pS->AddCourse(pC, i + 1, sem);
					pReg->getStudyPlay()->calculateGraphicsInfoForEachItem(pReg->getGUI()->getWindHeight() - pReg->getGUI()->getStatusBarHeight());
					pReg->checkOfferingR(pC, sem);
					break;
				}
			}
		}

		//TODO: given course code, get course title, crd hours from registrar
		//For now, we will add any dummy values


	}
	///OfferingTimeCheck

	actionChangeMenuItemTo->reverseExcute();
	delete actionChangeMenuItemTo;
	return true;
}

bool ActionAddCourse::Execute(Course* crs, SEMESTER& sem, int year)
{
	StudyPlan* pS = pReg->getStudyPlay();
	pS->AddCourse(crs, year, sem);
	return false;
}





ActionAddCourse::~ActionAddCourse()
{
}
