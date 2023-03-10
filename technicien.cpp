#include "technicien.h"

Technicien::Technicien(QString identifiant): Utilisateur(identifiant) {
}

Technicien::Technicien(QString identifiant, QVector<Categorie> categories) : Utilisateur(identifiant), categories(categories) {
}

Technicien::~Technicien() {

}

Ticket* Technicien::getTicket() const {
    return ticket;
}

void Technicien::setTicket(Ticket* ticket) {
    this->ticket = ticket;
    if(ticket != nullptr) ticket->setTechnicien(this);
}

const QVector<Categorie> Technicien::getCategories() const {
    return categories;
}

void Technicien::addCategorie(Categorie categorie) {
    categories.push_back(categorie);
}

void Technicien::removeCategorie(Categorie categorie) {
    categories.erase(std::remove(categories.begin(), categories.end(), categorie), categories.end());
}

void Technicien::fermerTicket() {
    if(ticket != nullptr) {
        ticket->fermer();
        ticket = nullptr;
    }
}

bool Technicien::estUnClient() {
    return false;
}

bool Technicien::peutTraiter(Ticket& ticket) {
    bool res = false;
    if(this->ticket == nullptr){
        // Le technicien ne traite pas un ticket

        for(int i = 0; i < categories.size(); i++) {
            Categorie c = categories[i];

            // Si le ticket possède une catégorie similaire à celle du technicien,
            // alors on retourne vrai, sinon on passe à la
            // catégorie suivante
            if(ticket.getCategorie() == c) res |= true;
        }
    }

    return res;
}
