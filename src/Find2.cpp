#include "Find2.h"

Find2::Find2(const std::string& m1, const std::string& m2)
{
    mot1 = std::vector<char>(m1.begin(), m1.end());
    mot2 = std::vector<char>(m2.begin(), m2.end());
}

// On parcourt mot1 une seule fois (indice i).
// j = la lettre de mot2 qu'on attend encore.
bool Find2::Chercher() const
{
    if (mot2.empty())
        return true;

    size_t j = 0;

    for (size_t i = 0; i < mot1.size(); i++)
    {
        if (mot1[i] == mot2[j])      // on a trouve la lettre attendue
        {
            j++;                     // on attend la suivante

            if (j == mot2.size())    // toutes les lettres trouvees
                return true;
        }
    }
    return false;
}

// Meme chose, mais quand mot2 est complet on le compte
// et on recommence a zero juste apres.
int Find2::Compter() const
{
    if (mot2.empty())
        return 0;

    int nb = 0;
    size_t j = 0;

    for (size_t i = 0; i < mot1.size(); i++)
    {
        if (mot1[i] == mot2[j])
        {
            j++;

            if (j == mot2.size())
            {
                nb++;
                j = 0;
            }
        }
    }
    return nb;
}
