#include <QApplication>

#include "gameview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameView* game = new GameView();
    game->show();
    game->start();

    return a.exec();
}
