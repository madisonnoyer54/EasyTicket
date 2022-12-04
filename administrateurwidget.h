#ifndef ADMINISTRATEURWIDGET_H
#define ADMINISTRATEURWIDGET_H

#include <QWidget>
#include "gestionnairedialogue.h"

namespace Ui {
class AdministrateurWidget;
}

class AdministrateurWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdministrateurWidget(Administrateur &admin, GestionnaireDialogue &gestionnaire, QWidget *parent = nullptr);
    ~AdministrateurWidget();

private slots:
    void on_assistance_clicked();

    void on_logiciel_clicked();

    void on_materiel_clicked();

    void on_securite_clicked();

private:
    Ui::AdministrateurWidget *ui;
    GestionnaireDialogue &gestionnaire;
};

#endif // ADMINISTRATEURWIDGET_H
