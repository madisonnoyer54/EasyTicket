#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("EasyTicket");
    connexion = new ConnexionWidget(this);
    //connexion->show();
    centralWidget()->layout()->addWidget(connexion);
    QMainWindow::setWindowIcon(QIcon(":/ressources/icon/icon.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGestionnaire(GestionnaireDialogue &gestionnaire) {
    this->gestionnaire = &gestionnaire;
    connexion->setGestionnaire(gestionnaire);
}


void MainWindow::on_MainWindow_destroyed() {

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    std::ignore = event;
    delete gestionnaire;
}

