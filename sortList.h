#ifndef SORTLIST_H
#define SORTLIST_H

#include<iostream>
#include<string>
#include<regex>
#include<fstream>
#include <stdio.h>
#include <dirent.h>
#include <sstream>
#include "input.h"
#include <algorithm>

using namespace std;
vector<string> explode(string const & s, char delim);
vector<string> wordlistsToVector(Input options);
string trim(string str);
vector<string> getFileNames(string directory);
bool checkForDuplicates(vector<string> checkList, string word);
vector<string> checkFormat(string wordToCheck, int status);
void wordlistToFile(Input options);
void splashScreen();
string removeExtensions(string input, int status);


#endif
