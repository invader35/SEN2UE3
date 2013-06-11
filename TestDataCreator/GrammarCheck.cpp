///////////////////////////////////////
// Workfile    : GrammarCheck.cpp
// Author      : Matthias Schett
// Date        : 06-04-2013
// Description : Creates test data
// Remarks     : -
// Revision    : 0
///////////////////////////////////////
#include "GrammarCheck.h"
#include <set>
using namespace std;

void printError(string fileName, scanner & scan){
    cout << "unkown file format for file " << fileName << endl;
    cout << "Error is near: " << scan.get_string();
}

bool isTbWord(scanner & scan){
    return scan.symbol_is_identifier();
}

bool isTbInt(scanner & scan){
    return scan.symbol_is_integer();
}

bool isTbReal(scanner & scan){
    return scan.symbol_is_real();
}

bool isTbDiv(scanner & scan){
    return scan.symbol_is_division();
}

bool isTbColon(scanner & scan){
    return scan.symbol_is_colon();
}

bool isTbComma(scanner & scan){
    return scan.symbol_is_comma();
}

bool checkHeader(scanner & scan){
    if(isTbWord(scan)){
        string word = scan.get_string();
        if(word == "Values"){
            scan.next_symbol();
            if(isTbDiv(scan)){
                scan.next_symbol();
                if(isTbInt(scan)){
                    if(scan.get_integer() < 1000){
                        scan.next_symbol();
                        if(isTbColon(scan)){
                            scan.next_symbol();
                            return true;
                        }
                    }
                }
            } 
        }
    }
    return false;
}

// Checks for duplicates and removes them -> also shows the caller if there was a duplicate
bool checkForDuplicate(set<double> & valueSet, double value){
    pair<set<double>::iterator, bool> ret = valueSet.insert(value);
    return ret.second;
}

void checkValues(scanner & scan, set<double> & valueSet, string fileName){
    
    while(!scan.symbol_is_eof()){
        if(isTbInt(scan)){
            int value = scan.get_integer();
            checkForDuplicate(valueSet, value);
        } else if(isTbReal(scan)){
            double value = scan.get_real();
            checkForDuplicate(valueSet, value);
        } else if(isTbComma(scan)){
            // DO NOTHING
        } else {
            printError(fileName, scan);
        }

        scan.next_symbol();
    }
}

bool checkGrammar(string fileName, set<double> & valueSet){
    ifstream file(fileName);
    scanner scan (file);
    
    bool result = true;
    if(checkHeader(scan)){
        checkValues(scan, valueSet, fileName);
    } else{
        printError(fileName, scan);
        result = false;
    }
    file.close();
    return result;
}