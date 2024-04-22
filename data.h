#pragma once
#include <string>
using namespace std;

struct Data // Data for in crime report
{
	string caseNum;
	string dateOCC;
	string crimeCode;
	string areaName;
	Data()
	{
		this->caseNum = "";
		this->dateOCC = "";
		this->crimeCode = "";
		this->areaName = "";
	}
	Data(string caseNum, string dateOCC, string crimeCode, string areaName)
	{
		this->caseNum = caseNum;
		this->dateOCC = dateOCC;
		this->crimeCode = crimeCode;
		this->areaName = areaName;
	}
};