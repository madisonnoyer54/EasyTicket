 #include "client.h"

Client::Client(QString identifiant) : Utilisateur(identifiant)
{
    listTickets = new QVector<Ticket *>();
}

Client::~Client()
{
    qDeleteAll(*listTickets);
}

Ticket& Client::nouveauTicket(QString informations, Categorie categorie){
    Ticket* ticket = new Ticket(this, informations, categorie);
    listTickets->push_front(ticket);
    return *ticket;
}

Ticket& Client::getTicket(int pos) const {
    return *listTickets->at(pos);
}

void Client::ajouterTicket(Ticket &ticket) {
    listTickets->push_back(&ticket);
}

const QVector<Ticket*>& Client::getTickets() const {
    return *listTickets;
}

bool Client::estUnClient() {
    return true;
}
