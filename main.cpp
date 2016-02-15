#include "mainwindow.h"
#include <QApplication>
#include "cell.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
    int n = 10 ;
    Cell grille[n][n];
    for(int i = 0; i < n ;i++){
        for(int j = 0; j < n; j++){
            grille[i][j] = Cell(i,j,10,1);
            grille[i][j].afficher_console();
        }
    }
    return 0;
}
