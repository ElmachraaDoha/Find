#ifndef FIND2_H
#define FIND2_H

#include <string>
#include <vector>

// Find2 : version avec vector<char> et une boucle ecrite a la main
class Find2
{
private:
    std::vector<char> mot1;
    std::vector<char> mot2;

public:
    Find2(const std::string& m1, const std::string& m2);

    bool Chercher() const;   // mot2 est-il dans mot1 ?
    int  Compter() const;    // combien de fois ?
};

#endif
