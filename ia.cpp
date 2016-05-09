#include "ia.h"
#include <iostream>
#include "mainwindow.h"
#include "hexacellboard.h"

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
    std::cout<<"biggestCell()"<<std::endl;
    HexaCell* startCell = biggestCell();
    std::cout<<"cellPath()"<<std::endl;
    list<HexaCell*> cellPath = closestCell(startCell);
    std::cout<<"movePopulation()"<<std::endl;
    if ( ! cellPath.empty() )
        MainWindow::getInstance()->movePopulation(cellPath,myPID);
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
    HexaCell* bighc = nullptr;
    for(i = 0; i < playingBoard->getHeight(); i++ ){
        for(j = 0; j<playingBoard->getWidth(); j++){
            currenthc = playingBoard->getHexaCell(i,j);
            if (currenthc != nullptr){
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
    HexaCell* currenthc = nullptr;
    list<HexaCell*> currentlist;
    list<HexaCell*> smalllist;
    for(i = 0; i < playingBoard->getHeight(); i++ ){
        for(j = 0; j<playingBoard->getWidth(); j++){
            currenthc = playingBoard->getHexaCell(i,j);
            if (currenthc != nullptr){
                if (currenthc->getPlayerID() != myPID){
                    currentlist = playingBoard->dijkstra(startCell, currenthc, myPID);
                    if ( !currentlist.empty()){
                        if ( smalllist.empty() ){
                            smalllist = currentlist;
                        }
                        if (currentlist.size() < smalllist.size()){
                            smalllist = currentlist;
                        }
                    }
                }
            }
        }
    }
    return smalllist;
}
