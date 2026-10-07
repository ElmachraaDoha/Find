#ifndef FIND1_H
#define FIND1_H

#include <string>

// Find1 : version avec std::string et la fonction find
class Find1
{
private:
    std::string mot1;
    std::string mot2;

public:
    Find1(const std::string& m1, const std::string& m2);

    bool Chercher() const;   // mot2 est-il dans mot1 ?
    int  Compter() const;    // combien de fois ?
};

#endif
