#include "hexacellboard.h"

HexaCellBoard::HexaCellBoard(QGraphicsScene* scene)
{
    this->setupBoard(scene);
}

HexaCellBoard::~HexaCellBoard()
{

}

void HexaCellBoard::setupBoard(QGraphicsScene *scene)
{
    int width= 15; //TODO: Il faut mettre ces machins en paramètres
    int height = 15;
    this->board.resize(width);

    for(int i = 0 ; i < width ; i ++)
    {
        this->board[i].resize(height);
        for(int j = 0 ; j < height ; j ++)
        {
            HexaCell* hc = new HexaCell(i,j,0,NORMAL,10);
            hc->setPos(hc->hexaSize*3/2*i,hc->hexaSize*sqrt(3.0)*(i/2.0+j));
            scene->addItem(hc);
            board[i][j] = hc;
        }
    }
}
