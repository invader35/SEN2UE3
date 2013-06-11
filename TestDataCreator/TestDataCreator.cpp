///////////////////////////////////////
// Workfile    : TestDataCreator.cpp
// Author      : Matthias Schett
// Date        : 06-04-2013
// Description : Creates test data
// Remarks     : -
// Revision    : 0
///////////////////////////////////////
#include "TestDataCreator.h"
#include <iostream>
#include <set>
using namespace std;

// Writes the file header
void writeFileHeader(ofstream & file, size_t numOfEntries){
    file << "Values" << "/" << numOfEntries << ":\n";
}

// Generates random values between 0 and 1000
int getRandomNumber(){
    return rgen::GetRandVal(0, 1000);
}

// Writes the values to the file
void writeDataToFile(ofstream & file){
    file << getRandomNumber() << ",";
}

// Checks if the file has .txt as file extension
string checkForFileExtension(string fileName){
    if(fileName.find_last_of(".txt") == string::npos){
        fileName.append(".txt");
    }
    return fileName;
}

void CreateTestFile(std::string fileName, size_t numOfEntries){
    ofstream file;
    file.open(checkForFileExtension(fileName));
    // Init random generator once for each file
    rgen::Init();

    writeFileHeader(file, numOfEntries);
    for(size_t i = 0; i <= numOfEntries; i++){
        writeDataToFile(file);
    }

    file.close();
    cout << "Test Data created" << endl;
}

// Writes overlap to file
void writeResultFile(ofstream & file, set<double> & valueSet){
    for(set<double>::iterator it = valueSet.begin(); it != valueSet.end(); ++it){
        file << "  " << *it;
    }
    file.close();
}

void CreateTestData(int argc, char *argv[]){
    if(argc < 2){
        cout << "Es wurden zu wenig Parameter uebergeben.\nBeispiel: TestDataCreator.exe TestFile 1000" << endl;
    } else if(argc > 1000){
        cout << "Es wurden zu viele Werte angefordert, es duerfen maximal 1000 Werte generiert werden" << endl;
    } else if((argc - 1) % 2 == 0) { 
        set<double> valueSet;
        for(int i = 1; i < argc; i+=2){
            int numOfEntries = atoi(argv[i+1]);
            if(numOfEntries < 0){
                cout << "Anzahl der Eintraege darf nur Positiv sein" << endl;
                numOfEntries -= -1;
            }
            string fileName(argv[i]);
            CreateTestFile(fileName, numOfEntries);
            set<double> tempSet = valueSet;
            if(checkGrammar(fileName, tempSet)){
                valueSet = tempSet;
            }
        }
        ofstream resultFile("Result.txt");
        writeResultFile(resultFile, valueSet);
    } else{
        cout << "Fehlerhafte Parameter Uebergabe.\nBeispiel: TestDataCreator.exe TestFile 1000" << endl;
    }
}

