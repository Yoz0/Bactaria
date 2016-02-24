#include "hexacell.h"
#include <QtWidgets>

HexaCell::HexaCell( int x, int y, int pID, CellType ct )
 : posX(x),
   posY(y),
   playerId(pID),
   type(ct)
{

}

QRectF HexaCell::boundingRect() const
{
    return QRectF(0,0,2*hexaScale, sqrt(3.0)*hexaScale);
}

QPainterPath HexaCell::shape() const
{
    QPainterPath path;
    QPolygonF pol;
    pol << QPointF( 1, 0 ) << QPointF( qreal(1.0/2), qreal(sqrt(3.0)/2) ) << QPointF( qreal(-1.0/2), qreal(sqrt(3.0)/2 ))
        << QPointF( -1, 0 ) << QPointF( qreal(-1.0/2), qreal(-sqrt(3.0)/2) ) << QPointF( qreal(1.0/2), qreal(-sqrt(3.0)/2) );
    path.addPolygon(pol);
    return path;
}

void HexaCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->drawRoundedRect(-100,-100,20,20,5,5);
}

