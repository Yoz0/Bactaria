#include "ia.h"
#include <iostream>
#include "mainwindow.h"

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param hcb [description]
 * @param PID [description]
 */
IA::IA(HexaCellBoard* hcb, int PID)
{
    playingBoard = hcb;
    myPID = PID;
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param startCell [description]
 */
void IA::action()
{
    HexaCell* startCell = biggestCell();
    list<HexaCell*> cellPath = closestCell(startCell);
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

/**
 * @brief [brief description]
 * @details [long description]
 * @return [description]
 */
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

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param startCell [description]
 * @return [description]
 */
list<HexaCell*> IA::closestCell(HexaCell* startCell)
{
    int i,j;
    HexaCell* currenthc;
    list<HexaCell*> currentlist;
    list<HexaCell*> smalllist;
    for(i = 0; i < playingBoard->getWidth(); i++ ){
        for(j = 0; j<playingBoard->getHeight(); j++){
            currenthc = playingBoard->getHexaCell(i,j);
            if (currenthc->getPlayerID() != myPID){
                currentlist = playingBoard->dijkstra(startCell, currenthc, myPID);
                if ( currentlist.empty()){
                    if ( !smalllist.empty() ){
                        smalllist = currentlist;
                    }
                    if (currentlist.size() < smalllist.size()){
                        smalllist = currentlist;
                    }
                }
            }
        }
    }
    return smalllist;
}
