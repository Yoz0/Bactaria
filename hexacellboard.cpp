#include "hexacellboard.h"

#include <queue>
#include <math.h>
#include <iostream>

#include "mainwindow.h"

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
    this->board.resize(height);

    for(int i = 0 ; i < height ; i ++)
    {
        this->board[i].resize(width);
        for(int j = 0 ; j < width ; j ++)
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

    for(int i = 0 ; i < height ; i ++)
    {
        for(int j = 0 ; j < width ; j ++)
        {
            if( i-1 >= 0 && board[i-1][j] != nullptr ) // i-1 j
                board[i][j]->setNewVoisin( board[i-1][j] );

            if( j-1 >= 0 && board[i][j-1] != nullptr ) // i j-1
                board[i][j]->setNewVoisin( board[i][j-1] );

            if ( i-1 >= 0 && j+1 < width && board[i-1][j+1] != nullptr ) // i-1 j+1
                board[i][j]->setNewVoisin( board[i-1][j+1] );

            if ( i+1 < height && board[i+1][j] != nullptr ) // i+1 j
                board[i][j]->setNewVoisin( board[i+1][j] );

            if ( j+1 < width && board[i][j+1] != nullptr ) // i j+1
                board[i][j]->setNewVoisin( board[i][j+1] );

            if ( i+1 < height && j-1 >= 0 && board[i+1][j-1] != nullptr) // i+1 j-1
                board[i][j]->setNewVoisin( board[i+1][j-1] );
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

bool pasFini( vector<vector<bool>> tab)
{
    for( auto i : tab )
        for ( auto j : i )
            if ( j == false )
                return true;
    return false;
}

list<HexaCell*> HexaCellBoard::dijkstra(HexaCell* start, HexaCell* end, int idPlayer)
{
    /*Truc nul d'Alexian...
     *
     * if( start == nullptr || end == nullptr )
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
    HexaCell* temp;

    boardDistance[start->getIndexLine()][start->getIndexColumn()] = 0;
    bool endFind = false;

    while( !qCell.empty() && !endFind)
    {
        temp = qCell.front();
        qCell.pop();
        for( auto voisin : temp->getVoisins() )
        {
            if( boardDistance[voisin->getIndexLine()][voisin->getIndexColumn()] == -2
                    && idPlayer == board[voisin->getIndexLine()][voisin->getIndexColumn()]->getPlayerID() ) // pas case vide et verif id
            {
                qCell.push( board[voisin->getIndexLine()][voisin->getIndexColumn()] );
                boardDistance[voisin->getIndexLine()][voisin->getIndexColumn()] = 1 + boardDistance[temp->getIndexLine()][temp->getIndexColumn()];
            }
            if( voisin == end )
            {
                boardDistance[voisin->getIndexLine()][voisin->getIndexColumn()] = 1 + boardDistance[temp->getIndexLine()][temp->getIndexColumn()];
                endFind = true;
            }
        }
    }

    if( endFind == false ){
        return nullptr;
    }
    std::list<HexaCell*>* ret = new std::list<HexaCell*>();
    temp = end;
    ret->push_front(end);

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
        ret->push_front(temp);
    }

    std::cout << "dijkstra fini !" << std::endl;
    return ret;
    */
     vector<vector<bool>> markedCells(height, vector<bool>(width) );
     vector<vector<int>> distanceBoard(height, vector<int>(width) );

     //initialisation
     int i, j;
     for (i=0;i<height;i++)
     {
         for (j=0;j<width;j++)
         {
            if (board[i][j]->getPlayerID() != idPlayer)
                  markedCells[i][j]=true;
            else
                  markedCells[i][j]=false;
             distanceBoard[i][j]=1000;
         }
     }
     distanceBoard[start->getIndexLine()][start->getIndexColumn()] = 0;

     int iMin, jMin, min=1000;
     while (pasFini(markedCells))
     {
         min = 10000000;
         for (i=0;i<height;i++)
         {
             for (j=0;j<width;j++)
             {
                if (distanceBoard[i][j] < min && !markedCells[i][j])
                {
                    iMin = i;
                    jMin = j;
                    min = distanceBoard[i][j];
                }
             }
         }

         list<HexaCell*> voisins = board[iMin][jMin]->getVoisins();
         for (auto voisin : voisins )
         {
             if (min+1 < distanceBoard[voisin->getIndexColumn()][voisin->getIndexLine()])
             {
                 distanceBoard[voisin->getIndexColumn()][voisin->getIndexLine()] = min +1;
             }
         }
         markedCells[iMin][jMin] = true;
     }

     HexaCell* temp = end;

     list<HexaCell *> ret;

     ret.push_back(end);

     while( temp != start )
     {
         min = 1000;
         for( auto voisin : temp->getVoisins() )
         {
            if (distanceBoard[voisin->getIndexColumn()][voisin->getIndexLine()] < min)
            {
                min=distanceBoard[voisin->getIndexColumn()][voisin->getIndexLine()];
                iMin = voisin->getIndexLine();
                jMin = voisin->getIndexColumn();
            }
         }
         temp = board[iMin][jMin];
         ret.push_front(temp);
     }
     return ret;
}

int HexaCellBoard::winTest()
{
    /*Fonction testant si le plateau est gagnant ou perdant. Si le joueur a gagné ( 80% du plateau
     * conquis ou ia défaite ), cette fonction renvoie 1 ( l'id du joueur). Si l'ia a gagnée ( joueur défait)
     * elle renvoie 2. Sinon, elle renvoie 0 et la partie peut continuer.
     *
     * Cette fonction est adaptée à la présence de cases "vides" dans le plateau.
     *
     * */

    int i, j, playerCount,iaCount, neutralCount, res;
    float somme;
    for (i=0;i<height;i++)
    {
        for (j=0;j<width; j++)
        {
            if (board[i][j]->getPlayerID() == 1)
                playerCount++;
            else if (board[i][j]->getPlayerID() == 2)
                iaCount++;
            else if (board[i][j]->getPlayerID() == 0)
                neutralCount++;
        }
    }
    somme = playerCount + iaCount + neutralCount;
    if (playerCount/somme > 0.8 || iaCount == 0)
    {
        res = 1;
    }
    else if (playerCount == 0)
    {
        res = 2;
    }
    else
    {
        res = 0;
    }
    return res;
}


