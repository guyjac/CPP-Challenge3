using namespace std;

#include "ReadWords.h"

/*
* Opens the file if possible. Closes if not.
*/
ReadWords::ReadWords(string fname){
	wordfile.open(fname);
    if (!wordfile){
		cout << "Failed to open " << fname << endl;
        exit(1);
    }
    //Skips the initial whitepsace
    wordfile >> nextword;
    eoffound = false;
}

/*
* This function is used to return the nextword in the file
*/
string ReadWords::getNextWord() {
    word = nextword;
    //Progress to the nextword
    wordfile >> nextword;
    return word;
}

/*
* Returns true whilst it is NOT at the end.
*/
bool ReadWords::isNextWord() {
      if (!wordfile.eof())
        eoffound = true;
      else
        eoffound = false;

    return eoffound;
}

/*
* Closes the wordfile
*/
void ReadWords::close() {

    if (wordfile.is_open())
        wordfile.close();
}


