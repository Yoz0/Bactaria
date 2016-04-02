#include "ia.h"
#include <iostream>
#include "mainwindow.h"
IA::IA(HexaCellBoard* hcb, int PID)
{
    playingBoard = hcb;
    myPID = PID;
}

void IA::action()
{
    HexaCell* startCell = biggestCell();
    list<HexaCell*>* cellPath = closestCell(startCell);
    /*
    if (cellPath==nullptr){
        std::cout<<"List is empty !"<<std::endl;
    }
    else {
        std::cout<<"List is not empty ! "<<cellPath->front()<<std::endl;
    }
    */
    //HexaCell* lastCell = cellPath->back();
    MainWindow::getInstance()->movePopulation(cellPath);
    //std::cout<<"startCell : "<<startCell->getIndexLine()<<" ; "<<startCell->getIndexColumn()<<" lastCell : "<<lastCell->getIndexLine()<<" ; "<<lastCell->getIndexColumn()<<std::endl;
}

HexaCell* IA::biggestCell()
{
    int i,j;
    HexaCell* currenthc;
    HexaCell* bighc;
    std::cout<<"pass"<<std::endl;
    for(i = 0; i < playingBoard->getWidth(); i++ ){
        for(j = 0; j<playingBoard->getHeight(); j++){
            currenthc = playingBoard->getHexaCell(i,j);
            if (currenthc->getPlayerID() == myPID){
                if (bighc == nullptr ){
                    bighc = currenthc;
                }
                if (bighc->getPopulation() < currenthc->getPopulation()){
                    bighc = currenthc;
                }
            }
        }
    }
    return bighc;
}

list<HexaCell*>* IA::closestCell(HexaCell* startCell)
{
    int i,j;
    HexaCell* currenthc;
    list<HexaCell*>* currentlist;
    list<HexaCell*>* smalllist;
    for(i = 0; i < playingBoard->getWidth(); i++ ){
        for(j = 0; j<playingBoard->getHeight(); j++){
            currenthc = playingBoard->getHexaCell(i,j);
            if (currenthc->getPlayerID() != myPID){
                currentlist = playingBoard->dijkstra(startCell, currenthc, myPID);
                if (currentlist != nullptr){
                    if (smalllist == nullptr ){
                        smalllist = currentlist;
                    }
                    if (currentlist->size() < smalllist->size()){
                        smalllist = currentlist;
                    }
                }
            }
        }
    }
    return smalllist;
}