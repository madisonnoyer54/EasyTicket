#ifndef GESTIONNAIREDIALOGUE_H
#define GESTIONNAIREDIALOGUE_H

#include <string>
#include "client.h"
#include "technicien.h"


/** @brief La classe GestionnaireDialogue est la classe qui permet d'interagire avec les différents utilisateur
 **
 ** @version 1
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class GestionnaireDialogue
{
    private:
       /// @brief Variable qui contient la list des utilisateurs
       std::list<Utilisateur> listUtilisateurs;


    public:
        /// @brief Le constructeur
        GestionnaireDialogue();

        /// @brief le destructeur
        ~GestionnaireDialogue();

        /// @brief Fonction qui permet de retourner le client par rapport à son identifiant
        Client getClient(std::string indentifiant);

        /// @brief Fonction qui permet de retourner le technicien par rapport à son identifiant
        Technicien getTechnicien(std::string indentifiant);
};

#endif // GESTIONNAIREDIALOGUE_H
