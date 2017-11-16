#include "sortList.h"
#include "input.h"

using namespace std;




void splashScreen() {
        cout<< " ____ ____ ____ ___ _    _ ____ ___"<< endl;
        cout<< "[__  |  | |__/  |  |    | [__   |  "<< endl;
        cout<< "___] |__| |  \\  |  |___ | ___]  |  "<< endl;
        cout<< "-----------------------------------"<< endl;
}


vector<string> slashSplitString(string input, char delimiter){
        stringstream stringToSplit(input);
        string segment;
        vector<string> seglist;

        while(getline(stringToSplit, segment, delimiter))
        {
                seglist.push_back(segment);
        }
        return seglist;
}

string trim(string str)
{
        int i = 0;
        for (char c : str)
        {
                if (!isspace(c))
                        break;
                i++;
        }
        string trimmed = str.substr(i, (str.length()-i));
        i = 0;
        for (char c : str)
        {
                if (isspace(c))
                        break;
                i++;
        }
        trimmed = trimmed.substr(0, i);
        return trimmed;
}

string removeExtensions(string input, int status){
        regex checkExtensions("^.+\\..*$");
        if (status == 1) {
                if(regex_match(input, checkExtensions)) {
                        for(int i = 0; i<input.length(); i++) {
                                if (input[i] == '.') {
                                      //  cout << "Found . in: " << input << endl;
                                        input = input.substr(0,i);
                                }
                        }
                }
        }
        return input;
}


vector<string> getFileNames(string directory){
        DIR *dpdf;
        struct dirent *epdf;
        std::vector<string> filenames;
        regex checkFiles("^.*\\.(txt|wordlist|list)$");
        dpdf = opendir(directory.c_str());
        if (dpdf != NULL) {
                while (epdf = readdir(dpdf)) {
                        if (regex_match(string(epdf->d_name), checkFiles)) {
                                if (directory[directory.size()-1] != '/') {
                                        filenames.push_back(directory+'/'+string(epdf->d_name));
                                } else {
                                        filenames.push_back(directory+string(epdf->d_name));
                                }
                        }
                }
        } else {
                cout << "[Error] - Directory does not exist" << endl;
                throw 1;
        }
        if (filenames.size() == 0) {
                cout << "[Error] - Directory does not contain .txt file" << endl;
        }
        return filenames;
}


bool checkForDuplicates(vector<string> checkList, string word){
        return(find(checkList.begin(), checkList.end(), word) != checkList.end());
}

void sort (vector<string> &vec) {
        sort(vec.begin(), vec.end());
}


vector<string> explode(string const & s, int status)
{
  vector<string> result;
    if (status == 1){
      istringstream iss(s);

      for (string token; getline(iss, token, '/'); )
      {
          result.push_back(move(token));
        }

        return result;
      }
  result.push_back(s);
  return result;
}



void wordlistToFile(Input options){
        vector<string> enumeratedVector;
        enumeratedVector = wordlistsToVector(options);
        ofstream newWordlist;
        int wordcount = 0;
        regex finalCheck("[a-zA-Z\\./0-9~]+");
        newWordlist.open(options.getOutput());
        for (int i = 0; i<enumeratedVector.size(); i++) {
          if(regex_match(enumeratedVector[i], finalCheck)){
            wordcount = wordcount + 1;
            newWordlist << enumeratedVector[i] << endl;
          }
        }
        cout << endl << "Created wordlist of " << wordcount << " words"<< endl;
        newWordlist.close();
}

vector<string> wordlistsToVector(Input options){
        vector<string> fileNameVector;
        vector<string> wordListVector;
        fileNameVector = getFileNames(options.getDirectory());
        cout << "Found " << fileNameVector.size() << " files to proccess" << endl;
        string line;
        string tempString;
        vector<string> temp;

        for(int i = 0; i<fileNameVector.size(); i++) {
                // cout << "Proccessing: " << fileNameVector[i] << endl;
                cout << "\r" << "Proccessing ==> " << fileNameVector[i] << "                        ";
                cout << flush;
                ifstream openCurrentList(fileNameVector[i]);
                while (getline(openCurrentList, line)) { // iterate line by line of file
                  temp = explode(line, options.getSplitURL());
                  for(int e = 0; e<temp.size(); e++){
                  tempString = trim(temp[e]);
                  tempString = removeExtensions(tempString, options.getExtension());
                  if (checkForDuplicates(wordListVector,tempString) == false){
                          wordListVector.push_back(tempString);
                        }
                }
        }
    }
        if (options.getSorting() == 1){
          sort(wordListVector);
        }

        return wordListVector;
}


int main(int argc, char* argv[]){

        Input options;

        try{
                options.getOptions(argc, argv);
        }catch (int e) {
          return 0;
        }

        splashScreen();
        options.showOptions();
        try{
                wordlistToFile(options);
        }catch(int e){
          return 0;
        }

        cout << "====== Done!=====" << endl;
        return 0;
}
