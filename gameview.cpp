#include "gameview.h"
#include "hexacell.h"
#include "hexacellboard.h"
#include <math.h>

GameView::GameView(QWidget* parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void GameView::start()
{
    // initialize hexaboard

}


void GameView::restartGame()
{
    // clear some stuff then call start()

}
