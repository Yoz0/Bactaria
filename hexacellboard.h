#ifndef HEXACELLBOARD_H
#define HEXACELLBOARD_H

#include <vector>
#include "hexacell.h"

using namespace std;

class HexaCellBoard
{
private:
    vector< vector <HexaCell*> > board;

public:
    HexaCellBoard();
    ~HexaCellBoard();
    HexaCell* getHexaCell(int i, int j) {  return board[i][j]; }
    int getWidth() { return board.size() ;}
    int getHeight() { return board[0].size() ;}
};

#endif // HEXACELLBOARD_H
