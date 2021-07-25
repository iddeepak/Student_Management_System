#include "Student_Manager.h"
#include <iostream>
DatabaseManager d;

void StudentManager ::inputData()
{
  d.setupDatabase();
  d.createTable();
  Student s;
  cout << endl;
  cout << "      ENTER STUDENT DETAILS " << endl;
  cout << "ENTER ROLL NO - ";
  cin >> s.rollno;
  cout << endl;
  cout << "ENTER NAME - ";
  cin >> s.name;
  cout << endl;
  cout << "ENTER FATHER'S NAME - ";
  cin >> s.fathername;
  cout << endl;
  cout << "ENTER CURRENT_CLASS NAME - ";
  cin >> s.current_class;
  cout << endl;
  Result rr;
  cout << "       ENTER RESULT DETAILS " << endl
       << endl;
  cout << "ENTER CLASS NAME - ";
  cin >> rr.class_;
  cout << endl;
  cout << "ENTER YEAR - ";
  cin >> rr.year;
  cout << endl;
  cout << "ENTER MARKS IN ENGLISH - ";
  cin >> rr.marks[0];
  cout << endl;
  cout << "ENTER MATH - ";
  cin >> rr.marks[1];
  cout << endl;
  cout << "ENTER HINDI - ";
  cin >> rr.marks[2];
  cout << endl;
  cout << "ENTER SCIENCE - ";
  cin >> rr.marks[3];
  cout << endl;
  cout << "ENTER SST - ";
  cin >> rr.marks[4];
  cout << endl;
  s.r.push_back(rr);
  cout << endl;
  s.printDetails();
  d.saveStudentData(s);
}

void StudentManager ::showStudentData()
{
  d.setupDatabase();
  d.getStudentData();
}

void StudentManager ::showStudentDataByRollno()
{
  Student s;
  int temp;
  cout << " GET DATA BY ROLLNO - " << endl;
  cin >> temp;
  d.setupDatabase();
  s = d.getStudentData(temp);
  s.printDetails();
}

void StudentManager ::showResultData()
{
  d.setupDatabase();
  d.getResultData();
}

void StudentManager ::showResultDataByRollno()
{
  Result rr;
  int temp;
  cout << " GET RESULT DATA BY ROLLNO - " << endl;
  cin >> temp;
  d.setupDatabase();
  rr = d.getResultData(temp);

  cout << "Class " << rr.class_ << endl;
  cout << "Year " << rr.year << endl;
  string temp_[5] = {"ENGLISH", "MATH", "HINDI", "SCIENCE", "SST"};
  for (int i = 0; i < 5; i++)
    cout << "MARKS IN " << temp_[i] << " " << rr.marks[i] << endl;
}
void StudentManager ::deleteData()
{
  int temp;
  cout << " ENTER ROLLNO TO DELETE DETAILS - " << endl;
  cin >> temp;
  d.setupDatabase();
  d.deleteData(temp);
}
void StudentManager ::updateData()
{
  int temp;
  cout << " ENTER ROLLNO TO UPDATE DETAILS - " << endl;
  cin >> temp;
  d.setupDatabase();
  d.updateData(temp);
}