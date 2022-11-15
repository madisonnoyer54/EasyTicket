#include "technicienwidget.h"
#include "ui_technicienwidget.h"

TechnicienWidget::TechnicienWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TechnicienWidget)
{
    ui->setupUi(this);
    parent->layout()->addWidget(this);
}

TechnicienWidget::~TechnicienWidget()
{
    delete ui;
}

void TechnicienWidget::setGestionnaire(GestionnaireDialogue *gestionnaire) {
    this->gestionnaire = gestionnaire;
    gestionnaire->addObserveur(*this);
}

void TechnicienWidget::setTechnicien(Technicien *technicien) {
    this->technicien = technicien;

    // Ajout des catégories pour pouvoir test
    parentWidget()->setWindowTitle("EasyTicket - Technicien : " + technicien->getId());
    reagir();
}

void TechnicienWidget::on_fermerTicket_clicked()
{
    technicien->fermerTicket();
    gestionnaire->assignerTicket(technicien);
}

void TechnicienWidget::on_changeCategorie_clicked()
{
    Ticket &ticket = *technicien->getTicket();
    Categorie c = Categorie::assistance;

    if(ui->Logiciel->isChecked()) c = Categorie::logiciel;
    if(ui->Materiel->isChecked()) c = Categorie::materiel;
    if(ui->Securite->isChecked()) c = Categorie::securite;

    ticket.setCategorie(c);
    ticket.setTechnicien(nullptr);
    technicien->setTicket(nullptr);
    gestionnaire->assignerTicket(&ticket);
    gestionnaire->assignerTicket(technicien);
}

void TechnicienWidget::reagir() {
    if(technicien->getTicket() == nullptr) {
        ui->ticketName->setText("");
        ui->Assistance->setDisabled(true);
        ui->Logiciel->setDisabled(true);
        ui->Materiel->setDisabled(true);
        ui->Securite->setDisabled(true);
        ui->changeCategorie->setDisabled(true);
        ui->fermerTicket->setDisabled(true);
        ui->textMessage->setDisabled(true);
        ui->envoyer->setDisabled(true);
        ui->ticketInfo->setText("");
    } else {
        Ticket *ticket = technicien->getTicket();
        ui->ticketName->setText(ticket->getIdTicket());
        ui->ticketInfo->setText(ticket->getInformations());
        ui->Assistance->setEnabled(true);
        ui->Logiciel->setEnabled(true);
        ui->Materiel->setEnabled(true);
        ui->Securite->setEnabled(true);
        ui->changeCategorie->setEnabled(true);
        ui->fermerTicket->setEnabled(true);
        ui->textMessage->setEnabled(true);
        ui->envoyer->setEnabled(true);
        switch(ticket->getCategorie()) {
            case Categorie::assistance:
                    ui->Assistance->setChecked(true);
                break;
            case Categorie::logiciel:
                    ui->Logiciel->setChecked(true);
                break;
            case Categorie::materiel:
                    ui->Materiel->setChecked(true);
                break;
            case Categorie::securite:
                    ui->Securite->setChecked(true);
                break;
        }
    }
}


void TechnicienWidget::on_envoyer_clicked()
{
    ui->textMessage->setText("");
}

