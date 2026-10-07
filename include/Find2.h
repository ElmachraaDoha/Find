#ifndef FIND2_H
#define FIND2_H

#include <vector>
using namespace std;

class Find2
{
private:
    vector<char> mot1;
    vector<char> mot2;

public:
    Find2(vector<char> m1, vector<char> m2);
    virtual ~Find2();

    bool Chercher() const;
};

#endif
