#include "ActionImpOffering.h"
#include <fstream>
#include "Registrar.h"
#include <iostream>
ActionImpOffering::ActionImpOffering(Registrar* p) :Action(p)
{}


bool ActionImpOffering::Execute()
{
	Rules newRules;
	ifstream infile("Files\\Offerings.txt");
	string dummy;
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];
	SEMESTER sem;
	Course_Code keyy;
	if (!infile)
	{
		cout << "File open failure";
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			infile.getline(line, size);
			//get year title.
			pch = strtok_s(line, ",", &context);
			newRules.OffringsList[i].Year = pch;
			//use dummy variable to skip semester name.
			//dummy = pch;
			pch = strtok_s(NULL, ",", &context);
			dummy = pch;
			if (dummy == " semester 1")
				sem = FALL;
			if (dummy == " semester 2")
				sem = SPRING;
			if (dummy == " semester 3")
				sem = SUMMER;
			//saving the courses
			while (pch != NULL)
			{
				newRules.OffringsList[i].Offerings[j].push_back(pch);
				pch = strtok_s(NULL, ",", &context);
				dummy = pch;
				OfferingCourses.insert(pair<Course_Code, SEMESTER>(dummy, sem));
				pch = strtok_s(NULL, ",", &context);
			}
		}
	}
	infile.close();
	pReg->setOfferingRules(newRules);
	return true;
}

bool ActionImpOffering::checkOffering(Course_Code c, SEMESTER s)
{
	std::map<Course_Code, SEMESTER>::iterator it;
	for (it = OfferingCourses.begin(); it != OfferingCourses.end(); it++)
	{
		if (it->first == c)
			if (OfferingCourses[c] == it->second)
				return false;
	}
}

ActionImpOffering::~ActionImpOffering()
{

}