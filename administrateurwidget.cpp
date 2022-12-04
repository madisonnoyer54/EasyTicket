#include "administrateurwidget.h"
#include "ui_administrateurwidget.h"

AdministrateurWidget::AdministrateurWidget(Administrateur &admin, GestionnaireDialogue &gestionnaire, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministrateurWidget),
    gestionnaire(gestionnaire)
{
    ui->setupUi(this);
    ui->name->setText(admin.getId());

    int nbTicket = gestionnaire.getNbTicket();
    ui->nbTicket->setText(ui->nbTicket->text() + " " + QString::number(nbTicket));
    ui->nbTicketOuvert->setText(ui->nbTicketOuvert->text() + " " + QString::number((float)gestionnaire.getNbTicketFerme() / (float) nbTicket * 100) + "%");
    on_assistance_clicked();
}

AdministrateurWidget::~AdministrateurWidget()
{
    delete ui;
}

void AdministrateurWidget::on_assistance_clicked()
{
    ui->nbTicketCateg->setText("Nombre de ticket dans la catégorie Assistance : " + QString::number(gestionnaire.getNbTicket(Categorie::assistance)));
}


void AdministrateurWidget::on_logiciel_clicked()
{
    ui->nbTicketCateg->setText("Nombre de ticket dans la catégorie Logiciel : " + QString::number(gestionnaire.getNbTicket(Categorie::logiciel)));
}


void AdministrateurWidget::on_materiel_clicked()
{
    ui->nbTicketCateg->setText("Nombre de ticket dans la catégorie Materiel : " + QString::number(gestionnaire.getNbTicket(Categorie::materiel)));
}


void AdministrateurWidget::on_securite_clicked()
{
    ui->nbTicketCateg->setText("Nombre de ticket dans la catégorie Securite : " + QString::number(gestionnaire.getNbTicket(Categorie::securite)));
}

