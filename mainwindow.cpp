#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
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
