#include "ticket.h"

Ticket::Ticket()
{

}

Ticket::~Ticket(){

}

void Ticket::setIdTicket(std::string id){
    idTicket = id;
}

bool Ticket::estOuvert() {
    return ouvert;
}

std::string Ticket::getIdTicket(){
    return idTicket;
}

void Ticket::fermer(){
    ouvert = false;
}

