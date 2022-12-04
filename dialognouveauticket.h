#ifndef DIALOGNOUVEAUTICKET_H
#define DIALOGNOUVEAUTICKET_H

// Permet de faire hériter la classe par QDialog
#include <QDialog>
// Permet d'inclure le modèle à l'interface
#include "gestionnairedialogue.h"

namespace Ui {
class DialogNouveauTicket;
}

/**
 * @brief La class DialogNouveauTicket hérite de la classe QDialog
 * C'est un dialog qui permet de créer un nouveau ticket
 *
 * @version 3b
 *
 * @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */
class DialogNouveauTicket : public QDialog
{
    Q_OBJECT

    private:
        /// @brief Variable contenant les information de l'interface utilisateur
        Ui::DialogNouveauTicket *ui;
        /// @brief Variable contenant le modèle de le logiciel
        GestionnaireDialogue *gestionnaire;
        /// @brief Variable contenant le client qui utilise le logiciel
        Client *client;

    private slots:
        /// @brief Listener de la buttonBox
        /// Créer un nouveau ticket si le bouton ok
        /// a était selectionné
        /// Ne fait rien sinon
        void on_buttonBox_accepted();


    public:
        /// @brief Constructeur du dialog
        ///
        /// @param parent Le parent du dialog
        explicit DialogNouveauTicket(QWidget *parent = nullptr);

        /// @brief Destructeur du dialog
        ~DialogNouveauTicket();

        /// @brief Methode qui permet de définir le modele du logiciel
        ///
        /// @param gestionnaire Modele du logiciel
        void setGestionnaire(GestionnaireDialogue *gestionnaire);

        /// @brief Methode qui permet de définir le client qui utilise le logiciel
        ///
        /// @param client Client qui utilise le logiciel
        void setClient(Client *client);
};

#endif // DIALOGNOUVEAUTICKET_H
