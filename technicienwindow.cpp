#include "technicienwindow.h"
#include "ui_technicienwindow.h"

Technicienwindow::Technicienwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::technicienwindow)
{
    ui->setupUi(this);
}

Technicienwindow::~Technicienwindow()
{
    delete ui;
}
