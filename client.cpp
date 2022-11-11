#include "client.h"

Client::Client(std::string identifiant) : Utilisateur(identifiant)
{
}

Client::~Client()
{
    for(Ticket* ticket : listTickets) {
        delete ticket;
    }
}

Ticket* Client::nouveauTicket(std::string informations, Categorie categorie){
    Ticket* ticket = new Ticket(informations, categorie);

    // Id du ticket qui sera l'identifiant de l'utilisateur suivis d'un numéro

    ticket->setIdTicket(idUtilisateur + std::to_string(prochainIdTicket++));
    listTickets.push_back(ticket);

    return ticket;
}


std::vector<Ticket*> Client::getTickets() const {
    return listTickets;
}

bool Client::estUnClient() {
    return true;
}

std::ostream& operator<<(std::ostream& os, Client const& client) {
    os << "[Client] " << client.getId() << " {" << std::endl;
    for(const Ticket* ticket : client.getTickets()) {
        os << "\t" << *ticket << ", " << std::endl;
    }
    os << "}" << std::endl;

    return os;
}
