#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_ajouterUnTicket_clicked()
{
    DialogNouveauTicket *dialog = new DialogNouveauTicket(this);
    dialog->show();
}

