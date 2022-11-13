 #include "client.h"

Client::Client(QString identifiant) : Utilisateur(identifiant)
{
}

Client::~Client()
{
    for(Ticket* ticket : listTickets) {
        delete ticket;
    }
}

Ticket& Client::nouveauTicket(QString informations, Categorie categorie){
    Ticket* ticket = new Ticket(informations, categorie);

    // Id du ticket qui sera l'identifiant de l'utilisateur suivis d'un numéro

    ticket->setIdTicket(idUtilisateur + QString::number(prochainIdTicket++));
    listTickets.push_back(ticket);

    return *ticket;
}


std::vector<Ticket*> Client::getTickets() const {
    return listTickets;
}

bool Client::estUnClient() {
    return true;
}

std::ostream& operator<<(std::ostream& os, Client const& client) {
    os << "[Client] " << client.getId().toUtf8().constData() << " {" << std::endl;
    for(const Ticket* ticket : client.getTickets()) {
        os << "\t" << *ticket << ", " << std::endl;
    }
    os << "}" << std::endl;

    return os;
}
