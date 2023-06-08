# Manuel utilisateur pour le projet **Space Crusade**

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

## Contrôles en jeu

Tous les contrôles sont indiqués dans la section **Tutorial** du jeu.

## Modes de jeu

Le jeu propose 2 modes de jeu :

- **Mode campagne** : le joueur joue à différents niveaux avec des ennemis de plus en plus forts.
- **Mode infini** : le joueur joue à un niveau infini. Le but de ce mode est de survivre le plus longtemps possible.

## Paramètres du jeu

Le jeu permet de changer les paramètres suivants :

- **Activation du mode coopératif** : permet de jouer à 2 joueurs en même temps (avec les touches z, q, s, d pour le joueur 1 et les touches haut, bas, gauche et droite).
- **Changement de la difficulté** : permet de changer la difficulté du jeu (facile, moyen, difficile ou custom en fonction des autres paramètres).
- **Customisation des différents éléments en jeu** : le jeu permet de modifier un grand nombres de paramètres tels que le cooldown des bonus ou encore la vitesse du vaisseau.