#ifndef IA_H
#define IA_H
#include "hexacellboard.h"
class IA
{
public:
    IA(HexaCellBoard* hcb, int PID);
    void action();
private:
    HexaCellBoard* playingBoard;
    int myPID;
    HexaCell* biggestCell();
    list<HexaCell*> closestCell(HexaCell* startCell);
};

#endif // IA_H
