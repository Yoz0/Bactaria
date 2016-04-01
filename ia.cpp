#include "ia.h"
#include <iostream>
IA::IA(HexaCellBoard* hcb, int PID)
{
    playingBoard = hcb;
    myPID = PID;
}

void IA::action()
{
    HexaCell* startCell = biggestCell();
    HexaCell* endCell = closestCell(startCell);
    //TODO: launch the action of moving the bactiara from to startCell to endCell
    std::cout<<"startCell : "<<startCell->getIndexLine()<<" ; "<<startCell->getIndexColumn()<<
               "\n endCell : "<<endCell->getIndexLine()<<" ; "<<endCell->getIndexColumn()<<std::endl;
}

HexaCell* IA::biggestCell()
{
    int i,j;
    HexaCell* currenthc;
    HexaCell* bighc;
    for(i = 0; i < playingBoard->getWidth(); i++ ){
        for(j = 0; j<playingBoard->getHeight(); j++){
            currenthc = playingBoard->getHexaCell(i,j);
            if (currenthc->getPlayerID() == myPID){
                if (bighc == NULL ){
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

HexaCell* IA::closestCell(HexaCell* startCell)
{
    int i,j;
    HexaCell* currenthc;
    HexaCell* closehc;
    list<HexaCell*> currentlist, smalllist;
    for(i = 0; i < playingBoard->getWidth(); i++ ){
        for(j = 0; j<playingBoard->getHeight(); j++){
            currenthc = playingBoard->getHexaCell(i,j);
            currentlist = playingBoard->dijkstra(startCell, currenthc, myPID);
            if (currentlist != nullptr){
                if (smalllist == nullptr ){
                    smalllist = currentlist;
                    closehc = currenthc;
                }
                if (currentlist.size() < smalllist.size()){
                    smalllist = currentlist;
                    closehc = currenthc;
                }
            }
        }
    }
    return closehc;
}
