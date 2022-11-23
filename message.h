#ifndef MESSAGE_H
#define MESSAGE_H

// Pour la gestion de l'identifiant et du contenu
#include <QString>
// Permet au message d'avoir son utilisateur
#include "utilisateur.h"

// Un Technicien connait un utilisateur, il faut donc déclarer
// cette classe (Mais il est inutile de la définir)
class Utilisateur;

/** @brief La classe Message est la classe qui permet de crée le message de la personne, on peut utilise cette classe pour modifier le message ou autre
 **
 ** @version 1a
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Message
{
    private:
        /// @brief Variable qui contient l'identifient du message
        QString idMessage;
        /// @brief Variable qui contient le contenu du message
        QString contenu;
        /// @brief Variable qui contient l'utilisateur du message
        Utilisateur *utilisateur;
        /// @brief Variable qui contient la date de création du message
        // Date dateDeCreation;

    public:
        /// @brief Le constructeur qui va appeler
        /// le constructeur du message
        ///
        /// @param idMessage L'identifiant du message
        /// @param contenu le contenu du message
        Message(QString idMessage,QString contenu);

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

        /// @brief La méthode qui permet de connaitre l'utilisateur du message
        ///
        /// @return L'utilisateur du message
        Utilisateur *getUtilisateur() const;

        /// @brief La méthode qui permet de définir le contenu d'un message
        ///
        /// @param contenu Le nouveau contenu du message
        void setContenu(QString contenu);

        /// @brief La méthode qui permet de définir l'identifiant d'un message
        ///
        /// @param idMessage Le nouveau identifiant du message
        void setIdMessage(QString idMessage);

        /// @brief La méthode qui permet de définir l'utlisateur d'un message
        ///
        /// @param utilisateur Le nouveau utilisateur du message
        void setUtilisateur(Utilisateur &utilisateur);



};

#endif // MESSAGE_H
