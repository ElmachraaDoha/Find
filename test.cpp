#include <iostream>
#include "Find1.h"
#include "Find2.h"

using namespace std;

void tester(const string& mot1, const string& mot2)
{
    Find1 f1(mot1, mot2);
    Find2 f2(mot1, mot2);

    cout << mot1 << " / " << mot2
         << "   Find1 : " << (f1.Chercher() ? "trouve" : "pas trouve")
         << " (" << f1.Compter() << ")"
         << "   Find2 : " << (f2.Chercher() ? "trouve" : "pas trouve")
         << " (" << f2.Compter() << ")" << endl;
}

int main()
{
    tester("compteur", "com");   // trouve
    tester("compteur", "cte");   // trouve
    tester("compteur", "ctm");   // PAS trouve : le m est avant le t
    tester("abcabc", "abc");     // trouve 2 fois
    return 0;
}
