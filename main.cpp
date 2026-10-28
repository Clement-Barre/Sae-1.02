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
    for (size_t i = 0; i < chaine.size(); ++i) {
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
    // Tri des scores dans l'ordre croissant.
    for (size_t numero_joueur = 0;
         numero_joueur < vecteur_joueur.size();
         ++numero_joueur)
    {
        size_t position = numero_joueur;

        while (position < vecteur_joueur.size()-1 &&
               vecteur_joueur[position].score >
               vecteur_joueur[position + 1].score)
        {
            joueur temporaire = vecteur_joueur[position];
            vecteur_joueur[position] = vecteur_joueur[position + 1];
            vecteur_joueur[position + 1] = temporaire;

            --position;
        }
    }

    return vecteur_joueur;
}

vector<joueur> tournoi_systeme_suisse(vector<joueur>& vecteur_joueur, string& jeu_choisi)
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
        if (jeu_choisi == "pile ou face")
        {
            while (joueurs_restants >= 2)
            {
                ++pile_face(
                    vecteur_joueur[joueurs_restants - 1],
                    vecteur_joueur[joueurs_restants - 2]
                ).score;

                joueurs_restants -= 2;
            }
        }

        if (joueurs_restants == 1)
        {
            ++vecteur_joueur[0].score;
        }

        tri_joueur_selon_score(vecteur_joueur);
    }

    return vecteur_joueur;
}

void affichageVecteurJoueur(vector<joueur>& vecteur_joueur)
{
    for (int numero_joueur = vecteur_joueur.size()-1;
         numero_joueur >= 0;
         --numero_joueur)
    {
        cout << vecteur_joueur[numero_joueur].prenom
             << " : "
             << vecteur_joueur[numero_joueur].score
             << endl;
    }
}

vector<joueur> creationVecteurJoueur(vector<joueur>& vecteur_joueur, size_t& nb_joueur)
{
    vecteur_joueur.resize(nb_joueur);
    string nom_joueur;
    for (size_t indice_joueur = 0; indice_joueur < nb_joueur; ++ indice_joueur)
    {
        cout << "Quel est le nom du joueur numéro " << indice_joueur+1 << " ?" << endl;
        cin >> nom_joueur;
        joueur joueur_temporaire;
        joueur_temporaire.prenom = nom_joueur;
        joueur_temporaire.score = 0;
        vecteur_joueur[indice_joueur] = joueur_temporaire;
    }
    return vecteur_joueur;
}

void tournoi()
{
    cout << "Jeux:" << endl << ">> Pile ou Face" << endl << ">> Deuxième jeu" << endl << ">> Troisième jeu" << endl << endl << "A quel jeu voulez-vous jouer?" << endl << endl;
    string jeu_choisi = "";
    getline (cin, jeu_choisi);
    ToLower(jeu_choisi);
    while (jeu_choisi != "pile ou face") // Ajouter les autres jeux plus tard avec des &&
    {
        cout << "Ceci n'est pas un jeu présent dans notre catalogue" << endl << "Choisissez un jeu présent dans la liste de jeux affichée plus haut" << endl << endl;
        getline (cin, jeu_choisi);
    }


    vector<joueur> vecteur_joueur;
    size_t nb_joueur;
    cout << "Combien de joueurs il y aura-t-il?" << endl;
    cin >> nb_joueur;
    vecteur_joueur = creationVecteurJoueur(vecteur_joueur, nb_joueur);
    // affichageVecteurJoueur(vecteur_joueur);

    cout << "Systèmes de tournoi:" << endl << ">> Suisse" << endl << ">> Round Robin" << endl << ">> Double Bracket" << endl << endl << "Quel système voulez-vous utiliser?" << endl << endl;
    string systeme_choisi = "";
    getline (cin, systeme_choisi);
    ToLower(systeme_choisi);
    while (systeme_choisi != "suisse" && systeme_choisi != "round robin" && systeme_choisi != "double bracket") // Ajouter les autres jeux plus tard avec des ||
    {
        cout << "Ceci n'est pas un système présent dans notre système" << endl << "Choisissez un système présent dans la liste de système affichée plus haut" << endl << endl;
        getline (cin, systeme_choisi);
    }
    if (systeme_choisi == "suisse")
    {
        vecteur_joueur = tournoi_systeme_suisse(vecteur_joueur, jeu_choisi);
    }
    cout << endl << "Podium:" << endl
         << "1ère place: " << vecteur_joueur[vecteur_joueur.size()-1].prenom << " avec un score de " << vecteur_joueur[vecteur_joueur.size()-1].score << endl
         << "2ème place: " << vecteur_joueur[vecteur_joueur.size()-2].prenom << " avec un score de " << vecteur_joueur[vecteur_joueur.size()-2].score << endl
         << "3ème place: " << vecteur_joueur[vecteur_joueur.size()-3].prenom << " avec un score de " << vecteur_joueur[vecteur_joueur.size()-3].score << endl;

    if (nb_joueur > 3)
    {
        cout << "Voulez-vous voir le classement complet?" << endl << ">> Oui" << endl << ">> Non" << endl;
        string reponse;
        cin >> reponse;
        ToLower(reponse);
        if (reponse == "oui")
        {
            affichageVecteurJoueur(vecteur_joueur);
        }
    }
}

int main()
{
    // vector<joueur> vecteur_joueur = {
    //     {"Aaron", 1},
    //     {"Clement", 1},
    //     {"Jonathan", 1},
    // };


    //tri_joueur_selon_score(vecteur_joueur);

    // string test = "TEST";
    // ToLower(test);
    // cout << test << endl;

    // cout << vecteur_joueur[1].score << " " << vecteur_joueur[2].score << endl;
    // pile_face(vecteur_joueur[1], vecteur_joueur[2]).score += 1;
    // cout << vecteur_joueur[1].score << " " << vecteur_joueur[2].score << endl;

    // tournoi_systeme_suisse(vecteur_joueur);

    // affichageVecteurJoueur(vecteur_joueur);

    tournoi();

    return 0;
}