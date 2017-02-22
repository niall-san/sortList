#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

class Input{

  int c;
  string outPutDir, directory;
  int sorting, extensions;

public:

  int splitURL;
  void getOptions(int argc, char* argv[]);
  string getDirectory();
  string getOutput();
  void show_usage(string name);
  int getSplitURL();
  void showOptions();
  int getSorting();
  int getExtension();

  Input(){
    splitURL = 0;
    sorting = 0;
    extensions = 0;
  }
};

#endif
