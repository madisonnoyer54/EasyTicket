#include "dialogconnexion.h"
#include "ui_dialogconnexion.h"

DialogConnexion::DialogConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnexion)
{
    ui->setupUi(this);
    setWindowTitle("Connexion");
}

DialogConnexion::~DialogConnexion()
{
    delete ui;
}
