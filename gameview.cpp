#include "gameview.h"
#include "hexacell.h"
#include "hexacellboard.h"
#include <math.h>
#include <iostream>

GameView::GameView(QWidget* parent)
{
    // set up the screen
    /*
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    */
    setFixedSize(1024,768);
}
