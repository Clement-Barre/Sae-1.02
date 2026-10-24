#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct joueur {
    string prenom;
    unsigned score;
};

joueur jeu_temporaire (joueur j1, joueur j2)
{
    return j1;
}

vector<joueur> tri_joueur_selon_score (vector<joueur> & vecteur_joueur) // Les scores sont tries dans l'ordre decroissant
{
    for (unsigned numero_joueur; numero_joueur < vecteur_joueur.size() -1 ; ++numero_joueur)
    {
        unsigned indice_de_decalage = ;
        while (vecteur_joueur[numero_joueur].score > vecteur_joueur[numero_joueur + indice_de_decalage].score)
        {
            joueur conteneur_temporaire_de_joueur = vecteur_joueur[numero_joueur];
            vecteur_joueur[numero_joueur] = vecteur_joueur[numero_joueur + indice_de_decalage];
            vecteur_joueur[numero_joueur + indice_de_decalage] = conteneur_temporaire_de_joueur;
            ++ indice_de_decalage;
        }
    }
    return vecteur_joueur;
}

vector<joueur> tournoi_systeme_suisse (vector<joueur> & vecteur_joueur)
{
    while (vecteur_joueur[vecteur_joueur.size()-1].score = vecteur_joueur[vecteur_joueur.size()-2].score)
    {
        for (unsigned numero_joueur = vecteur_joueur.size()-1; numero > 0; numero_joueur = numero_joueur - 2)
        {
            if (numero_joueur = 1 && vecteur_joueur.size() % 2 != 0)
                ++vecteur_joueur[numero_joueur].score;
            ++jeu_temporaire(vecteur_joueur[numero_joueur], vecteur_joueur[numero_joueur-1]).score;
        }
        vecteur_joueur = tri_joueur_selon_score(vecteur_joueur);
    }
    return vecteur_joueur;
}


int main()
{

    vecteur<joueur> vecteur_joueur = {
        {"Aaron", 5},
        {"Clement", 7},
        {"Jonathan", 4},
        {"Alain", 10}
    };
    vecteur_trie = tri_joueur_selon_score(vecteur_joueur);
    for (unsigned numero_joueur = 0; numero_joueur < vecteur_joueurs.size(); ++numero_joueur)
    {
        cout << vecteur_joueur[numero_joueur] << endl;
    }
    return 0;
}