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

    ui->categorie->setText(categorie_to_str(ticket.getCategorie()));

    QDateTime  dateCreation = ticket.getDateCreation();
    QDate date = dateCreation.date();
    QTime time = dateCreation.time();
    QString dateStr(QString::number(date.day()));
    dateStr.append("/");
    dateStr.append(QString::number(date.month()));
    dateStr.append("/");
    dateStr.append(QString::number(date.year()));
    dateStr.append(" à ");
    dateStr.append(QString::number(time.hour()));
    dateStr.append(" heure, ");
    dateStr.append(QString::number(time.minute()));
    dateStr.append(" minutes et ");
    dateStr.append(QString::number(time.second()));
    dateStr.append(" secondes.");
    ui->dateTicket->setText(dateStr);

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
