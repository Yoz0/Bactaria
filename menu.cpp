#include "menu.h"
#include "ui_menu.h"

/**
 * @brief [Constructeur Menu]
 * @details [Initialisatio..]
 * 
 * @param parent [description]
 * @param i [description]
 */
menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

/**
 * @brief [Destructeur Menu]
 * @details [long description]
 */
menu::~menu()
{
    delete ui;
}
