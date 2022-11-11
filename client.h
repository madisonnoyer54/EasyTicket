#ifndef CLIENT_H
#define CLIENT_H

/// Permet au client d'hériter d'utilisateur
#include "utilisateur.h"
/// Permet d'ajouter un champs de parametre categorie dans la méthode nouveauTicket
#include "categorie.h"
/// Permet de définir le type Ticket au vecteur
#include "ticket.h"
/// Permet de gérer une liste de ticket
#include <vector>
/// Permet de gérer l'affichage sur la sortie standard
#include <iostream>

/** @brief La classe Client est la classe qui permet de crée le compte client d'une personne, on lui attribuer un ou plusieur ticket
 ** La class Client hérite de la classe Utilisateur
 **
 ** @version 1a
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Client : public Utilisateur
{
    private:
        /// @brief Variable qui contient la liste des tickets du client
        std::vector<Ticket*> listTickets;

    public:
        /// @brief Le constructeur qui va appeler
        /// le constructeur de Utilisateur
        ///
        /// @param identifiant L'identifiant de l'utilisateur
        Client(std::string identifiant);

        /// @brief le destructeur
        ~Client();

        /// @brief La méthode qui permet d'ajouter un nouveau ticket à la list des tickets qui appartiennent au client
        /// le nouveau ticket est conposé d'informations et d'une catégorie
        ///
        /// @param informations Les informations du ticket
        ///
        /// @param categorie La categorie du ticket
        void nouveauTicket(std::string informations, Categorie categorie);

        /// @brief La méthode qui permet de connaitre la liste des tickets que possède l'utilisateur
        ///
        /// @return Un vecteur contenant la liste des tickets d'un utilisateur
        std::vector<Ticket*> getTickets() const;

        /// @brief La méthode qui permet de savoir si l'utilisateur est un client
        ///
        /// @return true
        bool estUnClient() override;
};

/// @brief Fonction qui permet d'afficher un client sur la sortie standard
///
/// @param os Flux de la sortie standard
///
/// @param client Constante du client
///
/// @return Flux de la sortie standard
std::ostream& operator<<(std::ostream& os, Client const& client);

#endif // CLIENT_H
