#include "mainwindow.h"
#include <list>
#include "hexacell.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    isInstanced = true;
    //Background image
    this->setStyleSheet("background-color: white");
                //"background-image:url(\"background.jpg\"); background-position: center;"
                //background-image: url(:Bactaria/background.jpg; background-position: center;  A CONTINUER en changeant taille de la fenêtre aussi

    started = false;
    this->start();
}

void MainWindow::start()
{
    scene = new QGraphicsScene();
    gameView = new GameView(this);
    hexaCellBoard = new HexaCellBoard(this->scene);
    gameView->setScene(scene);
    gameView->setParent(this);
    hexaCellBoard->setupBoard(this->scene);
    selectedCell = nullptr;

    startTimer(500);   // 1/2-second timer
    started = true;
}

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

void MainWindow::restart()
{
    // clear some stuff then call start()

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(started)
    {
        this->hexaCellBoard->cellGrowing();
    }
}

void MainWindow::newSelectedCell(HexaCell *hc)
{
    if (selectedCell == nullptr && hc->getPlayerID() == 0)
    {
        std::cout<<"case selectionnee"<<std::endl;
        selectedCell = hc;
    }
    else if (selectedCell != nullptr)
    {

        std::cout<<"avant dijkstra"<<std::endl;
        list<HexaCell*>* c = hexaCellBoard->dijkstra(selectedCell, hc, 0);

        if (c != nullptr)
        {
            std::cout<<"pointeur non nul"<<std::endl;
            movePopulation( c );
        }
        else
        {
        std::cout<<"nul"<<std::endl;
        }

        selectedCell = nullptr;
    }
}

void MainWindow::movePopulation(std::list<HexaCell*>* cellPath )
{
    int popToMove = (cellPath->front())->getPopulation() / 2;
    (cellPath->back())->setPopulation((cellPath->back())->getPopulation() - popToMove);
    (cellPath->front())->setPopulation((cellPath->front())->getPopulation() + popToMove);
}

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

bool MainWindow::isInstanced = false;
MainWindow* MainWindow::singleton;
