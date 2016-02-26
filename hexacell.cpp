#include "hexacell.h"
#include <QtWidgets>

HexaCell::HexaCell( int i, int j, int pID, CellType ct=NORMAL, int pop=0 )
    : indexCol(i),
      indexLine(j),
      playerId(pID),
      type(ct),
      population(pop)
{
    QPolygonF pol;
    pol << QPointF( 1, 0 ) << QPointF( qreal(1.0/2), qreal(sqrt(3.0)/2) ) << QPointF( qreal(-1.0/2), qreal(sqrt(3.0)/2 ))
        << QPointF( -1, 0 ) << QPointF( qreal(-1.0/2), qreal(-sqrt(3.0)/2) ) << QPointF( qreal(1.0/2), qreal(-sqrt(3.0)/2) );
    this->setPolygon( pol );
}

QPainterPath HexaCell::shape() const
{
    QPainterPath path;
    path.addPolygon( this->polygon() );
    return path;
}

void HexaCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->drawRoundedRect(-10,-10,20,20,5,5);
}

