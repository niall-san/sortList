#ifndef SORTLIST_H
#define SORTLIST_H

#include<iostream>
#include<string>
#include<regex>
#include<fstream>
#include <stdio.h>
#include <dirent.h>
#include <sstream>


using namespace std;

vector<string> wordlistsToVector(string directory);
vector<string> slashSplitString(string input, char delimiter);
string trim(string str);
vector<string> getFileNames(string directory);
bool checkForDuplicates(vector<string> checkList, string word);
string checkFormat(string wordToCheck);
void wordlistToFile(string listsDir, string outputDir);
vector<string> wordlistsToVector(string directory);
void splashScreen();


#endif
