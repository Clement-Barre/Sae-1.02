# SAÉ — Moteur d’organisation de tournois

Concevoir le cœur algorithmique d’une plateforme capable d’inscrire des joueurs, de les faire s’affronter dans un mini-jeu et de produire un classement final selon le format de compétition choisi.

La fiabilité du programme doit être vérifiée par des tests automatisés utilisant des **fichiers oracles** et la **redirection de flux sous Linux**.

## Sommaire

- [Objectifs du projet](#objectifs-du-projet)
- [Fonctionnalités attendues](#fonctionnalités-attendues)
- [Entrées et sorties](#entrées-et-sorties)
- [Tests automatisés](#tests-automatisés)
- [Livrables](#livrables)
- [Calendrier](#calendrier)
- [Évaluation](#évaluation)
- [Pénalités et règles concernant les sources](#pénalités-et-règles-concernant-les-sources)
- [Ressources](#ressources)
- [Points à clarifier dans l’énoncé](#points-à-clarifier-dans-lénoncé)

## Objectifs du projet

Le programme doit permettre de :

1. Lire la liste des participants.
2. Organiser leurs rencontres selon le format de tournoi choisi.
3. Utiliser un mini-jeu pour déterminer le vainqueur de chaque match.
4. Afficher le classement final.
5. Vérifier les résultats à l’aide de jeux d’essais et de fichiers oracles.

## Fonctionnalités attendues

### Mini-jeu

Implémenter un jeu simple permettant de départager deux joueurs. Exemples proposés :

- Pile ou face ;
- Pierre-feuille-ciseaux ;
- Jeu de dés ;
- Pendu.

Pour rendre les tests reproductibles, **les actions ou les résultats normalement aléatoires doivent être lus depuis l’entrée standard**.

### Formats de tournoi

Implémenter les trois méthodes d’appariement suivantes :

| Format | Intitulé |
| --- | --- |
| Système suisse | Tournoi selon le système suisse |
| Round Robin | Tournoi toutes rondes |
| Double Bracket | Arbre à élimination avec un *Loser Bracket* |

Le système de tournoi doit faire appel au mini-jeu pour déterminer le résultat de chaque rencontre.

## Entrées et sorties

### Contraintes générales

- **Ne pas ouvrir ni fermer de fichiers directement dans le code.**
- Lire les données depuis l’entrée standard, généralement le clavier.
- Écrire les résultats sur la sortie standard, généralement l’écran.
- Utiliser les redirections Linux `<` et `>` pour exécuter les tests à partir de fichiers.
- Ignorer les lignes de commentaires commençant par `#`.
- Afficher uniquement le classement final, sans texte superflu ni message de débogage.

### Format des entrées

Le programme lit d’abord les participants, puis les actions nécessaires au déroulement des mini-jeux de tout le tournoi.

| Préfixe | Contenu |
| --- | --- |
| `Joueur:` | Nom d’un participant |
| `Action:` | Valeur d’une action ou d’un résultat utilisé par le mini-jeu |
| `#` | Ligne de commentaire à ignorer |

Exemple fourni dans l’énoncé :

```text
# Liste des participants
Joueur:Alice
Joueur:Bob
Joueur:Charlie
Joueur:David
# Début du tournoi : par exemple, Pile=0 et Face=1
Action:0
Action:1
Action:1
Action:1
```

### Format des sorties

Chaque ligne du classement respecte le format suivant :

```text
rang:nom_du_joueur
```

Exemple fourni dans l’énoncé :

```text
1:Charlie
2:Alice
3:Bob
4:David
```

## Tests automatisés

### Principe des fichiers oracles

Un fichier oracle contient la sortie exacte attendue pour un fichier d’entrée donné. La sortie du programme est comparée à cet oracle pour vérifier le résultat du test.

Prévoir **au moins deux jeux d’essais complets par projet**, avec pour chacun :

- Un fichier d’entrée `.in` ;
- Un fichier oracle `.out`.

Les tests doivent notamment vérifier que le programme ignore correctement les commentaires présents dans les fichiers d’entrée.

### Exécution sous Linux

Si l’exécutable s’appelle `moteur_tournoi`, lancer le premier test avec :

```bash
./moteur_tournoi < test1.in > resultat1.out
```

Comparer ensuite la sortie produite avec l’oracle :

```bash
diff resultat1.out test1_oracle.out
```

Si `diff` n’affiche aucune différence, la sortie correspond exactement à l’oracle **pour ce test**.

### Jeu d’essai 1

**Fichier d’entrée : `test1.in`**

```text
# Inscription des 4 joueurs
Joueur:J1
Joueur:J2
Joueur:J3
Joueur:J4
# Série d’actions prédéfinies pour valider la logique du format de tournoi
Action:0
Action:1
Action:2
Action:0
```

**Fichier oracle : `test1_oracle.out`**

```text
1:J3
2:J1
3:J4
4:J2
```

### Jeu d’essai 2

**Fichier d’entrée : `test2.in`**

```text
# Inscription
Joueur:A
Joueur:B
Joueur:C
Joueur:D
# Actions déclenchant des scénarios particuliers : matchs nuls, loser bracket, etc.
Action:1
Action:1
Action:0
Action:1
Action:2
```

**Fichier oracle : `test2_oracle.out`**

```text
1:A
2:C
3:B
4:D
```

> Ces exemples sont repris de l’énoncé. Les règles du mini-jeu et des appariements n’y étant pas détaillées, ils doivent être adaptés à votre implémentation pour constituer des tests vérifiables.

## Livrables

Déposer une **archive ZIP** sur [Ametice](https://ametice.univ-amu.fr/course/view.php?id=145488) contenant :

- Un rapport PDF expliquant les systèmes de classement implémentés ;
- Au moins **trois projets Qt Creator**, à raison d’un projet par système de classement ;
- Au moins **deux jeux d’essais et les deux fichiers oracles correspondants par projet**.

L’archive ne doit contenir **aucun binaire, aucun exécutable et aucun fichier objet `.o`**.

### Nom de l’archive

Respecter la nomenclature fournie :

```text
TD_AA_E_BB_YYYY_ZZZ_BBBB_CCCC.zip
```

| Élément | Signification donnée dans l’énoncé |
| --- | --- |
| `AA` | Groupe de TD |
| `BB` | Numéro d’équipe |
| `YYYY`, `BBBB`, `CCCC`, etc. | Noms des étudiants de l’équipe, triés par ordre alphabétique |

## Calendrier

| Échéance | Travail attendu |
| --- | --- |
| Avant le **6 novembre à 18 h** | Dépôt de l’archive ZIP sur Ametice |
| Semaine du **16 novembre** | Présentation d’environ **10 minutes** |

## Évaluation

Le barème annoncé est sur **30 points**.

| Critère | Points annoncés |
| --- | --- |
| Rapport | 2 points |
| Présentation et diaporama, sans code | 3 points |
| Chaque système de classement | 5 points : 4 points pour l’algorithme et 1 point par fichier oracle, selon la formulation de l’énoncé |
| Chaque système de classement corrigé par les pairs | 2 points |

### Répartition de points au sein de l’équipe

Chaque étudiant dispose de **4 points à répartir librement** au sein de son groupe de projet.

- Équipe de 4 étudiants : **16 points** à répartir ;
- Équipe de 5 étudiants : **20 points** à répartir.

L’équipe pédagogique n’intervient pas dans cette répartition, sauf si elle conduit un ou plusieurs étudiants à dépasser la note de **30/30**.

## Pénalités et règles concernant les sources

### Orthographe

Plus de **deux fautes d’orthographe par page ou par diapositive** entraîne une pénalité de **1 point**, selon l’énoncé.

### Bugs

| Bug découvert | Pénalité |
| --- | --- |
| Premier bug | −3 points |
| Deuxième bug | −2 points |
| Troisième bug | −1 point |

Le malus est plafonné à **−6 points** à partir de trois bugs.

### Copie et code provenant de tiers

- **Copie sur un autre groupe** : note de **0** et conseil de discipline.
- **Code provenant d’un tiers sans source** — développeur externe, forum, LLM, etc. : mêmes sanctions que pour la copie.
- **Code provenant d’un tiers avec source** :
  - Si vous êtes capables d’expliquer le code : **note divisée par deux** ;
  - Sinon : **note de 0** et application des règles relatives à la copie.

## Ressources

- [Plateforme de dépôt Ametice](https://ametice.univ-amu.fr/course/view.php?id=145488)
- [Principe d’un oracle de test](https://en.wikipedia.org/wiki/Test_oracle)
- [Code fourni en amphithéâtre — à télécharger](https://casali.site/wp-content/uploads/2024/10/SAE_02_vote.zip)

## Points à clarifier dans l’énoncé

- La signification de `ZZZ` dans le nom de l’archive n’est pas précisée.
- Le barème annonce **5 points par système**, dont **4 pour l’algorithme**, tout en indiquant **1 point par fichier oracle** et en demandant au moins **deux oracles par projet**. Le décompte exact reste à confirmer.
- L’année des échéances n’est pas précisée dans le texte fourni.
