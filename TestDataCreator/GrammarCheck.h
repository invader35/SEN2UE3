///////////////////////////////////////
// Workfile    : GrammarCheck.cpp
// Author      : Matthias Schett
// Date        : 06-04-2013
// Description : Creates test data
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#include "scanner.h"
#include <fstream>
#include <string>
#include <iostream>
#include <set>

bool checkGrammar(std::string fileName, std::set<double> & valueSet);