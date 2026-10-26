# Contribuer au projet avec VS Code

Ce guide explique comment installer les outils, récupérer le projet, modifier le code, le compiler et partager son travail sur GitHub.

Il est prévu pour **Windows 10 ou 11 sur un ordinateur Intel/AMD 64 bits**. Les noms des boutons peuvent apparaître en français ou en anglais selon VS Code.

Le projet utilise du **C++17**. Qt et Qt Creator ne sont pas nécessaires pour le code actuel : le fichier `sae102.pro` contient `CONFIG -= qt`.

## 1. Comprendre les fichiers et les actions

| Élément | Utilité |
| --- | --- |
| `main.cpp` | Le code du programme à modifier. |
| `sae102.pro` | La configuration pour ouvrir et compiler le projet avec qmake/Qt Creator. On la conserve. |
| `main.exe` | Le programme généré sur Windows. Il est recréé lors de la compilation. |
| `.vscode/` | Les réglages locaux de compilation et de débogage de VS Code. |
| `.gitignore` | Les règles qui indiquent à Git quels fichiers ignorer. |

Les actions à distinguer :

- **Enregistrer** : écrire les modifications sur son ordinateur.
- **Compiler** : transformer le code en programme exécutable.
- **Commit** : enregistrer une étape du travail dans l'historique Git local.
- **Push** : envoyer les commits sur GitHub.
- **Pull** : récupérer et intégrer les commits d'une branche distante.
- **Pull request** : proposer de réunir les changements d'une branche avec ceux d'une autre branche.

La compilation ne remplace pas le `.pro`. Le fichier qu'elle produit ici est `main.exe`.

## 2. Avoir accès au dépôt

Chaque personne utilise son propre compte GitHub.

Le propriétaire d'un dépôt personnel peut ajouter les membres depuis **Settings → Collaborators → Add people**. Chaque membre doit accepter l'invitation avant de pouvoir envoyer ses modifications directement dans ce dépôt.

Ce guide suppose que les membres ont cet accès et travaillent avec des branches dans le même dépôt. Sans accès en écriture, demander l'invitation au propriétaire.

[Documentation GitHub : inviter des collaborateurs](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/repository-access-and-collaboration/inviting-collaborators-to-a-personal-repository).

## 3. Installer les outils — une seule fois

### VS Code et l'extension C/C++

1. Installer [Visual Studio Code](https://code.visualstudio.com/).
2. Ouvrir les extensions avec **Ctrl + Maj + X**.
3. Installer **C/C++**, publiée par **Microsoft** (`ms-vscode.cpptools`).

L'extension aide à écrire le code et à le déboguer. Elle ne contient pas de compilateur. Les fonctions Git de base sont déjà intégrées à VS Code.

[Documentation : le support C/C++ dans VS Code](https://code.visualstudio.com/docs/languages/cpp).

### Git

1. Installer [Git pour Windows](https://git-scm.com/downloads/win).
2. Pendant l'installation, conserver l'option qui rend Git disponible pour les autres logiciels et la ligne de commande.
3. Fermer toutes les fenêtres de VS Code, puis le rouvrir.
4. Ouvrir **Terminal → Nouveau terminal**, puis vérifier :

```powershell
git --version
```

Configurer ensuite l'auteur des futurs commits, en remplaçant les exemples par ses propres informations :

```powershell
git config --global user.name "Votre prénom ou pseudo"
git config --global user.email "votre-adresse@example.com"
```

Utiliser une adresse associée à son compte GitHub, ou l'adresse `noreply` fournie dans ses paramètres GitHub si l'on souhaite masquer son adresse personnelle. Ne pas conserver l'adresse d'exemple.

Ces informations identifient les commits ; elles ne remplacent pas la connexion à GitHub.

[Documentation Git : configuration initiale](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup).

### Le compilateur et le débogueur

1. Télécharger l'installateur **x86_64** sur [MSYS2](https://www.msys2.org/), qui fournit aussi les [instructions officielles d'installation](https://www.msys2.org/).
2. Installer MSYS2 dans le dossier proposé, normalement `C:\msys64`.
3. Ouvrir **MSYS2 UCRT64** depuis le menu Démarrer.
4. Installer les outils avec :

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

Accepter la sélection des paquets avec **Entrée**, puis confirmer avec **Y**. Cette commande se lance dans MSYS2, pas dans PowerShell.

5. Dans la recherche Windows, ouvrir **Modifier les variables d'environnement pour votre compte**.
6. Dans les variables utilisateur, sélectionner **Path → Modifier → Nouveau**.
7. Ajouter l'entrée suivante sans supprimer les autres :

```text
C:\msys64\ucrt64\bin
```

Si MSYS2 a été installé ailleurs, adapter ce chemin.

8. Fermer toutes les fenêtres de VS Code, puis le rouvrir.
9. Dans un nouveau terminal VS Code, vérifier :

```powershell
g++ --version
gdb --version
```

Les deux commandes doivent afficher une version.

[Guide officiel : installer GCC et GDB pour VS Code sous Windows](https://code.visualstudio.com/docs/cpp/config-mingw).

## 4. Récupérer le projet sur son ordinateur

1. Ouvrir le dépôt dans GitHub.
2. Cliquer sur **Code → HTTPS** et copier son URL.
3. Dans VS Code, ouvrir la palette avec **Ctrl + Maj + P**.
4. Rechercher **Git: Clone** et coller l'URL.
5. Choisir le dossier parent où enregistrer le projet.
6. Cliquer sur **Ouvrir** une fois le clonage terminé.

Si une connexion est demandée, utiliser son compte GitHub dans le navigateur. Ouvrir le dossier qui contient directement `main.cpp` et `sae102.pro`.

Le clonage est à faire une seule fois par ordinateur. Pour récupérer les changements suivants, utiliser un pull. Éviter le téléchargement ZIP pour ce fonctionnement avec Git.

[Documentation : cloner dans VS Code](https://code.visualstudio.com/docs/sourcecontrol/github).

## 5. Vérifier le `.gitignore`

Le dépôt utilise des configurations VS Code locales. Son `.gitignore`, à la racine, doit contenir au minimum :

```gitignore
*.exe
/.vscode/
```

Ainsi, les exécutables et les réglages VS Code restent sur chaque ordinateur. **Chaque membre devra créer sa configuration à l'étape suivante**, car `.vscode` n'est pas partagé.

Conserver les autres règles déjà présentes. Le fichier `.gitignore` lui-même doit être partagé par commit et push.

Un fichier ignoré peut apparaître grisé : c'est normal. Il reste utilisable sur l'ordinateur. Un fichier déjà suivi par Git ne devient pas ignoré automatiquement ; si un `.exe` reste dans les changements à envoyer, en parler au responsable du dépôt pour arrêter son suivi.

[Documentation GitHub : ignorer des fichiers](https://docs.github.com/en/get-started/git-basics/ignoring-files).

## 6. Configurer la compilation et l'exécution — une fois par copie du projet

La configuration ci-dessous compile `main.cpp` à la racine du projet et produit `main.exe`.

### Créer `.vscode/tasks.json`

Dans l'explorateur de VS Code, créer un dossier nommé `.vscode`, puis un fichier `tasks.json` dedans. S'il existe déjà, conserver une copie de son contenu avant de le remplacer par :

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Compiler le projet",
            "type": "process",
            "command": "g++",
            "args": [
                "-std=c++17",
                "-Wall",
                "-Wextra",
                "-g",
                "${workspaceFolder}/main.cpp",
                "-o",
                "${workspaceFolder}/main.exe"
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": ["$gcc"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

Enregistrer avec **Ctrl + S**. **Ctrl + Maj + B** compile maintenant le projet. Le terminal affiche les erreurs éventuelles.

[Documentation : les tâches de VS Code](https://code.visualstudio.com/docs/debugtest/tasks).

### Créer `.vscode/launch.json`

Dans le même dossier `.vscode`, créer `launch.json` avec :

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Lancer le projet",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/main.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/msys64/ucrt64/bin/gdb.exe",
            "preLaunchTask": "Compiler le projet"
        }
    ]
}
```

Adapter `miDebuggerPath` si MSYS2 est installé ailleurs. Enregistrer le fichier.

Ouvrir **Exécuter et déboguer** avec **Ctrl + Maj + D** et sélectionner **Lancer le projet** dans la liste en haut.

- **Ctrl + F5** : compiler puis exécuter sans débogage.
- **F5** : compiler puis déboguer.
- Le **bouton vert de ce panneau** lance la configuration sélectionnée.

Cette méthode utilise les deux fichiers ci-dessus. Le bouton en haut à droite d'un fichier C++ peut proposer une autre configuration.

Si la compilation échoue, corriger les erreurs avant de relancer. Ne pas choisir d'exécuter quand même un ancien programme.

[Documentation : lancer et déboguer dans VS Code](https://code.visualstudio.com/docs/debugtest/debugging). Pour les réglages propres à GDB, consulter le [guide C++ pour Windows](https://code.visualstudio.com/docs/cpp/config-mingw).

### Si des fichiers C++ sont ajoutés plus tard

Cette tâche compile uniquement `main.cpp`. Ajouter les autres fichiers `.cpp` dans `args`, avant `"-o"`, par exemple :

```json
"${workspaceFolder}/main.cpp",
"${workspaceFolder}/tournoi.cpp",
```

Ne pas lister les fichiers `.h` comme des fichiers à compiler. Mettre également à jour `SOURCES` dans `sae102.pro` pour garder le projet utilisable avec qmake.

## 7. Faire sa première compilation

1. Enregistrer les fichiers de code modifiés avec **Ctrl + S**.
2. Sélectionner **Lancer le projet**.
3. Appuyer sur **Ctrl + F5**.
4. Vérifier le résultat dans le terminal et essayer les cas concernés par ses modifications.

L'absence d'erreur de compilation ne garantit pas que le programme donne le bon résultat : il faut aussi le tester.

Pour vérifier manuellement en cas de problème, ouvrir un terminal **PowerShell** à la racine du projet et lancer :

```powershell
g++ -std=c++17 -Wall -Wextra -g main.cpp -o main.exe
```

Seulement si la compilation réussit :

```powershell
.\main.exe
```

## 8. Travailler à plusieurs avec des branches

Organisation proposée : conserver une branche principale commune et créer une branche pour chaque modification. Les changements sont ensuite réunis avec une pull request.

Dans les étapes suivantes, `main` désigne la branche principale. **Si le dépôt utilise `master` ou un autre nom, utiliser ce nom à la place.**

### Commencer une nouvelle modification

1. Terminer ou enregistrer dans un commit son travail en cours avant de changer de branche.
2. Cliquer sur le nom de la branche en bas à gauche et sélectionner **main**.
3. Ouvrir **Contrôle de code source** avec **Ctrl + Maj + G**.
4. Cliquer sur **… → Pull / Tirer** pour mettre `main` à jour.
5. Ouvrir **Ctrl + Maj + P → Git: Create Branch…**.
6. Donner un nom explicite, par exemple `clement/correction-tri` ou `jonathan/affichage-scores`.

La nouvelle branche devient la branche active. Vérifier son nom avant de modifier le code.

Créer une branche depuis une version à jour évite de commencer sur une ancienne version du projet. Les branches n'évitent pas tous les conflits : se répartir les fonctions à modifier reste utile.

[Documentation : créer et changer de branche dans VS Code](https://code.visualstudio.com/docs/sourcecontrol/branches-worktrees).

### Modifier, tester et faire un commit

1. Modifier le code sur sa branche.
2. Enregistrer, compiler et tester.
3. Ouvrir **Contrôle de code source**.
4. Cliquer sur chaque fichier modifié pour relire les différences.
5. Cliquer sur **+** à côté des fichiers à inclure dans le commit.
6. Écrire un message qui décrit la modification, par exemple `Corrige le tri des joueurs par score`.
7. Cliquer sur **Commit / Valider**.

Les fichiers sélectionnés avec **+** constituent le contenu du prochain commit. Si un fichier est encore modifié après sa sélection, le sélectionner de nouveau pour inclure la dernière version.

Faire des commits centrés sur une modification compréhensible. Un commit reste local jusqu'au push.

[Documentation : sélectionner et valider les modifications](https://code.visualstudio.com/docs/sourcecontrol/staging-commits).

### Envoyer sa branche sur GitHub

Au premier envoi, choisir **Publish Branch / Publier la branche**. Pour les envois suivants, utiliser **… → Push / Pousser** dans le contrôle de code source.

Se connecter à GitHub si demandé. Vérifier sur le site que les commits apparaissent en sélectionnant sa branche.

Le push de cette branche ne modifie pas encore la branche principale. Il rend le travail disponible pour les autres.

[Documentation : envoyer ses commits sur un dépôt distant](https://docs.github.com/en/get-started/using-git/pushing-commits-to-a-remote-repository).

### Proposer une pull request

1. Sur GitHub, ouvrir le dépôt puis **Pull requests → New pull request**. Un bouton **Compare & pull request** peut aussi être proposé après le push.
2. Choisir **base : main** et **compare : sa branche**.
3. Vérifier les fichiers concernés.
4. Écrire un titre, décrire la modification et préciser les essais effectués.
5. Cliquer sur **Create pull request** et demander une relecture à un membre.

Le membre qui intègre la modification vérifie le résultat puis utilise **Merge pull request** si GitHub l'autorise et que l'équipe est d'accord. Si des corrections sont demandées, les faire sur la même branche puis refaire commit et push : la pull request se met à jour.

Après la fusion, revenir sur `main` dans VS Code et faire un pull. Créer une nouvelle branche depuis ce `main` à jour pour le travail suivant.

[Documentation : créer une pull request](https://docs.github.com/en/pull-requests/how-tos/create-pull-requests/creating-a-pull-request).

## 9. Savoir si quelqu'un a envoyé des changements

Dans **Paramètres**, accessibles avec **Ctrl + ,**, chercher **Git: Autofetch** et l'activer. VS Code vérifie les nouveautés en arrière-plan, toutes les trois minutes par défaut.

Pour la branche distante suivie par la branche active :

- **↓2** indique deux commits à récupérer.
- **↑1** indique un commit local à envoyer.

Ce sont des indicateurs visuels ; une fenêtre de notification n'apparaît pas forcément. L'autofetch ne modifie pas les fichiers. Le pull intègre les changements.

**Attention aux branches :** si quelqu'un envoie du travail sur sa propre branche, il n'arrive pas dans `main` tant que sa pull request n'est pas fusionnée. L'indicateur de sa propre branche ne signale pas tous les changements de toutes les branches.

Un pull met à jour la branche active. Pour récupérer la dernière version commune, revenir sur `main` puis faire un pull. Pour continuer une branche déjà commencée avec les nouveaux changements de `main`, enregistrer son travail, mettre `main` à jour, revenir sur sa branche et utiliser **Git: Merge… → main**, puis tester le résultat.

[Documentation : fetch, pull, push et synchronisation](https://code.visualstudio.com/docs/sourcecontrol/repos-remotes).

## 10. Résoudre les problèmes courants

| Problème | Vérification ou correction |
| --- | --- |
| `git` n'est pas reconnu | Vérifier l'installation de Git, puis fermer toutes les fenêtres de VS Code et le rouvrir. |
| `g++` n'est pas reconnu | Vérifier l'installation des paquets MSYS2 et l'entrée `C:\msys64\ucrt64\bin` dans Path, puis rouvrir VS Code. |
| `miDebuggerPath` est invalide | Vérifier que GDB est installé et adapter son chemin dans `launch.json`. |
| `main.cpp` est introuvable | Ouvrir le dossier qui contient ce fichier, pas seulement le fichier isolé ou son dossier parent. |
| Erreur avec un numéro de ligne dans `main.cpp` | Corriger le code indiqué. Commencer par la première erreur : les suivantes peuvent en découler. |
| `Permission denied` sur `main.exe` | Arrêter le programme encore ouvert, puis recompiler. |
| Les derniers changements ne s'affichent pas à l'exécution | Enregistrer les fichiers, vérifier que la compilation réussit et lancer le bon exécutable. |
| Le `.gitignore` créé sur GitHub n'est pas sur l'ordinateur | Faire un pull de la branche sur laquelle il a été ajouté. |
| Le push est refusé pour manque de droits | Vérifier le compte connecté et l'acceptation de l'invitation au dépôt. |
| Le push indique que la branche distante a avancé | Conserver ses commits, faire un pull de cette branche et résoudre les conflits éventuels avant de pousser à nouveau. Ne pas forcer l'envoi pour contourner le refus. |

### Si Git bloque un pull ou un changement de branche

Si des modifications locales risquent d'être écrasées, conserver ce travail dans un commit ou le mettre temporairement de côté avec **Git: Stash (Include Untracked)**. Pour le récupérer ensuite, utiliser **Git: Apply Stash…** et sélectionner l'entrée correspondante. Cette restauration peut elle-même demander de résoudre des conflits.

[Documentation : mettre du travail de côté avec un stash](https://code.visualstudio.com/docs/sourcecontrol/branches-worktrees).

### Si Git signale un conflit

Cela signifie qu'il ne peut pas réunir automatiquement certaines modifications.

1. Ouvrir les fichiers en conflit depuis **Contrôle de code source**.
2. Comparer les deux versions dans l'éditeur de fusion.
3. Construire la version qui conserve les changements nécessaires des deux personnes. Ne pas sélectionner systématiquement un côté.
4. Retirer tous les marqueurs de conflit (`<<<<<<<`, `=======`, `>>>>>>>`).
5. Enregistrer, compiler et tester.
6. Ajouter les fichiers résolus avec **+**, puis terminer le commit de fusion demandé par Git.

Si la bonne version n'est pas évidente, se concerter avec la personne qui a modifié la même partie.

[Documentation : résoudre les conflits dans VS Code](https://code.visualstudio.com/docs/sourcecontrol/merge-conflicts).

## 11. La routine à retenir

Pour une nouvelle modification :

**Main à jour → nouvelle branche → modification → enregistrement → compilation et tests → commit → push → pull request.**

Après la fusion :

**Revenir sur main → pull → commencer la modification suivante.**

| Raccourci | Action |
| --- | --- |
| Ctrl + S | Enregistrer le fichier actif. |
| Ctrl + Maj + B | Compiler le projet avec la tâche configurée. |
| Ctrl + F5 | Compiler puis lancer la configuration sélectionnée. |
| F5 | Compiler puis déboguer la configuration sélectionnée. |
| Ctrl + Maj + G | Ouvrir le contrôle de code source. |
| Ctrl + Maj + P | Ouvrir la palette de commandes. |

Le terminal reste disponible pour diagnostiquer un problème, mais il n'est pas nécessaire de retaper la commande de compilation à chaque essai.
