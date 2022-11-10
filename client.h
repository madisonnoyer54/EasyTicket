#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "utilisateur.h"
#include "categorie.h"
#include <list>
#include "ticket.h"

/** @brief La classe Client est la classe qui permet de crée le compte client d'une personne, on lui attribuer un ou plusieur ticket
 ** La class Client hérite de la class Utilisateur
 **
 ** @version 1
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Client : public Utilisateur
{
    private:
        /// @brief Variable qui contient la liste des tickets du client
        std::list<Ticket> listTickets;

    public:
        /// @brief Le constructeur
        Client();

        /// @brief le destructeur
        ~Client();

        /// @brief Fonction qui permet d'ajouter un nouveau ticket à la list des tickets qui appartient au client
        /// le nouveau ticket est conposer d'information et d'un catégorie
        void nouveauTicket(std::string informations, Categorie categorie);
};

#endif // CLIENT_H
