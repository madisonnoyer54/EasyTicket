#include "ticket.h"

Ticket::Ticket(std::string informations, Categorie categorie) : informations(informations), categorie(categorie)
{

}

Ticket::~Ticket(){

}

void Ticket::setIdTicket(std::string id) {
    idTicket = id;
}

bool Ticket::estOuvert() const {
    return ouvert;
}

std::string Ticket::getIdTicket() const {
    return idTicket;
}

void Ticket::fermer(){
    ouvert = false;
}

std::string Ticket::getInformations() const {
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

std::ostream& operator<<(std::ostream& os, Ticket const& ticket) {
    os << "[" << ticket.getCategorie() << "] " << ticket.getInformations() << " : " << (ticket.estOuvert() ? "Ouvert" : "Fermer");

    return os;
}
