#ifndef CONNEXIONWIDGET_H
#define CONNEXIONWIDGET_H

#include <QWidget>
#include "clientwidget.h"
#include "technicienwidget.h"
#include "gestionnairedialogue.h"

namespace Ui {
class ConnexionWidget;
}

class ConnexionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnexionWidget(QWidget *parent = nullptr);
    ~ConnexionWidget();
    void setGestionnaire(GestionnaireDialogue *gestionnaire);

private slots:
    void on_connexion_clicked();

private:
    Ui::ConnexionWidget *ui;
    GestionnaireDialogue *gestionnaire;
};

#endif // CONNEXIONWIDGET_H
