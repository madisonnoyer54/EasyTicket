#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    ui->listTicket->setModel(model);
}

ClientWidget::~ClientWidget()
{
    delete ui;
    delete model;
}

void ClientWidget::on_ajouterUnTicket_clicked()
{
    DialogNouveauTicket *dialog = new DialogNouveauTicket(this);
    dialog->setClient(client);
    dialog->setGestionnaire(gestionnaire);
    dialog->show();
}

void ClientWidget::setGestionnaire(GestionnaireDialogue *gestionnaire) {
    this->gestionnaire = gestionnaire;
    gestionnaire->addObserveur(*this);
}

void ClientWidget::setClient(Client *client) {
    this->client = client;
    parentWidget()->setWindowTitle("EasyTicket - Client : " + client->getId());
    reagir();
}

void ClientWidget::reagir() {
    QStringList list;
    QVector<Ticket *> listTicket = client->getTickets();
    for(int i = 0; i < listTicket.size(); i++) {
        list << listTicket[i]->getIdTicket() + " :\n" + listTicket[i]->getInformations() + "\n" + (listTicket[i]->estOuvert() ? "Ouvert" : "Fermer");
    }
    model->setStringList(list);
    ui->listTicket->setModel(model);

}
