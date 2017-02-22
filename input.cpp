#include "input.h"
#include "sortList.h"

using namespace std;

void Input::show_usage(string name) // usage function called when no parameters entered
{       splashScreen();
       cerr << "Usage: " << name << " -d /myWordlistFolder  -o /outputdir/outputfile\n"
            << "Options:\n"
            << "\t-h \tShow this help message\n"
            << "\t-d \tDirectory where wordlists are (must be .txt)\n"
            << "\t-o \tFile to output as\n"
            << "\t-s \tSorting in ASCII order (by first character of word)\n"
            << "\t-f \tFormat lines that contains deeper than one directory\n"
            << "-------------------------------------------------------------\n"
            << "by oniichan\n"
            << endl;
}


string Input::getDirectory(){
  return directory;
}
string Input::getOutput(){
  return outPutDir;
}
int Input::getSplitURL(){
  return splitURL;
}
int Input::getSorting(){
  return sorting;
}



void Input::getOptions(int argc, char* argv[]){
  if (argc < 4) { //if program run without arguments show help and exit
          show_usage(argv[0]);
          throw 1;
  }

while( ( c = getopt (argc, argv, "hfso:d:") ) != -1 ) {
        switch(c) {
        case 'h':
                show_usage(argv[0]);
                throw 1;
        case 'f':
                splitURL = 1; //optional
                break;
        case 'o':
                if(optarg) outPutDir = optarg; //optional
                break;
        case 'd':
                if(optarg) directory = optarg; //optional
                break;
        case 's':
                sorting = 1; //optional
                break;
        case '?':
                if ((optopt == 'o') || (optopt == 'd')){
                  fprintf(stderr,"\033[031m[Error]\033[0m - Option -%c requires an argument.\n", optopt);
                  throw 1337;
                }else if (isprint (optopt)) {
                  fprintf (stderr,"\033[031m[Error]\033[0m - Unknown option '-%c' (-h for help).\n", optopt);
                  throw 1337;
                }else{
                  fprintf (stderr,"\033[031m[Error]\033[0m - Unknown option character ''\\x%x'.\n", optopt);
                  throw 1337;
                }
        }
}
}

void Input::showOptions(){
  cout << "[Wordlist Directory]" << " - " << directory << endl;
  cout << "[Output File]" << " - " << outPutDir << endl;
  if(splitURL == 0){
  cout << "[Splitting URLs]" << " - No"  << endl;
  } else {
  cout << "[Splitting URLs]" << " - Yes"  << endl;
  }
  if(sorting == 0){
  cout << "[Sorting in ASCII Order]" << " - No"  << endl;
  } else {
  cout << "[Sorting in ASCII Order]" << " - Yes"  << endl;
  }
  cout << "-----------------------------------" << endl;
}
