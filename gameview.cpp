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

    // set up the scene
    this->scene = new QGraphicsScene();
    this->scene->setSceneRect(0,0,1024,768);
    this->setScene(scene);

    // set up the model
    this->gameModel = new GameModel();
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
    HexaCell* testCell = new HexaCell(100, 100, 1, farm);

    // clear the screen
    scene->clear();
   // this->drawNewHexaCell(testCell);

}

void GameView::drawNewHexaCell(HexaCell* hc, int pos_x, int pos_y)
{
    QPolygonF pol;
    int SCALE_BY = 20;
    //pol << QPointF( 1, 0 ) << QPointF( 2, 0 ) << QPointF( 3, 1 ) << QPointF( 2, 2 ) << QPointF( 1, 2 ) << QPointF( 0, 1 );
    pol << QPointF( 1, 0 ) << QPointF( qreal(1.0/2), qreal(sqrt(3.0)/2) ) << QPointF( qreal(-1.0/2), qreal(sqrt(3.0)/2 ))
        << QPointF( -1, 0 ) << QPointF( qreal(-1.0/2), qreal(-sqrt(3.0)/2) ) << QPointF( qreal(1.0/2), qreal(-sqrt(3.0)/2) );


    for (size_t i = 0, n = pol.size(); i < n; ++i){
        pol[i] = pol[i] * SCALE_BY;
    }

    pol.translate( QPointF(pos_x, pos_y) );
    this->scene->addPolygon(pol);
}

void GameView::drawNewHexaCellBoard()
{
    for (int i = 0; i < gameModel->getWidthHexaCellBoard(); i ++)
    {
        for (int j = 0; j < gameModel->getHeightHexaCellBoard(); j ++)
        {

            drawNewHexaCell(gameModel->getHexaCell(i,j), ecart + sqrt(3.0)/2 * hexaScale * j,0);
         }
    }
}

void GameView::restartGame()
{
    // clear some stuff then call start()

    scene->clear();
    start();
}
