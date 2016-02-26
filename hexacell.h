#ifndef HEXACELL_H
#define HEXACELL_H
#include <QGraphicsPolygonItem>
#include <QColor>

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
    int         population;
    CellType    type;

public:
    const int   hexaScale = 20;

    HexaCell( int i, int j, int pID, CellType ct=NORMAL, int pop=0 );
    ~HexaCell();

    // Getter and setter
    int getIndexLine() const { return indexLine; }
    int getIndexColumn() const { return indexCol; }
    int getPlayerID() const { return playerId; }
    void setPlayerID(int id) { playerId = id; }
    CellType getCellType() const { return type; }
    int getPopulation() const { return population; }
    void setPopulation(int pop) { population = pop; }

    //override methods
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // HEXACELL_H
