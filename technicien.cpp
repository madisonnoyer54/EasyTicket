#include "technicien.h"

Technicien::Technicien(std::string identifiant): Utilisateur(identifiant) {
}

Technicien::Technicien(std::string identifiant, std::vector<Categorie> categories) : Utilisateur(identifiant), categories(categories) {

}

Technicien::~Technicien() {

}

Ticket* Technicien::getTicket() const {
    return ticket;
}

void Technicien::setTicket(Ticket* ticket) {
    this->ticket = ticket;
    ticket->setTechnicien(this);
}

const std::vector<Categorie> Technicien::getCategories() const {
    return categories;
}

void Technicien::addCategorie(Categorie categorie) {
    categories.push_back(categorie);
}

void Technicien::removeCategorie(Categorie categorie) {
    categories.erase(std::remove(categories.begin(), categories.end(), categorie), categories.end());
}

void Technicien::fermerTicket() {
    ticket->fermer();
    ticket = nullptr;
}

bool Technicien::estUnClient() {
    return false;
}

bool Technicien::peutTraiter(Ticket* ticket) {
    bool res = false;
    if(this->ticket == 0){
        // Le technicien ne traite pas un ticket

        for(Categorie c : categories) {

            // Si le ticket possède une catégorie similaire à celle du technicien,
            // alors on retourne vrai, sinon on passe à la
            // catégorie suivante
            if(ticket->getCategorie() == c) res |= true;
        }
    }

    return res;
}

std::ostream& operator<<(std::ostream& os, Technicien const& technicien) {
    os << "[Technicien] " << technicien.getId() << " {" << std::endl;
    os << "\tCategories : ";
    for(Categorie categorie : technicien.getCategories()) os << categorie << ", ";
    os << "\n";
    // On évite d'afficher un objet non défini
    if(technicien.getTicket() != 0) os << "\tDoit gerer : " << technicien.getTicket()->getIdTicket() << std::endl;
    os << "}" << std::endl;

    return os;
}
