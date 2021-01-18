#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>
#include <iostream>
#include <map>
#include "..\ViewField.h"
#include <conio.h>
using namespace std;
GUI::GUI()
{
	changeMenuItemTo(ITM_ADD, "GUI\\Images\\Menu\\Add.jpeg");
	changeMenuItemTo(ITM_DELETE, "GUI\\Images\\Menu\\Delete.jpeg");
	changeMenuItemTo(ITM_ADD_NOTES, "GUI\\Images\\Menu\\Add_note.jpeg");
	changeMenuItemTo(ITM_SHOW_NOTES, "GUI\\Images\\Menu\\Show_notes.jpeg");
	changeMenuItemTo(ITM_CHANGE_CRS_BY_CODE, "GUI\\Images\\Menu\\Update.jpeg");
	changeMenuItemTo(ITM_REORDER, "GUI\\Images\\Menu\\Reorder.jpg");
	changeMenuItemTo(ITM_SETTINGS, "GUI\\Images\\Menu\\Settings.jpeg");
	changeMenuItemTo(ITM_SHOWFilters, "GUI\\Images\\Menu\\Filters.jpg");
	changeMenuItemTo(ITMS_DEF, "GUI\\Images\\Menu\\DEF.jpg");
	changeMenuItemTo(ITM_PREQS, "GUI\\Images\\Menu\\PreReqs.jpg");
	changeMenuItemTo(ITM_COREQS, "GUI\\Images\\Menu\\CoReqs.jpg");

	pWind = new window(WindWidth, WindHeight, wx, wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	//pWind->SetBrush(BkGrndColor);
	//pWind->SetPen(BkGrndColor);
	//pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
	pWind->DrawImage(BACKGROUN_PATH_FILE, 0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);
	int widthOfBlackLine = 3;
	for (int i = 0; i < ITM_CNT; i++)
	{
		pWind->SetPen(BkGrndColor, widthOfBlackLine);
		//Draw a line before each icon
		pWind->DrawLine(i * MenuItemWidth, 0, i * MenuItemWidth, MenuBarHeight);
		pWind->DrawImage(filePathsForMenuItem->at(static_cast<MENU_ITEM>(i)), i * MenuItemWidth + widthOfBlackLine, 0, MenuItemWidth - widthOfBlackLine, MenuBarHeight);
		//pWind->DrawLine(i * MenuItemWidth, 0, i * MenuItemWidth , MenuBarHeight);

	}
	//Draw a line after last course.
	pWind->DrawLine((ITM_CNT - 1) * MenuItemWidth + MenuItemWidth + widthOfBlackLine, 0, (ITM_CNT - 1) * MenuItemWidth + MenuItemWidth + widthOfBlackLine, MenuBarHeight);

}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{

	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);
}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected())
		pWind->SetPen(RED, 2);
	else
		pWind->SetPen(BLACK, 2);
	pWind->SetBrush(ZewailCityBackground);
	graphicsInfo gInfo = pCrs->getGfxInfoComp().topLeft;
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);

	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK);

	ostringstream crd;
	crd << "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());
}

void GUI::DrawAcademicYear(const AcademicYear* pY)
{
	pWind->SetPen(BLACKONWHITE);
	pWind->DrawRectangle(pY->getGfxInfoComp().topLeft.x, pY->getGfxInfoComp().topLeft.y, pY->getGfxInfoComp().bottomRight.x, pY->getGfxInfoComp().bottomRight.y, FRAME);
	pWind->SetPen(BLACK);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(pY->getGfxInfoComp().topLeft.x + 10, (pY->getGfxInfoComp().topLeft.y + pY->getGfxInfoComp().bottomRight.y + 15) / 2, "Year " + to_string(pY->getYear()));
	pWind->SetPen(BLACK);

	//Line after word year
	pWind->DrawLine(WIDTH_YEAR_WORD, pY->getGfxInfoComp().topLeft.y, WIDTH_YEAR_WORD, pY->getGfxInfoComp().bottomRight.y);
	//line after year+ semester
	pWind->DrawLine(WIDTH_YEAR_WORD + WIDTH_SEMESTER_WORD, pY->getGfxInfoComp().topLeft.y, WIDTH_YEAR_WORD + WIDTH_SEMESTER_WORD, pY->getGfxInfoComp().bottomRight.y);

	//draw vertical row between semesters.
	int lastY = pY->getGfxInfoComp().bottomRight.y - CRS_HEIGHT - VERTICAL_SPACE_BETWEEN_YEARS - VERTICAL_SPACE_BETWEEN_SEMESTER_ / 2;
	for (int i = FALL; i < SEM_CNT; i++)
	{

		pWind->DrawLine(WIDTH_YEAR_WORD, lastY, pY->getGfxInfoComp().bottomRight.x, lastY);
		pWind->SetPen(BLACK);
		pWind->SetFont(15, ITALICIZED, BY_NAME, "Arial");
		pWind->DrawString(WIDTH_YEAR_WORD + 2, lastY + 5, i == 0 ? "Fall" : (i == 1 ? "Spring" : "Summer"));
		lastY = lastY - CRS_HEIGHT - VERTICAL_SPACE_BETWEEN_YEARS - VERTICAL_SPACE_BETWEEN_SEMESTER_ / 2;
	}


}


////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;


	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}


		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{

				case ITM_ADD: return ActionData{ ADD_CRS,x,y };	//Add course
				case ITM_CHANGE_CRS_BY_CODE: return ActionData{ CHANGE_BY_CODE ,x,y };
				case ITM_DELETE: return ActionData{ DEL_CRS,x,y };		//Delete course
				case ITM_REORDER: return ActionData{ REORDER ,x,y };
				case ITM_SHOW_NOTES: return ActionData{ SHOW_NOTES ,x,y };
				case ITM_ADD_NOTES: return ActionData{ ADD_NOTES,x,y };
				case ITM_SETTINGS: return ActionData{ SETTINGS,x,y };
				case ITM_SHOWFilters: return ActionData{ SHOW_FILTERS, x, y };
				case ITMS_DEF: return ActionData{ DEF_VIEW, x, y };
				case ITM_PREQS: return ActionData{ SHOW_PREQS, x, y };
				case ITM_COREQS: return ActionData{ SHOW_COREQS, x, y };
				default: return ActionData{ MENU_BAR };	   //A click on empty place in menu bar

				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}
ActionData GUI::GetUserAction() const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;


	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	
	//PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}


		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course

				case ITM_DELETE: return ActionData{ DEL_CRS };		//delete
				case ITM_SETTINGS : return ActionData{ SETTINGS };

				case ITM_ADD_NOTES: return ActionData{ ADD_NOTES };
				case ITM_SHOW_NOTES: return ActionData{ SHOW_NOTES };
				case ITM_SHOWFilters: return ActionData{ SHOW_FILTERS };
				default: return ActionData{ MENU_BAR };	   //A click on empty place in menu bar

				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}

ActionData GUI::GetCoordAndSenseDelete() const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;


	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);
		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course

				case ITM_DELETE: return ActionData{ DEL_CRS };		//delete
				case ITM_SETTINGS: return ActionData{ SETTINGS };

				case ITM_ADD_NOTES: return ActionData{ ADD_NOTES };
				case ITM_SHOW_NOTES: return ActionData{ SHOW_NOTES };
				case ITM_SHOWFilters: return ActionData{ SHOW_FILTERS };
				default: return ActionData{ MENU_BAR };	   //A click on empty place in menu bar

				}
			}

			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			
		}
		
		

	}
}

string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar



	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}








int GUI::getWindHeight() const
{
	return WindHeight;
}
int GUI::getWindWidth()const
{
	return WindWidth;
}
int GUI::getStatusBarHeight()const
{
	return StatusBarHeight;
}

void GUI::changeMenuItemTo(MENU_ITEM index, string filePath)
{

	if (filePathsForMenuItem->find(index) == filePathsForMenuItem->end()) {
		// not found
		filePathsForMenuItem->insert({ index, filePath });
	}
	else {
		// found
		filePathsForMenuItem->find(index)->second = filePath;
	}

	try
	{
		filePathsForMenuItem->find(index)->second = filePath;

	}
	catch (const char* msg)
	{
		filePathsForMenuItem->insert({ index, filePath });
	}
}

string GUI::getFilePathForMenuItemAt(MENU_ITEM mi)
{
	return filePathsForMenuItem->at(mi);
}

window* GUI::getWindow()
{
	return pWind;
}

void GUI::RedrawTempCrs(const Course* pCrs, STATE_DRAG_CRS sdc)
{
	pWind->SetPen(HiColor, 2);
	if(sdc ==OK)
		pWind->SetBrush(GREEN);
	else 
		pWind->SetBrush(RED);

	graphicsInfo gInfo = pCrs->getGfxInfoComp().topLeft;
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);

	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);

	ostringstream crd;
	crd << "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());
}

bool GUI::isPointInMenuBarRange(int x, int y)
{
	if (x > 0 && x < WindWidth && y>0 && y < MenuBarHeight)
		return true;
	return false;
}

void GUI::DrawOnlyTwoCourses(const Course* crs1, const Course* crs2)
{
	DrawCourse(crs1);
	DrawCourse(crs2);
}

GUI::~GUI()
{
	delete pWind;
	delete errorW;
}
/////////////////////////////////////////
void GUI::drawCred(const AcademicYear* pY)
{
	//pWind->SetPen(BLUE);
	//pWind->DrawRectangle(pY->getGfxInfoComp().topLeft.x, pY->getGfxInfoComp().topLeft.y, pY->getGfxInfoComp().bottomRight.x, pY->getGfxInfoComp().bottomRight.y, FRAME);
	for (int sem = 0, j = pY->getGfxInfoComp().topLeft.y + 80; sem < SEM_CNT || j <= 0; sem++, j -= CRS_HEIGHT + VERTICAL_SPACE_BETWEEN_SEMESTER_ + 5)
	{
		pWind->SetPen(BLACK);
		pWind->SetFont(20, BOLD, BY_NAME, "Arial");
		pWind->DrawString(pY->getGfxInfoComp().topLeft.x + 1100, j, "Total Credits:" + to_string(pY->getCredits(sem)));
		if (pY->getCredits(sem) > 18 || pY->getCredits(sem) < 9 && sem != SUMMER)
		{
			pWind->SetBrush(GREENYELLOW);
			pWind->SetPen(RED);
			pWind->SetFont(20, BOLD, BY_NAME, "Arial");
			pWind->DrawRectangle(pY->getGfxInfoComp().topLeft.x + 905, j - CRS_HEIGHT + 20, pY->getGfxInfoComp().topLeft.x + 1060, j + 20, FILLED);
			pWind->DrawString(pY->getGfxInfoComp().topLeft.x + 910, j, "MODERATE ISSUE");

		}
	}
}
void GUI::drawConcentrationIssue()
{
	pWind->SetPen(WHITE);
	pWind->SetFont(15, BOLD, BY_NAME, "Georgia");
	pWind->SetBrush(RED);
	pWind->DrawRectangle(900, 10, 1230, 35, FILLED);
	pWind->DrawString(915, 13, "Crtical Issue: Concentration Requirements");
}
void GUI::drawOfferingWarning(Course_Code c, SEMESTER s)
{
	string thissem;
	if (s == 0)
		thissem = "Fall";
	if (s == 1)
		thissem = "Spring";
	if (s == 2)
		thissem = "Summer";
    errorW = new window(500, 200, 500,500);
	errorW->FlushMouseQueue();
	errorW->FlushKeyQueue();
	errorW->ChangeTitle("Error!");
	errorW->SetBrush(GREENYELLOW);
	errorW->SetPen(BLACK);
	errorW->SetFont(15, BOLD, BY_NAME, "Georgia");
	errorW->DrawRectangle(20, 50, 450, 70, FILLED);
	errorW->DrawString(21, 50, ("MODERATE ISSUE: The course " + c + " is not offered in " + thissem));
	//UpdateInterface();
	while (true)
	{
		int x, y;
		errorW->GetMouseCoord(x, y);
		if (errorW->GetRed(x, y) == 0.8 && errorW->GetGreen(x, y) == 0.8 && errorW->GetBlue(x, y) == 0.8)
		{
			delete errorW;
			break;
		}
	}
}
void GUI::DrawDeps(int x1, int y1, int x2, int y2, depTypte dType)
{
	
	if (dType == PREQ)
	{
		pWind->SetPen(BLACK, 2);
		pWind->SetBrush(RED);
		pWind->DrawTriangle(x2, y2, x2 - 5, y2 - 5, x2 + 5, y2 - 5, FILLED);
		pWind->DrawLine(x1, y1, x2, y2);
		//
	}
	else if (dType == COREQ)
	{
		pWind->SetPen(RED, 2);
		pWind->SetBrush(BLACK);
		pWind->DrawLine(x1, y2, x2, y2);
		pWind->DrawTriangle(x2, y2, x2 - 5, y2 - 5, x2 + 5, y2 - 5, FILLED);
	}

	//pWind->DrawLine(x1, y1, x2, y2);
	
	/*
	* std::list<Course_Code>::const_iterator it;
	int xi = (crsClicked->getGfxInfoComp().topLeft.x+ crsClicked->getGfxInfoComp().bottomRight.x)/2;
	int yi= crsClicked->getGfxInfoComp().bottomRight.y;
	if (crsClicked->getPreReq().size() > 0)
	{
		list<Course_Code>& lst = crsClicked->getPreReq();
		for (auto it = lst.begin(); it != lst.end(); ++it)
		{
			Course* preC;
			preC= pReg->getStudyPlay()->getCourseForCourseCode((*it));
			int xf = (preC->getGfxInfoComp().topLeft.x + preC->getGfxInfoComp().bottomRight.x)/2;;
			int yf = preC->getGfxInfoComp().topLeft.y;
			pReg->getGUI()->getWindow()->SetPen(BLACK, 2);
			pReg->getGUI()->getWindow()->DrawLine(xi,yi, xf, yf-5);
			pReg->getGUI()->getWindow()->SetBrush(RED);
			pReg->getGUI()->getWindow()->DrawTriangle(xf, yf, xf - 5, yf - 5, xf + 5, yf - 5, FILLED);
		}
		
		list<Course_Code>& lstc = crsClicked->getCoReq();
		yi = (crsClicked->getGfxInfoComp().bottomRight.y + crsClicked->getGfxInfoComp().topLeft.y) / 2;
		for (auto itc = lstc.begin(); itc != lstc.end(); ++itc)
		{
			Course* preC;
			preC= pReg->getStudyPlay()->getCourseForCourseCode((*itc));
			int xf = (preC->getGfxInfoComp().topLeft.x + preC->getGfxInfoComp().bottomRight.x)/2;;
			int yf = (preC->getGfxInfoComp().bottomRight.y + preC->getGfxInfoComp().topLeft.y) / 2;
			pReg->getGUI()->getWindow()->SetPen(RED, 2);
			pReg->getGUI()->getWindow()->DrawLine(xi,yi, xf, yf);
			pReg->getGUI()->getWindow()->SetBrush(BLACK);
			pReg->getGUI()->getWindow()->DrawTriangle(xf,yf, xf-5,yf-5, xf-5,yf+5 , FILLED);
		}
		
		
	}
	*/
}