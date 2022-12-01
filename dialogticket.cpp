#include "dialogticket.h"
#include "ui_dialogticket.h"

DialogTicket::DialogTicket(GestionnaireDialogue &gestionnaire, Client &client, Ticket &ticket, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTicket),
    gestionnaire(gestionnaire),
    client(client),
    ticket(ticket)
{
    ui->setupUi(this);
    setWindowTitle(ticket.getIdTicket());
    model = new QStringListModel(this);
    ui->listMessage->setModel(model);
    ticket.addObserveur(*this);

    ui->contenuTicket->setText(ticket.getInformations());
    ui->idTicket->setText(ticket.getIdTicket());

    switch(ticket.getCategorie()) {
        case Categorie::assistance:
            ui->categorie->setText("Assistance");
            break;
        case Categorie::logiciel:
            ui->categorie->setText("Logiciel");
            break;
        case Categorie::materiel:
            ui->categorie->setText("Materiel");
            break;
        case Categorie::securite:
            ui->categorie->setText("Securite");
            break;
    }

    QDate  dateCreation = ticket.getDateCreation();
    QString date(QString::number(dateCreation.day()));
    date.append("/");
    date.append(QString::number(dateCreation.month()));
    date.append("/");
    date.append(QString::number(dateCreation.year()));
    ui->dateTicket->setText(date);

    Technicien *technicien = ticket.getTechnicien();
    if(technicien == nullptr) {
        ui->technicien->setText("Ticket actuellement traité par personne.");
    } else {
        ui->technicien->setText("Ticket actuellement traité par " + technicien->getId() + ".");
    }
    QString etat("Votre ticket est actuellement ");
    etat.append((ticket.estOuvert() ? "Ouvert" : "Fermer"));
    etat.append(".");
    ui->etatTicket->setText(etat);
}

DialogTicket::~DialogTicket()
{
    delete ui;
    delete model;
}

void DialogTicket::on_Envoyer_clicked()
{
    gestionnaire.ajouterMessage(ticket.ajouterMessage(client, ui->textMessage->toPlainText()));
    ui->textMessage->setText("");
}

void DialogTicket::reagir() {
    gestionnaire.chargerMessages(ticket);
    QStringList list;
    for(Message *message : ticket.getMessages().toStdVector())
    list << "<" + message->getUtilisateur()->getId() + "> " + message->getContenu();
    model->setStringList(list);
}
