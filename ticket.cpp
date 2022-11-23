#include "ticket.h"

Ticket::Ticket(QString informations, Categorie categorie) : informations(informations), categorie(categorie)
{
    listMessages = new QVector<Message*>();
    ouvert = true;
}

Ticket::~Ticket(){
}

void Ticket::setIdTicket(QString id) {
    idTicket = id;
}

bool Ticket::estOuvert() const {
    return ouvert;
}

const QString Ticket::getIdTicket() const {
    return idTicket;
}

void Ticket::fermer(){
    ouvert = false;
}

const QString Ticket::getInformations() const {
    return informations;
}

void Ticket::setInformations(QString informations) {
    this->informations = informations;
}

Categorie Ticket::getCategorie() const {
    return categorie;
}

void Ticket::setCategorie(Categorie categorie) {
    this->categorie = categorie;
}

Technicien* Ticket::getTechnicien() const {
    return technicien;
}

void Ticket::setTechnicien(Technicien* technicien) {
    this->technicien = technicien;
}

const QVector<Message *> &Ticket::getMessages() const {
    return *listMessages;
}

void Ticket::ajouterMessage(Utilisateur &utilisateur, QString message) {
    listMessages->append(new Message(utilisateur, "1",message));
    notifier();
}
