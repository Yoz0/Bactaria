Bactaria
========
Jeu de stratégie en temps réél, développé en C++ avec Qt

Description du projet
---------------------
Lire le cahier des charges disponible [ici](https://drive.google.com/file/d/0B0TeTfnKOJcfSnloVmdPck9XWmc/view?usp=sharing)

Actuellement implémenté
-----------------------
Un tableau de cellule héxagonale est présent.
Lorsque l'on passe la souris sur une cellule, elle apparait en subrillance et la population est indiquée.
Nous pouvons faire un double clic sur la cellule pour la sélectionner.
La couleur de la cellule change selon l'id du joueur.

Instructions d'installation
---------------------------
### Ubuntu/Linux
* `sudo apt-get update`
* `sudo apt-get install qt5-default`
* `cd ./chemin_du_dossier/Bactaria`
* `qmake`
* `make`
* `./Bactaria`

### Windows ou MacOS :
* Installer Qt https://www.qt.io/download-open-source/
* Ouvrir le projet Bactaria.pro
* Appuyer sue le bouton "Run"
