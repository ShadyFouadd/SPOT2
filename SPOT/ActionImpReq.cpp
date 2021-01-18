#include "ActionImpReq.h"
#include <fstream>
#include "Registrar.h"
#include <iostream>
ActionImpReq::ActionImpReq(Registrar* p) :Action(p)
{
}

void ActionImpReq::codesToVector(ifstream& file, vector<Course_Code>& vector)
{
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];
	file.getline(line, size);
	pch = strtok_s(line, ",", &context);
	while (pch != NULL)
	{
		vector.push_back(pch);
		pch = strtok_s(NULL, ",", &context);
	}
}

void ActionImpReq::functionImpReq(string filename)
{
	Rules newRules;
	int temp[5];
	ifstream infile(filename);
	if (!infile)
	{
		cout << "Requirements file failure";
	}
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];

	//get 1.TotalCredits, 2.ReqUnivCredits, 3.ReqTrackCredits, 4.ReqMajorCredits and 5.ConcentrationsNumber.
	for (int i = 0; i < 5; i++) //loop to read first 5 lines
	{
		temp[i] = 0;
		infile.getline(line, size);
		pch = strtok_s(line, ",", &context);
		while (pch != NULL)
		{
			temp[i] += stoi(pch);
			pch = strtok_s(NULL, ",", &context);
		}
	}
	newRules.TotalCredits = temp[0];
	newRules.ReqUnivCredits = temp[1];
	newRules.ReqTrackCredits = temp[2];
	newRules.ReqMajorCredits = temp[3];
	newRules.ConcentrationsNumber = temp[4];

	//6.get ReqConcentrationCredits
	infile.getline(line, size);
	pch = strtok_s(line, ",", &context);
	if (newRules.ConcentrationsNumber != 0)
	{
		for (int i = 0; i < newRules.ConcentrationsNumber; i++) //get number of elec& compulsory credits of concentrations
		{
			temp[0] = 0;
			for (int j = 0; j < 2; j++) //2 iterations to get 1-compulsory, 2-elective and store their sum in temp[0]
			{
				temp[0] += stoi(pch); //temp used to store sum
				pch = strtok_s(NULL, ",", &context);
			}
			newRules.ReqConcentrationCredits.push_back(temp[0]);
		}
	}
	else
	{
		newRules.ReqConcentrationCredits.push_back(0);
	}

	//get 7.UnivCompulsory
	codesToVector(infile, newRules.UnivCompulsory);

	//get 8.UnivElective
	codesToVector(infile, newRules.UnivElective);

	//get 9.TrackCompulsory
	codesToVector(infile, newRules.TrackCompulsory);

	//10.get MajorCompulsory
	codesToVector(infile, newRules.MajorCompulsory);

	//11.get MajorElective
	codesToVector(infile, newRules.MajorElective);

	//12. ... get concentrations Compulsory and elective courses
	for (int i = 0; i < newRules.ConcentrationsNumber; i++)
	{
		codesToVector(infile, newRules.ConcentrationsCompulsory[i]);
		codesToVector(infile, newRules.ConcentrationsElective[i]);
	}

	infile.close();
	//pass the rules to the registrar
	pReg->setRules(newRules);
}

bool ActionImpReq::Execute()
{
	switch (pReg->getSignedStudest()->getMajor())
	{
	case CIE:
		functionImpReq("Files\\CIE_REQ.txt");
		break;
	case ENV:
		functionImpReq("Files\\ENV_REQ.txt");
		break;
	case NANES:
		functionImpReq("Files\\NAN_REQ.txt");
		break;
	case NANED:
		functionImpReq("Files\\NAN_REQ.txt");
		break;
	case REE:
		functionImpReq("Files\\REE_REQ.txt");
		break;
	case SPC:
		functionImpReq("Files\\SPC_REQ.txt");
		break;
	default:
		break;
	};

	return true;
}

ActionImpReq::~ActionImpReq()
{

}