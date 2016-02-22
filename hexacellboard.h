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
};

#endif // HEXACELLBOARD_H
