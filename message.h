#ifndef MESSAGE_H
#define MESSAGE_H

// Pour la gestion de l'identifiant et du contenu
#include <QString>
#include <QDateTime>
// Permet au message d'avoir son utilisateur
#include "utilisateur.h"
#include "ticket.h"

class Ticket;

class Utilisateur;

/** @brief La classe Message est la classe qui permet de créer un message envoyé par un utilisateur par rapport a un ticket
 **
 ** @version 3b
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Message
{
    private:
        /// @brief Variable qui contient l'identifient du message
        QString idMessage;
        Ticket &ticket;
        /// @brief Variable qui contient le contenu du message
        QString contenu;
        /// @brief Variable qui contient l'auteur du message
        Utilisateur *auteur;
        QDateTime date;

    public:
        /// @brief Le constructeur par défaut
        ///
        /// @param utilisateur L'utilisateur a l'origine du message
        /// @param contenu le contenu du message
        Message(Ticket &ticket, Utilisateur &utilisateur, QString contenu);

        /// @brief le destructeur
        ~Message();

        /// @brief La méthode qui permet de connaitre le contenu du message
        ///
        /// @return Le contenu du message
        QString getContenu() const;

        /// @brief La méthode qui permet de connaitre l'identifient du message
        ///
        /// @return L'identifient du message
        QString getIdMessage() const;

        /// @brief La méthode qui permet de connaitre l'auteur du message
        ///
        /// @return L'auteur du message
        Utilisateur *getUtilisateur() const;
        Ticket &getTicket() const;
        QDateTime getDateCreation() const;

        /// @brief La méthode qui permet de définir le contenu d'un message
        ///
        /// @param contenu Le nouveau contenu du message
        void setContenu(QString contenu);

        /// @brief La méthode qui permet de définir l'identifiant d'un message
        ///
        /// @param idMessage Le nouveau identifiant du message
        void setIdMessage(QString idMessage);

        /// @brief La méthode qui permet de définir l'auteur d'un message
        ///
        /// @param utilisateur Le nouvel utilisateur du message
        void setUtilisateur(Utilisateur &utilisateur);

        void setDateCreation(QDateTime date);

};

#endif // MESSAGE_H
