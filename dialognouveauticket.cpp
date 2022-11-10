#include "dialognouveauticket.h"
#include "ui_dialognouveauticket.h"

DialogNouveauTicket::DialogNouveauTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNouveauTicket)
{
    ui->setupUi(this);
}

DialogNouveauTicket::~DialogNouveauTicket()
{
    delete ui;
}
