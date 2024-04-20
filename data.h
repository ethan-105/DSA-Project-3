#pragma once
#include <string>
using namespace std;

struct Data // Data for in crime report
{
	string caseNum;
	string dateOCC;
	string timeOCC;
	string areaName;
	Data()
	{
		this->caseNum = "";
		this->dateOCC = "";
		this->timeOCC = "";
		this->areaName = "";
	}
	Data(string caseNum, string dateOCC, string timeOCC, string areaName)
	{
		this->caseNum = caseNum;
		this->dateOCC = dateOCC;
		this->timeOCC = timeOCC;
		this->areaName = areaName;
	}
};