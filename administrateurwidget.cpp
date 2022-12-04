#include "administrateurwidget.h"
#include "ui_administrateurwidget.h"

AdministrateurWidget::AdministrateurWidget(Administrateur &admin, GestionnaireDialogue &gestionnaire, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministrateurWidget),
    gestionnaire(gestionnaire)
{
    ui->setupUi(this);
    ui->name->setText(admin.getId());
}

AdministrateurWidget::~AdministrateurWidget()
{
    delete ui;
}
