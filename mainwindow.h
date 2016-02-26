#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include "gameview.h"
#include "hexacellboard.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private:
    QGraphicsScene* scene;
    GameView*       gameView;
    HexaCellBoard*  hexaCellBoard;

};

#endif // MAINWINDOW_H
