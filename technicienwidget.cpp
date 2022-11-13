#include "technicienwidget.h"
#include "ui_technicienwidget.h"

TechnicienWidget::TechnicienWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TechnicienWidget)
{
    ui->setupUi(this);
}

TechnicienWidget::~TechnicienWidget()
{
    delete ui;
}

void TechnicienWidget::setGestionnaire(GestionnaireDialogue *gestionnaire) {
    this->gestionnaire = gestionnaire;
}

void TechnicienWidget::setTechnicien(Technicien *technicien) {
    this->technicien = technicien;

    // Ajout des catégories pour pouvoir test

    technicien->addCategorie(Categorie::assistance);
    technicien->addCategorie(Categorie::materiel);
    technicien->addCategorie(Categorie::securite);
    technicien->addCategorie(Categorie::logiciel);
    gestionnaire->assignerTicket(technicien);
    reagir();
}

void TechnicienWidget::on_fermerTicket_clicked()
{
    technicien->fermerTicket();
    gestionnaire->assignerTicket(technicien);
    reagir();
    std::cout << "----- Apres fermeture ---- \n" << *gestionnaire;
}

void TechnicienWidget::reagir() {
    if(technicien->getTicket() == nullptr) {
        ui->fermerTicket->setDisabled(true);
        ui->ticketName->setText("");
        ui->ticketInfo->setText("");
    } else {
        Ticket *ticket = technicien->getTicket();
        ui->ticketName->setText(ticket->getIdTicket());
        ui->ticketInfo->setText(ticket->getInformations());
    }
}
