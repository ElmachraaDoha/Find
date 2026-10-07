#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

#include "Find1.h"
#include "Find2.h"

using namespace std;
using namespace std::chrono;

int main()
{
    // 1. Lire les mots (jusqu'a 1 000 000)
    ifstream fichier("mots.txt");
    if (!fichier)
    {
        cout << "Erreur : impossible d'ouvrir mots.txt" << endl;
        return 1;
    }

    vector<string> mots;
    string mot;

    while (mots.size() < 1000000 && getline(fichier, mot))
    {
        if (!mot.empty() && mot[mot.size() - 1] == '\r')   // fichier Windows
            mot.erase(mot.size() - 1);

        if (!mot.empty())
            mots.push_back(mot);
    }
    fichier.close();

    cout << "Nombre de mots lus : " << mots.size() << endl;

    // 2. Demander mot2
    string mot2;
    cout << "Entrez mot2 : ";
    cin >> mot2;

    // 3. Creer les objets UNE SEULE FOIS (avant le chrono),
    //    pour ne mesurer que la recherche.
    vector<Find1> tab1;
    vector<Find2> tab2;

    for (size_t i = 0; i < mots.size(); i++)
    {
        tab1.push_back(Find1(mots[i], mot2));
        tab2.push_back(Find2(mots[i], mot2));
    }

    // 4. Tests sur 10, 100, ... mots
    size_t tailles[] = {10, 100, 1000, 10000, 100000, 1000000};

    // Nombre total de recherches par test (repetitions = TOTAL / n).
    // Comme ca chaque test dure a peu pres le meme temps.
    const long long TOTAL = 10000000;

    cout << "\n" << left
         << setw(10) << "Nb mots"
         << setw(10) << "Trouves"
         << setw(13) << "Occurrences"
         << setw(14) << "Find1 (ms)"
         << setw(14) << "Find2 (ms)"
         << setw(16) << "Find1 ns/rech"
         << "Find2 ns/rech" << endl;
    cout << string(90, '-') << endl;

    for (size_t n : tailles)
    {
        if (n > mots.size())
            continue;

        // --- a) Combien de mots trouves ? Combien d'occurrences ? (une fois)
        int trouves1 = 0, trouves2 = 0;
        long long occ1 = 0, occ2 = 0;

        for (size_t i = 0; i < n; i++)
        {
            if (tab1[i].Chercher()) trouves1++;
            if (tab2[i].Chercher()) trouves2++;
            occ1 += tab1[i].Compter();
            occ2 += tab2[i].Compter();
        }

        // --- b) Chrono Find1
        long long repetitions = TOTAL / n;
        long long compteur1 = 0;

        auto debut1 = steady_clock::now();
        for (long long r = 0; r < repetitions; r++)
            for (size_t i = 0; i < n; i++)
                if (tab1[i].Chercher())
                    compteur1++;
        auto fin1 = steady_clock::now();

        // --- c) Chrono Find2
        long long compteur2 = 0;

        auto debut2 = steady_clock::now();
        for (long long r = 0; r < repetitions; r++)
            for (size_t i = 0; i < n; i++)
                if (tab2[i].Chercher())
                    compteur2++;
        auto fin2 = steady_clock::now();

        // --- d) Temps total (ms) et temps moyen par recherche (ns)
        long long ns1 = duration_cast<nanoseconds>(fin1 - debut1).count();
        long long ns2 = duration_cast<nanoseconds>(fin2 - debut2).count();
        long long nbRecherches = repetitions * (long long)n;

        cout << left
             << setw(10) << n
             << setw(10) << trouves1
             << setw(13) << occ1
             << setw(14) << ns1 / 1000000
             << setw(14) << ns2 / 1000000
             << setw(16) << fixed << setprecision(2) << (double)ns1 / nbRecherches
             << (double)ns2 / nbRecherches << endl;

        // Les deux classes doivent donner la meme chose
        if (trouves1 != trouves2 || occ1 != occ2 || compteur1 != compteur2)
            cout << "  ATTENTION : Find1 et Find2 ne donnent pas les memes resultats !" << endl;
    }

    return 0;
}
