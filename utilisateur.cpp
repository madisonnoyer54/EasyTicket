#include "utilisateur.h"

Utilisateur::Utilisateur(QString idUtilisateur) : idUtilisateur(idUtilisateur)
{

}


Utilisateur::~Utilisateur()
{

}

const QString Utilisateur::getId() const {
    return idUtilisateur;
}
