#include "connexionwidget.h"
#include "ui_connexionwidget.h"

ConnexionWidget::ConnexionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnexionWidget)
{
    ui->setupUi(this);
}

ConnexionWidget::~ConnexionWidget()
{
    delete ui;
}

void ConnexionWidget::on_connexion_clicked()
{
    if(ui->Client->isChecked()) {
        hide();
        ClientWidget *clientWidget = new ClientWidget(parentWidget());
        clientWidget->show();
    }
    if(ui->Technicien->isChecked()) {
        hide();
        TechnicienWidget *technitienWidget = new TechnicienWidget(parentWidget());
        technitienWidget->show();
    }
}

