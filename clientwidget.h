#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

// Permet de faire hériter la classe par Qwidget
#include <QWidget>
// Permet de gérer le dialogue d'un nouveau ticket
#include "dialognouveauticket.h"
// Permet d'inclure le modèle à l'interface
#include "gestionnairedialogue.h"
// Cette classe héritera d'observeur
#include "observeur.h"
// Model de la listView
#include <QStringListModel>
// Dialog de gestion de ticket
#include <dialogticket.h>

namespace Ui {
class ClientWidget;
}

/**
 * @brief La classe clientWidget permet l'affichage des informations visible par un client
 * et permets de gérer les actions possible qu'un client puisse faire
 *
 * Cette classe hérite de QWidget et d'observeur
 *
 * @version 3a
 *
 * @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */
class ClientWidget : public QWidget, Observeur
{
    Q_OBJECT

    private:
        /// @brief Variable contenant les information de l'interface utilisateur
        Ui::ClientWidget *ui;
        /// @brief Variable contenant le modèle de le logiciel
        GestionnaireDialogue *gestionnaire;
        /// @brief Variable contenant le client qui utilise le logiciel
        Client *client;
        /// @brief Variable contenant le model de la listeView
        QStringListModel *model;


    private slots:
        /// @brief Listener du bouton ajouter un ticket
        /// Ouvre un dialog qui permettera de créer/ouvrir
        /// un nouveau ticket
        void on_ajouterUnTicket_clicked();

        /// @brief Listener des éléments de la liste de ticket
        /// Ouvre un dialog qui permet au client d'envoyer un message
        /// a propos d'un ticket
        void on_listTicket_clicked(const QModelIndex &index);

        /// @brief Listener du selecteur de date
        /// Fait réagir l'interface pour afficher
        /// les choix de ticket possible
        void on_dateSup_userDateChanged(const QDate &date);

        /// @brief Listener du selecteur de date
        /// Fait réagir l'interface pour afficher
        /// les choix de ticket possible
        void on_dateInf_userDateChanged(const QDate &date);

public:
        /// @brief Constructeur de ClientWidget
        ///
        /// @param parent Parent du widget
        explicit ClientWidget(QWidget *parent = nullptr);

        /// @brief Destructeur de ClientWidget
        ~ClientWidget();

        /// @brief Methode qui permet de définir le modele du logiciel
        ///
        /// @param gestionnaire Modele du logiciel
        void setGestionnaire(GestionnaireDialogue &gestionnaire);

        /// @brief Methode qui permet de définir le client qui utilise le logiciel
        ///
        /// @param client Client qui utilise le logiciel
        void setClient(Client &client);

        /// @brief Methode reagir qui fait
        /// reagir la listeView lorsqu'elle est appelée
        void reagir() override;
};

#endif // CLIENTWIDGET_H
