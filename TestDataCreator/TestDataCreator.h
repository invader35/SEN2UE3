///////////////////////////////////////
// Workfile    : TestDataCreator.h
// Author      : Matthias Schett
// Date        : 06-04-2013
// Description : Creates test data
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#include "RandomGen.h"
#include <fstream>
#include <string>
#include "GrammarCheck.h"

// Creates TestData
void CreateTestData(int argc, char *argv[]);
// Creates a single Test File
void CreateTestFile(std::string fileName, size_t numOfEntries);