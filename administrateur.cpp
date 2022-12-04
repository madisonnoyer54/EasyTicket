#include "administrateur.h"

Administrateur::Administrateur(QString identifiant) : Utilisateur(identifiant)
{

}

Administrateur::~Administrateur(){

}

bool Administrateur::estUnClient() {
    return false;
}
