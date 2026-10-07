#include "Find2.h"

Find2::Find2(vector<char> m1, vector<char> m2)
{
    mot1 = m1;
    mot2 = m2;
}

Find2::~Find2()
{
}

bool Find2::Chercher() const
{
    if (mot2.empty())
        return true;

    int j = 0;

    for (int i = 0; i < mot1.size(); i++)
    {
        if (mot1[i] == mot2[j])
        {
            j++;

            if (j == mot2.size())
                return true;
        }
    }

    return false;
}
