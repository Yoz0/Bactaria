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

public:
    static MainWindow* getInstance()
    {
        if(isInstanced==false)
        {
            singleton=new MainWindow();
            return singleton;
        }
        else
        {
            return singleton;
        }
    }

    void start();
    void restart();

    void timerEvent(QTimerEvent *event);

protected:
    void closeEvent(QCloseEvent *event);

private:
    QGraphicsScene* scene;
    GameView*       gameView;
    HexaCellBoard*  hexaCellBoard;

    static MainWindow*     singleton;
    static bool     isInstanced;


    bool            started;
    bool            maybeClose();

    MainWindow(QWidget *parent = 0);

};

#endif // MAINWINDOW_H