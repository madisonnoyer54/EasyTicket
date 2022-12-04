#ifndef TICKET_H
#define TICKET_H

// Pour la gestion de l'identifiant
#include <QString>
// Pour gérer la categorie du ticket
#include "categorie.h"
// Pour définir la classe technicien
// qui représente le technicien qui gèrera la classe
#include "technicien.h"
// Pour que le ticket puisse connaitre son créateur
#include "client.h"
// Pour que le ticket connaisse une liste de ticket
#include "message.h"
// Pour permettre au ticket d'hérite de objectObserve
#include "objetobserve.h"
// Pour permettre au ticket d'avoir une date de création
#include <QDateTime>

class Technicien;
class Client;
class Message;

/** @brief La classe Ticket est la classe qui permet de créer un ticket
 **
 ** Elle contient les methodes pour fermer le ticket ou le
 ** construite (à l'aide du constructeur)
 **
 ** Cette classe hérite de ObjetObserve
 **
 ** @version 3b
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Ticket : public ObjetObserve
{

    private:
        /// @brief Variable qui contient le numéro du ticket
        QString idTicket;

        /// @brief Variable qui contient l'information ouvert/fermer du ticket
        /// Vrai sur le ticket est ouvert, faux sinon
        bool ouvert;

        /// @brief Variable qui contient les informations du ticket
        QString informations;

        /// @brief Variable qui désigne la catégorie du ticket
        Categorie categorie;

        /// @brief Variable qui désigne le technicien qui s'occupe du ticket
        Technicien* technicien = nullptr;

        /// @brief Variable qui désigne le créateur du ticket
        Client *client;

        /// @brief Variable qui désigne la liste des messages du ticket
        QVector<Message *> *listMessages;

        /// @brief Variable qui contient la date de création du ticket
        QDateTime dateCreation;


    public:
        /// @brief Le constructeur par défaut définir les champs informations
        /// et categorie de la classe.
        ///
        /// @param client Pointeur vers le créateur du ticket
        /// @param informations Informations rentré par le client sur le ticket
        /// @param categorie Categorie du ticket choisis par le client
        Ticket(Client *client, QString informations, Categorie categorie);

        /// @brief le destructeur ne fait rien
        ~Ticket();

        /// @brief La méthode permet de retourner l'identifiant du ticket
        ///
        /// @return L'identifiant du ticket
        const QString getIdTicket() const;

        /// @brief La méthode permet de changer le numéro du ticket
        ///
        /// @param id Le nouvel identifiant du ticket
        void setIdTicket(QString id);

        /// @brief La méthode permet de savoir si le ticket est ouvert ou non.
        ///
        /// @return true si le ticket est ouvert et false sinon
        bool estOuvert() const;

        /// @brief La méthode permet de fermer le ticket
        ///
        /// le champs ouvert passera a false
        void fermer();

        /// @brief La méthode permet de connaitre les informations d'un ticket
        ///
        /// @return Les informations donné par le client sur le ticket
        const QString getInformations() const;

        /// @brief La méthode permet de définir des informations pour rapport à un ticket
        ///
        /// @param Les nouvelles informations par rapport à un ticket
        void setInformations(QString informations);

        /// @brief La méthode qui permet de connaitre la categorie d'un ticket
        ///
        /// @return La categorie d'un ticket
        Categorie getCategorie() const;

        /// @brief La méthode qui permet de définir la categorie d'un ticket
        ///
        /// @param categorie La nouvelle categorie du ticket
        void setCategorie(Categorie categorie);

        /// @brief La méthode qui permet de connaitre le
        /// technicien qui gère le ticket
        ///
        /// @return Le technicien qui gère le ticket
        Technicien* getTechnicien() const;

        /// @brief La méthode qui permet de connaitre le
        /// créateur du ticket
        ///
        /// @return Le créateur du ticket
        Client* getClient() const;

        /// @brief La méthode qui permet de définir le technicien
        /// qui va gérer le ticket
        ///
        /// @param technicien Le nouveau technicien du ticket
        void setTechnicien(Technicien* technicien);

        /// @brief La méthode qui permet de connaitre le
        /// moment de création d'un ticket
        ///
        /// @return Le temps correspondant au moment
        /// de création du ticket
        const QDateTime &getDateCreation() const;

        /// @brief La méthode qui permet de définir une date
        /// de création au ticket
        ///
        /// @param date La date de création
        void setDateCreation(QDateTime date);

        /// @brief La méthode qui permet de retourner la liste des messages
        ///
        /// @return Qvector contenant la liste des messages
        const QVector<Message *> &getMessages() const;

        /// @brief La méthode qui permet d'ajouter un message
        /// à la liste des messages
        ///
        /// @param utilisateur L'utilisateur qui envoit le message
        /// @param message Contenu du message
        Message &ajouterMessage(Utilisateur &utilisateur, QString message);

        /// @brief La méthode qui permet d'ajouter un message déjà
        /// existant à la liste des messages si il n'est pas
        /// déjà dans celle ci
        ///
        /// @param message Référence vers le message
        void ajouterMessage(Message &message);
};

#endif // TICKET_H
