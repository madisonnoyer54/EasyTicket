#include "utilisateur.h"

Utilisateur::Utilisateur(std::string idUtilisateur) : idUtilisateur(idUtilisateur)
{

}


Utilisateur::~Utilisateur()
{

}

std::string Utilisateur::getId() const {
    return idUtilisateur;
}
