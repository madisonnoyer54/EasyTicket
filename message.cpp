#include "message.h"


Message::Message(Ticket &ticket, Utilisateur &utilisateur, QString contenu) : ticket(ticket), contenu(contenu), auteur(&utilisateur)
{
    date = QDateTime::currentDateTime();
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

Ticket &Message::getTicket() const {
    return ticket;
}

QDateTime Message::getDateCreation() const {
    return date;
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

void Message::setDateCreation(QDateTime date) {
    this->date = date;
}
