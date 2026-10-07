#include "Find1.h"

Find1::Find1(string m1, string m2)
{
    mot1 = m1;
    mot2 = m2;
}

Find1::~Find1()
{
}

bool Find1::Chercher() const
{
    return mot1.find(mot2) != string::npos;
}
