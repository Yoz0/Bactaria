#include "hexacellboard.h"
#include "mainwindow.h"

#include <queue>
#include <math.h>
#include <string>
#include <iostream>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QIODevice>
#include <QTextStream>

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param scene [description]
 */
HexaCellBoard::HexaCellBoard(QGraphicsScene* scene)
{
}

/**
 * @brief [brief description]
 * @details [long description]
 * @return [description]
 */
HexaCellBoard::~HexaCellBoard()
{
    for (auto row: board){
        for (auto hc: row){
            std::cout<<"delete hc : "<<hc<<std::endl;
            if (hc != nullptr)
                delete hc;
        }
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param scene [description]
 * @param f [description]
 */
void HexaCellBoard::setupBoard(QGraphicsScene *scene, string f)
{
    QFile file( QString::fromStdString(f) );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Error in HexaCellBoard::setupBoard, read board from file : " << f << std::endl;
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    QStringList list = line.split(' ');
    height = list.at(0).toInt();
    width = list.at(1).toInt();
    // on resize board
    this->board.resize(height);
    for(int i=0; i<board.size(); i++)
        board[i].resize(width);
    // on lit chaque ligne
    while (!in.atEnd()) {
        line = in.readLine();
        list = line.split(' ');
        int i = list.at(0).toInt();
        int j = list.at(1).toInt();
        HexaCell* hc = new HexaCell(i, j,
                                    list.at(2).toInt(),
                                    static_cast<CellType>( list.at(3).toInt() ),
                                    list.at(4).toInt());

        hc->setPos(hc->hexaSize*3/2*j,hc->hexaSize*sqrt(3.0)*(j/2.0+i));
        scene->addItem(hc);
        board[i][j] = hc;

        // insert into list..
        if (hc->getPlayerID() == 1)
            playerCells.push_back(hc);
        else if (hc->getPlayerID() == 2)
            botCells.push_back(hc);
    }
    // Les voisins de chaques hexacell
    for(int i = 0 ; i < height ; i ++)
    {
        std::cout << std::endl;
        for(int j = 0 ; j < width ; j ++)
        {

            if( board[i][j] != nullptr )
            {
                std::cout<< 1 << " ";
                if( i-1 >= 0 && board[i-1][j] != nullptr ) // i-1 j
                    board[i][j]->setNewVoisin( board[i-1][j] );

                if( j-1 >= 0 && board[i][j-1] != nullptr ) // i j-1
                    board[i][j]->setNewVoisin( board[i][j-1] );

                if ( i+1 < height && j-1 >= 0 && board[i+1][j-1] != nullptr ) // i+1 j-1
                    board[i][j]->setNewVoisin( board[i+1][j-1] );

                if ( i+1 < height && board[i+1][j] != nullptr ) // i+1 j
                    board[i][j]->setNewVoisin( board[i+1][j] );

                if ( j+1 < width && board[i][j+1] != nullptr ) // i j+1
                    board[i][j]->setNewVoisin( board[i][j+1] );

                if ( i-1 >= 0 && j+1 < width && board[i-1][j+1] != nullptr) // i-1 j+1
                    board[i][j]->setNewVoisin( board[i-1][j+1] );
            }

            else
                std::cout<< 0 << " ";
        }
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param r [description]
 */
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

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param tab [description]
 * @return [description]
 */
bool pasFini( vector<vector<bool>> tab)
{
    for( auto i : tab )
        for ( auto j : i )
            if ( j == false )
                return true;
    return false;
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param start [description]
 * @param end [description]
 * @param idPlayer [description]
 * @return [description]
 */
list<HexaCell*> HexaCellBoard::dijkstra(HexaCell* start, HexaCell* end, int idPlayer)
{
     vector<vector<bool>> markedCells(height, vector<bool>(width) );
     vector<vector<int>> distanceBoard(height, vector<int>(width) );

     //initialisation
     int i, j;
     for (i=0;i<height;i++)
     {
         for (j=0;j<width;j++)
         {
            if (board[i][j] != nullptr){
                if (board[i][j]->getPlayerID() != idPlayer)
                      markedCells[i][j]=true;
                else
                      markedCells[i][j]=false;
            }
            else
                markedCells[i][j]=true;
            distanceBoard[i][j]=1000;
         }
     }
     distanceBoard[start->getIndexLine()][start->getIndexColumn()] = 0;

     //Cherche les distances
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
             if (min+1 < distanceBoard[voisin->getIndexLine()][voisin->getIndexColumn()])
             {
                 distanceBoard[voisin->getIndexLine()][voisin->getIndexColumn()] = min +1;
             }
         }
         markedCells[iMin][jMin] = true;
     }

     //Si il n'y a pas de chemins
     if (distanceBoard[end->getIndexLine()][end->getIndexColumn()] == 1000){
         list<HexaCell *> ret;
         return ret;
     }

     //Remonte pour renvoyer le bon chemin
     HexaCell* temp = end;

     list<HexaCell *> ret;

     ret.push_back(end);

     while( temp != start )
     {
         min = 1000;
         for( auto voisin : temp->getVoisins() )
         {
            if (voisin->getPlayerID()==idPlayer && distanceBoard[voisin->getIndexLine()][voisin->getIndexColumn()] < min)
            {
                min=distanceBoard[voisin->getIndexLine()][voisin->getIndexColumn()];
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
    /* Fonction testant si le plateau est gagnant ou perdant.
     * Si le joueur a gagné ( 80% du plateau conquis ou ia défaite ), cette fonction renvoie 1 ( l'id du joueur).
     * Si l'ia a gagnée (joueur défait) elle renvoie 2.
     * Sinon, elle renvoie 0 et la partie peut continuer.
     *
     * Cette fonction est adaptée à la présence de cases "vides" dans le plateau.
     * */

    int i, j, playerCount, iaCount, neutralCount, res;
    playerCount = 0;
    neutralCount = 0;
    iaCount = 0;
    float somme;
    for (i=0;i<height;i++)
    {
        for (j=0;j<width; j++)
        {
            if (board[i][j] != nullptr){
               if (board[i][j]->getPlayerID() == 1)
                    playerCount++;
                else if (board[i][j]->getPlayerID() == 2)
                    iaCount++;
                else if (board[i][j]->getPlayerID() == 0)
                    neutralCount++;
            }
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
