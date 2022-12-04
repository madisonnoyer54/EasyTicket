#ifndef CONNEXIONWIDGET_H
#define CONNEXIONWIDGET_H

// Permet de faire hériter la classe par Qwidget
#include <QWidget>
// Permet d'inclure le modèle à l'interface
#include "gestionnairedialogue.h"
// Interface utilisateur du client
#include "clientwidget.h"
// Interface utilisateur du technicien
#include "technicienwidget.h"

namespace Ui {
class ConnexionWidget;
}

/**
 * @brief La classe ConnexionWidget permet la connection de l'utilisateur
 * en lui permettant de rentrer son identifiant
 * ainisi que de choisir son role (Client, Technicien ou Administrateur)
 *
 * Cette classe hérite de QWidget
 *
 * @version 3b
 *
 * @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */
class ConnexionWidget : public QWidget
{
    Q_OBJECT

    private:
        /// @brief Variable contenant les information de l'interface utilisateur
        Ui::ConnexionWidget *ui;
        /// @brief Variable contenant le modèle de le logiciel
        GestionnaireDialogue *gestionnaire;
        /// @brief Widget d'affichage du technicien
        TechnicienWidget *technitienWidget;
        /// @brief Widget d'affichage du client
        ClientWidget *clientWidget;


    private slots:
        /// @brief Listener du bouton connexion
        /// Qui fait que l'utilisateur se connecte
        /// et puisse voir l'affichage des informations
        /// du client si c'est un client
        /// ou des informations du technicien
        /// si c'est un technicien
        void on_connexion_clicked();

        /// @brief Listener du de l'entrée texte
        /// Qui fait qu'appuyer sur Entrée valide
        /// la sélection et agit comme un appui sur
        /// le bouton de connexion
        void on_identifiantText_returnPressed();

public:
        /// @brief Constructeur de ConnexionWidget
        ///
        /// @param parent Parent du widget
        explicit ConnexionWidget(QWidget *parent = nullptr);

        /// @brief Destructeur de ConnexionWidget
        ~ConnexionWidget();

        /// @brief Methode qui permet de définir le modele du logiciel
        ///
        /// @param gestionnaire Modele du logiciel
        void setGestionnaire(GestionnaireDialogue &gestionnaire);
};

#endif // CONNEXIONWIDGET_H
