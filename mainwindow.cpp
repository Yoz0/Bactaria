#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene();
    gameView = new GameView(this);
    hexaCellBoard = new HexaCellBoard(this->scene);
    gameView->setScene(scene);
    gameView->setParent(this);
}
