#include "gestionnairedialogue.h"

GestionnaireDialogue::GestionnaireDialogue() :
    listUtilisateurs(*new QMap<QString, Utilisateur*>())
{
    QString targetDb = QDir::currentPath().append("/EasyTicket.db");
    if(!QFile::exists(targetDb)){
        QFile::copy(":/ressources/EasyTicket.db", targetDb);
    }

    db.setDatabaseName(targetDb);
    db.open();
}

GestionnaireDialogue::~GestionnaireDialogue()
{
    qDeleteAll(listUtilisateurs);
    db.close();
}

Client* GestionnaireDialogue::getClient(QString identifiant){

    // La map possède t'elle une valeur pour l'identifiant ?
    if(listUtilisateurs.count(identifiant)) {
        if(listUtilisateurs[identifiant]->estUnClient()) return (Client*) listUtilisateurs[identifiant];
        else return nullptr;
    }

    Client *client = nullptr;
    QSqlQuery query;
    query.exec("SELECT * FROM Client WHERE UPPER(idUtilisateur) = UPPER('" + identifiant + "')");
    if (query.next()) {
        client = new Client(query.value(0).toString());
        listUtilisateurs[identifiant] = client;
        chargerTickets(*client);
    }

    return client;
}

Technicien* GestionnaireDialogue::getTechnicien(QString identifiant){
    // La map possède t'elle une valeur pour l'identifiant ?

    if(listUtilisateurs.count(identifiant)) {
        if(!listUtilisateurs[identifiant]->estUnClient()) return (Technicien*) listUtilisateurs[identifiant];
        else return nullptr;
    }

    Technicien *technicien = nullptr;
    QSqlQuery query;
    query.exec("SELECT * FROM Technicien WHERE UPPER(idUtilisateur) = UPPER('" + identifiant + "')");
    if (query.next()) {
        technicien = new Technicien(query.value(0).toString());
        listUtilisateurs[identifiant] = technicien;
    }

    return technicien;
}

const QMap<QString, Utilisateur*>& GestionnaireDialogue::getUtilisateurs() const {
    return listUtilisateurs;
}

void GestionnaireDialogue::chargerTickets(Client &client) {
    QSqlQuery query;
    query.exec("SELECT * FROM Ticket WHERE UPPER(idClient) = UPPER('" + client.getId() + "')");

    while(query.next()) {
        Categorie c = Categorie::assistance;
        QString categorie = query.value("nomCategorie").toString();
        if(categorie == "Logiciel") c = Categorie::logiciel;
        if(categorie == "Materiel") c = Categorie::materiel;
        if(categorie == "Securite") c = Categorie::securite;

        Ticket *ticket = new Ticket(query.value("informations").toString(), c);
        client.ajouterTicket(*ticket);
        ticket->setIdTicket(query.value("idTicket").toString());
        if(query.value("ouvert").toInt() != 1) ticket->fermer();
        ticket->setDateCreation(query.value("dateCreation").toDate());

        QSqlQuery technicienQuery;
        technicienQuery.exec("SELECT * FROM Techinicien WHERE UPPER(idTicket) = UPPER('" + ticket->getIdTicket() + "')");
        if(technicienQuery.next()) {
            QString idTechnicien = technicienQuery.value("idUtilisateur").toString();
            Technicien *technicien;
            if(listUtilisateurs.count(idTechnicien)) {
                technicien = (Technicien*) listUtilisateurs[idTechnicien];
            } else {
                technicien = new Technicien(idTechnicien);
                listUtilisateurs[idTechnicien] = technicien;
            }
            technicien->setTicket(ticket);
        }
    }
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
