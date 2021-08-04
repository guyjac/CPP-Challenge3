using namespace std;

#include "ReadWords.h"
#include "Student.h"

#include <cctype>
#include <list>
#include <iostream>

/*
* Used by the sort method to sort the students by reg no.
*/

bool compareStudents(const Student& first, const Student& sec){
    return first.getRegNo() < sec.getRegNo();
}

/*
* Prints the average grades for students below a given float [Function 1]
* Loops through the student array
* Checks if a studenst mark is greater than the argument mark. Prints values if true.
* Boolean none is used to measure if nothing is found, in which case the user is alerted
*/
static void Averages(list<Student> poplist, float mark){

    poplist.sort(compareStudents);

    bool none = true;
    for (auto studs : poplist){
        //The average mark must be less or equal to the given argument
        if(studs.getAverageMark() <= mark){
            none = false;
            //Prints using overrided <<
            cout << studs << endl;
        }
    }
    cout << endl;
    if(none)
        cout << "No results were found. \n \n";
}

/*
* Prints specific modules for students above a given mark
* Loops through student array and utilises getmark.
* Catches exceptions that may arise if student doesn't take module
* Use boolean "none" to measure if any results are found. If none are found, alert user with warning.
*/
static void ModMarks(list<Student> poplist, float mark, string module){

    bool none = true;
    for(auto studs : poplist){
        try
        {   //Check if the given mark is greater than the mark for the given module
            if(studs.getMark(module) >= mark)
            {
                none = false;
                cout << "Reg:";
                cout << studs.getRegNo();
                cout << " Name:" + studs.getName() + "\n" + module +": ";
                cout << studs.getMark(module) << endl << endl;
            }
        }
        //Catch exceptions if the student doesn't contain that module
        catch (NoMarkException e)
        {
        }
    }
    if(none)
        cout << "No results were found. \n \n";
}

/*
* User inputs filenames for student details and scores
* Creates two filereader objects to input the student details and marks
* These are stored in an Array of student objects, and a map of scores (for each student object)
*
*/
int main(){

    //List of students.
    list<Student> liststuds;
    string fsearch, marks;
    cout << "Please enter the filename for students" << endl;
    cin >> fsearch;
    cout << "Please enter the markfile name" << endl;
    cin >> marks;

    cout << endl;

    //Create filereader objects.
    ReadWords reader = ReadWords(fsearch);
    ReadWords mark = ReadWords(marks);

    //Loops through the student file and create a list of Student objects
    while (reader.isNextWord() == true)
    {
        string regnum = reader.getNextWord();
        string studname = reader.getNextWord();
        studname = studname + " " + reader.getNextWord();
        //Add the student name and reg into an object, and then list
        Student p(studname, stoi(regnum));
        liststuds.push_back(p);
    }

    /*
    * Loop through the marks and add them to the student objects
    * Iterate through student array and add scores based on reg number
    * Use boolean fs to see if a student mark reg matches a student in our list of student objects.
    *
    */
    while (mark.isNextWord() == true)
    {
        bool fs = false;
        int regmar = stoi( mark.getNextWord() );
        string module = mark.getNextWord();
        string grade  = mark.getNextWord();
        list<Student>::iterator it;
        for (it = liststuds.begin(); it != liststuds.end(); ++it){
            //If the reg number of the object in the list matches the input reg from marks file
            if(it->getRegNo() == regmar)
            {   //Multiple by 10 and then divide by 10, due to float Math weirdness
                it->addMark(module, (stoi(grade)*10)/10 );
                fs = true;
            }
        }
        if(!fs){
            cout << "WARNING: Student with Reg:" << regmar << " was not found!" << endl << endl;
        }
    }

    /*
    * Loop through our student collection and use printf to display all their grades.
    */
    for (auto studs : liststuds){
        studs.allMarks();
    }

    /*
    * Menu loop. Ask for user inputs to test the functions
    */
    bool running = true;
    while(running){

        //Reset values
        int input = 0;
        float mark = 0.0;
        string module ="";

        cout << "Please select an option \n" << endl;
        cout << "Type [1] to test function 1 (Averages)\nType [2] to test function 2 (Modules) \nType [3] to quit \n";
        cin >> input;

        if (input==1){
            //Function 1, provides the average marks
            cout << "Please enter a mark [float value]\n";
            cin >> mark;
            cout << endl;
            Averages(liststuds, mark);
        }
        if (input==2){
            //Function 2, checks a modules score given a specific value
            cout << "Please enter a mark [float value]\n";
            cin >> mark;
            cout << "Please enter a module name [string]\n";
            cin >> module;
            cout << endl;
            ModMarks(liststuds, mark, module);
        }
        if (input==3){
            //Quit the program
            cout << "Program terminated";
            running = false;
        }
    }
}



