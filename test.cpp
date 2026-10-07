#include <iostream>
#include <vector>

#include "Find1.h"
#include "Find2.h"

using namespace std;

int main()
{

    Find1 f1("compteur", "cte");

        if (f1.Chercher())
        {
            cout << "Find1 : mot2 existe dans mot1" << endl;
        }
        else
        {
            cout << "Find1 : mot2 n'existe pas dans mot1" << endl;
        }


    vector<char> mot1 = {'c', 'o', 'm', 'p', 't', 'e', 'u', 'r'};
    vector<char> mot2 = {'c', 't', 'e'};

    Find2 f2(mot1, mot2);

        if (f2.Chercher())
        {
            cout << "Find2 : mot2 existe dans mot1" << endl;
        }
        else
        {
            cout << "Find2 : mot2 n'existe pas dans mot1" << endl;
        }

    return 0;
}
