#ifndef UTILISATEUR_H
#define UTILISATEUR_H

// Pour la gestion de l'identifiant
#include <string>

/** @brief La classe Utilisateur est la classe qui permet de crée differents utilisateur tel que les clients et les technicien
 ** Cette class est abstraite
 ** @version 1
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Utilisateur
{
    private:
        /// @brief Variable qui contient l'identifiant de l'utilisateur
        std::string idUtilisateur;


    public:
        /// @brief Le constructeur
        Utilisateur();

        /// @brief le destructeur
        ~Utilisateur();

        /// @brief Fonction qui retourne l'identifiant de l'utilisateur
        virtual std::string getId() = 0;
};

#endif // UTILISATEUR_H
