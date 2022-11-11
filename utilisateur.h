#ifndef UTILISATEUR_H
#define UTILISATEUR_H

// Pour la gestion de l'identifiant
#include <string>

/** @brief La classe Utilisateur est la classe mère de toutes les implémentations de utilisateur (Client et Technicien).
 *
 *  Elle contient deux méthodes abstraites ("le destructeur" et estUnClient)
 *
 ** @version 1a
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Utilisateur
{
    protected:
        /// @brief Variable qui contient l'identifiant de l'utilisateur
        std::string idUtilisateur;

        /// @brief Le constructeur qui assigne le paramètre
        /// idUtilisateur au champs idUtilisateur
        Utilisateur(std::string idUtilisateur);

    public:
        /// @brief le destructeur ne fait rien, mais doit être
        /// défini comme abstrait.
        virtual ~Utilisateur();

        /// @brief La méthode qui retourne l'identifiant de l'utilisateur
        ///
        /// Méthode constante car elle ne fait que retourner un champs
        /// sans le modifier.
        ///
        /// @return l'identifiant de l'utilisateur
        std::string getId() const;

        /// @brief La méthode qui permet de savoir si l'utilisateur est un client
        ///
        /// @return true si l'utilisateur est un client, false sinon
        virtual bool estUnClient() = 0;
};

#endif // UTILISATEUR_H
