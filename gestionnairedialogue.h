#ifndef GESTIONNAIREDIALOGUE_H
#define GESTIONNAIREDIALOGUE_H

/// Permet de retourner un objet de type Client pour la fonction getClient
#include "client.h"
/// Permet de retourner un objet de type Technicien pour la fonction getTechnicien
#include "technicien.h"
/// Permet de gérer une hashmap d'utilisateur
#include <map>

/** @brief La classe GestionnaireDialogue est la classe qui permet d'interagir avec les différents utilisateurs
 **
 ** @version 1a
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class GestionnaireDialogue
{
    private:
       /// @brief Variable qui contient la hashmap des utilisateurs par rapport à leur identifiant
       std::map<QString, Utilisateur*> listUtilisateurs;
       /// @brief Variable qui contient la file d'attente des tickets non traité
       std::vector<Ticket*> fileTicket;

    public:
        /// @brief Le constructeur
        GestionnaireDialogue();

        /// @brief le destructeur
        ~GestionnaireDialogue();

        /// @brief La méthode qui permet de retourner le client par rapport à son identifiant
        ///
        /// @param identifiant Identifiant du client
        ///
        /// @return Le client possèdant l'identifiant entré en paramètre
        Client* getClient(QString identifiant);

        /// @brief La méthode qui permet de retourner le technicien par rapport à son identifiant
        ///
        /// @param identifiant Identifiant du technicien
        ///
        /// @return Le technicien possédant l'identifiant entré en paramètre
        Technicien* getTechnicien(QString identifiant);

        /// @brief La méthode qui permet d'avoir la map des utilisateurs
        ///
        /// @return Map contenant tout les utilisateurs
        std::map<QString, Utilisateur*> getUtilisateurs() const;

        /// @brief La méthode qui permet d'assigner un ticket à un Technicien
        /// ou a le mettre en file d'attente si il faut
        ///
        /// @param ticket Le ticket
        void assignerTicket(Ticket* ticket);

        /// @brief La méthode qui permet d'assigner un ticket à un Technicien
        ///
        /// @param technicien Le technicien
        void assignerTicket(Technicien* technicien);
};

/// @brief Fonction qui permet d'afficher les données du gestionnaire sur la sortie standard
///
/// @param os Flux de la sortie standard
///
/// @param technicien Constante du gestionnaire
///
/// @return Flux de la sortie standard
std::ostream& operator<<(std::ostream& os, GestionnaireDialogue const& dialog);

#endif // GESTIONNAIREDIALOGUE_H
