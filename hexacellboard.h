#ifndef HEXACELLBOARD_H
#define HEXACELLBOARD_H

#include <vector>
#include <list>
#include <QGraphicsScene>
#include "hexacell.h"
#include <QObject>

using namespace std;

class HexaCellBoard
{
private:
    vector<vector<HexaCell*>>   board;
    list<HexaCell*>             playerCells;
    list<HexaCell*>             botCells;
    HexaCell*                   selected;
    int width;
    int height;

public:
    // Constructor / Destructor
    HexaCellBoard(QGraphicsScene* scene);
    ~HexaCellBoard();

    // Getter / Setter
    HexaCell* getHexaCell(int i, int j) { return board[i][j]; }
    int getWidth() { return width;}
    int getHeight() { return height;}


    //GameAction
    void setupBoard( QGraphicsScene* scene );
    void cellGrowing();
    list<HexaCell*> dijkstra(HexaCell* start, HexaCell* end, int idPlayer);
    int winTest();

};

#endif // HEXACELLBOARD_H
