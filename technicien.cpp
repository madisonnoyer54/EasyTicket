#include "technicien.h"

Technicien::Technicien(std::string identifiant): Utilisateur(identifiant)
{

}

Technicien::~Technicien()
{

}

Ticket* Technicien::getTicket() const{
    return ticket;
}

void Technicien::fermerTicket(){
    ticket->fermer();
}

bool Technicien::estUnClient() {
    return false;
}

std::ostream& operator<<(std::ostream& os, Technicien const& technicien) {
    os << "[Technicien] " << technicien.getId() << " {" << std::endl;

    // On évite d'afficher un objet non défini
    if(technicien.getTicket() != nullptr) os << *technicien.getTicket() << std::endl;
    os << "}" << std::endl;

    return os;
}
