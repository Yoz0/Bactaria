#include "mainwindow.h"
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