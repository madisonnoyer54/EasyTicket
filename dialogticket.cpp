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
    reagir();
}

DialogTicket::~DialogTicket()
{
    delete ui;
    delete model;
}

void DialogTicket::on_Envoyer_clicked()
{
    ticket.ajouterMessage(client, ui->textMessage->toPlainText());
    ui->textMessage->setText("");
}

void DialogTicket::reagir() {
    QStringList list;
    for(Message *message : ticket.getMessages().toStdVector())
    list << "<" + message->getUtilisateur()->getId() + "> " + message->getContenu();
    model->setStringList(list);
}
