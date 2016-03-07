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
    void start();
    void restart();

    void timerEvent(QTimerEvent *event);

private:
    QGraphicsScene* scene;
    GameView*       gameView;
    HexaCellBoard*  hexaCellBoard;

    bool            started;
};

#endif // MAINWINDOW_H
