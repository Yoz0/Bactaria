#include "mainwindow.h"
#include <list>
#include "hexacell.h"
#include "config.h"

bool MainWindow::isInstanced = false;
MainWindow* MainWindow::singleton;

/**
 * @brief This is the main widget
 * @param parent The parent of the widget, should be null
 */
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    gameView = new GameView(this);
    gameView->setParent(this);
    isInstanced = true;
    //Background image
    this->setStyleSheet(("background-image: url("+PATH_TO_IMAGE+");").c_str());

    setContextMenuPolicy(Qt::NoContextMenu);

    started = false;
    this->start();
}

/**
 * @brief Load all the things we need to play
 */
void MainWindow::start()
{
    scene = new QGraphicsScene();

    gameView->setScene(scene);
    gameView->setParent(this);

    hexaCellBoard = new HexaCellBoard(this->scene);
    hexaCellBoard->setupBoard(this->scene, PATH_TO_MODEL);

    selectedCell = nullptr;
    hoverCell = nullptr;

    ia = new IA(hexaCellBoard,2);

    timerMain = startTimer(MAINSPEED);
    timerIA = startTimer(IASPEED);
    started = true;
}

/**
 * @brief Catch the closeEvent.
 * @details Launch maybeClose() to ask the user if he really want to quit.
 * If so close the windows
 * 
 * @param event The close Event
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
 * @brief clear some stuff then call start()
 */
void MainWindow::restart()
{
    delete hexaCellBoard;
    delete ia;
    delete scene;
    started = false;
    start();
}

/**
 * @brief Catch the timerEvent
 * @details If the timeEvent is timerMain then grow the cell, and check if there is a winner
 * If the timerEvent is timerIA call ia->action()
 * @param event the timerEvent
 */
void MainWindow::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == timerMain && started )
    {
        this->hexaCellBoard->cellGrowing();
        int winner = this->hexaCellBoard->winTest();
        if (winner == 1)
            WinRestart();
        else if (winner == 2)
            LoseRestart();
    }
    if (event->timerId() == timerIA && started)
        this->ia->action();
}

/**
 * @brief Select a new Cell
 * @details If there isn't a selected Cell and the Cell belongs to the player, select that Cell
 * If there is already a selected Cell move the population from the previous selected cell to @hc
 * 
 * @param hc a pointer to the new selected Cell
 * @return true if hc is selected at the end false otherwise.
 */
bool MainWindow::newSelectedCell(HexaCell *hc)
{
    if (selectedCell == nullptr && hc->getPlayerID() == 1)
    {
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

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param hc [description]
 */
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
 * @brief Move half the population from the first Cell to the last Cell of cellPath
 * @details It should be noted that movePopulation() check wether it's legal to do that move before
 * 
 * @param cellPath a list of pointer to Hexacell, all HexaCell should be adjacent
 * @param playerID the Id of the player trying to do that move
 */
void MainWindow::movePopulation(std::list<HexaCell*> cellPath, int playerID )
{
    HexaCell* startCell = cellPath.front();
    HexaCell* endCell = cellPath.back();
    int popToMove = (startCell)->getPopulation() / 2;
    if (playerID != startCell->getPlayerID()){
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
 * @brief Demande de confirmation de quitter le jeu
 * @details
 * @return true (exit) or false (cancel)
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

/**
 * @brief Permet de choisir de rejouer en  cas de victoire
 * @details
 * @return relance le jeu ou quitte le jeu
 */
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

/**
 * @brief Permet de rejouer en  cas de défaite
 * @details
 * @return relance le jeu ou quitte le jeu
 */
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
