#include "gestionnairedialogue.h"

GestionnaireDialogue::GestionnaireDialogue()
{

}

GestionnaireDialogue::~GestionnaireDialogue()
{
}

Client* GestionnaireDialogue::getClient(QString identifiant){

    // La map possède t'elle une valeur pour l'identifiant ?

    if(listUtilisateurs.count(identifiant)) {

        if(listUtilisateurs[identifiant]->estUnClient()) return (Client*) listUtilisateurs[identifiant];
        // L'utilisateur n'est pas un client. On retourne null pour l'instant.
        // A changer dans une prochaine version
        else return nullptr;

    }

    // Aucun utilisateur possède cet identifiant, afin de tester
    // Un nouveau client va être créé
    Client* res = new Client(identifiant);

    listUtilisateurs[identifiant] = res;

    return res;
}

Technicien* GestionnaireDialogue::getTechnicien(QString identifiant){
    // La map possède t'elle une valeur pour l'identifiant ?

    if(listUtilisateurs.count(identifiant)) {

        if(!listUtilisateurs[identifiant]->estUnClient()) return (Technicien*) listUtilisateurs[identifiant];
        // L'utilisateur n'est pas un client. On retourne null pour l'instant.
        // A changer dans une prochaine version
        else return nullptr;

    }

    // Aucun utilisateur possède cet identifiant, afin de tester
    // Un nouveau client va être créé
    Technicien* res = new Technicien(identifiant);

    listUtilisateurs[identifiant] = res;

    return res;
}

QMap<QString, Utilisateur*> GestionnaireDialogue::getUtilisateurs() const {
    return listUtilisateurs;
}

void GestionnaireDialogue::assignerTicket(Ticket* ticket) {

    // On regarde l'ensemble des utilisateurs actuels
    for(const auto& kv : listUtilisateurs.toStdMap()) {

        // Si l'utilisateur est un technicien
        // et qu'il peut traiter le ticket
        // On lui assigne le ticket
        // Sinon on passe à l'utilisateur suivant
        if(!kv.second->estUnClient() && ticket->getTechnicien() == nullptr) {
            Technicien* technicien = (Technicien*) kv.second;
            if(technicien->peutTraiter(*ticket)) {
                technicien->setTicket(*ticket);
            }
        }
    }

    // Si le ticket n'a pas trouvé de technicien apte à
    // le traiter, on l'ajoute dans une file d'attente
    if(ticket->getTechnicien() == nullptr) {
        fileTicket.push_back(ticket);
    }
}

void GestionnaireDialogue::assignerTicket(Technicien* technicien) {
    for(int i = 0; i < fileTicket.count(); i++) {
        Ticket* ticket = fileTicket[i];
        if(technicien->peutTraiter(*ticket) && ticket->estOuvert()) {
            technicien->setTicket(*ticket);
        }
    }
    if(technicien->getTicket() != nullptr)
        fileTicket.erase(std::remove(fileTicket.begin(), fileTicket.end(), technicien->getTicket()));
}

std::ostream& operator<<(std::ostream& os, GestionnaireDialogue const& dialog) {
    // kv étant un couple key value, avec pour clé l'identifiant et value l'utilisateur
    for(const auto& kv : dialog.getUtilisateurs().toStdMap()) {
        if(kv.second->estUnClient())os << *(Client *const) kv.second;
        else os << *(Technicien *const) kv.second;
        os << std::endl;
    }

    return os;
}
