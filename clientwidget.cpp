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
    QDateTime dateInf = ui->dateInf->dateTime();
    QDateTime dateSup = ui->dateSup->dateTime();
    for(int i = 0; i < listTicket.size(); i++) {
        QDateTime dateTicket = listTicket[i]->getDateCreation();
        if(dateTicket <= dateInf && dateTicket >= dateSup)
            list << listTicket[i]->getIdTicket() + " :\n" + listTicket[i]->getInformations() + "\n" + (listTicket[i]->estOuvert() ? "Ouvert" : "Fermer");
    }
    model->setStringList(list);
    ui->listTicket->setModel(model);

}

void ClientWidget::on_listTicket_clicked(const QModelIndex &index)
{
    DialogTicket *dialog = new DialogTicket(*gestionnaire, *client, client->getTicket(index.row()), this);

    dialog->show();
}


void ClientWidget::on_dateSup_userDateChanged(const QDate &date)
{
    std::ignore = date;
    reagir();
}


void ClientWidget::on_dateInf_userDateChanged(const QDate &date)
{
    std::ignore = date;
    reagir();
}

