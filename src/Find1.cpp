#include "Find1.h"

Find1::Find1(const std::string& m1, const std::string& m2)
{
    mot1 = m1;
    mot2 = m2;
}

// Pour chaque lettre de mot2, on demande a find()
// ou elle est dans mot1, APRES la lettre precedente.
bool Find1::Chercher() const
{
    size_t pos = 0;                          // ou on recommence a chercher

    for (size_t j = 0; j < mot2.size(); j++)
    {
        size_t p = mot1.find(mot2[j], pos);  // cherche la lettre a partir de pos

        if (p == std::string::npos)          // lettre introuvable
            return false;

        pos = p + 1;                         // la lettre suivante est cherchee apres
    }
    return true;
}

// Meme chose, mais quand mot2 est complet on le compte
// et on recommence a zero juste apres.
int Find1::Compter() const
{
    if (mot2.empty())
        return 0;

    int nb = 0;
    size_t pos = 0;
    size_t j = 0;

    while (true)
    {
        size_t p = mot1.find(mot2[j], pos);

        if (p == std::string::npos)
            break;

        pos = p + 1;
        j++;

        if (j == mot2.size())   // mot2 complet : une occurrence de plus
        {
            nb++;
            j = 0;
        }
    }
    return nb;
}
