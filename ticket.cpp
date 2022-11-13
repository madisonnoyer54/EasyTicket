#include "ticket.h"

Ticket::Ticket(std::string informations, Categorie categorie) : informations(informations), categorie(categorie)
{
    ouvert = true;
}

Ticket::~Ticket(){

}

void Ticket::setIdTicket(std::string id) {
    idTicket = id;
}

bool Ticket::estOuvert() const {
    return ouvert;
}

const std::string Ticket::getIdTicket() const {
    return idTicket;
}

void Ticket::fermer(){
    ouvert = false;
}

const std::string Ticket::getInformations() const {
    return informations;
}

void Ticket::setInformations(std::string informations) {
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

    os << "[" << ticket.getIdTicket() << "] <" << ticket.getCategorie() << "> " << ticket.getInformations() << " : " << ((ticket.estOuvert()) ? "Ouvert" : "Fermer");

    return os;
}
