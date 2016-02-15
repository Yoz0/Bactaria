#include "cell.h"
#include <iostream>

using namespace std;
Cell::Cell()
{
    x = 0;
    y = 0;
    population = 0;
    type = -1;
}

Cell::Cell(int init_x, int init_y, int init_pop, int init_type)
{
    x = init_x;
    y = init_y;
    population = init_pop;
    type = init_type;
}

void Cell::afficher_console(){
    cout << "postion (" << x <<"," << y <<") population = "<< population << " ; type = " << type << endl;
}
