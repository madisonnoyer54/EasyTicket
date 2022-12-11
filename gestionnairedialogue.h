#ifndef GESTIONNAIREDIALOGUE_H
#define GESTIONNAIREDIALOGUE_H

/// Permet de retourner un objet de type Administrateur pour la fonction getClient
#include "administrateur.h"
/// Permet de retourner un objet de type Client pour la fonction getClient
#include "client.h"
/// Permet de retourner un objet de type Technicien pour la fonction getTechnicien
#include "technicien.h"
/// permet de définir la class GestionnaireDialogue comme un objet qui fera
/// réagir les classes de l'interface graphique
#include "objetobserve.h"
/// Permet de gérer une hashmap d'utilisateur
#include <QMap>
/// Permet de gérer la base de donnée
#include <QSqlDatabase>
/// Permet de gérer les requetes vers la base de donnée
#include <QSqlQuery>
/// Permet de gérer les résultats des requetes
#include <QVariant>
/// Permet de gérer les fichiers pour copier la base de donnée en local
#include <QFile>
/// Permet de gérer les dossiers pour créer le dossier qui contiendra la base de donnée
#include <QDir>
#include <QStandardPaths>

/** @brief La classe GestionnaireDialogue est la classe qui permet d'interagir avec les différents utilisateurs
 **
 ** @version 3c
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class GestionnaireDialogue : public ObjetObserve
{
    private:
       /// @brief Variable qui contient la hashmap des utilisateurs par rapport à leur identifiant
       QMap<QString, Utilisateur*> &listUtilisateurs;
       /// @brief Variable qui contient la base de donnée
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

        /// @brief La méthode qui permet de retourner l'admnistrateur par rapport à son identifiant
        ///
        /// @param identifiant Identifiant de l'admnistrateur
        ///
        /// @return L'admnistrateur possédant l'identifiant entré en paramètre
        Administrateur* getAdministrateur(QString identifiant);

        /// @brief La méthode qui permet d'avoir la map des utilisateurs
        ///
        /// @return Map contenant tout les utilisateurs
        const QMap<QString, Utilisateur*>& getUtilisateurs() const;

        /// @brief La méthode qui permet d'assigner un ticket à un Technicien
        /// ou a le mettre en file d'attente si il faut
        ///
        /// @param ticket Le ticket
        void assignerTicket(Ticket &ticket);

        /// @brief La méthode qui permet d'assigner un ticket à un Technicien
        ///
        /// @param technicien Le technicien
        void assignerTicket(Technicien &technicien);

        /// @brief La méthode qui permet de fermer une ticket
        ///
        /// @param ticket Référence vers le ticket
        void fermerTicket(Ticket &ticket);

        /// @brief La méthode qui permet d'ajouter un nouveau ticket dans la base de donnée
        ///
        /// @param ticket Référence vers le nouveau ticket
        void nouveauTicket(Ticket &ticket);

        /// @brief La méthode qui permet de changer la catégorie d'un ticket
        ///
        /// @param ticket Référence vers le ticket
        /// @param categorie Categorie du ticket
        void changeCategorie(Ticket &ticket, Categorie categorie);

        /// @brief La méthode qui permet de rajouter un message dans la base de donnée
        ///
        /// @param message Référence vers un message
        void ajouterMessage(Message &message);

        /// @brief La méthode qui permet de charger les messages en liens avec un ticket
        ///
        /// @param ticket Référence vers le ticket
        void chargerMessages(Ticket &ticket);

        /// @brief La méthode qui permet de savoir la liste des techniciens
        /// qui peuvent gérer un ticket
        ///
        /// @param ticket Référence vers le ticket
        ///
        /// @return QVector
        QVector<Technicien *> &getTechniciensPeuventGerer(Ticket &ticket);

        /// @brief La méthode qui permet d'assigner un ticket à un technicien
        ///
        /// @param technicien Référence vers un technicien
        /// @param ticket Référence vers un ticket
        void assignerTicket(Technicien &technicien, Ticket &ticket);

        int getNbTicket(QDate debut, QDate fin);
        int getNbTicketFerme(QDate debut, QDate fin);
        int getNbTicket(Categorie categorie, QDate debut, QDate fin);
        int getNbTicketFerme(Categorie categorie, QDate debut, QDate fin);
        int getNbTechnicien(Categorie categorie);
        int getNbTicketTraitement(QDate debut, QDate fin);
        int getNbTicketTraitement(Categorie categorie, QDate debut, QDate fin);

    private:

        /// @brief La méthode qui permet de charger les tickets d'un client
        ///
        /// @param client Référence vers le client
        void chargerTickets(Client &client);

        /// @brief La méthode qui permet de charger un technicien de la base de donnée
        ///
        /// @param identifiant Identifiant du technicien
        Technicien* chargerTechnicien(QString identifiant);

        /// @brief La méthode qui permet de charger un client de la base de donnée
        ///
        /// @param identifiant Identifiant du client
        Client* chargerClient(QString identifiant);
};

#endif // GESTIONNAIREDIALOGUE_H
