#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <unistd.h>
#include <iostream>
#include "input.h"
#include <string>

using namespace std;

class Input{

  int c;
  string outPutDir, directory;
  int sorting;

public:

  int splitURL;
  void getOptions(int argc, char* argv[]);
  string getDirectory();
  string getOutput();
  void show_usage(string name);
  int getSplitURL();
  void showOptions();
  int getSorting();

  Input(){
    splitURL = 0;
    sorting = 0;
  }
};

#endif
