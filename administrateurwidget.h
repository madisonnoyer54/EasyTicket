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

    void on_dateAvant_userDateChanged(const QDate &date);

    void on_dateApres_userDateChanged(const QDate &date);

private:
    Ui::AdministrateurWidget *ui;
    GestionnaireDialogue &gestionnaire;

    void reagir();
};

#endif // ADMINISTRATEURWIDGET_H
