#include "gameview.h"
#include "hexacell.h"
#include "hexacellboard.h"
#include <math.h>
#include <iostream>

/**
 * @brief [Constructeur GameView]
 * @details [long description]
 * 
 * @param parent [Le widget parent]
 */
GameView::GameView(QWidget* parent)
{
    // set up the screen

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1366,768);
}
