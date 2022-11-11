#ifndef TECHNICIEN_H
#define TECHNICIEN_H

#include "utilisateur.h"
#include "ticket.h"

// Un Technicien connait un ticket, il faut donc déclarer
// cette classe (Mais il est inutile de la définir)
class Ticket;


/** @brief La classe Technicien est la classe qui permet de créer un technicien
 ** Le tecnicien connait un Ticket et une ou plusieur catégorie(s) de ticket
 ** La classe Technicien hérite de la class Utilisateur
 **
 ** @version 1a
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Technicien : public Utilisateur
{
    private:
        /// @brief Variable qui contient le ticket utiliser par le technicien
        Ticket *ticket;

        /// @brief Variable qui contient la/les catégorie(s) du Technicien
        /// Une catégorie définie les differentes action que le technicien peut effectuer sur le ticket
        Categorie lesCategories[4];

    public:
        /// @brief Le constructeur
        /// @param identifiant L'identifiant du technicien
        Technicien(std::string identifiant);

        /// @brief le destructeur ne fait rien
        ~Technicien();

        /// @brief La méthode qui permet de retourner le ticket du technicien
        ///
        /// @return Le ticket que possede le technicien
        Ticket *getTicket() const;

        /// @brief La méthode qui permet de fermer le ticket que gère le technicien
        void fermerTicket();

        /// @brief La méthode qui permet de savoir si l'utilisateur est un client
        ///
        /// @return false
        bool estUnClient() override;
};

/// @brief Fonction qui permet d'afficher un technicien sur la sortie standard
///
/// @param os Flux de la sortie standard
///
/// @param technicien Constante du technicien
///
/// @return Flux de la sortie standard
std::ostream& operator<<(std::ostream& os, Technicien const& technicien);

#endif // TECHNICIEN_H
