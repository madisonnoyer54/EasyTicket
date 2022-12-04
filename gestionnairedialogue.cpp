#include "gestionnairedialogue.h"

GestionnaireDialogue::GestionnaireDialogue() :
    listUtilisateurs(*new QMap<QString, Utilisateur*>())
{
    // On rechercher le dossier ou les données logiciels peuvent être stockées
    QString targetDb = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(targetDb);

    if(!dir.exists()) {

        // Si il n'existe pas on le créer

        dir.mkdir(targetDb);
    }

    // On chercher le chemin qui mène vers la copie de la base de donnée
    targetDb = targetDb.append("/EasyTicket.db");
    if(!QFile::exists(targetDb)){

        // On fait une copie de la base de donnée si elle n'existe pas
        QFile::copy(":/ressources/EasyTicket.db", targetDb);

    }

    // Par sécurité on donne les permissions sur la copie de la base de donnée
    QFile(targetDb).setPermissions(QFileDevice::WriteUser | QFileDevice::ReadUser | QFileDevice::ExeUser);

    // On ouvre la copie de la base de donnée
    db.setDatabaseName(targetDb);
    db.open();
}

GestionnaireDialogue::~GestionnaireDialogue()
{
    qDeleteAll(listUtilisateurs);
    db.close();
}

Client* GestionnaireDialogue::getClient(QString identifiant){

    Client *client = nullptr;

    // La map possède t'elle une valeur pour l'identifiant ?
    if(listUtilisateurs.contains(identifiant)) {
        if(listUtilisateurs[identifiant]->estUnClient()) client = (Client*) listUtilisateurs[identifiant];
        else client = nullptr;
    }

    if(client == nullptr) {
        // Le client n'est pas dans la liste des utilisateurs déjà chargés
        client = chargerClient(identifiant);
    }

    return client;
}

Client* GestionnaireDialogue::chargerClient(QString identifiant) {
    Client *client = nullptr;
    QSqlQuery query;
    query.exec("SELECT * FROM Client WHERE UPPER(idUtilisateur) = UPPER('" + identifiant + "')");
    if (query.first()) {
        // On créer le client avec son id et on le rajoute à la liste des utilisateurs

        client = new Client(query.value(0).toString());
        listUtilisateurs[identifiant] = client;
        chargerTickets(*client);
    }

    return client;
}

Technicien* GestionnaireDialogue::getTechnicien(QString identifiant){
    // La map possède t'elle une valeur pour l'identifiant ?

    Technicien *technicien = nullptr;

    if(listUtilisateurs.contains(identifiant)) {
        if(!listUtilisateurs[identifiant]->estUnClient()) technicien = (Technicien*) listUtilisateurs[identifiant];
        else technicien = nullptr;
    }

    if(technicien == nullptr) {
        // Le technicien n'est pas dans la liste des utilisateurs déjà chargés
        technicien = chargerTechnicien(identifiant);
    }

    return technicien;
}

Technicien* GestionnaireDialogue::chargerTechnicien(QString identifiant) {
    Technicien *technicien = nullptr;

    QSqlQuery query;
    query.exec("SELECT * FROM Technicien WHERE UPPER(idUtilisateur) = UPPER('" + identifiant + "')");
    if (query.first()) {
        //On créer le technicien avec son id et on le rajoute à la liste des utilisateurs

        technicien = new Technicien(query.value("idUtilisateur").toString());
        listUtilisateurs[identifiant] = technicien;

        // On rajoute au technicien toutes les catégories qu'il peut gérer
        QSqlQuery secondQuery;
        secondQuery.exec("SELECT nomCategorie FROM Peut_gerer WHERE UPPER(idTechnicien) = UPPER('" + technicien->getId() + "')");

        while(secondQuery.next()) {
            Categorie c = str_to_categorie(secondQuery.value("nomCategorie").toString());
            technicien->addCategorie(c);
        }

        // On charge le ticket que gère le technicien
        QSqlQuery ticketQuery;
        ticketQuery.exec("SELECT * FROM Ticket WHERE UPPER(idTechnicien) = UPPER('" + identifiant + "') ORDER BY dateCreation");

        if(ticketQuery.first()) {
            Categorie c = str_to_categorie(ticketQuery.value("nomCategorie").toString());

            Ticket *ticket = new Ticket(nullptr, ticketQuery.value("informations").toString(), c);
            ticket->setIdTicket(ticketQuery.value("idTicket").toString());
            if(ticketQuery.value("ouvert").toInt() != 1) ticket->fermer();
            ticket->setDateCreation(ticketQuery.value("dateCreation").toDateTime());

            technicien->setTicket(ticket);
        } else {
            // Si il ne gère pas de ticket, on va chercher un ticket disponible qu'il peut traiter
            assignerTicket(*technicien);
        }
    }

    return technicien;
}

const QMap<QString, Utilisateur*>& GestionnaireDialogue::getUtilisateurs() const {
    return listUtilisateurs;
}

void GestionnaireDialogue::chargerTickets(Client &client) {
    QSqlQuery query;
    query.exec("SELECT * FROM Ticket WHERE UPPER(idClient) = UPPER('" + client.getId() + "') ORDER BY dateCreation");

    while(query.next()) {
        Categorie c = str_to_categorie(query.value("nomCategorie").toString());

        Ticket *ticket = new Ticket(&client, query.value("informations").toString(), c);
        client.ajouterTicket(*ticket);
        ticket->setIdTicket(query.value("idTicket").toString());

        // On ferme le ticket si il est déclaré comme fermé dans la bdd
        if(query.value("ouvert").toInt() != 1) ticket->fermer();

        ticket->setDateCreation(query.value("dateCreation").toDateTime());

        if(ticket->estOuvert() && !query.value("idTechnicien").isNull()) {

            QSqlQuery technicienQuery;
            technicienQuery.exec("SELECT * FROM Technicien WHERE UPPER(idUtilisateur) = UPPER('" + query.value("idTechnicien").toString() + "')");

            if(technicienQuery.next()) {

                QString idTechnicien = technicienQuery.value("idUtilisateur").toString();
                Technicien *technicien;

                if(listUtilisateurs.contains(idTechnicien)) {
                    technicien = (Technicien*) listUtilisateurs[idTechnicien];
                } else {
                    technicien = new Technicien(idTechnicien);
                    listUtilisateurs[idTechnicien] = technicien;
                }

                technicien->setTicket(ticket);
            }
        } else if(ticket->estOuvert()) {
            // Si le ticket est ouvert et qu'aucun technicien gère le ticket
            // On va chercher a assigner a un technicien le ticket
            assignerTicket(*ticket);
        }
    }
}

void GestionnaireDialogue::assignerTicket(Ticket &ticket) {

    QSqlQuery query;
    QString categorie = categorie_to_str(ticket.getCategorie());
    query.exec("SELECT T.idUtilisateur FROM Technicien T, Peut_gerer P WHERE T.idUtilisateur = P.idTechnicien AND idUtilisateur NOT IN (SELECT idTechnicien FROM Ticket WHERE idTechnicien IS NOT NULL) AND UPPER(P.nomCategorie) = UPPER('" + categorie + "')");

    if(query.first()) {
        // On prend l'id du premier technicien
        QString idTechnicien = query.value("idUtilisateur").toString();
        Technicien *technicien;

        // On le cherche dans la liste, si il n'y est pas
        // On le créer
        if(listUtilisateurs.contains(idTechnicien)) {
            technicien = (Technicien *) listUtilisateurs[idTechnicien];
        } else {
            technicien = new Technicien(idTechnicien);
            listUtilisateurs[idTechnicien] = technicien;
        }

        // On lui assigne le ticket
        technicien->setTicket(&ticket);
        query.finish();

        // Mise à jour de la base de donnée : on donne l'id du technicien au ticket
        QSqlQuery queryTechnicien;
        queryTechnicien.prepare("UPDATE Ticket SET idTechnicien = '" + idTechnicien + "' WHERE idTicket = " + ticket.getIdTicket());
        queryTechnicien.exec();
    }

    notifier();
}

void GestionnaireDialogue::assignerTicket(Technicien &technicien) {
    Ticket *ticket = nullptr;

    for(Categorie categorieTechnicien : technicien.getCategories()) {
        QString categorie = categorie_to_str(categorieTechnicien);
        QSqlQuery query;

        query.exec("SELECT * FROM Ticket WHERE ouvert = 1 AND idTechnicien IS NULL AND UPPER(nomCategorie) = UPPER('" + categorie + "') ORDER BY dateCreation");
        if(query.first()) {

            // On ne selectionne que le ticket le plus vieux de toutes les catégories
            if(ticket == nullptr || ticket->getDateCreation() > query.value("dateCreation").toDateTime()) {

                // Si le ticket est plus vieux que le ticket déjà en mémoire on change de ticket pour
                // le plus vieux
                ticket = new Ticket(nullptr, query.value("informations").toString(), categorieTechnicien);
                ticket->setIdTicket(query.value("idTicket").toString());
                ticket->setDateCreation(query.value("dateCreation").toDateTime());
                technicien.setTicket(ticket);

                // On met à jour la base de donnée
                query.exec("UPDATE Ticket SET idTechnicien = '" + technicien.getId() + "' WHERE idTicket = " + ticket->getIdTicket());
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
    QString categorie = categorie_to_str(ticket.getCategorie());

    // Transformation de la date en string
    QDateTime dateTime =  ticket.getDateCreation();
    QDate date = dateTime.date();
    QString dateString = QString::number(date.year()) + "-" + QString::number(date.month()) + "-" + QString::number(date.day()).rightJustified(2, '0');
    QTime time = dateTime.time();
    dateString += " " + QString::number(time.hour()).rightJustified(2, '0') + ":" + QString::number(time.minute()).rightJustified(2, '0') + ":" + QString::number(time.second()).rightJustified(2, '0');

    // Ajout du ticket dans la base de donnée
    query.exec("INSERT INTO TICKET(idClient, idTechnicien, informations, dateCreation, nomCategorie) VALUES('" + ticket.getClient()->getId() + "', null, '" + ticket.getInformations() + "', date('" + dateString + "') ,'" + categorie + "')");
    ticket.setIdTicket(query.lastInsertId().toString());

    assignerTicket(ticket);

    notifier();
}

void GestionnaireDialogue::changeCategorie(Ticket &ticket, Categorie categorie) {
    ticket.setCategorie(categorie);

    QString categorieString = categorie_to_str(categorie);

    // Changement de la catégorie du ticket dans la base de donnée
    QSqlQuery query;
    query.exec("UPDATE Ticket SET idTechnicien = NULL, nomCategorie = '" + categorieString + "' WHERE idTicket = " + ticket.getIdTicket());
}

void GestionnaireDialogue::ajouterMessage(Message &message) {
    QSqlQuery query;

    // Transformation de la date en string
    QDateTime dateTime =  message.getDateCreation();
    QDate date = dateTime.date();
    QString dateString = QString::number(date.year()) + "-" + QString::number(date.month()) + "-" + QString::number(date.day()).rightJustified(2, '0');
    QTime time = dateTime.time();
    dateString += " " + QString::number(time.hour()).rightJustified(2, '0') + ":" + QString::number(time.minute()).rightJustified(2, '0') + ":" + QString::number(time.second()).rightJustified(2, '0');

    // Ajout de la base du message dans la base de donnée
    query.exec("INSERT INTO Message(idTicket, idUtilisateur, contenu, dateCreation) VALUES(" + message.getTicket().getIdTicket() + ",'" + message.getUtilisateur()->getId() + "','" + message.getContenu() + "', date('" + dateString + "'))");
    message.setIdMessage(query.lastInsertId().toString());
}

void GestionnaireDialogue::chargerMessages(Ticket &ticket) {
    QSqlQuery query;

    query.exec("SELECT * FROM MESSAGE WHERE idTicket = " + ticket.getIdTicket() + " ORDER BY dateCreation");
    while(query.next()) {
        Utilisateur *utilisateur = nullptr;

        // On récupère l'utilisateur qui a envoyé le message dans la liste des utilisateurs
        // Si il existe pas on le créer
        QString idUtilisateur = query.value("idUtilisateur").toString();
        if(listUtilisateurs.contains(idUtilisateur)) {
            utilisateur = listUtilisateurs[idUtilisateur];
        } else {
            utilisateur = new Client(idUtilisateur);
            listUtilisateurs[idUtilisateur] = utilisateur;
        }

        Message *message = new Message(ticket, *utilisateur, query.value("contenu").toString());
        message->setIdMessage(query.value("idMessage").toString());
        message->setDateCreation(query.value("dateCreation").toDateTime());

        ticket.ajouterMessage(*message);
    }
}

QVector<Technicien *> &GestionnaireDialogue::getTechniciensPeuventGerer(Ticket &ticket) {
    QVector<Technicien *> &res = *new QVector<Technicien *>();

    QSqlQuery query;
    QString categorie = categorie_to_str(ticket.getCategorie());
    query.exec("SELECT T.idUtilisateur FROM Technicien T, Peut_gerer P WHERE T.idUtilisateur = P.idTechnicien AND idUtilisateur NOT IN (SELECT idTechnicien FROM Ticket WHERE idTechnicien IS NOT NULL) AND UPPER(P.nomCategorie) = UPPER('" + categorie + "')");

    while(query.next()) {
        // On prend l'id du premier technicien
        QString idTechnicien = query.value("idUtilisateur").toString();
        Technicien *technicien;

        // On le cherche dans la liste, si il n'y est pas
        // On le créer
        if(listUtilisateurs.contains(idTechnicien)) {
            technicien = (Technicien *) listUtilisateurs[idTechnicien];
        } else {
            technicien = new Technicien(idTechnicien);
            listUtilisateurs[idTechnicien] = technicien;
        }

        res.append(technicien);
    }

    return res;
}

void GestionnaireDialogue::assignerTicket(Technicien &technicien, Ticket &ticket) {
    QSqlQuery query;

    Technicien &ancienTechnicien = *ticket.getTechnicien();
    ticket.setTechnicien(&technicien);
    query.exec("UPDATE Ticket SET idTechnicien = '" + technicien.getId() + "' WHERE idTicket = " + ticket.getIdTicket());
    ancienTechnicien.setTicket(nullptr);
    assignerTicket(ancienTechnicien);

    notifier();
}
