#include "game.h"
#include "hexacell.h"
#include "hexacellboard.h"
#include <math.h>

Game::Game(QWidget* parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    this->scene = new QGraphicsScene();
    this->scene->setSceneRect(0,0,1024,768);
    this->setScene(scene);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void Game::start()
{
    // initialize hexaboard
    HexaCell* testCell = new HexaCell(100, 100, 1, farm);

    // clear the screen
    scene->clear();
    this->drawNewHexaCell(testCell);

}

void Game::drawNewHexaCell(HexaCell* hc)
{
    QPolygonF pol;
    //pol << QPointF( 1, 0 ) << QPointF( 2, 0 ) << QPointF( 3, 1 ) << QPointF( 2, 2 ) << QPointF( 1, 2 ) << QPointF( 0, 1 );
    pol << QPointF( 1, 0 ) << QPointF( qreal(1/2), qreal(sqrt(3)/2) ) << QPointF( qreal(-1/2), qreal(sqrt(3)/2 ))
        << QPointF( -1, 0 ) << QPointF( qreal(-1/2), qreal(-sqrt(3)/2) ) << QPointF( qreal(1/2), qreal(-sqrt(3)/2) );

    int SCALE_BY = 10;
    for (size_t i = 0, n = pol.size(); i < n; ++i){
        pol[i] = pol[i] * SCALE_BY;
    }

    pol.translate( QPointF(hc->getPosX(), hc->getPosY()) );
    this->scene->addPolygon(pol);
}

void Game::restartGame()
{
    // clear some stuff then call start()

    scene->clear();
    start();
}
