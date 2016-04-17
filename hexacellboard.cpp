#include "hexacellboard.h"

#include <queue>
#include <math.h>
#include <string>
#include <iostream>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QIODevice>
#include <QTextStream>
#include "mainwindow.h"

HexaCellBoard::HexaCellBoard(QGraphicsScene* scene)
{
    //width= 4;
    //height = 4;
}

HexaCellBoard::~HexaCellBoard()
{

}

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
    width = list.at(0).toInt();
    height = list.at(1).toInt();

    // on resize board
    this->board.resize(width);
    for(int i=0; i<board.size(); i++)
        board[i].resize(height);

    // on lit chaque ligne
    while (!in.atEnd()) {
        line = in.readLine();
        list = line.split(' ');

        HexaCell* hc = new HexaCell(list.at(0).toInt(),
                                    list.at(1).toInt(),
                                    list.at(2).toInt(),
                                    static_cast<CellType>( list.at(3).toInt() ),
                                    list.at(4).toInt());
        hc->setPos(hc->hexaSize*3/2*list.at(0).toInt(),hc->hexaSize*sqrt(3.0)*(list.at(0).toInt()/2.0+list.at(1).toInt()));
        scene->addItem(hc);
        board[list.at(0).toInt()][list.at(1).toInt()] = hc;
        playerCells.push_back(hc);
    }

    // Les voisins de chaques hexacell
    for(int i = 0 ; i < width ; i ++)
    {
        for(int j = 0 ; j < height ; j ++)
        {
            if( board[i][j] != nullptr )
            {
                if( i-1 >= 0 && board[i-1][j] != nullptr ) // i-1 j
                    board[i][j]->setNewVoisin( board[i-1][j] );

                if( j-1 >= 0 && board[i][j-1] != nullptr ) // i j-1
                    board[i][j]->setNewVoisin( board[i][j-1] );

                if ( i+1 < width && j-1 >= 0 && board[i+1][j-1] != nullptr ) // i+1 j-1
                    board[i][j]->setNewVoisin( board[i+1][j-1] );

                if ( i+1 < width && board[i+1][j] != nullptr ) // i+1 j
                    board[i][j]->setNewVoisin( board[i+1][j] );

                if ( j+1 < height && board[i][j+1] != nullptr ) // i j+1
                    board[i][j]->setNewVoisin( board[i][j+1] );

                if ( i-1 >= 0 && j+1 < height && board[i-1][j+1] != nullptr) // i-1 j+1
                    board[i][j]->setNewVoisin( board[i-1][j+1] );
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
            //todo: dernier pas forcèment du même idée
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
