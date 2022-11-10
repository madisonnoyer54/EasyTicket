#ifndef TICKET_H
#define TICKET_H

// Pour la gestion de l'identifiant
#include <string>
#include "categorie.h"
#include "technicien.h"


/** @brief La classe Ticket est la classe qui permet de crée et d'avoir les information du ticket.
 **
 ** @version 1
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Ticket
{

    private:
        /// @brief Variable qui contient le numéro du ticket
        std::string idTicket;

        /// @brief Variable qui contient l'information ouvert/fermer du ticket
        /// Vrai sur le ticket est ouvert, faux sinon
        bool ouvert;

        /// @brief Variable qui contient les informations du ticket
        std::string informations;

        /// @brief Variable qui désigne la catégorie du ticket
        Categorie categorie;

        /// @brief Variable qui désigne le technicien qui s'occupe du ticket
        Technicien technicien;


    public:
        /// @brief Le constructeur
        Ticket();

        /// @brief le destructeur
        ~Ticket();

        /// @brief La fonction permet de retourner le numéro du ticket
        std::string getIdTicket();

        /// @brief La fonction permet de changer le numéro du ticket
        void setIdTicket(std::string nom);

        /// @brief La fonction permet de savoir si le ticket est ouvert ou non.
        /// Cette fonction retourne Vrai si le ticket est ouvert et faux sinon
        bool estOuvert();

        /// @brief La fonction permet de fermer le ticket
        void fermer();
    };

#endif // TICKET_H
