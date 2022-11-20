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
}

DialogTicket::~DialogTicket()
{
    delete ui;
}

void DialogTicket::on_Envoyer_clicked()
{
    ui->textMessage->setText("");
}

