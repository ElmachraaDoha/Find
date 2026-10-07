#ifndef FIND1_H
#define FIND1_H

#include <string>
using namespace std;

class Find1
{
private:
    string mot1;
    string mot2;

public:
    Find1(string m1, string m2);
    virtual ~Find1();

    bool Chercher() const;
};

#endif
