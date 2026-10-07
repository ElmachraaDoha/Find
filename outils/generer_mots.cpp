// Generateur de fichier de mots pour le projet Find.
//
// Usage : generer_mots <sortie> <nbMots> [fichierBase]
//   - fichierBase (optionnel) : ses mots sont recopies en premier, puis on
//     complete avec des mots generes jusqu'a nbMots mots DISTINCTS.
//   - Generateur deterministe (graine fixe) : meme fichier a chaque execution.
//
// Exemple : generer_mots mots.txt 1000000 mots_10000.txt

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

static mt19937 gen(20261005);

// uniform_int_distribution n'est pas portable : on utilise un simple modulo.
static size_t alea(size_t n) { return (size_t)(gen() % n); }

static const char* VOCAB[] = {
    "texte", "tableau", "entete", "classe", "recherche", "objet", "chaine",
    "graphe", "correct", "compilateur", "index", "vecteur", "table", "mots",
    "comptage", "electeur", "memoire", "tri", "compte", "test", "text", "code",
    "valeur", "programmation", "programme", "compteur", "pointeur", "count",
    "fichier", "algorithme", "boucle", "entier", "pile", "reel", "counter",
    "file", "teste", "cete", "etc", "cet", "ete", "tec", "cte", "ligne",
    "fonction", "variable", "tableau", "liste", "arbre", "noeud", "heritage"
};
static const size_t NB_VOCAB = sizeof(VOCAB) / sizeof(VOCAB[0]);

static string lettresAlea(size_t n, const string& alphabet)
{
    string s;
    for (size_t i = 0; i < n; i++)
        s += alphabet[alea(alphabet.size())];
    return s;
}

static string motAlea()
{
    const string alpha = "abcdefghijklmnopqrstuvwxyz";
    size_t t = alea(100);

    if (t < 10)                                   // mot + 4 chiffres : "table1892"
        return string(VOCAB[alea(NB_VOCAB)]) + to_string(1000 + alea(9000));

    if (t < 35)                                   // 1 a 3 mots colles, parfois du bruit
    {
        string s = alea(3) == 0 ? lettresAlea(1 + alea(3), alpha) : "";
        size_t k = 1 + alea(3);
        for (size_t i = 0; i < k; i++)
            s += VOCAB[alea(NB_VOCAB)];
        if (alea(3) == 0)
            s += lettresAlea(1 + alea(3), alpha);
        return s;
    }

    if (t < 60)                                   // lettres c, t, e : "ctetcte"
        return lettresAlea(4 + alea(11), "ctee");

    string s = lettresAlea(3 + alea(18), alpha);  // lettres au hasard
    if (alea(4) == 0)                             // avec un mot du vocabulaire glisse dedans
        s.insert(alea(s.size() + 1), VOCAB[alea(NB_VOCAB)]);
    return s;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Usage : " << argv[0] << " <sortie> <nbMots> [fichierBase]" << endl;
        return 1;
    }

    size_t nb = (size_t)strtoull(argv[2], NULL, 10);
    ofstream out(argv[1]);
    if (!out || nb == 0)
    {
        cout << "Erreur : sortie invalide" << endl;
        return 1;
    }

    unordered_set<string> deja;
    deja.reserve(nb * 2);
    size_t ecrits = 0;

    if (argc > 3)
    {
        ifstream base(argv[3]);
        if (!base)
        {
            cout << "Erreur : impossible d'ouvrir " << argv[3] << endl;
            return 1;
        }
        string ligne;
        while (ecrits < nb && getline(base, ligne))
        {
            if (!ligne.empty() && ligne[ligne.size() - 1] == '\r')
                ligne.erase(ligne.size() - 1);
            if (!ligne.empty() && deja.insert(ligne).second)
            {
                out << ligne << '\n';
                ecrits++;
            }
        }
    }

    while (ecrits < nb)
    {
        string m = motAlea();
        if (deja.insert(m).second)
        {
            out << m << '\n';
            ecrits++;
        }
    }

    cout << ecrits << " mots ecrits dans " << argv[1] << endl;
    return 0;
}
