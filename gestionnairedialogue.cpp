#include "gestionnairedialogue.h"

GestionnaireDialogue::GestionnaireDialogue()
{

}

GestionnaireDialogue::~GestionnaireDialogue()
{

}

Client* GestionnaireDialogue::getClient(std::string identifiant){

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

Technicien* GestionnaireDialogue::getTechnicien(std::string identifiant){
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

std::map<std::string, Utilisateur*> GestionnaireDialogue::getUtilisateurs() const {
    return listUtilisateurs;
}

std::ostream& operator<<(std::ostream& os, GestionnaireDialogue const& dialog) {
    // kv étant un couple key value, avec pour clé l'identifiant et value l'utilisateur
    for(const auto& kv : dialog.getUtilisateurs()) {
        if(kv.second->estUnClient())os << *(Client *const) kv.second;
        else os << *(Technicien *const) kv.second;
        os << std::endl;
    }

    return os;
}
