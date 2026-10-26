#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;


struct joueur {
    string prenom;
    unsigned score;
};


void ToLower(string& chaine) {
    for (size_t i = 0; i < chaine.size(); i++) {
        chaine[i] = tolower(chaine[i]);
    }
}

joueur& pile_face(joueur& j1, joueur& j2) {
    static mt19937 generateur(random_device{}());
    uniform_int_distribution<int> distribution(0,1);

    string choixJoueur = "";
    string pasChoixJoueur = "";
    string nomJoueurChoix = "";
    string nomJoueurPasChoix = "";
    int rdNombre = distribution(generateur);
    int rdPerso = distribution(generateur);

    if ( rdPerso == 0) {
        nomJoueurChoix = j1.prenom;
        nomJoueurPasChoix = j2.prenom;
    } else {
        nomJoueurChoix = j2.prenom;
        nomJoueurPasChoix = j1.prenom;
    }

    while ( not (choixJoueur == "pile" || choixJoueur == "face") ) {
        cout << "Pile ou Face " << nomJoueurChoix << " : ";
        cin >> choixJoueur ;
        ToLower(choixJoueur);
    }

    if ( choixJoueur == "pile" ) {
        pasChoixJoueur = "face";
    } else {
        pasChoixJoueur = "pile";
    }

    cout << nomJoueurChoix << " a choisie " << choixJoueur 
    << " donc " << nomJoueurPasChoix << " a " << pasChoixJoueur << endl;
    
    if ( choixJoueur == "pile") {
        if ( rdNombre == 0) {
            if ( rdPerso == 0) {
                cout << "1 Le resultat du lancer est Pile. Donc le gagnant est " << nomJoueurPasChoix << endl;
                return j1;
            } else {
                cout << "2 Le resultat du lancer est Pile. Donc le gagnant est " << nomJoueurChoix << endl;
                return j2;
            }
        } else {
            if ( rdPerso == 0) {
                cout << "3 Le resultat du lancer est Face. Donc le gagnant est " << nomJoueurChoix << endl;
                return j2;
            } else {
                cout << "4 Le resultat du lancer est Face. Donc le gagnant est " << nomJoueurPasChoix << endl;
                return j1;
            }
        }
    } else {
        if ( rdNombre == 0) {
            if (rdPerso == 0) {
                cout << "5 Le resultat du lancer est Pile. Donc le gagnant est " << nomJoueurChoix << endl;
                return j2;
            } else {
                cout << "6 Le resultat du lancer est Pile. Donc le gagnant est " << nomJoueurPasChoix << endl;
                return j1;
            }
        } else {
            if (rdPerso == 0) {
                cout << "7 Le resultat du lancer est Face. Donc le gagnant est " << nomJoueurPasChoix << endl;
                return j1;
            } else {
                cout << "8 Le resultat du lancer est Face. Donc le gagnant est " << nomJoueurChoix << endl;
                return j2;
            }
        }
    }
}

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
        {"Aaron", 1},
        {"Clement", 1},
        {"Jonathan", 1},
        {"Alain", 1}
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

    string test = "TEST";
    ToLower(test);
    cout << test << endl;
    cout << vecteur_joueur[1].score << " " << vecteur_joueur[2].score << endl;
    pile_face(vecteur_joueur[1], vecteur_joueur[2]).score += 1;
    cout << vecteur_joueur[1].score << " " << vecteur_joueur[2].score << endl;

    return 0;
}