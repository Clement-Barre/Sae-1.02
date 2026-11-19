#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

struct joueur {
    string prenom;
    short score;
};

void ToLower(string& chaine) {
    for (size_t i = 0; i < chaine.size(); ++i) {
        chaine[i] = tolower(chaine[i]);
    }
}

string flux_cin_string () // Fonction que M. Casali a donne dans la SAE s102 de l'annee 2025/2026 (etudiee en TP). La syntaxe est legerement modifiee afin de montrer la comprehension de la fonction donnee.
{
    string la_string;
    while (true)
    {
        getline(cin, la_string);
        if ((!cin) || (la_string.substr(0,2) != "//")) break;
    }
    return la_string;
}

int flux_cin_entier () // Fonction que M. Casali a donne dans la SAE s102 de l'annee 2025/2026 (etudiee en TP). La syntaxe est legerement modifiee afin de montrer la comprehension de la fonction donnee.
{
    string la_string_contenant_l_entier;
    while (true)
    {
        getline (cin, la_string_contenant_l_entier);
        if ((!cin) || (la_string_contenant_l_entier.substr(0,2) != "//")) break;
    }
    return stoi(la_string_contenant_l_entier);
}

int lecture_seed() // Renvoie l'entier present apres "seed:"
{
    string seed_str;
    while (true)
    {
        getline (cin, seed_str);
        if ((!cin) || (seed_str.substr(0,2) != "//")) break;
    }
    return stoi(seed_str.substr (5,seed_str.size()));
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

joueur pierre_feuille_ciseaux (joueur & j1, joueur & j2) {
    //cout << "Joueur 1 choisissez un coup : ";
    string choixJ1 (flux_cin_string());
    //cout << "Joueur 2 choisissez un coup : ";
    string choixJ2 (flux_cin_string());
    ToLower(choixJ1);
    ToLower(choixJ2);
    //spéciaux
    if ( (choixJ1 == "volcan") && (choixJ2 == "pluie")) return j2;
    else if ( (choixJ1 == "volcan") && (choixJ2 == "escargot")) return j1;
    else if ( (choixJ1 == "pluie") && (choixJ2 == "volcan")) return j1;
    else if ( (choixJ1 == "pluie") && (choixJ2 == "escargot")) return j2;
    else if ( (choixJ1 == "escargot") && (choixJ2 == "volcan")) return j2;
    else if ( (choixJ1 == "escargot") && (choixJ2 == "pluie")) return j1;
    //normaux
    if ( (choixJ1 == "pierre") && (choixJ2 == "feuille")) return j2;
    else if ( (choixJ1 == "pierre") && (choixJ2 == "ciseaux")) return j1;
    else if ( (choixJ1 == "feuille") && (choixJ2 == "pierre")) return j1;
    else if ( (choixJ1 == "feuille") && (choixJ2 == "ciseaux")) return j2;
    else if ( (choixJ1 == "ciseaux") && (choixJ2 == "pierre")) return j2;
    else if ( (choixJ1 == "ciseaux") && (choixJ2 == "feuille")) return j1;
    //cout << "Egalité: " << j1.prenom << " gagne" << endl;
    return j1;
}

// Pile ou Face truqué
joueur pile_face_triche (joueur & j1) {
    cout << "Le gagnant de ce pile ou face est le joueur 1, c'est absolument pas truqué promis";
    return j1;
}

// Pile ou face normal
joueur pile_face (joueur & j1, joueur & j2, unsigned& seed) {
    // Ajouter la partie avec le choix pseudo aléatoire
    static mt19937 generateur(seed);
    uniform_int_distribution<int> distribution(0,1);
    unsigned choixNombreRandom = distribution(generateur);
    // cout << "La pièce à été lancé, si c'est pile alors j1 gagne, si c'est face alors j2 gagne";
    if (choixNombreRandom == 0) {
        //cout << "Pile: " << j1.prenom << " gagne" << endl;
        return j1;
    }
    else {
        //cout << "Pile: " << j2.prenom << " gagne" << endl;
        return j2;
    }
}

//Pile ou face ou tranche
joueur pile_face_tranche (joueur & j1, joueur & j2) {
    //cout << "Joueur 1 choisissez entre pile, face et tranche: ";
    string choixJ1 (flux_cin_string());
    //cout << "Joueur 2 choisissez entre pile, face et tranche : ";
    string choixJ2 (flux_cin_string());
    ToLower(choixJ1);
    ToLower(choixJ2);
    if ( (choixJ1 == "pile") && (choixJ2 == "tranche")) return j2;
    else if ( (choixJ1 == "pile") && (choixJ2 == "face")) return j1;
    else if ( (choixJ1 == "tranche") && (choixJ2 == "pile")) return j1;
    else if ( (choixJ1 == "tranche") && (choixJ2 == "face")) return j2;
    else if ( (choixJ1 == "face") && (choixJ2 == "pile")) return j2;
    else if ( (choixJ1 == "face") && (choixJ2 == "tranche")) return j1;
    //cout << "Egalite " << j1.prenom << " gagne";
    return j1;
}

joueur& jeu_temporaire(joueur& j1, joueur&)
{
    return j1;
}

joueur manche (joueur& j1, joueur& j2, unsigned& seed)
{
    short victoires_j1 = 0;
    short victoires_j2 = 0;
    joueur gagnant;
    gagnant = pile_face(j1, j2, seed);
    if (gagnant.prenom == j1.prenom && gagnant.score == j1.score)
        ++victoires_j1;
    else
        ++victoires_j2;
    //cout << "Pierre feuille ciseaux entre " << j1.prenom << " et " << j2.prenom << endl;
    gagnant = pierre_feuille_ciseaux(j1, j2);
    if (gagnant.prenom == j1.prenom && gagnant.score == j1.score)
        ++victoires_j1;
    else
        ++victoires_j2;
    if (victoires_j1 > 1 || victoires_j2 > 1)
    {
        if (victoires_j1 > victoires_j2)
            return j1;
        return j2;
    }
    //cout << "Pile face tranche entre " << j1.prenom << " et " << j2.prenom << endl;
    gagnant = pile_face_tranche(j1, j2);
    if (gagnant.prenom == j1.prenom && gagnant.score == j1.score)
        return j1;
    return j2;
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

void suppression_element_vecteur_joueur(vector<joueur>& vecteur_joueur, short indice_element)
{
    vector<joueur> vecteur_resultat;
    joueur element = vecteur_joueur[indice_element];
    bool deja_supprime = false;
    for (short indice = 0; indice < short (vecteur_joueur.size()); ++indice)
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

void incrementation_element_vecteur_joueur(vector<joueur>& vecteur_joueur, joueur& gagnant)
{
    vector<joueur> vecteur_resultat;
    joueur joueur_a_incrementer;
    bool deja_incremente = false;
    for (short indice = 0; indice < short (vecteur_joueur.size()); ++indice)
    {
        if (deja_incremente == false && vecteur_joueur[indice].prenom == gagnant.prenom && vecteur_joueur[indice].score == gagnant.score)
        {
            joueur_a_incrementer = gagnant;
            ++joueur_a_incrementer.score;
            vecteur_resultat.push_back(joueur_a_incrementer);
            deja_incremente = true;
        }
        else
            vecteur_resultat.push_back(vecteur_joueur[indice]);
    }
    vecteur_joueur = vecteur_resultat;
}

void tournoi_double_bracket(vector<joueur>& vecteur_joueur, unsigned& seed)
{
    vector<joueur> winner_bracket = vecteur_joueur;
    vector<joueur> loser_bracket;
    vector<joueur> elimine;
    joueur gagnant;
    while (winner_bracket.size() > 1)
    {
        for (short indice_joueur_winner_bracket = 0; indice_joueur_winner_bracket < short (winner_bracket.size()) - 1; ++indice_joueur_winner_bracket)
        {
            gagnant = manche(winner_bracket[indice_joueur_winner_bracket], winner_bracket[indice_joueur_winner_bracket+1], seed);
            if (gagnant.prenom == winner_bracket[indice_joueur_winner_bracket].prenom && gagnant.score == winner_bracket[indice_joueur_winner_bracket].score)
            {
                ++winner_bracket[indice_joueur_winner_bracket].score;
                loser_bracket.push_back(winner_bracket[indice_joueur_winner_bracket+1]);
                suppression_element_vecteur_joueur(winner_bracket, indice_joueur_winner_bracket+1);
            }
            else
            {
                ++winner_bracket[indice_joueur_winner_bracket+1].score;
                loser_bracket.push_back(winner_bracket[indice_joueur_winner_bracket]);
                suppression_element_vecteur_joueur(winner_bracket, indice_joueur_winner_bracket);
            }
        }
        if (winner_bracket.size()%2 == 1)
            ++winner_bracket.back().score;
        for (size_t indice_joueur_loser_bracket = 0; indice_joueur_loser_bracket < loser_bracket.size() - 1; ++indice_joueur_loser_bracket)
        {
            gagnant = manche(loser_bracket[indice_joueur_loser_bracket], loser_bracket[indice_joueur_loser_bracket+1], seed);
            if ((gagnant.prenom == loser_bracket[indice_joueur_loser_bracket].prenom && gagnant.score == loser_bracket[indice_joueur_loser_bracket].score))
            {
                ++loser_bracket[indice_joueur_loser_bracket].score;
                elimine.push_back(loser_bracket[indice_joueur_loser_bracket+1]);
                suppression_element_vecteur_joueur(loser_bracket, indice_joueur_loser_bracket+1);
            }
            else
            {
                ++loser_bracket[indice_joueur_loser_bracket+1].score;
                elimine.push_back(loser_bracket[indice_joueur_loser_bracket]);
                suppression_element_vecteur_joueur(loser_bracket, indice_joueur_loser_bracket);
            }
        }
    }
    gagnant = manche(winner_bracket[0], loser_bracket[0], seed);
    if (gagnant.prenom == loser_bracket[0].prenom && gagnant.score == loser_bracket[0].score)
    {
        gagnant = manche(winner_bracket[0], loser_bracket[0], seed);
        if (gagnant.prenom == winner_bracket[0].prenom && gagnant.score == winner_bracket[0].score)
            ++winner_bracket[0].score;
        else
            ++loser_bracket[0].score;
    }
    else
        ++winner_bracket[0].score;
    vecteur_joueur[0] = winner_bracket[0];
    vecteur_joueur[1] = loser_bracket[0];
    for (size_t indice_elimine = 0; indice_elimine < elimine.size(); ++ indice_elimine)
        vecteur_joueur[2 + indice_elimine] = elimine[indice_elimine];
    vecteur_joueur = tri_joueur_selon_score(vecteur_joueur);
}

void creationVecteurJoueur(vector<joueur>& vecteur_joueur, short& nb_joueur)
{
    vecteur_joueur.resize(nb_joueur);
    for (short indice_joueur = 0; indice_joueur < short (nb_joueur); ++ indice_joueur)
    {
        joueur joueur_temporaire;
        joueur_temporaire.prenom = flux_cin_string();
        joueur_temporaire.score = 0;
        vecteur_joueur[indice_joueur] = joueur_temporaire;
    }
}

int main()
{
    unsigned seed (lecture_seed());
    short nb_joueurs (flux_cin_entier());
    vector<joueur> vecteur_joueur;
    creationVecteurJoueur(vecteur_joueur, nb_joueurs);
    tournoi_double_bracket(vecteur_joueur, seed);
    affichageVecteurJoueur(vecteur_joueur);
    return 0;
}