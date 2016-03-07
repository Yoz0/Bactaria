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
    vector< vector <HexaCell*> >    board;
    std::list<int>                  listOfPlayerId;
    int width;
    int height;

public:
    // Constructor / Destructor
    HexaCellBoard(QGraphicsScene* scene);
    ~HexaCellBoard();

    // Getter / Setter
    HexaCell* getHexaCell(int i, int j) { return board[i][j]; }
    int getWidth() { return board.size() ;}
    int getHeight() { return board[0].size() ;}

    //
    void setupBoard( QGraphicsScene* scene );

};

#endif // HEXACELLBOARD_H
