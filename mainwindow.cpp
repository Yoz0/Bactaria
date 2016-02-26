#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene();
    gameView = new GameView(this);
}
