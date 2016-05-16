#include "hexacell.h"
#include "mainwindow.h"
#include <iostream>
#include <QtWidgets>
#include <QRadialGradient>

using namespace std;

/**
 * @brief Constructeur HexaCell
 * 
 * @param i Index colonne
 * @param j Index ligne
 * @param pID ID joueur
 * @param ct Type de cellule
 * @param pop Population de départ
 */
HexaCell::HexaCell( int i, int j, int pID, CellType ct=NORMAL, int pop=0 )
    : indexLine(i),
      indexCol(j),
      playerId(pID),
      type(ct),
      population(pop),
      mouseHover(false),
      highlight(false),
      selected(false)
{
    QPolygonF pol;
    pol << QPointF( 1, 0 ) << QPointF( qreal(1.0/2), qreal(sqrt(3.0)/2) ) << QPointF( qreal(-1.0/2), qreal(sqrt(3.0)/2 ))
        << QPointF( -1, 0 ) << QPointF( qreal(-1.0/2), qreal(-sqrt(3.0)/2) ) << QPointF( qreal(1.0/2), qreal(-sqrt(3.0)/2) );
    for (size_t i = 0, n = pol.size(); i < n; ++i){
        pol[i] = pol[i] * this->hexaSize;
    }
    this->setPolygon( pol );

    //Allows mouse events
    setFlags(ItemIsSelectable | ItemIsFocusable );
    setAcceptHoverEvents(true);

    effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10);
    effect->setColor(QColor(0,0,0,1));
    effect->setOffset(QPointF(5,5));
    setGraphicsEffect(effect);
}

/**
 * @brief Destructeur HexaCell
 */
HexaCell::~HexaCell()
{
    for(auto i : voisins)
    {
        delete i;
        i = nullptr;
    }
    voisins.clear();

    delete effect;
}

/**
 * @brief Méthode shape, renvoie la forme de la cellule
 * @return retourne un QPainterPath
 */
QPainterPath HexaCell::shape() const
{
    QPainterPath path;
    path.addPolygon( this->polygon() );
    return path;
}

/**
 * @brief Méthode Paint, dessine la Cellule
 * 
 * @param painter [description]
 * @param option [description]
 * @param widget [description]
 */
void HexaCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    //SetPen for painter
    QPen p;
    p.setStyle(Qt::SolidLine);
    p.setWidth(2);
    if(selected)
    {
        p.setBrush(Qt::yellow);
        this->setZValue(2);
    }
    else
    {
        p.setBrush(Qt::black);
        this->setZValue(1);
    }
    p.setCapStyle(Qt::SquareCap);
    p.setJoinStyle(Qt::MiterJoin);
    painter->setPen(p);

    //SetBrush for painter
    QColor color;
    switch(playerId)
    {
    case 0:
        color = QColor(251,253,248);
        break;
    case 1:
        color = QColor(70,109,150);
        break;
    case 2:
        color = QColor(208,107,103);
        break;
    default:
        cerr << "Error hexacell.cpp : paint playerID";

    }

    if( highlight )
        color = QColor(239,235,18);

    QRadialGradient gradient( 2, 2, 30, 2, 2);
    //color = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    //if ( option->state & QStyle::State_MouseOver )
    if ( mouseHover == true )
        gradient.setColorAt(0, color.light(170));
    else
        gradient.setColorAt(0, color);
    gradient.setColorAt(1, QColor::fromRgbF(0,0,0,1));
    QBrush b(gradient);
    painter->setBrush(b);
    painter->drawPolygon(this->polygon());

    //Population Text
    //if( option->state & QStyle::State_MouseOver )
    painter->drawText( this->boundingRect(), Qt::AlignCenter, QString::number( this->population ) );
}

/**
 * @brief Fait grossir la population de la cellule
 */
void HexaCell::growing()
{
    this->population+= 1;
    this->update();
}

/**
 * @brief S'active quand on clique sur la cellule, appelle MainWindow::newSelectedCell
 * 
 */
void HexaCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    selected = MainWindow::getInstance()->newSelectedCell(this);
    this->update();
}

/**
 * @brief S'active quand on passe la souris sur la cellule, illumine la case
 *
 */
void HexaCell::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    MainWindow::getInstance()->newHoverCell(this);
    mouseHover = true;
    this->update();
}

/**
 * @brief S'active quand on enlève la souris de la cellule, dé-illumine la case.
 *
 */
void HexaCell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mouseHover = false;
    this->update();
}
