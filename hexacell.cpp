#include "hexacell.h"
#include <iostream>
#include <QtWidgets>
#include <QRadialGradient>

using namespace std;

HexaCell::HexaCell( int i, int j, int pID, CellType ct=NORMAL, int pop=0 )
    : indexCol(i),
      indexLine(j),
      playerId(pID),
      type(ct),
      population(pop),
      mouseHover(false)
{
    QPolygonF pol;
    pol << QPointF( 1, 0 ) << QPointF( qreal(1.0/2), qreal(sqrt(3.0)/2) ) << QPointF( qreal(-1.0/2), qreal(sqrt(3.0)/2 ))
        << QPointF( -1, 0 ) << QPointF( qreal(-1.0/2), qreal(-sqrt(3.0)/2) ) << QPointF( qreal(1.0/2), qreal(-sqrt(3.0)/2) );
    for (size_t i = 0, n = pol.size(); i < n; ++i){
        pol[i] = pol[i] * this->hexaSize;
    }
    this->setPolygon( pol );

    //Allows mouse events
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10);
    effect->setColor(QColor(0,0,0,1));
    effect->setOffset(QPointF(5,5));
    setGraphicsEffect(effect);
}

HexaCell::~HexaCell()
{

}

QPainterPath HexaCell::shape() const
{
    QPainterPath path;
    path.addPolygon( this->polygon() );
    return path;
}

void HexaCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    //SetPen for painter
    QPen p;
    p.setStyle(Qt::SolidLine);
    p.setWidth(1);
    p.setBrush(Qt::black);
    p.setCapStyle(Qt::SquareCap);
    p.setJoinStyle(Qt::MiterJoin);
    painter->setPen(p);

    //SetBrush for painter
    QColor color(60, 60, 170);
    QRadialGradient gradient( 2, 2, 30, 2, 2);
    color = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if ( option->state & QStyle::State_MouseOver )
        gradient.setColorAt(0, color.light(170));
    else
        gradient.setColorAt(0, color);
    gradient.setColorAt(1, QColor::fromRgbF(0,0,0,1));
    QBrush b(gradient);
    painter->setBrush(b);
    painter->drawPolygon(this->polygon());
}

void HexaCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    this->update();
}

void HexaCell::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    this->update();
}

void HexaCell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    this->update();
}

