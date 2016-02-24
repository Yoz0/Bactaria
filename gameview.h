#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <list>

#include "hexacellboard.h"
#include "hexacell.h"
#include "gamemodel.h"

class GameView: public QGraphicsView
{
    Q_OBJECT

public:
    // constructors
    GameView(QWidget* parent=NULL);

    // events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);

    // get / set
    QGraphicsScene* getScene();

public slots:
    void start();
    void restartGame();

private:
    // private attributes
    QGraphicsScene*     scene;
    GameModel*          gameModel;
    int ecart = 100;


    // private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawNewHexaCell(HexaCell* hc, int pos_x, int pos_y);
    void drawNewHexaCellBoard();

};

#endif // GAMEVIEW_H
