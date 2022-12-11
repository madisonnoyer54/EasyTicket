#include "administrateurwidget.h"
#include "ui_administrateurwidget.h"

AdministrateurWidget::AdministrateurWidget(Administrateur &admin, GestionnaireDialogue &gestionnaire, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministrateurWidget),
    gestionnaire(gestionnaire)
{
    ui->setupUi(this);
    ui->name->setText(admin.getId());

    reagir();
}

AdministrateurWidget::~AdministrateurWidget()
{
    delete ui;
}

void AdministrateurWidget::on_assistance_clicked()
{
    reagir();
}


void AdministrateurWidget::on_logiciel_clicked()
{
    reagir();
}


void AdministrateurWidget::on_materiel_clicked()
{
    reagir();
}


void AdministrateurWidget::on_securite_clicked()
{
    reagir();
}


void AdministrateurWidget::on_dateAvant_userDateChanged(const QDate &date)
{
    std::ignore = date;
    reagir();
}


void AdministrateurWidget::on_dateApres_userDateChanged(const QDate &date)
{
    std::ignore = date;
    reagir();
}

void AdministrateurWidget::reagir() {
    QDate debut = ui->dateAvant->date();
    QDate fin = ui->dateApres->date();

    int nbTicket = gestionnaire.getNbTicket(debut, fin);
    ui->nbTicket->setText("Nombre de ticket : " + QString::number(nbTicket));

    if(nbTicket != 0) {
        ui->nbTicketOuvert->setText("Pourcentage de ticket ouvert " + QString::number((float)gestionnaire.getNbTicketFerme(debut, fin) / (float) nbTicket * 100) + "%");
        ui->nbTicketEnTraitement->setText("Pourcentage de ticket en traitement " + QString::number((float)gestionnaire.getNbTicketTraitement(debut, fin) / (float) nbTicket * 100) + "%");
    } else {
        ui->nbTicketOuvert->setText("Pourcentage de ticket ouvert 0%");
                ui->nbTicketEnTraitement->setText("Pourcentage de ticket en traitement 0%");
    }

    Categorie c = Categorie::assistance;
    if (ui->securite->isChecked()) c = Categorie::securite;
    else if (ui->materiel->isChecked()) c = Categorie::materiel;
    else if (ui->logiciel->isChecked()) c = Categorie::logiciel;

    int nbTicketCateg = gestionnaire.getNbTicket(c, debut, fin);
    ui->nbTicketCateg->setText("Nombre de ticket dans la catégorie " + categorie_to_str(c) + " : " + QString::number(nbTicketCateg));
    ui->nbTech->setText("Nombre de Technicien : " + QString::number(gestionnaire.getNbTechnicien(c)));
    if(nbTicketCateg != 0) {
        ui->nbTicketOuvertCateg->setText("Pourcentage de ticket ouvert dans la catégorie " + categorie_to_str(c) + " : " + QString::number((float)gestionnaire.getNbTicketFerme(c, debut, fin) / (float) nbTicketCateg * 100) + "%");
        ui->nbTraitementCateg->setText("Pourcentage de ticket en traitement dans la catégorie " + categorie_to_str(c) + " : " + QString::number((float)gestionnaire.getNbTicketTraitement(c, debut, fin) / (float) nbTicketCateg * 100) + "%");
    } else {
        ui->nbTicketOuvertCateg->setText("Pourcentage de ticket ouvert dans la catégorie " + categorie_to_str(c) + " : 0%");
        ui->nbTraitementCateg->setText("Pourcentage de ticket en traitement dans la catégorie " + categorie_to_str(c) + " : 0%");
    }
}
