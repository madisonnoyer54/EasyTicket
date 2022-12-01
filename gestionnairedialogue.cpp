#include "gestionnairedialogue.h"
#include <QStandardPaths>
#include <QSqlError>

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
    QFile(targetDb).setPermissions(QFileDevice::WriteUser | QFileDevice::ReadUser | QFileDevice::ExeUser);

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
    if (query.first()) {
        technicien = new Technicien(query.value("idUtilisateur").toString());
        listUtilisateurs[identifiant] = technicien;

        QSqlQuery secondQuery;

        secondQuery.exec("SELECT nomCategorie FROM Peut_gerer WHERE UPPER(idTechnicien) = UPPER('" + technicien->getId() + "')");

        while(secondQuery.next()) {
            Categorie c = Categorie::assistance;
            QString categorie = secondQuery.value("nomCategorie").toString();
            if(categorie == "Logiciel") c = Categorie::logiciel;
            if(categorie == "Materiel") c = Categorie::materiel;
            if(categorie == "Securite") c = Categorie::securite;
            technicien->addCategorie(c);
        }

        QSqlQuery ticketQuery;

        ticketQuery.exec("SELECT * FROM Ticket WHERE UPPER(idTechnicien) = UPPER('" + identifiant + "')");
        if(ticketQuery.first()) {
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
        } else {
            assignerTicket(technicien);
        }
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

        Ticket *ticket = new Ticket(&client, query.value("informations").toString(), c);
        client.ajouterTicket(*ticket);
        ticket->setIdTicket(query.value("idTicket").toString());
        if(query.value("ouvert").toInt() != 1) ticket->fermer();
        ticket->setDateCreation(query.value("dateCreation").toDate());
        if(ticket->estOuvert() && !query.value("idTechnicien").isNull()) {
            QSqlQuery technicienQuery;
            technicienQuery.exec("SELECT * FROM Technicien WHERE UPPER(idUtilisateur) = UPPER('" + query.value("idTechnicien").toString() + "')");
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
        } else if(ticket->estOuvert()) {
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

    query.exec("SELECT T.idUtilisateur FROM Technicien T, Peut_gerer P WHERE T.idUtilisateur = P.idTechnicien AND idUtilisateur NOT IN (SELECT idTechnicien FROM Ticket WHERE idTechnicien IS NOT NULL) AND UPPER(P.nomCategorie) = UPPER('" + categorie + "')");

    if(query.first()) {
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
        queryTechnicien.prepare("UPDATE Ticket SET idTechnicien = '" + idTechnicien + "' WHERE idTicket = " + ticket->getIdTicket());
        queryTechnicien.exec();
    }

    notifier();
}

void GestionnaireDialogue::assignerTicket(Technicien* technicien) {
    Ticket *ticket = nullptr;

    for(Categorie categorieTechnicien : technicien->getCategories()) {
        if(ticket == nullptr) {
            QString categorie = "Logiciel";
            switch (categorieTechnicien) {
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
            QSqlQuery query;

            query.exec("SELECT * FROM Ticket WHERE ouvert = 1 AND idTechnicien IS NULL AND UPPER(nomCategorie) = UPPER('" + categorie + "') ORDER BY dateCreation");
            if(query.first()) {
                ticket = new Ticket(nullptr, query.value("informations").toString(), categorieTechnicien);
                ticket->setIdTicket(query.value("idTicket").toString());
                ticket->setDateCreation(query.value("dateCreation").toDate());
                technicien->setTicket(ticket);

                query.exec("UPDATE Ticket SET idTechnicien = '" + technicien->getId() + "' WHERE idTicket = " + ticket->getIdTicket());
            }
        }
    }
}

void GestionnaireDialogue::fermerTicket(Ticket &ticket) {
    QSqlQuery query;
    query.exec("UPDATE Ticket SET ouvert = 0, idTechnicien = null WHERE idTicket = " + ticket.getIdTicket());
    notifier();
}


void GestionnaireDialogue::nouveauTicket(Ticket &ticket) {
    QSqlQuery query;
    QString categorie = "Logiciel";
    switch (ticket.getCategorie()) {
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
    QDate date =  ticket.getDateCreation();
    QString dateString = QString::number(date.year()) + "-" + QString::number(date.month()) + "-" + QString::number(date.day()).rightJustified(2, '0');
    query.exec("INSERT INTO TICKET(idClient, idTechnicien, informations, dateCreation, nomCategorie) VALUES('" + ticket.getClient()->getId() + "', null, '" + ticket.getInformations() + "', date('" + dateString + "') ,'" + categorie + "')");
    query.lastError();
    ticket.setIdTicket(query.lastInsertId().toString());

    assignerTicket(&ticket);

    notifier();
}

void GestionnaireDialogue::changeCategorie(Ticket &ticket, Categorie categorie) {
    ticket.setCategorie(categorie);

    QString categorieString = "Logiciel";
    switch (categorie) {
        case Categorie::assistance:
            categorieString = "Assistance";
            break;
        case Categorie::logiciel:
            break;
        case Categorie::materiel:
            categorieString = "Materiel";
            break;
        case Categorie::securite:
            categorieString = "Securite";
            break;
    }

    QSqlQuery query;
    query.exec("UPDATE Ticket SET nomCategorie = '" + categorieString + "' WHERE idTicket = " + ticket.getIdTicket());
}

void GestionnaireDialogue::ajouterMessage(Message &message) {
    QSqlQuery query;
    QDate date =  message.getDateCreation();
    QString dateString = QString::number(date.year()) + "-" + QString::number(date.month()) + "-" + QString::number(date.day()).rightJustified(2, '0');
    query.exec("INSERT INTO Message(idTicket, idUtilisateur, contenu, dateCreation) VALUES(" + message.getTicket().getIdTicket() + ",'" + message.getUtilisateur()->getId() + "','" + message.getContenu() + "', date('" + dateString + "'))");
    message.setIdMessage(query.lastInsertId().toString());
}

void GestionnaireDialogue::chargerMessages(Ticket &ticket) {
    QSqlQuery query;

    query.exec("SELECT * FROM MESSAGE WHERE idTicket = " + ticket.getIdTicket());
    while(query.next()) {
        Utilisateur *utilisateur;
        QString idUtilisateur = query.value("idUtilisateur").toString();
        utilisateur = new Client(idUtilisateur);
        Message *message = new Message(ticket, *utilisateur, query.value("contenu").toString());
        message->setIdMessage(query.value("idMessage").toString());
        message->setDateCreation(query.value("dateCreation").toDate());

        ticket.ajouterMessage(*message);
    }
}
