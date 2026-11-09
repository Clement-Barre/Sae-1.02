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

void affichageVecteurJoueur(vector<joueur>& vecteur_joueur)
{
    for (int numero_joueur = vecteur_joueur.size()-1;
         numero_joueur >= 0;
         --numero_joueur)
    {
        cout << vecteur_joueur.size() - numero_joueur
             << "eme place: "
             << vecteur_joueur[numero_joueur].prenom
             << " avec un score de "
             << vecteur_joueur[numero_joueur].score
             << endl;
    }
}

joueur& pile_face_ancien (joueur& j1, joueur& j2) {
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

    cout << "Ce match de pile ou face oppose " << j1.prenom << " a " << j2.prenom << endl;
    cout << nomJoueurChoix << " tu as ete choisi(e), donc a toi de decider de prendre pile ou face" << endl;

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

    cout << nomJoueurChoix << " a choisi " << choixJoueur
         << " donc " << nomJoueurPasChoix << " a " << pasChoixJoueur << endl;

    if ( choixJoueur == "pile") {
        if ( rdNombre == 0) {
            if ( rdPerso == 0) {
                cout << "1 Le resultat du lancer est Pile. Donc le gagnant est " << nomJoueurChoix << endl;
                return j1;
            } else {
                cout << "2 Le resultat du lancer est Pile. Donc le gagnant est " << nomJoueurPasChoix << endl;
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

// Fonction pierre feuille ciseaux (Si quelqu'un veut la faire sentez-vous libre de le faire, sinon je (Aaron) la ferai si personne ne veut la faire
joueur pierre_feuille_ciseaux (const joueur & j1, const joueur & j2) {
    string choixJ1, choixJ2;
    cout << "Joueur 1 choisissez un coup : ";
    cin >> choixJ1;
    cout << "Joueur 2 choisissez un coup : ";
    cin >> choixJ2;
    if ( (choixJ1 == "Pierre") && (choixJ2 == "Feuille")) return j2;
    else if ( (choixJ1 == "Pierre") && (choixJ2 == "Ciseau")) return j1;
    else if ( (choixJ1 == "Feuille") && (choixJ2 == "Pierre")) return j1;
    else if ( (choixJ1 == "Feuille") && (choixJ2 == "Ciseaux")) return j2;
    else if ( (choixJ1 == "Ciseaux") && (choixJ2 == "Pierre")) return j2;
    else if ( (choixJ1 == "Ciseaux") && (choixJ2 == "Feuille")) return j1;
    else if (choixJ1 == choixJ2) {
        cout << "Egalité, donc on fait gagner le joueur 1 parceque c'est comme ca.";
        return j1;
    }
}

// Pile ou Face truqué
joueur pile_face_triche (const joueur & j1, const joueur & j2) {
    cout << "Le gagnant de ce pile ou face est le joueur 1, c'est absolument pas truqué promis";
    return j1;
}

// Pile ou face normal
joueur pile_face (const joueur & j1, const joueur & j2) {
    // Ajouter la partie avec le choix pseudo aléatoire
    unsigned seed = 1234567890; //Mettre la seed
    static mt19937 generateur(seed);
    uniform_int_distribution<int> distribution(0,1);
    unsigned choixNombreRandom = 0;
    cout << "La pièce à été lancé, si c'est pile alors j1 gagne, si c'est face alors j2 gagne";
    if (choixNombreRandom == 0) {
        cout << "Pile, j1 gagne !" << endl;
        return j1;
    }
    else {
        cout << "Face, j2 gagne !" << endl;
        return j2;
    }
}


joueur& jeu_temporaire(joueur& j1, joueur&)
{
    return j1;
}

vector<joueur> tri_joueur_selon_score(vector<joueur>& vecteur_joueur) // Tri des scores dans l'ordre croissant.
{
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

void suppression_element_vecteur_joueur(vector<joueur>& vecteur_joueur, size_t indice_element)
{
    vector<joueur> vecteur_resultat;
    joueur element = vecteur_joueur[indice_element];
    bool deja_supprime = false;
    for (size_t indice = 0; indice < vecteur_joueur.size(); ++indice)
    {
        if (deja_supprime == false && vecteur_joueur[indice].prenom == element.prenom && vecteur_joueur[indice].score == element.score)
        {
            deja_supprime = true;
        }
        else
        {
            vecteur_resultat.push_back(vecteur_joueur[indice]);
        }
    }
    vecteur_joueur = vecteur_resultat;
}

void tournoi_round_robin(vector<joueur>& vecteur_joueur, string& jeu_choisi)
{
    size_t nb_joueur = vecteur_joueur.size();
    size_t ecart_entre_joueur = 1;
    if (jeu_choisi == "pile ou face")
    {
        while (ecart_entre_joueur < vecteur_joueur.size())
        {
            for (size_t indice_joueur = 0; indice_joueur + ecart_entre_joueur< nb_joueur ; ++indice_joueur)
            {
                ++pile_face(vecteur_joueur[indice_joueur], vecteur_joueur[indice_joueur + ecart_entre_joueur]).score;
            }
            ++ecart_entre_joueur;
        }
    }
    tri_joueur_selon_score(vecteur_joueur);
}

void creationVecteurJoueur(vector<joueur>& vecteur_joueur, size_t& nb_joueur)
{
    vecteur_joueur.resize(nb_joueur);
    string nom_joueur;
    for (size_t indice_joueur = 0; indice_joueur < nb_joueur; ++ indice_joueur)
    {
        cout << "Quel est le nom du joueur numero " << indice_joueur+1 << " ?" << endl;
        cin >> nom_joueur;
        joueur joueur_temporaire;
        joueur_temporaire.prenom = nom_joueur;
        joueur_temporaire.score = 0;
        vecteur_joueur[indice_joueur] = joueur_temporaire;
    }
}

void tournoi()
{
    vector<joueur> vecteur_joueur;
    size_t nb_joueur;
    cout << endl << "Combien de joueurs il y aura-t-il?" << endl;
    cin >> nb_joueur;
    creationVecteurJoueur(vecteur_joueur, nb_joueur);

    if (nb_joueur < 2)
    {
        cout << "Il n'y a pas assez de joueurs pour faire un tournoi" << endl;
    }

    else
    {
        cout << endl << "Systemes de tournoi:" << endl << ">> Suisse" << endl << ">> Round Robin" << endl << ">> Double Bracket" << endl << endl << "Quel systeme voulez-vous utiliser?" << endl << endl;
        string systeme_choisi = "";
        getline (cin, systeme_choisi);
        ToLower(systeme_choisi);

        while (systeme_choisi != "suisse" && systeme_choisi != "round robin" && systeme_choisi != "double bracket")
        {
            cout << "Ceci n'est pas un systeme present dans notre systeme" << endl << "Choisissez un systeme present dans la liste de systeme affichee plus haut" << endl << endl;
            getline (cin, systeme_choisi);
        }

        cout << "Jeux:" << endl << ">> Pile ou Face" << endl << ">> Deuxieme jeu" << endl << ">> Troisieme jeu" << endl << endl << "A quel jeu voulez-vous jouer?" << endl << endl;
        string jeu_choisi = "";
        getline (cin, jeu_choisi);
        ToLower(jeu_choisi);

        while (jeu_choisi != "pile ou face") // Ajouter les autres jeux plus tard avec des &&
        {
            cout << "Ceci n'est pas un jeu present dans notre catalogue" << endl << "Choisissez un jeu present dans la liste de jeux affichee plus haut" << endl << endl;
            getline (cin, jeu_choisi);
        }

        if (systeme_choisi == "suisse")
        {
            tournoi_systeme_suisse(vecteur_joueur, jeu_choisi);
        }
        if (systeme_choisi == "round robin")
        {
            tournoi_round_robin(vecteur_joueur, jeu_choisi);
        }
        if (systeme_choisi == "double bracket")
        {
            tournoi_double_bracket(vecteur_joueur, jeu_choisi);
        }

        cout << endl << "Podium:" << endl
             << "1ere place: " << vecteur_joueur[vecteur_joueur.size()-1].prenom << " avec un score de " << vecteur_joueur[vecteur_joueur.size()-1].score << endl
             << "2eme place: " << vecteur_joueur[vecteur_joueur.size()-2].prenom << " avec un score de " << vecteur_joueur[vecteur_joueur.size()-2].score << endl
             << "3eme place: " << vecteur_joueur[vecteur_joueur.size()-3].prenom << " avec un score de " << vecteur_joueur[vecteur_joueur.size()-3].score << endl;

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