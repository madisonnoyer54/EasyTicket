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

void DialogConnexion::on_pushButton_clicked()
{
    ClientWindow *window = new ClientWindow(parentWidget());
    window->show();
    close();
}

void DialogConnexion::on_IdentificationClient_clicked()
{
    Technicienwindow *window = new Technicienwindow(parentWidget());
    window->show();
    close();
}
