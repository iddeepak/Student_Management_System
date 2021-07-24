#include "sqlite3.h"
#include "Student.h"
using namespace std;

class DatabaseManager
{

private:
     sqlite3 *DB;

public:
     void setupDatabase();
     void createTable();
     void closeDatabase();

     void saveStudentData(Student x);
     void saveResultData(Result x, int rollno);

     void getStudentData();
     Student getStudentData(int rollno);
     void getResultData();
     Result getResultData(int rollno);
     void deleteData(int rollno);
     void updateData(int rollno);
};