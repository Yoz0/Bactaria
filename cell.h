#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell();
    Cell(int, int, int, int);
    void afficher_console();
private:
    int population;
    int x,y;
    int type; // -1 : inaccessible ; 0 : neutre ; 1 ou plus : identifiant du joueur;
};

#endif // CELL_H
