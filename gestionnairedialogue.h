#ifndef GESTIONNAIREDIALOGUE_H
#define GESTIONNAIREDIALOGUE_H

/// Permet de retourner un objet de type Client pour la fonction getClient
#include "client.h"
/// Permet de retourner un objet de type Technicien pour la fonction getTechnicien
#include "technicien.h"
/// permet de définir la class GestionnaireDialogue comme un objet qui fera
/// réagir les classes de l'interface graphique
#include "objetobserve.h"
/// Permet de gérer une hashmap d'utilisateur
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QFile>
#include <QDir>

/** @brief La classe GestionnaireDialogue est la classe qui permet d'interagir avec les différents utilisateurs
 **
 ** @version 3b
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class GestionnaireDialogue : public ObjetObserve
{
    private:
       /// @brief Variable qui contient la hashmap des utilisateurs par rapport à leur identifiant
       QMap<QString, Utilisateur*> &listUtilisateurs;
       /// @brief Variable qui contient la file d'attente des tickets non traité
       QVector<Ticket*> fileTicket;
       QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;

    public:
        /// @brief Le constructeur
        GestionnaireDialogue();

        /// @brief le destructeur
        ~GestionnaireDialogue();

        /// @brief La méthode qui permet de retourner le client par rapport à son identifiant
        ///
        /// @param identifiant Identifiant du client
        ///
        /// @return Le client possèdant l'identifiant entré en paramètre
        Client* getClient(QString identifiant);

        /// @brief La méthode qui permet de retourner le technicien par rapport à son identifiant
        ///
        /// @param identifiant Identifiant du technicien
        ///
        /// @return Le technicien possédant l'identifiant entré en paramètre
        Technicien* getTechnicien(QString identifiant);

        /// @brief La méthode qui permet d'avoir la map des utilisateurs
        ///
        /// @return Map contenant tout les utilisateurs
        const QMap<QString, Utilisateur*>& getUtilisateurs() const;

        /// @brief La méthode qui permet d'assigner un ticket à un Technicien
        /// ou a le mettre en file d'attente si il faut
        ///
        /// @param ticket Le ticket
        void assignerTicket(Ticket* ticket);

        /// @brief La méthode qui permet d'assigner un ticket à un Technicien
        ///
        /// @param technicien Le technicien
        void assignerTicket(Technicien* technicien);

        void fermerTicket(Ticket &ticket);

        void nouveauTicket(Ticket &ticket);

        void changeCategorie(Ticket &ticket, Categorie categorie);

        void ajouterMessage(Message &message);

        void chargerMessages(Ticket &ticket);

    private:

        void chargerTickets(Client &client);
};

#endif // GESTIONNAIREDIALOGUE_H
