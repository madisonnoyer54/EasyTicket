#include "ticket.h"

Ticket::Ticket(QString informations, Categorie categorie) : informations(informations), categorie(categorie)
{
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

std::ostream& operator<<(std::ostream& os, Ticket const& ticket) {

    os << "[" << ticket.getIdTicket().toUtf8().constData() << "] <" << ticket.getCategorie() << "> " << ticket.getInformations().toUtf8().constData() << " : " << ((ticket.estOuvert()) ? "Ouvert" : "Fermer");

    return os;
}
