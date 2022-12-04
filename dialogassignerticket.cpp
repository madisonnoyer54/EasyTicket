#include "dialogassignerticket.h"
#include "ui_dialogassignerticket.h"

DialogAssignerTicket::DialogAssignerTicket(Ticket &ticket, GestionnaireDialogue &gestionnaire, TechnicienWidget &widget, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAssignerTicket),
    ticket(ticket),
    gestionnaire(gestionnaire),
    widget(widget)
{
    ui->setupUi(this);
    techniciens = gestionnaire.getTechniciensPeuventGerer(ticket);
    model = new QStringListModel(this);
    ui->listTechnicien->setModel(model);

    QStringList list;

    for(int i = 0; i < techniciens.size(); i++) {
        Technicien *technicien = techniciens[i];
        list << technicien->getId();
    }

    model->setStringList(list);
    setWindowTitle("Choisir un technicien");
    if(techniciens.size() > 0) {
        ui->listTechnicien->setCurrentIndex(model->index(0,0));
        widget.desactiver();
    }
}

DialogAssignerTicket::~DialogAssignerTicket()
{
    delete ui;
}

#include <QtDebug>

void DialogAssignerTicket::on_buttonBox_accepted()
{
    if(model->rowCount() > 0) {
        QModelIndex index = ui->listTechnicien->currentIndex();
        Technicien *choix = gestionnaire.getTechnicien(index.data(Qt::DisplayRole).toString());
        if(choix != nullptr) gestionnaire.assignerTicket(*choix, ticket);
    }
    hide();
    delete this;
}

