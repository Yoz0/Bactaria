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
    gameView = new GameView(this);
    gameView->setParent(this);
    isInstanced = true;
    //Background image
    this->setStyleSheet("background-image: url(./data/sci_fi-wallpaper-1366x768.jpg);");

    setContextMenuPolicy(Qt::NoContextMenu);

    started = false;
    this->start();
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

    gameView->setScene(scene);
    gameView->setParent(this);

    hexaCellBoard = new HexaCellBoard(this->scene);
    hexaCellBoard->setupBoard(this->scene, "data/model1.txt");

    selectedCell = nullptr;
    hoverCell = nullptr;

    ia = new IA(hexaCellBoard,2);

    timerSecond = startTimer(1000);
    timerFast = startTimer(100);
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

    std::cout<<"delete hexaCellBoard"<<std::endl;
    delete hexaCellBoard;
    std::cout<<"delete ia"<<std::endl;
    delete ia;
    std::cout<<"delete scene"<<std::endl;
    delete scene;
    started = false;
    std::cout<<"all delete successfull"<<std::endl;
    start();

}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param event [description]
 */
void MainWindow::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == timerSecond && started )
    {
        this->hexaCellBoard->cellGrowing();
        this->ia->action();
        int winner = this->hexaCellBoard->winTest();
        if (winner == 1)
            WinRestart();
        else if (winner == 2)
            LoseRestart();
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param hc [description]
 */
bool MainWindow::newSelectedCell(HexaCell *hc)
{
    if (selectedCell == nullptr && hc->getPlayerID() == 1)
    {
        std::cout<<"case selectionnee"<<std::endl;
        selectedCell = hc;
        return true;
    }
    else if (selectedCell != nullptr)
    {
        list<HexaCell*> c = hexaCellBoard->dijkstra(selectedCell, hc, 1);

        if (!c.empty())
        {
            movePopulation(c,1);
        }
        selectedCell->setSelected(false);
        selectedCell = nullptr;

        for( auto i : path )
        {
            i->setHighlight(false);
        }
        path.clear();

        return false;
    }
    return false;
}

void MainWindow::newHoverCell(HexaCell *hc)
{
    hoverCell = hc;
    if( selectedCell != nullptr )
    {
        list<HexaCell*> c = hexaCellBoard->dijkstra(selectedCell, hoverCell, 1);

        for( auto i : path )
        {
            i->setHighlight(false);
        }

        for( auto i : c )
        {
            i->setHighlight(true);
        }

        path = c;
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
    startCell->update();
    endCell->update();
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

bool MainWindow::WinRestart()
{
    QMessageBox msgBox;
    QMessageBox::StandardButton ret;
    QCloseEvent *event;
    ret = QMessageBox::question(this,
                               tr("Congratulations!"),
                               tr("You won! Play again?"),
                               QMessageBox::Yes| QMessageBox::No);
         if (ret == QMessageBox::Yes)
         {
             start();
         }
         else if (ret == QMessageBox::No)
         {
             closeEvent(event);

         }
}

bool MainWindow::LoseRestart()
{
    QMessageBox msgBox;
    QMessageBox::StandardButton ret;
    QCloseEvent *event;
    ret = QMessageBox::question(this,
                               tr("What a shame!"),
                               tr("You lost! Play again?"),
                               QMessageBox::Yes| QMessageBox::No);
         if (ret == QMessageBox::Yes)
         {
             restart();
         }
         else if (ret == QMessageBox::No)
         {
             closeEvent(event);
         }
}
