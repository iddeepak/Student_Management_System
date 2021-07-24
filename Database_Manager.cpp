#include <iostream>
#include <string>
#include "sqlite3.h"
#include "Database_Manager.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char *)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}
void DatabaseManager ::setupDatabase()

{

    int exit = 0;
    exit = sqlite3_open("example.db", &DB);

    if (exit != SQLITE_OK)
    {
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
    }
    else
        cout << "Opened Database Successfully!" << endl;
}

void DatabaseManager ::createTable()
{
    std::string sql = "CREATE TABLE IF NOT EXISTS STUDENT("
                      "ROLLNO  PRIMARYKEY   INT     NOT NULL,"
                      "NAME           TEXT    NOT NULL,"
                      "FATHERNAME     TEXT    NOT NULL,"
                      "CURRENT_CLASS  INT     NOT NULL );";
    int exit = 0;
    char *messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Student Table created Successfully" << std::endl;

    sql = "CREATE TABLE IF NOT EXISTS RESULT("
          "ROLLNO         INT     NOT NULL,"
          "CLASS          INT     NOT NULL,"
          "YEAR           INT     NOT NULL,"
          "ENGLISH        TEXT    NOT NULL,"
          "MATH           TEXT    NOT NULL,"
          "HINDI          TEXT    NOT NULL,"
          "SCIENCE        TEXT    NOT NULL,"
          "SST            TEXT    NOT NULL );";

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Result Table created Successfully" << std::endl;
}

void DatabaseManager ::closeDatabase()
{
    sqlite3_close(DB);
}

void DatabaseManager ::saveStudentData(Student x)
{

    string query = "INSERT INTO STUDENT"
                   "  VALUES (?,?,?,?); ";

    sqlite3_stmt *stmt;
    const char *err;
    if (sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, &err) == SQLITE_OK)
    {

        int i = 1;
        sqlite3_bind_int(stmt, i++, x.rollno);
        sqlite3_bind_text(stmt, i++, x.name.c_str(), -1, nullptr);
        sqlite3_bind_text(stmt, i++, x.fathername.c_str(), -1, nullptr);
        sqlite3_bind_int(stmt, i++, x.current_class);

        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);

    for (int i = 0; i < x.r.size(); i++)
    {
        saveResultData(x.r[i], x.rollno);
    }
}

void DatabaseManager ::saveResultData(Result x, int rollno)
{
    string query = "INSERT INTO RESULT"
                   "  VALUES (?,?,?,?,?,?,?,?); ";

    sqlite3_stmt *stmt;
    const char *err;
    if (sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, &err) == SQLITE_OK)
    {

        int i = 1;
        sqlite3_bind_int(stmt, i++, rollno);
        sqlite3_bind_int(stmt, i++, x.class_);
        sqlite3_bind_int(stmt, i++, x.year);
        sqlite3_bind_int(stmt, i++, x.marks[0]);
        sqlite3_bind_int(stmt, i++, x.marks[1]);
        sqlite3_bind_int(stmt, i++, x.marks[2]);
        sqlite3_bind_int(stmt, i++, x.marks[3]);
        sqlite3_bind_int(stmt, i++, x.marks[4]);

        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
}

void DatabaseManager ::getStudentData()
{
    string query = "SELECT * FROM STUDENT;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "DB error: " << sqlite3_errmsg(DB) << endl;
        exit(1);
    }
    int rollno;
    char *name;
    char *fathername;
    int current_class;
    cout << "hello";
    while (sqlite3_step(stmt) == SQLITE_ROW)

    {
        rollno = sqlite3_column_int(stmt, 0);
        name = (char *)sqlite3_column_text(stmt, 1);
        fathername = (char *)sqlite3_column_text(stmt, 2);
        current_class = sqlite3_column_int(stmt, 3);
        cout << rollno << " " << name << " " << fathername << " " << current_class << endl;
    }
}
Student DatabaseManager ::getStudentData(int rollno)
{
    Student s;
    string query = "SELECT * FROM STUDENT WHERE ROLLNO = " + to_string(rollno) + ";";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "DB error: " << sqlite3_errmsg(DB) << endl;
        exit(1);
    }

    string name;
    string fathername;
    int current_class;
    while (sqlite3_step(stmt) == SQLITE_ROW)

    {
        rollno = sqlite3_column_int(stmt, 0);
        name = (char *)sqlite3_column_text(stmt, 1);
        fathername = (char *)sqlite3_column_text(stmt, 2);
        current_class = sqlite3_column_int(stmt, 3);
        // cout << rollno << " " << name << " " << fathername << " " << current_class << endl;
    }

    s.rollno = rollno;
    s.name = (string)name;
    s.fathername = (string)fathername;
    s.current_class = current_class;

    return s;
}
void DatabaseManager ::getResultData()
{
    string query = "SELECT * FROM RESULT;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "DB error: " << sqlite3_errmsg(DB) << endl;
        exit(1);
    }
    int rollno, class_, year;
    char *x[5];

    while (sqlite3_step(stmt) == SQLITE_ROW)

    {
        rollno = sqlite3_column_int(stmt, 0);
        class_ = sqlite3_column_int(stmt, 1);
        year = sqlite3_column_int(stmt, 2);
        for (int i = 0; i < 5; i++)
            x[i] = (char *)sqlite3_column_text(stmt, i + 3);

        cout << rollno << " " << class_ << " " << year << " ";
        for (int i = 0; i < 5; i++)
            cout << x[i] << " ";

        cout << endl;
    }
}
Result DatabaseManager ::getResultData(int rollno)
{
    Result rr;
    string query = "SELECT * FROM RESULT WHERE ROLLNO = " + to_string(rollno) + ";";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0) != SQLITE_OK)
    {
        cerr << "DB error: " << sqlite3_errmsg(DB) << endl;
        exit(1);
    }
    int class_, year;
    int x[5];

    while (sqlite3_step(stmt) == SQLITE_ROW)

    {
        rollno = sqlite3_column_int(stmt, 0);
        class_ = sqlite3_column_int(stmt, 1);
        year = sqlite3_column_int(stmt, 2);
        for (int i = 0; i < 5; i++)
            x[i] = sqlite3_column_int(stmt, i + 3);

        //  cout << rollno << " " << class_ << " " << year << " ";
        rr.class_ = class_;
        rr.year = year;
        for (int i = 0; i < 5; i++)
        { //cout << x[i] << " ";
            rr.marks[i] = x[i];
        }

        // cout << endl;
    }
    return rr;
}
void DatabaseManager ::deleteData(int rollno)
{
    string query = "DELETE FROM STUDENT WHERE ROLLNO = " + to_string(rollno) + ";";

    int exit = 0;
    char *messaggeError;
    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error DELETE" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Record deleted Successfully!" << std::endl;

    query = "DELETE FROM RESULT WHERE ROLLNO = " + to_string(rollno) + ";";
    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error DELETE" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Record deleted Successfully!" << std::endl;
}

void DatabaseManager ::updateData(int rollno)
{

    string name_string, query;
    int exit, name_int;
    char *messaggeError;

    while (1)
    {

        cout << "\nAVAILABLE OPERATIONS : \n1. UPDATE NAME \n2."
             << " UPDATE FATHER'S NAME\n3. UPDATE CURRENT_CLASS \n4. "
                "UPDATE CLASS \n5. UPDATE YEAR \n6. UPDATE MARKS IN ENGLISH \n7. "
                "UPDATE MARKS IN MATH \n8. UPDATE MARKS IN HINDI \n9. UPDATE MARKS IN SCIENCE \n10."
                "UPDATE MARKS IN SST \n"
             << "11. Exit " << endl;
        int check;
        cin >> check;
        switch (check)
        {
        case 1:

            cout << "ENTER NAME - " << endl;
            cin >> name_string;
            query = "UPDATE STUDENT SET NAME = '" + name_string + "' WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;

            break;
        case 2:
            cout << "ENTER FATHER'S NAME - " << endl;
            cin >> name_string;
            query = "UPDATE STUDENT SET FATHERNAME = '" + name_string + "' WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        case 3:
            cout << "ENTER CURRENT_CLASS - " << endl;
            cin >> name_int;
            query = "UPDATE STUDENT SET CURRENT_CLASS = " + to_string(name_int) + " WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        case 4:
            cout << "ENTER CLASS - " << endl;
            cin >> name_int;
            query = "UPDATE RESULT SET CLASS = " + to_string(name_int) + " WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        case 5:
            cout << "ENTER YEAR - " << endl;
            cin >> name_int;
            query = "UPDATE RESULT SET YEAR = " + to_string(name_int) + " WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        case 6:
            cout << "ENTER MARKS IN ENGLISH - " << endl;
            cin >> name_string;
            query = "UPDATE RESULT SET ENGLISH = '" + name_string + "' WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        case 7:
            cout << "ENTER MARKS IN MATH - " << endl;
            cin >> name_string;
            query = "UPDATE RESULT SET MATH = '" + name_string + "' WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        case 8:
            cout << "ENTER MARKS IN HINDI - " << endl;
            cin >> name_string;
            query = "UPDATE RESULT SET HINDI = '" + name_string + "' WHERE ROLLNO=" + to_string(rollno) + "; ";

            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        case 9:
            cout << "ENTER MARKS IN SCIENCE - " << endl;
            cin >> name_string;
            query = "UPDATE RESULT SET SCIENCE = '" + name_string + "' WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        case 10:
            cout << "ENTER MARKS IN SST - " << endl;
            cin >> name_string;
            query = "UPDATE RESULT SET SST = '" + name_string + "' WHERE ROLLNO=" + to_string(rollno) + "; ";
            exit = sqlite3_exec(DB, query.c_str(), callback, 0, &messaggeError);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error UPDATE" << std::endl;
                sqlite3_free(messaggeError);
            }
            else
                std::cout << "Record UPDATED Successfully!" << std::endl;
            break;
        default:
            break;
        }
        if (check == 11)
            break;
    }
}