#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct joueur {
    string prenom;
    unsigned score;
};

joueur& jeu_temporaire(joueur& j1, joueur&)
{
    return j1;
}

vector<joueur> tri_joueur_selon_score(vector<joueur>& vecteur_joueur)
{
    // Tri des scores dans l'ordre décroissant.
    for (size_t numero_joueur = 1;
         numero_joueur < vecteur_joueur.size();
         ++numero_joueur)
    {
        size_t position = numero_joueur;

        while (position > 0 &&
               vecteur_joueur[position].score >
               vecteur_joueur[position - 1].score)
        {
            joueur temporaire = vecteur_joueur[position];
            vecteur_joueur[position] = vecteur_joueur[position - 1];
            vecteur_joueur[position - 1] = temporaire;

            --position;
        }
    }

    return vecteur_joueur;
}

vector<joueur> tournoi_systeme_suisse(vector<joueur>& vecteur_joueur)
{
    if (vecteur_joueur.size() < 2)
    {
        return vecteur_joueur;
    }

    tri_joueur_selon_score(vecteur_joueur);

    while (vecteur_joueur.back().score ==
           vecteur_joueur[vecteur_joueur.size() - 2].score)
    {
        size_t joueurs_restants = vecteur_joueur.size();

        while (joueurs_restants >= 2)
        {
            ++jeu_temporaire(
                vecteur_joueur[joueurs_restants - 1],
                vecteur_joueur[joueurs_restants - 2]
            ).score;

            joueurs_restants -= 2;
        }

        if (joueurs_restants == 1)
        {
            ++vecteur_joueur[0].score;
        }

        tri_joueur_selon_score(vecteur_joueur);
    }

    return vecteur_joueur;
}

int main()
{
    vector<joueur> vecteur_joueur = {
        {"Aaron", 5},
        {"Clement", 7},
        {"Jonathan", 4},
        {"Alain", 10}
    };

    tri_joueur_selon_score(vecteur_joueur);

    for (size_t numero_joueur = 0;
         numero_joueur < vecteur_joueur.size();
         ++numero_joueur)
    {
        cout << vecteur_joueur[numero_joueur].prenom
             << " : "
             << vecteur_joueur[numero_joueur].score
             << endl;
    }

    return 0;
}