#include "ActionDisplayFilters.h"
#include "Registrar.h"
#include "DEFs.h"
#include <iostream>
#include "Text_field.h"
using namespace std;
#include "ITM_Img_list_field.h"
#include "ViewField.h"
#include"DEFs.h"
#include "ListImagesFields.h"

ActionDisplayFilters::ActionDisplayFilters(Registrar* pReg) : Action(pReg)
{
	this->pWind = new window(WINDOW_WIDTH, WINDOW_HEIGHT, X_S, Y_S);
	this->pWind->ChangeTitle("Display Filters");
	pGUI = pReg->getGUI();
	pS = pReg->getStudyPlay();
	filters = new ListImagesFields(pWind, MARGIN_VALUE, (TEXT_FIELD_HEIGHT + 50));
	pWind->SetFont(15, BOLD, BY_NAME, "Georgia");
	DoneButton = new ButtonField(pWind, WINDOW_WIDTH - 170, WINDOW_HEIGHT - 70);

	ClearDrawingArea();
}

bool ActionDisplayFilters::Execute()
{
	bool isInterfaceUpdate = false;

	this->pWind->FlushMouseQueue();
	this->pWind->FlushKeyQueue();
	this->pWind->UpdateBuffer();
	
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;
	

	UpdateInterface();

	lastFilter = err;
	while (true)
	{

		int x, y;
		this->pWind->GetMouseCoord(x, y);
		if (this->pWind->GetRed(x, y) == 0.8 && this->pWind->GetGreen(x, y) == 0.8 && this->pWind->GetBlue(x, y) == 0.8)
		{
			cout << "Hello";
			delete this->pWind;
			break;
		}
		
		else if (this->pWind->GetRed(x, y) == 1 && this->pWind->GetGreen(x, y) == 1 && this->pWind->GetBlue(x, y) == 1)
		{
			cout << "Hello";
			UpdateInterface();
		}
		
		int xc, yc;
		cout << "Hello0";
		ctInput = this->pWind->GetMouseClick(xc, yc);	//Get the coordinates of the user click
		ktInput = this->pWind->GetKeyPress(cKeyData);
		lastFilter = filters->getFinalFilterSelected();
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			cout << "Hello1";
			filters->setSelectedForXY(xc, yc);
		}
		if (DoneButton->isButtonClick(x, y) && ctInput == LEFT_CLICK)
		{
			cout << "Hello2";
			try
			{
				isInterfaceUpdate = DoneClicked();
				delete this->pWind;
				break;
			}
			catch (const char* msg)
			{
			}

		}
	}

	switch (filters->getFinalFilterSelected())
	{
	case Year1:
	{
		cout << "Hello year";
		pGUI->UpdateInterface();
		pS->getAcadamicYearAt(1)->DrawMe(pGUI);
		break;
	}
	case Year2:
	{
		pGUI->UpdateInterface();
		pS->getAcadamicYearAt(2)->DrawMe(pGUI);
		break;
	}
	case Year3:
	{
		pGUI->UpdateInterface();
		pS->getAcadamicYearAt(3)->DrawMe(pGUI);
		break;
	}
	case Year4:
	{
		pGUI->UpdateInterface();
		pS->getAcadamicYearAt(4)->DrawMe(pGUI);
		break;
	}
	case Year5:
		pGUI->UpdateInterface();
		pS->getAcadamicYearAt(5)->DrawMe(pGUI);
		break;
	}

	return isInterfaceUpdate;
}

void ActionDisplayFilters::ClearDrawingArea() const
{

	this->pWind->DrawImage(BACKGROUN_PATH_FILE, 0, 0);
}

void ActionDisplayFilters::UpdateInterface() const
{

	this->pWind->SetBuffering(true);
	ClearDrawingArea();
	this->pWind->UpdateBuffer();
	this->pWind->SetBuffering(false);
	//DrawAllTextFields();
	//DrawSelectMajorString();
	DrawFilters();
	DrawButton();

}

void ActionDisplayFilters::DrawFilters()const
{
	ITM_Img_list_field* imgs[] = {
		new ITM_Img_list_field(this->pWind, "GUI\\Images\\\Majors\\Year1.jpg",Year1),
		new ITM_Img_list_field(this->pWind, "GUI\\Images\\\Majors\\Year2.jpg",Year2),
		new ITM_Img_list_field(this->pWind, "GUI\\Images\\\Majors\\Year3.jpg",Year3),
		new ITM_Img_list_field(this->pWind, "GUI\\Images\\\Majors\\Year4.jpg",Year4),
		new ITM_Img_list_field(this->pWind, "GUI\\Images\\\Majors\\Year5.jpg",Year5),
	};
	filters->addItmImagesAndClear(imgs, 5);
	filters->DrawMe();

}

void ActionDisplayFilters::DrawButton()const
{
	DoneButton->DrawMe();
}

bool ActionDisplayFilters::DoneClicked() const
{
	if (filters->isSelected())
	{
		if (lastFilter != err && lastFilter != filters->getFinalFilterSelected())
		{
			pReg->loadNewDefaultPlan();
			return true;
		}
		else
		{
			return false;
		}
	}
}

ActionDisplayFilters::~ActionDisplayFilters()
{

}