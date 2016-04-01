#include "hexacellboard.h"
#include <queue>
#include <math.h>

HexaCellBoard::HexaCellBoard(QGraphicsScene* scene)
{
    width= 4;
    height = 4;
}

HexaCellBoard::~HexaCellBoard()
{

}

void HexaCellBoard::setupBoard(QGraphicsScene *scene)
{
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

    for(int i = 0 ; i < width ; i ++)
    {
        for(int j = 0 ; j < width ; j ++)
        {
            if( i-1 >= 0 && board[i-1][j] != nullptr ) // i-1 j
                board[i][j]->setNewVoisin( board[i-1][j] );

            if( j-1 >= 0 && board[i][j-1] != nullptr ) // i j-1
                board[i][j]->setNewVoisin( board[i][j-1] );

            if ( i-1 >= 0 && j-1 >= 0 && board[i-1][j-1] != nullptr ) // i-1 j-1
                board[i][j]->setNewVoisin( board[i-1][j-1] );

            if ( i+1 < width && board[i+1][j] != nullptr ) // i+1 j
                board[i][j]->setNewVoisin( board[i+1][j] );

            if ( j+1 < height && board[i][j+1] != nullptr ) // i j+1
                board[i][j]->setNewVoisin( board[i][j+1] );

            if ( i+1 < width && j+1 < height && board[i][j+1] != nullptr) // i+1 j+1
                board[i][j]->setNewVoisin( board[i+1][j+1] );
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
        b->growing();
    }
}


list<HexaCell*>* HexaCellBoard::dijkstra(HexaCell* start, HexaCell* end, int idPlayer)
{
    if( start != nullptr || end != nullptr )
        return nullptr;

    vector<vector<int>> boardDistance(width, vector<int>(height) );
    queue<HexaCell*> qCell;

    for(int i=0; i < width; i++)
    {
        for(int j=0; j < height; j++)
        {
            if( board[i][j] == nullptr )
                boardDistance[i][j] = -1;
            else
                boardDistance[i][j] = -2;
        }
    }

    qCell.push(start);
    HexaCell* temp = start;

    boardDistance[start->getIndexLine()][start->getIndexColumn()] = 0;

    while( temp != end || !qCell.empty() )
    {
        for( auto voisin : temp->getVoisins() )
        {
            if( boardDistance[voisin->getIndexLine()][voisin->getIndexColumn()] == -2
                    && idPlayer == board[voisin->getIndexLine()][voisin->getIndexColumn()]->getPlayerID() ) // pas case vide et verif id
            {
                qCell.push( board[voisin->getIndexLine()][voisin->getIndexColumn()] );
                boardDistance[voisin->getIndexLine()][voisin->getIndexColumn()] = 1 + boardDistance[temp->getIndexLine()][temp->getIndexColumn()];
            }
        }

        qCell.pop();
        temp = qCell.front();
    }

    if( temp != end )
        return nullptr;

    list<HexaCell*>* ret;
    temp = end;
    ret->push_back(end);

    HexaCell* temp2;
    int value;

    while( temp != start )
    {
        value = 1000;
        for( auto voisin : temp->getVoisins() )
        {
            if( boardDistance[voisin->getIndexLine()][voisin->getIndexColumn()] < value
                    && boardDistance[voisin->getIndexLine()][voisin->getIndexColumn()] == -2)
            {
                temp2 = voisin;
                value = boardDistance[voisin->getIndexLine()][voisin->getIndexColumn()];
            }
        }
        temp2 = temp;
        ret->push_back(temp);
    }

    return ret;
}
