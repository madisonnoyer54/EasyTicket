#include "gestionnairedialogue.h"
#include <QStandardPaths>

GestionnaireDialogue::GestionnaireDialogue() :
    listUtilisateurs(*new QMap<QString, Utilisateur*>())
{
    QString targetDb = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(targetDb);
    if(!dir.exists()) {
        dir.mkdir(targetDb);
    }
    targetDb = targetDb.append("/EasyTicket.db");
    if(!QFile::exists(targetDb)){
        QFile::copy(":/ressources/EasyTicket.db", targetDb);
    }
    QFile(targetDb).setPermissions(QFileDevice::WriteOther | QFileDevice::ReadOther | QFileDevice::ExeOther);

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

        if(!query.value("idTicket").isNull()) {
            QSqlQuery ticketQuery;

            ticketQuery.exec("SELECT * FROM Ticket WHERE UPPER(idTicket) = UPPER('" + query.value("idTicket").toString() + "')");
            if(ticketQuery.next()) {
                Categorie c = Categorie::assistance;
                QString categorie = ticketQuery.value("nomCategorie").toString();
                if(categorie == "Logiciel") c = Categorie::logiciel;
                if(categorie == "Materiel") c = Categorie::materiel;
                if(categorie == "Securite") c = Categorie::securite;

                Ticket *ticket = new Ticket(nullptr, ticketQuery.value("informations").toString(), c);
                ticket->setIdTicket(ticketQuery.value("idTicket").toString());
                if(ticketQuery.value("ouvert").toInt() != 1) ticket->fermer();
                ticket->setDateCreation(ticketQuery.value("dateCreation").toDate());

                technicien->setTicket(ticket);
            }
            }
    }

    return technicien;
}

const QMap<QString, Utilisateur*>& GestionnaireDialogue::getUtilisateurs() const {
    return listUtilisateurs;
}

#include <QSqlError>

void GestionnaireDialogue::chargerTickets(Client &client) {
    QSqlQuery query;
    query.exec("SELECT * FROM Ticket WHERE UPPER(idClient) = UPPER('" + client.getId() + "')");

    while(query.next()) {
        Categorie c = Categorie::assistance;
        QString categorie = query.value("nomCategorie").toString();
        if(categorie == "Logiciel") c = Categorie::logiciel;
        if(categorie == "Materiel") c = Categorie::materiel;
        if(categorie == "Securite") c = Categorie::securite;

        Ticket *ticket = new Ticket(&client, query.value("informations").toString(), c);
        client.ajouterTicket(*ticket);
        ticket->setIdTicket(query.value("idTicket").toString());
        if(query.value("ouvert").toInt() != 1) ticket->fermer();
        ticket->setDateCreation(query.value("dateCreation").toDate());

        QSqlQuery technicienQuery;
        technicienQuery.exec("SELECT * FROM Technicien WHERE UPPER(idTicket) = UPPER('" + ticket->getIdTicket() + "') AND UPPER(idClient) = UPPER('" + client.getId() + "')");
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
        } else {
            assignerTicket(ticket);
        }
    }
}

void GestionnaireDialogue::assignerTicket(Ticket* ticket) {

    QSqlQuery query;

    QString categorie = "Logiciel";
    switch (ticket->getCategorie()) {
        case Categorie::assistance:
            categorie = "Assistance";
            break;
        case Categorie::logiciel:
            break;
        case Categorie::materiel:
            categorie = "Materiel";
            break;
        case Categorie::securite:
            categorie = "Securite";
            break;
    }

    query.exec("SELECT T.idUtilisateur FROM Technicien T, Peut_gerer P WHERE T.idUtilisateur = P.idTechnicien AND T.idTicket IS NULL AND UPPER(P.nomCategorie) = UPPER('Securite')");

    if(query.next()) {
        QString idTechnicien = query.value("idUtilisateur").toString();
        Technicien *technicien;
        if(listUtilisateurs.count(idTechnicien) != 0) {
                    technicien = (Technicien *) listUtilisateurs[idTechnicien];
        } else {
            technicien = new Technicien(idTechnicien);
            listUtilisateurs[idTechnicien] = technicien;
        }
        technicien->setTicket(ticket);
        query.finish();

        QSqlQuery queryTechnicien;
        queryTechnicien.prepare("UPDATE Technicien SET idTicket = '" + ticket->getIdTicket() + "', idClient = '" + ticket->getClient()->getId() + "' WHERE UPPER(idUtilisateur) = UPPER('" + idTechnicien +"')");
        queryTechnicien.exec();
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
