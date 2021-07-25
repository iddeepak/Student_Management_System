#include <string>
#include <vector>

using namespace std;

struct Result
{
    int class_, year;
    int marks[5];
};

class Student
{

public:
    int rollno;
    string name, fathername;
    vector<Result> r;
    int current_class;

    void printDetails();
    void printResult(Result x);
};
