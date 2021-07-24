#include <iostream>
#include "Student_Manager.h"
using namespace std;

int main()
{
    StudentManager sm;

    while (1)
    {
        cout << "\nAVAILABLE OPERATIONS : \n1. INPUT STUDENT'S DATA \n2."
             << " GET STUDENT DATA BY ROLL NO. \n3. GET RESULT DATA BY ROLL NO. \n4. "
                "UPDATE DATA \n5. DELETE DATA \n"
             << "6. Exit " << endl;
        int check;
        cin >> check;
        switch (check)
        {
        case 1:
            sm.inputData();
            break;
        case 2:
            sm.showStudentDataByRollno();
            break;
        case 3:
            sm.showResultDataByRollno();
            break;
        case 4:
            sm.updateData();
            break;
        case 5:
            sm.deleteData();
            break;
        default:
            break;
        }
        if (check == 6)
            break;
    }

    return 0;
}
