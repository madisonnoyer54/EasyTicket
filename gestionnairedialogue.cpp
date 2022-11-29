#include "gestionnairedialogue.h"
#include <QSqlDatabase>

GestionnaireDialogue::GestionnaireDialogue() :
    listUtilisateurs(*new QMap<QString, Utilisateur*>())
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
}

GestionnaireDialogue::~GestionnaireDialogue()
{
    qDeleteAll(listUtilisateurs);
}

Client* GestionnaireDialogue::getClient(QString identifiant){

    // La map possède t'elle une valeur pour l'identifiant ?

    if(listUtilisateurs.count(identifiant)) {
        if(listUtilisateurs[identifiant]->estUnClient()) return (Client*) listUtilisateurs[identifiant];
        else return nullptr;
    }

    if(identifiant.startsWith("TEST")) {
        // Aucun utilisateur possède cet identifiant, afin de tester
        // Un nouveau client va être créé
        Client* res = new Client(identifiant);

        listUtilisateurs[identifiant] = res;
        return res;
    }

    return nullptr;
}

Technicien* GestionnaireDialogue::getTechnicien(QString identifiant){
    // La map possède t'elle une valeur pour l'identifiant ?

    if(listUtilisateurs.count(identifiant)) {
        if(!listUtilisateurs[identifiant]->estUnClient()) return (Technicien*) listUtilisateurs[identifiant];
        else return nullptr;
    }

    if(identifiant.startsWith("TEST")) {
        // Aucun utilisateur possède cet identifiant, afin de tester
        // Un nouveau client va être créé
        Technicien* res = new Technicien(identifiant);

        listUtilisateurs[identifiant] = res;

        return res;
    }

    return nullptr;
}

const QMap<QString, Utilisateur*>& GestionnaireDialogue::getUtilisateurs() const {
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
                technicien->setTicket(ticket);
            }
        }
    }

    // Si le ticket n'a pas trouvé de technicien apte à
    // le traiter, on l'ajoute dans une file d'attente
    if(ticket->getTechnicien() == nullptr) {
        fileTicket.push_back(ticket);
    }
    notifier();
}

void GestionnaireDialogue::assignerTicket(Technicien* technicien) {
    Ticket *ticketDonne = nullptr;
    for(int i = 0; i < fileTicket.count(); i++) {
        Ticket* ticket = fileTicket[i];
        if(technicien->peutTraiter(*ticket) && ticket->estOuvert()) {
            technicien->setTicket(ticket);
            ticketDonne = ticket;
        }
    }
    if(ticketDonne != nullptr)
        fileTicket.erase(std::remove(fileTicket.begin(), fileTicket.end(), ticketDonne));
    notifier();
}
