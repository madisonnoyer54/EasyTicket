#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

/// Permet au administrateur d'hériter d'utilisateur
#include "utilisateur.h"


/** @brief La classe Administrateur est la classe qui permet de créer le compte administrateur d'une personne
 ** La class Administrateur hérite de la classe Utilisateur
 **
 ** Elle contientl les methodes pour fermer le ticket ou le
 ** construite (à l'aide du constructeur)
 **
 ** @version 3c
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Administrateur : public Utilisateur
{
    public:
        /// @brief Le constructeur par défaut
        ///
        /// @param identifiant L'indentifiant de l'utilisateur
        Administrateur(QString identifiant);

         /// @brief le destructeur ne fait rien
        ~Administrateur();

        /// @brief La méthode qui permet de savoir si l'utilisateur est un client
        ///
        /// @return false
        bool estUnClient() override;
};

#endif // ADMINISTRATEUR_H
