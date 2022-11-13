#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("EasyTicket");
    connexion = new ConnexionWidget(this);
    connexion->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGestionnaire(GestionnaireDialogue *gestionnaire) {
    this->gestionnaire = gestionnaire;
    connexion->setGestionnaire(gestionnaire);
}
