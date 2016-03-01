Bactaria --> Jeu de stratégie en temps réél, développé en C++ avec QT

Projet de base :
	Un tableau de cellule héxagonale est présent.
	Lorsque l'on passe la souris sur une cellule, elle apparait en subrillance et la population est indiquée.
	Nous pouvons faire un double clic sur la cellule pour la sélectionner.
	La couleur de la cellule change selon l'id du joueur.

Instructions pour compiler et lancer le projet sous Ubuntu / Linux:
$ sudo apt-get update
$ sudo apt-get install qt5-default
$ cd ./chemin_du_dossier/Bactaria
$ qmake
$ make
$ ./Bactaria

Sous Windows ou MacOS il est nécessaire d'installer Qt puis d'ouvrir le projet :
https://www.qt.io/download-open-source/