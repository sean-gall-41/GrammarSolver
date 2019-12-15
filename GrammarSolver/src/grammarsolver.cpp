/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include <sstream>
#include "grammarsolver.h"
#include "strlib.h" //for StringSplit and trim

using namespace std;
//const string DELIMITER = "::=";

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    Vector<string> outVec;
    Map<string, Vector<string>> grammarMap;
    generateGrammarMap(input, grammarMap);
    //TODO: implement recursive algorithm to generate random symbol from the grammar.
    for (int i = 0; i < times; i++) { //loop times times to generate times number of random instantiations of symbol
        string symbolInstance = "";
        grammarGenerate(grammarMap, symbolInstance, symbol);
        outVec.add(trim(symbolInstance)); //If we do not add ws between symbols, no need for trim...
    }
    return outVec; // create a caller condition on whether outVec is empty or not
    //return {};           // This is only here so it will compile
}

//Implementation of helper function for generating the map representation of the grammar from input istream
void generateGrammarMap(istream& input, Map<string, Vector<string>>& inMap) {
    string stringToParse = "", key = ""; //stringToParse is each line of the BNF formatted grammar
    int lineCounter = 0;

    //Robust implementation (more testing Berhaps...)
    while (getline(input, stringToParse)) {
        stringToParse = trim(stringToParse); //trim the string in case there are extra ws chars at ends
        int indexOfDelim = stringToParse.find("::=");
        int i = 0;
        while (i < indexOfDelim) {
            if (stringToParse[i] != ' ') {
                key += stringToParse[i];
            }
            ++i;
        }
        i +=3;
        //error checking like non-robust version...
        if (inMap.containsKey(key)) {
            //NOTE: Have to declare a string object and initialize to the desired string
            //As a string literal is represented internally as const char*
            throw runtime_error("The key " + key + " already exists.");
        }
        //now get the substring associated with the value of rules and trim it
        stringToParse = trim(stringToParse.substr(i));
        Vector<string> valueVec = stringSplit(stringToParse, "|");
        for (string rule : valueVec) {
            rule = trim(rule); //trim the rule of any extra ws.
        }
        inMap.put(key, valueVec);
        cout << key << " ; " << valueVec.toString() << endl;
        key = "";
        ++lineCounter;
    }
//    while (getline(input, stringToParse)) { //FIXME: need a better condition for the loop
//        int indexOfDelim = stringToParse.find("::="); //declaring a variable as we want this value to use later
//        if (indexOfDelim == string::npos) {
//            //Throws a runtime_error to the caller ie grammarmain (FIXME: the file is in poor format, cannot continue!)
//            throw runtime_error("INPUT FILE IS IN INCORRECT FORMAT. EXPECTED \"::=\" IN LINE " + integerToString(lineCounter + 1) + ".");
//        }
//        else {
//            int i = 0;
//            while (i < indexOfDelim /*stringToParse[i] != ':'*/) { //This loop serves to obtain the key of a given line
//                key += stringToParse[i];
//                ++i;
//            }
//            i += 3;
//            //If the map contains the key before adding it, then we must have a copy.
//            if (inMap.containsKey(key)) {
//                //NOTE: Have to declare a string object and initialize to the desired string
//                //As a string literal is represented internally as const char*
//                throw runtime_error("The key " + key + " already exists.");
//            }
//            inMap.put(key, stringSplit(stringToParse.substr(i), "|"));
//            //cout << inMap.toString() << endl;
//            key = ""; //re initialize-key!
//            ++lineCounter;
//        }
//    }
}

//does not return anything, so the recursion will have to rely on internally altering inVec
//The idea being that we move "sequentially" in adding strings to our vec via recursive calls to grammarGenerate
void grammarGenerate(const Map<string, Vector<string>>& inMap, string& result, string symbol) {
    if (symbol.length() == 0) { //throw a string (exception? is that its own type?) if the symbol passed is empty
        throw runtime_error("The symbol entered is empty.");
    }
    if (!inMap.containsKey(symbol)) { //This is the base case: if the symbol is not one of our keys, then we take it to be a terminal
        result += symbol;             //and add it to our result string
        result += " "; // add an extra space since the stringstream skips whitespace
    }
    else {
        //TODO Break down each rule by finding matching keys sequentially for all symbols in the rule
        string rule = randomElement(inMap.get(symbol)); //get a random element of the value associated with key == symbol
        stringstream ruleAnalyzer(rule); //Construct a stringstream containing contents of rule string
        while (ruleAnalyzer >> symbol) { //skip whitespace by default thanks to intrinisic properties of extraction operator
            grammarGenerate(inMap, result, symbol);
        }
        ruleAnalyzer.clear(); //Is this call necessary?
        //ruleAnalyzer.close(); ig close isnt inherited by sstream...
    }
}

