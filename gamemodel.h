#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <list>

#include "hexacellboard.h"
#include "hexacell.h"

class GameModel
{
private:
    HexaCellBoard*      hexaCellBoard;
    std::list<int>      listOfPlayerId;
public:
    GameModel();
    HexaCell*  getHexaCell(int i, int j) { return hexaCellBoard->getHexaCell(i,j); }
    int getWidthHexaCellBoard() { return hexaCellBoard->getWidth();}
    int getHeightHexaCellBoard() { return hexaCellBoard->getHeight() ;}

};

#endif // GAMEMODEL_H
