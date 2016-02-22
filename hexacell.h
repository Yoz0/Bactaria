#ifndef HEXACELL_H
#define HEXACELL_H

enum CellType
{
    normal = 0,
    farm = 1
};

class HexaCell
{
private:
    CellType    type;
    int         playerId;
    int         posX;
    int         posY;

public:
    HexaCell( int x, int y, int pID, CellType ct );
    ~HexaCell();

    int getPosX() { return posX; }
    int getPosY() { return posX; }
    int getPlayerID() { return playerId; }
    void setPlayerID(int id) { playerId = id; }
    CellType getCellType() { return type; }
    void setCellType(CellType ct) { type = ct; }
};

#endif // HEXACELL_H
