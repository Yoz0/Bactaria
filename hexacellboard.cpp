#include "hexacellboard.h"

HexaCellBoard::HexaCellBoard(QGraphicsScene* scene)
{

}

HexaCellBoard::~HexaCellBoard()
{

}

void HexaCellBoard::setupBoard(QGraphicsScene *scene)
{
    int width= 4; //TODO: Il faut mettre ces machins en paramètres
    int height = 4;
    this->board.resize(width);

    for(int i = 0 ; i < width ; i ++)
    {
        this->board[i].resize(height);
        for(int j = 0 ; j < height ; j ++)
        {
            if( i == 0 && j == 0)
            {
                HexaCell* hc = new HexaCell(i,j,1,NORMAL,10);
                hc->setPos(hc->hexaSize*3/2*i,hc->hexaSize*sqrt(3.0)*(i/2.0+j));
                scene->addItem(hc);
                board[i][j] = hc;
                playerCells.push_back(hc);
            }
            else if ( i == 3 && j == 3)
            {
                HexaCell* hc = new HexaCell(i,j,2,NORMAL,10);
                hc->setPos(hc->hexaSize*3/2*i,hc->hexaSize*sqrt(3.0)*(i/2.0+j));
                scene->addItem(hc);
                board[i][j] = hc;
                botCells.push_back(hc);
            }
            else
            {
                HexaCell* hc = new HexaCell(i,j,0,NORMAL,10);
                hc->setPos(hc->hexaSize*3/2*i,hc->hexaSize*sqrt(3.0)*(i/2.0+j));
                scene->addItem(hc);
                board[i][j] = hc;
            }
        }
    }
}

void HexaCellBoard::cellGrowing()
{
    for( auto c : playerCells )
    {
        c->growing();
    }

    for( auto b : botCells )
    {
        b.growing();
    }
}
