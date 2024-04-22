#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map> // Necessary for below, not used in main code

using namespace std;

struct ParsedCSV {
    vector<unordered_map<string, string>> csvData;
    vector<string> headers;
    ParsedCSV() {}
    vector<string> readCSVLine(string line) {
        size_t index = 0;
        unsigned int headerPos = 0;
        vector<string> output;
        while (true) {
            size_t endIndex = index;
            string nextToAdd = "";
            if (line[index] == '"') {
                endIndex = line.find('"', index + 1);
                output.push_back(line.substr(index + 1, (endIndex - index - 1)));
                if (endIndex == string::npos) {
                    break;
                }
                index = endIndex + 2;
                continue;
            }
            endIndex = line.find(',', index);
            if (endIndex == string::npos) {
                break;
            }
            output.push_back(line.substr(index, (endIndex - index)));
            index = endIndex + 1;
        }
        return output;
    }
    bool parseFile(string fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            throw new invalid_argument("File could not be opened");
        }
        string line;
        getline(file, line);
        headers = readCSVLine(line);
        while (getline(file, line))
        {
            if (csvData.size() % 10000 == 0) {
                cout << csvData.size() << endl;
            }
            vector<string> vect = readCSVLine(line);
            if (vect.size() != headers.size()) {
                throw new invalid_argument("Row " + to_string(csvData.size()+2) + " did not match header column count");
            }
            unordered_map<string, string> toPush;
            for (int i = 0; i < vect.size(); i++) {
                toPush.emplace(headers[i], vect[i]);
            }
            csvData.push_back(toPush);
        }
    }
};


