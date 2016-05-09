#include "hexacell.h"
#include "mainwindow.h"
#include <iostream>
#include <QtWidgets>
#include <QRadialGradient>

using namespace std;

/**
 * @brief [Constructeur HexaCell]
 * @details [long description]
 * 
 * @param i [Index colonne]
 * @param j [Index ligne]
 * @param pID [ID joueu]r
 * @param ct [Type de cellule]
 * @param pop [Population de départ]
 */
HexaCell::HexaCell( int i, int j, int pID, CellType ct=NORMAL, int pop=0 )
    : indexLine(i),
      indexCol(j),
      playerId(pID),
      type(ct),
      population(pop),
      mouseHover(false),
      highlight(false)
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

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10);
    effect->setColor(QColor(0,0,0,1));
    effect->setOffset(QPointF(5,5));
    setGraphicsEffect(effect);

}

/**
 * @brief [Destructeur HexaCell]
 * @details [long description]
 */
HexaCell::~HexaCell()
{

}

/**
 * @brief [Méthode shape]
 * @details [long description]
 * @return [retourne un QPainterPath]
 */
QPainterPath HexaCell::shape() const
{
    QPainterPath path;
    path.addPolygon( this->polygon() );
    return path;
}

/**
 * @brief [brief description]
 * @details [long description]
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
        std::cerr << "Error hexacell.cpp : paint playerID";

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
 * @brief [brief description]
 * @details [long description]
 */
void HexaCell::growing()
{
    this->population+= 1;
    this->update();
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param event [description]
 */
void HexaCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    selected = MainWindow::getInstance()->newSelectedCell(this);
    this->update();
}

void HexaCell::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    MainWindow::getInstance()->newHoverCell(this);
    mouseHover = true;
    this->update();
}

void HexaCell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mouseHover = false;
    this->update();
}

/*
void HexaCell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        int factArg = 0;
                int fact(1);
                factArg = QInputDialog::getInt(0, "Factorial Calculator",
                    "Factorial of:", 1);
                int i=2;
                while (i <= factArg) {
                    fact = fact * i;
                    ++i;
                }


                    QString response = QString("The factorial of %1 is %2.\n%3")
                        .arg(factArg).arg(fact)
                        .arg("Compute another factorial?");
                    QMessageBox msgBox;
                    QFont font; font.setBold(true);
                    msgBox.setFont(font);
                    QMessageBox::StandardButton ret;
                    ret = QMessageBox::question(0, "Play again?", response,
                        QMessageBox::Save | QMessageBox::No);



        QMessageBox msgBox;
        QPushButton *more_bact_Button = msgBox.addButton(QObject::tr("Add"), QMessageBox::ActionRole);
        QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);
        QMessageBox::StandardButton box;
        msgBox.setText("You right-clicked");
        msgBox.exec();
        if (msgBox.clickedButton() == more_bact_Button)
        {

        }

    }
    //else if (event->button() == Qt::LeftButton)
    //QGraphicsItem::mouseReleaseEvent(event);
    //this->update();
}
*/
