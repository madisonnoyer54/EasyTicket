#include "connexionwidget.h"
#include "ui_connexionwidget.h"

ConnexionWidget::ConnexionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnexionWidget)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    ui->errorLabel->setVisible(false);
}

ConnexionWidget::~ConnexionWidget()
{
    delete ui;
}

void ConnexionWidget::on_connexion_clicked()
{
    ui->progressBar->setVisible(true);
    if(ui->Client->isChecked()) {
        ui->progressBar->setValue(30);
        clientWidget = new ClientWidget(parentWidget());
        ui->progressBar->setValue(60);
        Client *client = gestionnaire->getClient(ui->identifiantText->text());
        if(client == nullptr) {
            ui->progressBar->setVisible(false);
            ui->errorLabel->setVisible(true);
            ui->errorLabel->setText("Impossible d'identifier le client : " + ui->identifiantText->text());
        } else {
            clientWidget->setClient(*client);
            clientWidget->setGestionnaire(*gestionnaire);
            ui->progressBar->setValue(100);
            hide();
            parentWidget()->layout()->addWidget(clientWidget);
        }
    }
    if(ui->Technicien->isChecked()) {
        ui->progressBar->setValue(30);
        technitienWidget = new TechnicienWidget(parentWidget());
        ui->progressBar->setValue(60);
        Technicien *technicien = gestionnaire->getTechnicien(ui->identifiantText->text());
        if(technicien == nullptr) {
            ui->progressBar->setVisible(false);
            ui->errorLabel->setVisible(true);
            ui->errorLabel->setText("Impossible d'identifier le technicien : " + ui->identifiantText->text());
        } else {
            technitienWidget->setTechnicien(*technicien);
            technitienWidget->setGestionnaire(*gestionnaire);
            ui->progressBar->setValue(100);
            hide();
            parentWidget()->layout()->addWidget(technitienWidget);
        }
    }
}


void ConnexionWidget::setGestionnaire(GestionnaireDialogue &gestionnaire) {
    this->gestionnaire = &gestionnaire;
}

void ConnexionWidget::on_identifiantText_returnPressed()
{
    this->ui->connexion->click();
}

