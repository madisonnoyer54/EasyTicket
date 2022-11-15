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
        clientWidget = new ClientWidget(parentWidget());
        clientWidget->setGestionnaire(gestionnaire);
        clientWidget->setClient(gestionnaire->getClient(ui->identifiantText->toPlainText()));
        parentWidget()->layout()->addWidget(clientWidget);
    }
    if(ui->Technicien->isChecked()) {
        hide();
        technitienWidget = new TechnicienWidget(parentWidget());
        technitienWidget->setGestionnaire(gestionnaire);
        technitienWidget->setTechnicien(gestionnaire->getTechnicien(ui->identifiantText->toPlainText()));
        parentWidget()->layout()->addWidget(technitienWidget);
    }
}


void ConnexionWidget::setGestionnaire(GestionnaireDialogue *gestionnaire) {
    this->gestionnaire = gestionnaire;
}
