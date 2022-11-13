#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include "dialognouveauticket.h"
#include "gestionnairedialogue.h"

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();
    void setGestionnaire(GestionnaireDialogue *gestionnaire);
    void setClient(Client *client);

private slots:
    void on_ajouterUnTicket_clicked();

private:
    Ui::ClientWidget *ui;
    GestionnaireDialogue *gestionnaire;
    Client *client;
};

#endif // CLIENTWIDGET_H
