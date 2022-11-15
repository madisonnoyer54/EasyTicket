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
    try{
        if(ui->Client->isChecked()) {
            ui->progressBar->setValue(30);
            clientWidget = new ClientWidget(parentWidget());
            clientWidget->setGestionnaire(gestionnaire);
            ui->progressBar->setValue(60);
            clientWidget->setClient(gestionnaire->getClient(ui->identifiantText->toPlainText()));
            ui->progressBar->setValue(100);
            hide();
            parentWidget()->layout()->addWidget(clientWidget);
        }
        if(ui->Technicien->isChecked()) {
            ui->progressBar->setValue(30);
            technitienWidget = new TechnicienWidget(parentWidget());
            technitienWidget->setGestionnaire(gestionnaire);
            ui->progressBar->setValue(60);
            technitienWidget->setTechnicien(gestionnaire->getTechnicien(ui->identifiantText->toPlainText()));
            ui->progressBar->setValue(100);
            hide();
            parentWidget()->layout()->addWidget(technitienWidget);
        }
    } catch (UtilisateurNonTrouveException unte) {
        ui->errorLabel->setVisible(true);
        ui->progressBar->setVisible(false);
        ui->errorLabel->setText(unte.getMessage());
    }
}


void ConnexionWidget::setGestionnaire(GestionnaireDialogue *gestionnaire) {
    this->gestionnaire = gestionnaire;
}
