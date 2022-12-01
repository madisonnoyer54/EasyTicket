#include "ticket.h"

Ticket::Ticket(Client *client, QString informations, Categorie categorie) : informations(informations), categorie(categorie), client(client)
{
    listMessages = new QVector<Message*>();
    ouvert = true;
    dateCreation = QDate::currentDate();
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

Client* Ticket::getClient() const {
    return client;
}

void Ticket::setTechnicien(Technicien* technicien) {
    this->technicien = technicien;
}

const QDate &Ticket::getDateCreation() const {
    return dateCreation;
}

void Ticket::setDateCreation(QDate date) {
    dateCreation = date;
}

const QVector<Message *> &Ticket::getMessages() const {
    return *listMessages;
}

Message &Ticket::ajouterMessage(Utilisateur &utilisateur, QString message) {
    Message *msg = new Message(*this, utilisateur,message);
    listMessages->append(msg);
    notifier();

    return *msg;
}

#include <QDebug>

void Ticket::ajouterMessage(Message &message) {
    bool isIn = false;
    for(Message *messageInList : listMessages->toStdVector()) isIn |=  (messageInList->getIdMessage() == message.getIdMessage());
    if(!isIn) listMessages->push_back(&message);
}
