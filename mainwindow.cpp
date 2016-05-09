#include "mainwindow.h"
#include <list>
#include "hexacell.h"
#include <iostream>

bool MainWindow::isInstanced = false;
MainWindow* MainWindow::singleton;

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param parent [description]
 */
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    isInstanced = true;
    //Background image
    this->setStyleSheet("background-image: url(./data/sci_fi-wallpaper-1366x768.jpg);");

    setContextMenuPolicy(Qt::NoContextMenu);

    started = false;
    this->start();
    selectedCell = nullptr;
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param e [description]
 */
void MainWindow::start()
{
    scene = new QGraphicsScene();
    gameView = new GameView(this);
    hexaCellBoard = new HexaCellBoard(this->scene);
    gameView->setScene(scene);
    gameView->setParent(this);

    hexaCellBoard->setupBoard(this->scene, "data/model1.txt");
    selectedCell = nullptr;
    ia = new IA(hexaCellBoard,2);

    startTimer(1000);   // 1/2-second timer
    started = true;
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param event [description]
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeClose())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 */
void MainWindow::restart()
{
    // clear some stuff then call start()

}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param event [description]
 */
void MainWindow::timerEvent(QTimerEvent *event)
{
    if(started)
    {
        this->hexaCellBoard->cellGrowing();
        //this->ia->action();
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param hc [description]
 */
void MainWindow::newSelectedCell(HexaCell *hc)
{
    if (selectedCell == nullptr && hc->getPlayerID() == 1)
    {
        std::cout<<"case selectionnee"<<std::endl;
        selectedCell = hc;
    }
    else if (selectedCell != nullptr)
    {

        std::cout<<"avant dijkstra"<<std::endl;
        list<HexaCell*> c = hexaCellBoard->dijkstra(selectedCell, hc, 1);
        std::cout<<"apres dijkstra"<<std::endl;

        if (!c.empty())
        {
            std::cout<<"liste non vide"<<std::endl;
            movePopulation(c,1);
        }
        else
        {
            std::cout<<"liste vide"<<std::endl;
        }
        selectedCell = nullptr;
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param cellPath [description]
 */
void MainWindow::movePopulation(std::list<HexaCell*> cellPath, int playerID )
{
    HexaCell* startCell = cellPath.front();
    HexaCell* endCell = cellPath.back();
    int popToMove = (startCell)->getPopulation() / 2;
    if (playerID != startCell->getPlayerID()){
        std::cout<<"Erreur, la cellule de départ n'appartient pas au player"<<std::endl;
        return;
    }
    if (endCell->getPlayerID() == playerID)
    {
        startCell->decPopulation(popToMove);
        endCell->incPopulation(popToMove);
    }
    else{
        if (endCell->getPopulation() > popToMove){
            startCell->decPopulation(popToMove);
            endCell->decPopulation(popToMove);
        }
        else{
            startCell->decPopulation(popToMove);
            endCell->setPopulation(popToMove - endCell->getPopulation());
            if (endCell->getPlayerID() == 1)
                hexaCellBoard->removePlayerCell(endCell);
            else if (endCell->getPlayerID() == 2)
                hexaCellBoard->removeBotCell(endCell);

            if (playerID == 1)
                hexaCellBoard->addPlayerCell(endCell);
            if (playerID == 2)
                hexaCellBoard->addBotCell(endCell);

            endCell->setPlayerID(playerID);
        }
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 * @return [description]
 */
bool MainWindow::maybeClose() //Confirm close event
{
   QMessageBox msgBox;
   QMessageBox::StandardButton ret;
   ret = QMessageBox::question(this,
                              tr("Bactaria"),
                              tr("Are you sure you want to leave this lovely game?"),
                              QMessageBox::Yes| QMessageBox::Cancel);
   msgBox.setStyleSheet("background-color: blue");
        if (ret == QMessageBox::Yes)
        {
            return true;
        }
        else if (ret == QMessageBox::Cancel)
        {
            return false;
        }
    return true;
}
