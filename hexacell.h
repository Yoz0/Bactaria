#ifndef HEXACELL_H
#define HEXACELL_H
#include <QGraphicsPolygonItem>
#include <QColor>
#include <list>
#include <QRadialGradient>
#include <QtWidgets>

using namespace std;

enum CellType
{
    NORMAL = 0,
    FARM = 1
};

class HexaCell : public QGraphicsPolygonItem
{

private:
    int         indexLine;
    int         indexCol;
    int         playerId;
    CellType    type;
    int         population;
    bool        mouseHover;
    bool        highlight;
    bool        selected;

    list<HexaCell*> voisins;
    QGraphicsDropShadowEffect* effect;

public:
    static const int   hexaSize = 20;

    HexaCell( int i, int j, int pID, CellType ct, int pop );
    ~HexaCell();

    // Getter and setter
    int getIndexLine() const { return indexLine; }
    int getIndexColumn() const { return indexCol; }
    int getPlayerID() const { return playerId; }
    void setPlayerID(int id) { playerId = id; }
    CellType getCellType() const { return type; }
    int getPopulation() const { return population; }
    void setPopulation(int pop) { population = pop; }
    void incPopulation(int pop) { population += pop; }
    void decPopulation(int pop) { population -= pop; }
    list<HexaCell *> getVoisins() const { return voisins; }
    void setNewVoisin(HexaCell* v) { voisins.push_back(v); }
    void setHighlight(bool value){ highlight = value; update();}
    void setSelected(bool value){ selected = value; update();}

    //override methods
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    //GameAction
    void growing();
/*
signals:
    void rightClicked();
*/

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


};

#endif // HEXACELL_H
