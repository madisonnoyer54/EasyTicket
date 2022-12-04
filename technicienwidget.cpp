#include "technicienwidget.h"
#include "ui_technicienwidget.h"

TechnicienWidget::TechnicienWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TechnicienWidget)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
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
}

void TechnicienWidget::on_fermerTicket_clicked()
{
    gestionnaire->fermerTicket(*technicien->getTicket());
    technicien->fermerTicket();
    gestionnaire->assignerTicket(technicien);
    reagir();
}

void TechnicienWidget::on_changeCategorie_clicked()
{
    Ticket &ticket = *technicien->getTicket();
    Categorie c = Categorie::assistance;

    if(ui->Logiciel->isChecked()) c = Categorie::logiciel;
    if(ui->Materiel->isChecked()) c = Categorie::materiel;
    if(ui->Securite->isChecked()) c = Categorie::securite;

    gestionnaire->changeCategorie(ticket, c);
    ticket.setTechnicien(nullptr);
    technicien->setTicket(nullptr);
    qDebug() << technicien->peutTraiter(ticket);
    if(technicien->peutTraiter(ticket)) technicien->setTicket(&ticket);
    else {
        gestionnaire->assignerTicket(&ticket);
        gestionnaire->assignerTicket(technicien);
    }
}

void TechnicienWidget::reagir() {
    Ticket *ticket = technicien->getTicket();
    if(ticket == nullptr) {
        desactiver();
    } else {
        activer();
        afficheDonnee();
    }
}

void TechnicienWidget::afficheDonnee() {
    Ticket *ticket = technicien->getTicket();
    ui->ticketName->setText(ticket->getIdTicket());
    ui->ticketInfo->setText(ticket->getInformations());
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
    gestionnaire->chargerMessages(*technicien->getTicket());
    QStringList list;
    for(Message *message : ticket->getMessages().toStdVector())  list << "<" + message->getUtilisateur()->getId() + "> " + message->getContenu();
    model->setStringList(list);
    ui->textMessage->setText("");
    ui->messageList->setModel(model);
}

void TechnicienWidget::desactiver() {
    ui->ticketName->setText("");
    ui->ticketInfo->setText("");
    ui->textMessage->setText("");
    ui->Assistance->setDisabled(true);
    ui->Logiciel->setDisabled(true);
    ui->Materiel->setDisabled(true);
    ui->Securite->setDisabled(true);
    ui->changeCategorie->setDisabled(true);
    ui->fermerTicket->setDisabled(true);
    ui->textMessage->setDisabled(true);
    ui->envoyer->setDisabled(true);
    ui->messageList->setDisabled(true);
    model->setStringList(*new QStringList());
}

void TechnicienWidget::activer() {
    ui->Assistance->setEnabled(true);
    ui->Logiciel->setEnabled(true);
    ui->Materiel->setEnabled(true);
    ui->Securite->setEnabled(true);
    ui->changeCategorie->setEnabled(true);
    ui->fermerTicket->setEnabled(true);
    ui->textMessage->setEnabled(true);
    ui->envoyer->setEnabled(true);
    ui->messageList->setEnabled(true);
}

void TechnicienWidget::on_envoyer_clicked()
{
    gestionnaire->ajouterMessage(technicien->getTicket()->ajouterMessage(*technicien, ui->textMessage->toPlainText()));
    ui->textMessage->setText("");
    reagir();
}

