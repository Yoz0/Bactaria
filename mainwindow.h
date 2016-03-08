#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QMessageBox>
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

protected:
    void closeEvent(QCloseEvent *event);

private:
    QGraphicsScene* scene;
    GameView*       gameView;
    HexaCellBoard*  hexaCellBoard;

    bool            started;
    bool            maybeClose();
};

#endif // MAINWINDOW_H
