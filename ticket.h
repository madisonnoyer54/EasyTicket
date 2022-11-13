#ifndef TICKET_H
#define TICKET_H

// Pour la gestion de l'identifiant
#include <QString>
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


    public:
        /// @brief Le constructeur par défaut définir les champs informations
        /// et categorie de la classe.
        ///
        /// @param informations Informations rentré par le client sur le ticket
        /// @param categorie Categorie du ticket choisis par le client
        Ticket(QString informations, Categorie categorie);

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
        /// @return Le tehcnicien qui gère le ticket
        Technicien* getTechnicien() const;

        /// @brief La méthode qui permet de définir le technicien
        /// qui va gérer le ticket
        ///
        /// @param technicien Le nouveau technicien du ticket
        void setTechnicien(Technicien* technicien);
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
