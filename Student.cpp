#include <iostream>
#include "Student.h"

using namespace std;

void Student ::printDetails()
{
        cout << "      STUDENT'S DETAILS :" << endl;
        cout << "ROLLNO - " << rollno << endl;
        cout << "NAME - " << name << endl;
        cout << "FATHER'S NAME - " << fathername << endl;
        cout << "CURRENT CLASS NAME - " << current_class << endl
             << endl;

        for (int i = 0; i < r.size(); i++)
        {
                printResult(r[i]);
        }
}

void Student ::printResult(Result x)
{
        cout << "      STUDENT'S RESULT DETAILS : " << endl;
        cout << "Class " << x.class_ << endl;
        cout << "Year " << x.year << endl;
        string temp_[5] = {"ENGLISH", "MATH", "HINDI", "SCIENCE", "SST"};
        for (int i = 0; i < 5; i++)
                cout << "MARKS IN " << temp_[i] << " - " << x.marks[i] << endl;
}