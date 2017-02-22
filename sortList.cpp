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
  regex checkExtensions("^.+\\..+");
  if (status == 1){
  if(regex_match(input, checkExtensions)){
    for(int i = 0; i<input.length(); i++){
      if (input[i] == '.'){
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
        regex checkFiles("^.*(.txt)$");
        dpdf = opendir(directory.c_str());
        if (dpdf != NULL) {
                while (epdf = readdir(dpdf)) {
                        if (regex_match(string(epdf->d_name), checkFiles)) {
                                if (directory[directory.size()] != '/') {
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
        for (int i = 0; i<checkList.size(); i++) {
                if(checkList[i] == word) {
                        //cout << "Duplicate " << word << " Found" << endl;
                        return false;
                }
        }
        return true;
}

int letterToAscii (string letter){
  string s = letter;
  return (s[0]);
}
bool order (string i, string j) { return (letterToAscii(i)<letterToAscii(j)); }
void sort (vector<string> &vec) {
    sort(vec.begin(), vec.end(), order);
}

string checkFormat(string wordToCheck){
        //cout << "Checking format of: " << wordToCheck << endl;
        stringstream tempString;
        wordToCheck = trim(wordToCheck);
        for(int i = 0; i < wordToCheck.size(); i++) {
                if(wordToCheck[i] == '/') {
                        for (int i=0; i<wordToCheck.length(); i++)
                        {
                                if (wordToCheck[i] == '/')
                                        if (i != wordToCheck.length()-1) {
                                                wordToCheck[i] = '\n';
                                        } else wordToCheck[i]=' ';
                        }
                        //cout << "Returning: " << wordToCheck;
                        return trim(wordToCheck);

                } else if(wordToCheck[i] == '\\') {
                        for (int i=0; i<wordToCheck.length(); i++)
                        {
                                if (wordToCheck[i] == '\\')
                                        if (i != wordToCheck.length()-1) {
                                                wordToCheck[i] = '\n';
                                        } else wordToCheck[i]=' ';
                        }
                        return trim(wordToCheck);
                }
        }
        return trim(wordToCheck);
}

void wordlistToFile(string listsDir, string outputDir, int splitURL, int sorting, int status){
        vector<string> enumeratedVector;
        enumeratedVector = wordlistsToVector(listsDir, splitURL, sorting, status);
        ofstream newWordlist(outputDir);
        for (int i = 0; i<enumeratedVector.size(); i++) {
                newWordlist << enumeratedVector[i] << endl;
        }
        newWordlist.close();
}

vector<string> wordlistsToVector(string directory, int splitURL, int sorting, int status){
        vector<string> fileNameVector;
        vector<string> wordListVector;
        fileNameVector = getFileNames(directory);
        cout << "Found " << fileNameVector.size() << " files to proccess" << endl;
        string line;
        string formattedString;

        for(int i = 0; i<fileNameVector.size(); i++) {
                // cout << "Proccessing: " << fileNameVector[i] << endl;
                cout << "\r" << "Proccessing ==> " << fileNameVector[i] << "                        ";
                cout << flush;
                ifstream openCurrentList(fileNameVector[i]);
                if (splitURL == 1) {
                        while (getline(openCurrentList, line) ) { // iterate line by line of file
                                formattedString = checkFormat(line);
                                if(checkForDuplicates(wordListVector, checkFormat(line)) == true) {
                                        formattedString = removeExtensions(formattedString);
                                        wordListVector.push_back(formattedString); //append line to vector
                                }
                        }
                } else {
                        while (getline(openCurrentList, line) ) { // iterate line by line of file
                                if(checkForDuplicates(wordListVector, line) == true) {
                                        formattedString = removeExtensions(line);
                                        wordListVector.push_back(formattedString); //append line to vector
                                }
                        }
                }
                if (sorting == 1){
                  sort(wordListVector);
                }
        }
        cout << endl << "Created wordlist of " << wordListVector.size() << " words"<< endl;
        return wordListVector;
}


int main(int argc, char* argv[]){

        Input options;

        try{
                options.getOptions(argc, argv);
        }catch (int e) {
                if (e == 1) {
                        return 0;
                }
                return 0;
        }

        splashScreen();
        options.showOptions();
        try{
                wordlistToFile(options.getDirectory(), options.getOutput(), options.getSplitURL(), options.getSorting(), options.getExtension());
        } catch (int e) {

        }

        cout << "====== Done!=====" << endl;
        return 0;
}
