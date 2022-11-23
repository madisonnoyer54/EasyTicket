#ifndef TECHNICIENWIDGET_H
#define TECHNICIENWIDGET_H

// Permet de faire hériter la classe par Qwidget
#include <QWidget>
// Permet d'inclure le modèle à l'interface
#include "gestionnairedialogue.h"
// Cette classe héritera d'observeur
#include "observeur.h"

namespace Ui {
class TechnicienWidget;
}

/**
 * @brief La classe TechnicienWidget correspond à la classe
 * de l'interface graphique fait pour le technicien
 *
 * Cette classe hérite de QWidget de Observeur
 *
 * @version 2a
 *
 * @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */
class TechnicienWidget : public QWidget, Observeur
{
    Q_OBJECT

    private:
        /// @brief Variable contenant les information de l'interface utilisateur
        Ui::TechnicienWidget *ui;
        /// @brief Variable contenant le modèle de le logiciel
        GestionnaireDialogue *gestionnaire;
        /// @brief Variable contenant le technicien utilise le logiciel
        Technicien *technicien;


    private slots:
        /// @brief Listener du bouton fermer ticket
        /// Ferme le ticket que traite actuellement le
        /// technicien
        void on_fermerTicket_clicked();
        /// @brief Listener du bouton changer la categorie
        /// Change la catégorie du ticket que traite actuellement le
        /// technicien
        void on_changeCategorie_clicked();
        /// @brief Listener du bouton envoyer
        /// Envoie un message relié au ticket traité par
        /// le technicien
        void on_envoyer_clicked();

    public:
        /// @brief Constructeur de widget
        ///
        /// @param parent Parent du widget
        explicit TechnicienWidget(QWidget *parent = nullptr);

        /// @brief Destructeur du widget
        ~TechnicienWidget();

        /// @brief Methode qui permet de définir le modele du logiciel
        ///
        /// @param gestionnaire Modele du logiciel
        void setGestionnaire(GestionnaireDialogue *gestionnaire);

        /// @brief Methode qui permet de définir le technicient qui utilise le logiciel
        ///
        /// @param technicien Technicien qui utilise le logiciel
        void setTechnicien(Technicien *technicien);

        /// @brief Methode reagir qui fait
        /// reagir les informations sur le ticket
        /// traité
        void reagir() override;

    private:
        /// @brief Methode qui permet d'afficher les informations du ticket sur l'affichage graphique
        ///
        /// Affichage de l'id du ticket, des informations et de la categorie
        void afficheDonnee();

        /// @brief Methode qui permet de desactiver les boutons et textinput
        /// lors que le technicien n'a plus de ticket a traiter
        void desactiver();

        /// @brief Methode qui permet d'activer les boutons et textinput
        /// lors que le technicien a un ticket a traiter
        void activer();
};

#endif // TECHNICIENWIDGET_H
