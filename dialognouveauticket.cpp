#include "dialognouveauticket.h"
#include "ui_dialognouveauticket.h"

DialogNouveauTicket::DialogNouveauTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNouveauTicket)
{
    ui->setupUi(this);
}

DialogNouveauTicket::~DialogNouveauTicket()
{
    delete ui;
}

void DialogNouveauTicket::setGestionnaire(GestionnaireDialogue *gestionnaire) {
    this->gestionnaire = gestionnaire;
}

void DialogNouveauTicket::setClient(Client *client) {
    this->client = client;
}

void DialogNouveauTicket::on_buttonBox_accepted()
{
    Categorie c;
    if(ui->Assistance->isChecked()) c = Categorie::assistance;
    if(ui->Logiciel->isChecked()) c = Categorie::logiciel;
    if(ui->Materiel->isChecked()) c = Categorie::materiel;
    if(ui->Securite->isChecked()) c = Categorie::securite;
    gestionnaire->assignerTicket(&client->nouveauTicket(ui->informationsText->toPlainText(), c));
    std::cout << "------ Ajout d'un ticket ------ \n" << *gestionnaire;
}

