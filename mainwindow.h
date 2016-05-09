#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QMessageBox>
#include "gameview.h"
#include "hexacellboard.h"
#include "ia.h"

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

    bool newSelectedCell(HexaCell* hc);
    void newHoverCell(HexaCell* hc);

    void movePopulation(list<HexaCell*> cellPath, int playerID );
    bool LoseRestart();
    bool WinRestart();

protected:
    void closeEvent(QCloseEvent *event);

private:
    QGraphicsScene* scene;
    GameView*       gameView;
    HexaCellBoard*  hexaCellBoard;
    HexaCell*       selectedCell;
    HexaCell*       hoverCell;
    list<HexaCell*> path;
    IA*             ia;

    static MainWindow*     singleton;
    static bool     isInstanced;


    bool            started;
    bool            maybeClose();

    int timerMain;
    int timerIA;

    MainWindow(QWidget *parent = 0);

};

#endif // MAINWINDOW_H
