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

#include "administrateurwidget.h"

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
            ui->progressBar->setValue(0);
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
            ui->progressBar->setValue(0);
        } else {
            technitienWidget->setTechnicien(*technicien);
            technitienWidget->setGestionnaire(*gestionnaire);
            ui->progressBar->setValue(100);
            hide();
            parentWidget()->layout()->addWidget(technitienWidget);
        }
    }
    if(ui->Administrateur->isChecked()) {
        ui->progressBar->setValue(30);
        Administrateur *administrateur = gestionnaire->getAdministrateur(ui->identifiantText->text());
        ui->progressBar->setValue(60);
        if(administrateur == nullptr) {
            ui->progressBar->setVisible(false);
            ui->errorLabel->setVisible(true);
            ui->errorLabel->setText("Impossible d'identifier l'administrateur : " + ui->identifiantText->text());
            ui->progressBar->setValue(0);
        } else {
            AdministrateurWidget *widget = new AdministrateurWidget(*administrateur, *gestionnaire, this);
            ui->progressBar->setValue(100);
            hide();
            parentWidget()->layout()->addWidget(widget);
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

