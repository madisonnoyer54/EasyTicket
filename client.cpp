#include "client.h"

Client::Client(std::string identifiant) : Utilisateur(identifiant)
{
}

Client::~Client()
{

}

void Client::nouveauTicket(std::string informations, Categorie categorie){
    listTickets.push_back(new Ticket(informations, categorie));
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
