#ifndef DIALOGNOUVEAUTICKET_H
#define DIALOGNOUVEAUTICKET_H

#include <QDialog>
#include "gestionnairedialogue.h"

namespace Ui {
class DialogNouveauTicket;
}

class DialogNouveauTicket : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNouveauTicket(QWidget *parent = nullptr);
    ~DialogNouveauTicket();
    void setGestionnaire(GestionnaireDialogue *gestionnaire);
    void setClient(Client *client);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogNouveauTicket *ui;
    GestionnaireDialogue *gestionnaire;
    Client *client;

};

#endif // DIALOGNOUVEAUTICKET_H
