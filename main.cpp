#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	std::cout << "Hello world!" << std::endl;

	ifstream file("Trimmed_Crime_Data_from_2020_to_Present.csv");
	string line;
	getline(file, line); // Clear header
	while (getline(file, line))
	{
		// Date reported
		size_t firstDelim = line.find(',');
		size_t secondDelim = line.find(',', firstDelim + 1);
		string dateRptd = line.substr(firstDelim + 1, 10);
		cout << dateRptd << " ";
		// Date Occurred
		string dateOCC = line.substr(secondDelim + 1, 10);
		cout << dateOCC << " ";
		// Time Occurred
		size_t thirdDelim = line.find(',', secondDelim + 1);
		string timeOCC = line.substr(thirdDelim + 1, 4);
		cout << timeOCC << " ";
		// Area Name
		size_t fifthDelim = line.find(',', line.find(',', thirdDelim + 1) + 1);
		size_t sixthDelim = line.find(',', fifthDelim + 1);
		string areaName = line.substr(fifthDelim + 1, (sixthDelim - (fifthDelim + 1)));
		cout << areaName << endl;
	}
}