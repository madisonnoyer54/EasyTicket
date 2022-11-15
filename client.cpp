 #include "client.h"

Client::Client(QString identifiant) : Utilisateur(identifiant)
{
}

Client::~Client()
{
}

Ticket& Client::nouveauTicket(QString informations, Categorie categorie){
    Ticket* ticket = new Ticket(informations, categorie);

    // Id du ticket qui sera l'identifiant de l'utilisateur suivis d'un numéro

    ticket->setIdTicket(idUtilisateur + QString::number(prochainIdTicket++));
    listTickets.push_back(ticket);

    return *ticket;
}


const QVector<Ticket*>& Client::getTickets() const {
    return listTickets;
}

bool Client::estUnClient() {
    return true;
}

std::ostream& operator<<(std::ostream& os, Client const& client) {
    os << "[Client] " << client.getId().toUtf8().constData() << " {" << std::endl;
    QVector<Ticket*> tickets = client.getTickets();
    for(int i = 0; i < tickets.size(); i++) {
        Ticket* ticket = tickets[i];
        os << "\t" << *ticket << ", " << std::endl;
    }
    os << "}" << std::endl;

    return os;
}
