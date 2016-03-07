#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <list>

#include "hexacellboard.h"
#include "hexacell.h"

class GameView: public QGraphicsView
{
    Q_OBJECT

public:
    // constructors
    GameView(QWidget* parent=NULL);

private:

    // private methods
};

#endif // GAMEVIEW_H
