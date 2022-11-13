#ifndef TECHNICIENWIDGET_H
#define TECHNICIENWIDGET_H

#include <QWidget>
#include "gestionnairedialogue.h"

namespace Ui {
class TechnicienWidget;
}

class TechnicienWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TechnicienWidget(QWidget *parent = nullptr);
    ~TechnicienWidget();
    void setGestionnaire(GestionnaireDialogue *gestionnaire);
    void setTechnicien(Technicien *technicien);

private slots:
    void on_fermerTicket_clicked();

private:
    Ui::TechnicienWidget *ui;
    GestionnaireDialogue *gestionnaire;
    Technicien *technicien;

    void reagir();
};

#endif // TECHNICIENWIDGET_H
