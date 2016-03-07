#ifndef HEXACELLBOARD_H
#define HEXACELLBOARD_H

#include <vector>
#include <list>
#include <QGraphicsScene>
#include "hexacell.h"

using namespace std;

class HexaCellBoard
{
private:
    vector<vector<HexaCell*>>   board;
    list<HexaCell*>             playerCells;
    list<HexaCell*>             botCells;
    HexaCell*                   selected;

public:
    // Constructor / Destructor
    HexaCellBoard(QGraphicsScene* scene);
    ~HexaCellBoard();

    // Getter / Setter
    HexaCell* getHexaCell(int i, int j) { return board[i][j]; }
    int getWidth() { return board.size() ;}
    int getHeight() { return board[0].size() ;}

    //GameAction
    void setupBoard( QGraphicsScene* scene );
    void cellGrowing();
};

#endif // HEXACELLBOARD_H
