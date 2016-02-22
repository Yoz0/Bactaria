#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <list>

#include "hexacellboard.h"
#include "hexacell.h"

class Game: public QGraphicsView
{
    Q_OBJECT

public:
    // constructors
    Game(QWidget* parent=NULL);

    // events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);

    // get / set
    QGraphicsScene* getScene();
    HexaCellBoard*  getHexaBoard() { return hexaCellBoard; }

public slots:
    void start();
    void restartGame();

private:
    // private attributes
    QGraphicsScene*     scene;
    HexaCellBoard*      hexaCellBoard;
    std::list<int>      listOfPlayerId;

    // private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawNewHexaCell( HexaCell* hc );
};

#endif // GAME_H
