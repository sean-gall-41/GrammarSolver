/*
 * CS 106B Recursion Problems
 * This file declares necessary function prototypes, so that other files
 * are able to call the recursive functions you will write.
 *
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * (If you want to declare your own helper function prototypes,
 *  do that near the top of your .cpp file, not here.)
 */

#ifndef _recursionproblems_h
#define _recursionproblems_h

#include <iostream>
#include <string>
#include "gbufferedimage.h"
#include "gwindow.h"
#include "vector.h"
#include "map.h"

// function prototype declarations
// (If you want to declare your own helper function prototypes, do that near
//  the top of your .cpp file, not here.  You should NOT modify this file.)
Vector<std::string> grammarGenerate(std::istream& input, std::string symbol, int times);
//Helper function to generate a map reperesentation of the grammar within input
void generateGrammarMap(std::istream& input, Map<std::string, Vector<std::string>>& inMap);
//Helper function to recursively generate a vector of vector.size() occurances of symbol
void grammarGenerate(const Map<std::string, Vector<std::string>>& inMap, std::string& result, std::string symbol);
#endif

/*
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 */
