#include "StudyPlan.h"
#include <iostream>
#include <algorithm>
//#include <boost/algorithm/string.hpp>
using namespace std;


void StudyPlan::instantiatePlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++)
		plan->push_back(new AcademicYear);
}

StudyPlan::StudyPlan()
{
	instantiatePlan();
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 

	(*plan)[year - 1]->AddCourse(pC, sem);
	
	return true;
}
bool StudyPlan::DeleteCourse(Course* pC, int year, SEMESTER sem, int orderOfCourse)
{
	(*plan)[year - 1]->DeleteCourse(pC, sem, orderOfCourse);
	return true;
}

void StudyPlan::DeleteAll()
{
	plan->clear();
	instantiatePlan();
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan->size(); i++)
	{
		(*plan)[i]->DrawMe(pGUI);
		(*plan)[i]->DrawCredits(pGUI);
	}
}

AcademicYear* StudyPlan::getAcadamicYearAt(int year)
{

	return (*plan)[year - 1];
}

//LastY is expected to be pReg->getGUI()->getWindHeight() - pReg->getGUI()->getStatusBarHeight()
void StudyPlan::calculateGraphicsInfoForEachItem(int lastYe)
{

	int lastY = lastYe;
	int sartingX = WIDTH_YEAR_WORD + WIDTH_SEMESTER_WORD;
	int lastTopLeft = lastY;
	int year = 1;
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		(*academicYear)->setYear(year++);
		lastY -= VERTICAL_SPACE_BETWEEN_YEARS;
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			sartingX = WIDTH_YEAR_WORD + WIDTH_SEMESTER_WORD+HORIZENTAL_SPACE_BETWEEN_COURSES_;
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			lastY -= VERTICAL_SPACE_BETWEEN_SEMESTER_;
			
			lastY -= CRS_HEIGHT;
			bool isFound = false;;
			std::list<Course*>::iterator it;
			for (it = currentSemester.begin(); it != currentSemester.end(); it++)
			{
				//cout << sartingX;
				Course* currentCourse = (*it);
				graphicsInfoComprehensive graphicInfoComp;
				graphicInfoComp.topLeft.x = sartingX;
				graphicInfoComp.topLeft.y = lastY;
				graphicInfoComp.bottomRight.x = sartingX + CRS_WIDTH;
				graphicInfoComp.bottomRight.y = lastY + CRS_HEIGHT;
				currentCourse->setGfxInfoComp(graphicInfoComp);
				sartingX += HORIZENTAL_SPACE_BETWEEN_COURSES_ + CRS_WIDTH;

				isFound = true;
			}
			//if(!isFound)
			//	lastY = lastY+CRS_HEIGHT-VERTICAL_SPACE_BETWEEN_SEMESTER_;
			lastY -= VERTICAL_SPACE_BETWEEN_SEMESTER_;

		}
		graphicsInfoComprehensive graphicInfoComp;
		graphicInfoComp.topLeft.x = 10;
		graphicInfoComp.topLeft.y = lastY ;
		graphicInfoComp.bottomRight.x = 1300 - 30;
		graphicInfoComp.bottomRight.y = lastTopLeft - VERTICAL_SPACE_BETWEEN_YEARS;
		(*academicYear)->setGfxInfoComp(graphicInfoComp);
		lastTopLeft = lastY;
	}
}

Course* StudyPlan::getCourseAtGraphicsInfo(graphicsInfo point)
{
	bool isFound = false;
	//Looping over acadamic years
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		//checking first if it's in bounds of acadameic Year
		if (point.x >= (*academicYear)->getGfxInfoComp().topLeft.x && point.x < (*academicYear)->getGfxInfoComp().bottomRight.x
			&& point.y >= (*academicYear)->getGfxInfoComp().topLeft.y && point.y < (*academicYear)->getGfxInfoComp().bottomRight.y
			)
		{
			//it's in the boundary of that academic year
			//Looping over semesters.
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
				std::list<Course*>::iterator it;
				//Checking if it's in that semester, if not it will skip that iteration.
				//1- checking first if the size >0 if not then no courses in in that sem
				if ((currentSemester).size() == 0)
					continue;
				//2- checking second for coordinates, if it reaches that point, then no way to give error for empty currenSemester
				if (!(point.y > (*currentSemester.begin())->getGfxInfoComp().topLeft.y && point.y < (*currentSemester.begin())->getGfxInfoComp().bottomRight.y))
					continue;
				for (it = currentSemester.begin(); it != currentSemester.end(); it++)
				{
					Course* currentCourse = (*it);


					if (point.x >= currentCourse->getGfxInfoComp().topLeft.x && point.x < currentCourse->getGfxInfoComp().bottomRight.x
						&& point.y >= currentCourse->getGfxInfoComp().topLeft.y && point.y < currentCourse->getGfxInfoComp().bottomRight.y
						)
					{
						return currentCourse;
					}
				}
			}
		}
	}
	//if it reaches that point that mean he couldn't find that course, meanning that user clicked on somewhere not on course
	//then it will throw an error, meaning it must be handled from the place it will call it.
	throw "Course not found";
}

//over riding the function to use it in deleting courses
Course* StudyPlan::getCourseAtGraphicsInfo(graphicsInfo point, SEMESTER& deletedSemester, int& deletedYear,int& orderOfCourse)
{
	int count=-1;
	bool isFound = false;
	//Looping over acadamic years
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		//checking first if it's in bounds of acadameic Year
		if (point.x >= (*academicYear)->getGfxInfoComp().topLeft.x && point.x < (*academicYear)->getGfxInfoComp().bottomRight.x
			&& point.y >= (*academicYear)->getGfxInfoComp().topLeft.y && point.y < (*academicYear)->getGfxInfoComp().bottomRight.y
			)
		{
			//it's in the boundary of that academic year
			//Looping over semesters.
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
				std::list<Course*>::iterator it;
				//Checking if it's in that semester, if not it will skip that iteration.
				//1- checking first if the size >0 if not then no courses in in that sem
				if ((currentSemester).size() == 0)
					continue;
				//2- checking second for coordinates, if it reaches that point, then no way to give error for empty currenSemester
				if (!(point.y > (*currentSemester.begin())->getGfxInfoComp().topLeft.y && point.y < (*currentSemester.begin())->getGfxInfoComp().bottomRight.y))
					continue;
				for (it = currentSemester.begin(); it != currentSemester.end(); it++)
				{
					Course* currentCourse = (*it);
					count++;
					if (point.x >= currentCourse->getGfxInfoComp().topLeft.x && point.x < currentCourse->getGfxInfoComp().bottomRight.x
						&& point.y >= currentCourse->getGfxInfoComp().topLeft.y && point.y < currentCourse->getGfxInfoComp().bottomRight.y
						)
					{
						deletedSemester = static_cast<SEMESTER>(sem);
						deletedYear = (*academicYear)->getYear();
						orderOfCourse = count;
						return currentCourse;
					}
				}
				count = -1;
			}
		}
	}
	//if it reaches that point that mean he couldn't find that course, meanning that user clicked on somewhere not on course
	//then it will throw an error, meaning it must be handled from the place it will call it.
	throw "Course not found";
}

void StudyPlan::getSemAndYearForPoint(int x, int y, SEMESTER& semester, int& year)
{
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		//check if it's in this academic year.
		if (x >= (*academicYear)->getGfxInfoComp().topLeft.x && x < (*academicYear)->getGfxInfoComp().bottomRight.x
			&& y >= (*academicYear)->getGfxInfoComp().topLeft.y && y < (*academicYear)->getGfxInfoComp().bottomRight.y
			)
		{
			//it's in this academic year.
			year = (*academicYear)->getYear();
			//Looping over sems
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
				std::list<Course*>::iterator it;
				if ((currentSemester).size() == 0)
					continue;
				if ((y > (*currentSemester.begin())->getGfxInfoComp().topLeft.y- VERTICAL_SPACE_BETWEEN_SEMESTER_ && y < (*currentSemester.begin())->getGfxInfoComp().bottomRight.y +VERTICAL_SPACE_BETWEEN_SEMESTER_)
					&& x > WIDTH_SEMESTER_WORD+WIDTH_YEAR_WORD && x < 1300)
				{
					semester = static_cast<SEMESTER>(sem);
					return;
				}
			}


		}
	}
	throw "Not found";
}
////////////////////////////////////////////////////////////////////////////
bool StudyPlan::checkCReqS()
{

	bool found1 = new bool;
	bool found2 = new bool;
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			std::list<Course*>::iterator it;
			for (it = currentSemester.begin(); it != currentSemester.end(); it++)
			{
				//First Concentration
				if ((*it)->getCode() == "NANENG513")
				{
					found1 = false;
					if ((*it)->getCode() == "NANENG515")
						found2 = false;
					if (!found1 && !found2)
						return false;
					else
						return true;
				}
				//Second Concentration
				if ((*it)->getCode() == "NANENG501")
				{
					found1 = false;
					if ((*it)->getCode() == "NANENG522")
						found2 = false;
					if (!found1 && !found2)
						return false;
					else
						return true;
				}
				//Third Concentration
				if ((*it)->getCode() == "NANENG511")
				{
					found1 = false;
					if ((*it)->getCode() == "NANENG530")
						found2 = false;
					if (!found1 && !found2)
						return false;
					else
						return true;
				}
				/*
				if ((*it)->getCode() == "NANENG513" || (*it)->getCode() == "NANENG501" || (*it)->getCode() == "NANENG511")
					found1 = false;
				if ((*it)->getCode() == "NANENG515" || (*it)->getCode() == "NANENG522" || (*it)->getCode() == "NANENG530")
					found2 = false;
				*/
			}
		}
	}
}
bool StudyPlan::checkCReqD()
{

	bool found1 = new bool;
	bool found2 = new bool;
	bool found3 = new bool;
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			std::list<Course*>::iterator it;
			for (it = currentSemester.begin(); it != currentSemester.end(); it++)
			{
				//First Concentration
				if ((*it)->getCode() == "NANENG513")
				{
					if ((*it)->getCode() == "NANENG515")
						found1 = false;
				}
				//Second Concentration
				if ((*it)->getCode() == "NANENG501")
				{
					if ((*it)->getCode() == "NANENG522")
						found2 = false;
				}
				//Third Concentration
				if ((*it)->getCode() == "NANENG511")
				{
					if ((*it)->getCode() == "NANENG530")
						found3 = false;
				}
				if ((found1 && (found2 || found3) == false) || (found2 && (found1 || found3) == false) || (found3 && (found1 || found2) == false))
					return false;
				else
					return true;
				/*
				if ((*it)->getCode() == "NANENG513" || (*it)->getCode() == "NANENG501" || (*it)->getCode() == "NANENG511")
					found1 = false;
				if ((*it)->getCode() == "NANENG515" || (*it)->getCode() == "NANENG522" || (*it)->getCode() == "NANENG530")
					found2 = false;
				*/
			}
		}
	}
}


void StudyPlan::drawCourseDependencies(GUI* pGUI, depTypte dType)
{
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			std::list<Course*>::iterator it;
			for (it = currentSemester.begin(); it != currentSemester.end(); it++)
			{
				Course* currentCourse = (*it);
				int x1, y1;
				x1 = (currentCourse->getGfxInfoComp().topLeft.x + currentCourse->getGfxInfoComp().bottomRight.x) / 2;
				y1 = currentCourse->getGfxInfoComp().topLeft.y;
				//x1 = currentCourse->getGfxInfo().x;
				//y1 = currentCourse->getGfxInfo().y;
				list<Course_Code> preqs = currentCourse->getPreReq();
				list<Course_Code> coreqs = currentCourse->getCoReq();
				std::list<Course_Code>::iterator itt;
				// depCourse;
				if (dType == PREQ)
				{
					for (itt = preqs.begin(); itt != preqs.end(); itt++)
					{
						int x2, y2;
						Course* depCourse = getCourseByCode((*itt));

						if (depCourse != NULL)
						{
							x2 = (depCourse->getGfxInfoComp().topLeft.x + depCourse->getGfxInfoComp().bottomRight.x) / 2;
							y2 = depCourse->getGfxInfoComp().bottomRight.y;
							//x2 = depCourse->getGfxInfo().x;
							//y2 = depCourse->getGfxInfo().y;
							depCourse->DrawCourseDeps(pGUI, x1, y1, x2, y2, dType);
						}
					}
				}
				else if (dType == COREQ)
				{
					for (itt = coreqs.begin(); itt != coreqs.end(); itt++)
					{
						int x2, y2;
						Course* depCourse = getCourseByCode((*itt));

						if (depCourse != NULL)
						{
							x2 = (depCourse->getGfxInfoComp().topLeft.x + depCourse->getGfxInfoComp().bottomRight.x) / 2;
							y2 = depCourse->getGfxInfoComp().bottomRight.y ;
							//x2 = depCourse->getGfxInfo().x;
							//y2 = depCourse->getGfxInfo().y;
							depCourse->DrawCourseDeps(pGUI, x1, y2-15, x2, y2-15, dType);
						}
					}
				}
			}

		}
	}
}
void  StudyPlan::drawCourseDependencies(GUI* pGUI, depTypte dType, Course* currentCourse)
{
	int x1, y1;
	x1 = (currentCourse->getGfxInfoComp().topLeft.x + currentCourse->getGfxInfoComp().bottomRight.x) / 2;
	y1 = currentCourse->getGfxInfoComp().topLeft.y;
	//x1 = currentCourse->getGfxInfo().x;
	//y1 = currentCourse->getGfxInfo().y;
	list<Course_Code> preqs = currentCourse->getPreReq();
	list<Course_Code> coreqs = currentCourse->getCoReq();
	std::list<Course_Code>::iterator itt;
	if (dType == PREQ)
	{
		for (itt = preqs.begin(); itt != preqs.end(); itt++)
		{
			int x2, y2;
			Course* depCourse = getCourseByCode((*itt));

			if (depCourse != NULL)
			{
				x2 = (depCourse->getGfxInfoComp().topLeft.x + depCourse->getGfxInfoComp().bottomRight.x) / 2;
				y2 = depCourse->getGfxInfoComp().bottomRight.y;
				//x2 = depCourse->getGfxInfo().x;
				//y2 = depCourse->getGfxInfo().y;
				depCourse->DrawCourseDeps(pGUI, x1, y1, x2, y2-5, dType);
			}
		}
	}
	else if (dType == COREQ)
	{
		for (itt = coreqs.begin(); itt != coreqs.end(); itt++)
		{
			int x2, y2;
			Course* depCourse = getCourseByCode((*itt));

			if (depCourse != NULL)
			{
				x2 = (depCourse->getGfxInfoComp().topLeft.x + depCourse->getGfxInfoComp().bottomRight.x) / 2;
				y2 = depCourse->getGfxInfoComp().bottomRight.y;
				//x2 = depCourse->getGfxInfo().x;
				//y2 = depCourse->getGfxInfo().y;
				depCourse->DrawCourseDeps(pGUI, x1, y2-15, x2, y2-15, dType);
			}
		}
	}

}
Course* StudyPlan::getCourseByCode(Course_Code code) const
{
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			std::list<Course*>::iterator it;
			for (it = currentSemester.begin(); it != currentSemester.end(); it++)
			{
				Course* currentCourse = (*it);
				string s = currentCourse->getCode();
				if (stringIsEqual(code, s))
					return currentCourse;
			}
		}
	}
}

bool StudyPlan::stringIsEqual(string& f, string& s) const
{
	return std::equal(f.begin(), f.end(), s.begin(),s.end(),
		[](char f, char s) {
			return tolower(f) == tolower(s);
		});
}
//
void StudyPlan::setMap(int sem, FILTERS year)
{
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			if ((*academicYear)->getCredits(sem) > 18 || (*academicYear)->getCredits(sem) < 9 && sem != SUMMER)
			{
				int Year = (*academicYear)->getYear();
				switch (Year)
				{
				case 1:
					year = Year1;
					break;
				case 2:
					year = Year2;
					break;
				case 3:
					year = Year3;
					break;
				case 4:
					year = Year4;
					break;
				case 5:
					year = Year5;
					break;
				default:
					break;
				}
				credProblemMap.insert(pair<int, FILTERS>(sem, year));
			}
		}
	}
}
void StudyPlan::setMap(Course* pC, int sem)
{
	offeringProblemMap.insert(pair<Course*, int>(pC, sem));
}
StudyPlan::~StudyPlan()
{
}
