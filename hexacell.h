#ifndef HEXACELL_H
#define HEXACELL_H
#include <QGraphicsPolygonItem>
#include <QColor>

enum CellType
{
    normal = 0,
    farm = 1
};

class HexaCell : public QGraphicsPolygonItem
{
public:
    const int   hexaScale = 20;

    HexaCell( int x, int y, int pID, CellType ct );
    ~HexaCell();

    int getPosX() { return posX; }
    int getPosY() { return posX; }
    int getPlayerID() { return playerId; }
    void setPlayerID(int id) { playerId = id; }
    CellType getCellType() { return type; }
    void setCellType(CellType ct) { type = ct; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    CellType    type;
    int         playerId;
    int         posX;
    int         posY;

};

#endif // HEXACELL_H
