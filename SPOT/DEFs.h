#pragma once

//This header file contains some defenitions to be used all over the application
#include <string>
using namespace std;
typedef string Course_Code;

enum MAJORS
{
	FOUNDATION,
	CIE,
	//NAN is taked keyword, so I use NANE instead of NAN
	NANES,
	NANED,
	REE,
	ENV,
	SPC,
	MAJORS_COUNT_SUPPORTED,
	//used specifically in student class
	NOT_DEFINED
};
//Semesters
enum SEMESTER
{
	FALL,
	SPRING,
	SUMMER,
	SEM_CNT	//number of semesters 
};
enum depTypte
{
	PREQ,
	COREQ
};

//All possible actions
enum ActionType
{
	ADD_CRS,	//Add a course to study plan
	CHANGE_BY_CODE, //User will be able to change couuse in study plan to another one by writing another course code 
	DEL_CRS,	//Delete a course from study plan
	REORDER,
	SETTINGS,
	SAVE,		//Save a study plan to file
	LOAD,		//Load a study plan from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	EXIT,		//Exit the application

	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area
	DEF_VIEW,
	SHOW_PREQS,
	SHOW_COREQS,

	CANCEL,
	ADD_NOTES, //Add written notes
	SHOW_NOTES, //Show written notes	//ESC key is pressed
	SHOW_FILTERS,
	//this is made specifcally for showing info for course selected, if it's selected and use clicked on delete button. it should delete the coure.
	DEL_BUTTON_CLICKED
	//TODO: Add more action types

};
enum FILTERS
{
	Year1,
	Year2,
	Year3,
	Year4,
	Year5,
	SEMS,
	err
};
//to sotre data related to the last action
struct ActionData
{
	ActionType actType;
	int x, y;
	
};


