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


    // 1. Ouverture du fichier
    ifstream fichier("mots.txt");

    if (!fichier)
    {
        cout << "Erreur : impossible d'ouvrir mots.txt" << endl;
        return 1;
    }


    // 2. Lecture des mots
    vector<string> mots;
    string mot;

    while (getline(fichier, mot) && mots.size() < 10000)
    {
        if (!mot.empty())
        {
            mots.push_back(mot);
        }
    }

    fichier.close();

    cout << "Nombre de mots lus : " << mots.size() << endl;

    if (mots.size() < 10000)
    {
        cout << "Attention : le fichier contient moins de 10000 mots."
             << endl;
    }


    // 3. Mot a rechercher
    string mot2;

    cout << "\nEntrez mot2 : ";
    cin >> mot2;


    // 4. Tailles des tests
    int tailles[] = {10, 100, 1000, 10000};

        // Nombre de repetitions
        const int repetitions = 10000;


    // 5. Tableau des resultats

    cout << "\n";
    cout << "================================================================================================"
         << endl;

    cout << left
         << setw(15) << "Nb mots"
         << setw(20) << "Find1 (ms)"
         << setw(20) << "Find2 (ms)"
         << setw(20) << "Find1 moyen"
         << setw(20) << "Find2 moyen"
         << endl;

    cout << "-------------------------------------------------------------------------------------------------"
         << endl;


    // 6. Tests

    for (int n : tailles)
    {
        // Si le fichier ne contient pas assez de mots
        if (n > mots.size())
        {
            continue;
        }

        // Find1

        long long compteur1 = 0;

        auto debut1 = high_resolution_clock::now();

        for (int r = 0; r < repetitions; r++)
        {
            for (int i = 0; i < n; i++)
            {
                Find1 f1(mots[i], mot2);

                if (f1.Chercher())
                {
                    compteur1++;
                }
            }
        }

        auto fin1 = high_resolution_clock::now();

        auto temps1 =
            duration_cast<milliseconds>(fin1 - debut1);

        // Find2
        long long compteur2 = 0;

        auto debut2 = high_resolution_clock::now();

        for (int r = 0; r < repetitions; r++)
        {
            for (int i = 0; i < n; i++)
            {
                vector<char> v1(mots[i].begin(), mots[i].end());
                vector<char> v2(mot2.begin(), mot2.end());

                Find2 f2(v1, v2);

                if (f2.Chercher())
                {
                    compteur2++;
                }
            }
        }

        auto fin2 = high_resolution_clock::now();

        auto temps2 =
            duration_cast<milliseconds>(fin2 - debut2);

        // Moyenne par recherche

        long long nombreRecherches =
            (long long)n * repetitions;

        double moyenne1 =
            (double)temps1.count() / nombreRecherches;

        double moyenne2 =
            (double)temps2.count() / nombreRecherches;

        // Affichage

        cout << left
             << setw(15) << n
             << setw(20) << temps1.count()
             << setw(20) << temps2.count()
             << setw(20) << fixed << setprecision(6) << moyenne1
             << setw(20) << fixed << setprecision(6) << moyenne2
             << endl;
    }

    cout << "================================================================================================="
         << endl;

    return 0;
}
