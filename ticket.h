#ifndef TICKET_H
#define TICKET_H

// Pour la gestion de l'identifiant
#include <string>
#include "categorie.h"
#include "technicien.h"

class Technicien;

/** @brief La classe Ticket est la classe qui permet de créer un ticket
 **
 ** Elle contientl les methodes pour fermer le ticket ou le
 ** construite (à l'aide du constructeur)
 **
 ** @version 1a
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
        bool ouvert = true;

        /// @brief Variable qui contient les informations du ticket
        std::string informations;

        /// @brief Variable qui désigne la catégorie du ticket
        Categorie categorie;

        /// @brief Variable qui désigne le technicien qui s'occupe du ticket
        Technicien* technicien;


    public:
        /// @brief Le constructeur par défaut définir les champs informations
        /// et categorie de la classe.
        ///
        /// @param informations Informations rentré par le client sur le ticket
        /// @param categorie Categorie du ticket choisis par le client
        Ticket(std::string informations, Categorie categorie);

        /// @brief le destructeur ne fait rien
        ~Ticket();

        /// @brief La méthode permet de retourner l'identifiant du ticket
        ///
        /// @return L'identifiant du ticket
        std::string getIdTicket() const;

        /// @brief La méthode permet de changer le numéro du ticket
        ///
        /// @param id Le nouvel identifiant du ticket
        void setIdTicket(std::string id);

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
        std::string getInformations() const;

        /// @brief La méthode permet de définir des informations pour rapport à un ticket
        ///
        /// @param Les nouvelles informations par rapport à un ticket
        void setInformations(std::string informations);

        /// @brief La méthode qui permet de connaitre la categorie d'un ticket
        ///
        /// @return La categorie d'un ticket
        Categorie getCategorie() const;

        /// @brief La méthode qui permet de définir la categorie d'un ticket
        ///
        /// @param La nouvelle categorie du ticket
        void setCategorie(Categorie categorie);
    };

/// @brief Fonction qui permet d'afficher un ticket sur la sortie standard
///
/// @param os Flux de la sortie standard
///
/// @param ticket Constante du ticket
///
/// @return Flux de la sortie standard
std::ostream& operator<<(std::ostream& os, Ticket const& ticket);

#endif // TICKET_H
