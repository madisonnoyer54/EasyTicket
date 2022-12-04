#ifndef DIALOGASSIGNERTICKET_H
#define DIALOGASSIGNERTICKET_H

// Permet de faire hériter la classe par QDialog
#include <QDialog>
// Permet d'inclure le modèle à l'interface
#include "gestionnairedialogue.h"
// Model de la listView
#include <QStringListModel>
// Permet d'influer sur le widget parent
#include "technicienwidget.h"

namespace Ui {
class DialogAssignerTicket;
}

class TechnicienWidget;

/**
 * @brief La class DialogAssignerTicket hérite de la classe QDialog
 * C'est un dialog qui permet d'assigner un technicien au ticket
 *
 * @version 3c
 *
 * @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */
class DialogAssignerTicket : public QDialog
{
    Q_OBJECT
    private:
        /// @brief Variable contenant les information de l'interface utilisateur
        Ui::DialogAssignerTicket *ui;
        /// @brief Variable contenant le ticket a assigner
        Ticket &ticket;
        /// @brief Variable contenant le modèle du logiciel
        GestionnaireDialogue &gestionnaire;
        /// @brief Variable contenant la liste des techniciens pouvant gérer le ticket
        QVector<Technicien *> techniciens;
        /// @brief Variable contenant le model de la listeView
        QStringListModel *model;
        /// @brief Variable contenant le widget ayant appelé le dialog
        TechnicienWidget &widget;

    public:
        /// @brief Constructeur du dialog qui servire a assigner un technicien spécifique au ticket
        ///
        /// @param ticket Référence vers le ticket
        /// @param gestionnaire Référence vers le modèle
        /// @param widget Widget parent appelant la classe
        explicit DialogAssignerTicket(Ticket &ticket, GestionnaireDialogue &gestionnaire, TechnicienWidget &widget, QWidget *parent = nullptr);

        /// @brief destructeur
        ~DialogAssignerTicket();

private slots:

        /// @brief Listener du bouton accepter
        ///
        /// Assigne le technicien au ticket si un technicien est choisi
        /// Fermeture du dialogue
        void on_buttonBox_accepted();
};

#endif // DIALOGASSIGNERTICKET_H
