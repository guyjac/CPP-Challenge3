using namespace std;

#include "student.h"

/*
* Create a student with a name and reg number. A student inherits from person
*/
Student::Student(const string &name, int regNo) : Person (name){
    //set Regno
    this->regNo = regNo;
    //Initialise an empty map
    this -> marks.clear();
}

/*
* Method to add the mark to the map
* If a mark for the module is already present it will be overwritten
*/
void Student::addMark(const string &module, float mark){
    marks[module] = mark;
}

/*
* Method to retrieve the mark for a module
* Throw NoMarkException if student has no mark for that module
*/
float Student::getMark(const string &module) const throw (NoMarkException){

    try{
        return marks.at(module);
    }
    catch(exception e){
        throw NoMarkException();
    }
}

/*
* Method to return registration number
*/
int Student::getRegNo() const{
    return regNo;
}
/*
* Calculates the students average mark by looping and dividing the total by a counter
* Returns 0 if no marks are found
*/
float Student::getAverageMark() const{
    float avg = 0.0;
    int count = 0;
    //Loop through all the marks for the student all calculate an average.
    for (auto s : marks){
        avg +=s.second;
        count ++;
    }
    //Return if a value is found, otherwise return 0.0
    if (count != 0)
        return avg/count;
    return 0.0;
}

/*
* Loops through grades to find a minimum. Bool F is used to determine if a grade is not found.
* If a grade is not found, return 0.0. Else, return the minimum found.
* Initial value of minimum is set as 100 as this is the highest possible score
*/
float Student::getMinimumMark() const{
    bool f = false;
    float minn = 100;
    //Find the smallest value and return it
    for (auto s : marks){
        if (minn>s.second){
            minn = s.second;
            f = true;
        }
    }
    if (f)
        return minn;
    return 0.0;
}

/*
* Find the maximum mark and return it.
* Initially starts at 0.0 as this is the lowest grade possible.
* If no grades are found a default 0.0 will return
*/
float Student::getMaximumMark() const{
    //Minimum mark for a student starts at 0.0
    float maxx = 0.0;
    //Find the largest value and return it
    for (auto s : marks){
        if (maxx<s.second){
            maxx = s.second;
        }
    }
    return maxx;
}

/*
* Print the Reg, name (converted to a c string
* Then loop through a given students marks array and print all their scores
*/
void Student::allMarks(){
    printf("Reg:%d", this->getRegNo() );
    printf(" Name:%s",  this->getName().c_str()  );

    printf("\n");
    for (auto s : marks){
        printf("Module: %s", s.first.c_str());
        printf(" Grade: %.2f",s.second);
        printf("\n");
    }
    printf("\n");
}

// should output name, regno, and minimum, maximum and average marks on a single line
ostream& operator << (ostream &str, const Student &s)
{
    str << "Name:" << s.getName() << " Reg:" << s.getRegNo() <<" Min:"<< s.getMinimumMark()<< " Max:" << s.getMaximumMark() << " Avg:" << s.getAverageMark();
    return str;
}

