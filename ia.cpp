#include "ia.h"
#include <iostream>
#include "mainwindow.h"
#include "hexacellboard.h"

/**
 * @brief This is the IA player
 * 
 * @param hcb a pointer to the playing HexaCellBoard
 * @param PID the player ID of the IA player (Should be 2)
 */
IA::IA(HexaCellBoard* hcb, int PID)
{
    playingBoard = hcb;
    myPID = PID;
}

/**
 * @brief Choose what to do as the IA
 * @details Currently, the IA find its bigger cell and move half the pop from that cell to the closer cell that's not his.
 * 
 */
void IA::action()
{
    HexaCell* startCell = biggestCell();
    list<HexaCell*> cellPath = closestCell(startCell);
    if ( ! cellPath.empty() )
        MainWindow::getInstance()->movePopulation(cellPath,myPID);
}

/**
 * @brief Find the biggest cell of the IA
 * @return a pointer to taht HexaCell
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
 * @brief Find the closest Cell of @stratCell that's not belonging to the IA
 * @param startCell a pointer to a HexaCell belonging to the IA
 * @return The path from @startCell to the closest Cell that's not belonging to the IA
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
