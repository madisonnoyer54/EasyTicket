#include "message.h"


Message::Message(QString idMessage,QString contenu)
{
 this->idMessage = idMessage;
 this->contenu = contenu;
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
    return utilisateur;
}

void Message::setContenu(QString contenu){
    this->contenu = contenu;
}

void Message::setIdMessage(QString idMessage){
    this->idMessage = idMessage;
}

void Message::setUtilisateur(Utilisateur &utilisateur){
    this->utilisateur = &utilisateur;
}
