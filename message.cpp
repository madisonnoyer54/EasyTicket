#include "message.h"


Message::Message(Utilisateur &utilisateur, QString idMessage, QString contenu) : idMessage(idMessage), contenu(contenu), auteur(&utilisateur)
{
}

Message::~Message(){

}

QString Message::getContenu() const {
    return contenu;
}


QString Message::getIdMessage() const{
    return idMessage;
}

Utilisateur* Message::getUtilisateur() const{
    return auteur;
}

void Message::setContenu(QString contenu){
    this->contenu = contenu;
}

void Message::setIdMessage(QString idMessage){
    this->idMessage = idMessage;
}

void Message::setUtilisateur(Utilisateur &utilisateur){
    this->auteur = &utilisateur;
}
