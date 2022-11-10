#ifndef TECHNICIEN_H
#define TECHNICIEN_H

#include "utilisateur.h"
#include "ticket.h"


/** @brief La classe Technicien est la classe qui permet de crée un technicien
 ** Le tecnicien contient un Ticket et une ou plusieur catégorie(s)
 ** La classe Technicien hérite de la class Utilisateur
 **
 ** @version 1
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Technicien : public Utilisateur
{
    private:
        /// @brief Variable qui contient le ticket utiliser par le technicien
        Ticket ticket;

        /// @brief Variable qui contient la/les catégorie(s) du Technicien
        /// Une catégorie définie les differentes action que le technicien peut effectuer sur le ticket
        Categorie lesCategories[4];

    public:
        /// @brief Le constructeur
        Technicien();

        /// @brief le destructeur
        ~Technicien();

        /// @brief Fonction qui permet de retourner le ticket du technicien
        Ticket getTicket();

        /// @brief Fonction qui permet de fermer le ticket du technicien
        void fermerTicket();
};

#endif // TECHNICIEN_H
