#ifndef DIALOGTICKET_H
#define DIALOGTICKET_H

// Permet de faire hériter la classe par QDialog
#include <QDialog>
// Permet d'inclure le modèle à l'interface
#include "gestionnairedialogue.h"
// Model de la listView
#include <QStringListModel>

namespace Ui {
class DialogTicket;
}

/**
 * @brief La class DialogTicket hérite de la classe QDialog
 * C'est un dialog qui permet au client de voir les informations sur un ticket
 * et communiquer avec le technicien par rapport a ce ticket
 *
 * @version 3b
 *
 * @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */
class DialogTicket : public QDialog, Observeur
{
    Q_OBJECT

    private:
        /// @brief Variable contenant les information de l'interface utilisateur
        Ui::DialogTicket *ui;
        /// @brief Variable contenant le modèle de le logiciel
        GestionnaireDialogue &gestionnaire;
        /// @brief Variable contenant le client qui utilise le logiciel
        Client &client;
        /// @brief Variable contenant le ticket que le client consulte
        Ticket &ticket;
        /// @brief Model de la liste des messages
        QStringListModel *model;
        /// @brief Affiche les messages du ticket
        void afficherMessages();

    public:
        /// @brief Constructeur du dialog
        ///
        /// @param parent Le parent du dialog
        explicit DialogTicket(GestionnaireDialogue &gestionnaire, Client &client, Ticket &ticket, QWidget *parent = nullptr);

        /// @brief Destructeur du dialog
        ~DialogTicket();

        /// @brief Methode reagir qui fait
        /// reagir un objet lorsqu'elle est appelée
        void reagir() override;

    private slots:
        /// @brief Envoit un message sur le ticket
        void on_Envoyer_clicked();
};

#endif // DIALOGTICKET_H
