# Space Crusade (projet INFO 1)

## Documentation technique

La documentation technique du code est dans le **fichier Doxygen.html dans le répertoire doc à la racine du projet.**
<br>
Ce document est à ouvrir **avec un navigateur** car il est chargé à partir des fichiers de configuration Doxygen.

## Prérequis

**Avoir la librairie MLV installée.**
<br>
Tutoriel pour les O.S. linux : http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/installation_linux.html

## Installation

Installer les packages nécessaires :
```sh 
sudo apt update && sudo apt install build-essential
```

Cloner le repo avec : 
```sh 
git clone https://github.com/Flamby000/Shootemup_V2.git
```

## Utilisation et lancement du jeu

Pour lancer le jeu :

```sh
make run
```

## Modes de jeu

Le jeu propose 2 modes de jeu :

- **Mode campagne** : le joueur joue à différents niveaux avec des ennemis de plus en plus forts.
- **Mode infini** : le joueur joue à un niveau infini. Le but de ce mode est de survivre le plus longtemps possible.

## Paramètres du jeu

Le jeu permet de changer les paramètres suivants :

- **Activation du mode coopératif** : permet de jouer à 2 joueurs en même temps (avec les touches z, q, s, d pour le joueur 1 et les touches haut, bas, gauche et droite).
- **Changement de la difficulté** : permet de changer la difficulté du jeu (facile, moyen, difficile ou custom en fonction des autres paramètres).
- **Customisation des différents éléments en jeu** : le jeu permet de modifier un grand nombres de paramètres tels que le cooldown des bonus ou encore la vitesse du vaisseau.
