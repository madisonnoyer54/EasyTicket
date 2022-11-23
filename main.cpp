#include "mainwindow.h"

#include <QApplication>
#include "gestionnairedialogue.h"

// Voici une idée de la base de donnée
// Pour pouvoir se connecter dans le logiciel
// Identifiant des clients :
// TESTJosephine, TESTMartin, TESTAlexia, TESTGoogle
//
// Technicien qui gère la catégorie Matériel : TESTMichel
// Technicien qui gère les catégories Assistance et Securite : TESTAntoine
// Igenieur : TESTLea
//
// Ajout d'un utilisateur en rentrant un identifiant de la forme :
// TESTNom

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    // Afin de tester nous allons simuler un monde
    // Avec des clients qui ont créé des tickets
    // Et nous les affichons sur la sortie standard
    GestionnaireDialogue* gestionnaire = new GestionnaireDialogue();

    Client* client = gestionnaire->getClient("TESTJosephine");
    Ticket* ticket = &client->nouveauTicket("Mon disque dur prend feu apres avoir utilise votre logiciel. Je ne comprend pas....", Categorie::materiel);
    gestionnaire->assignerTicket(ticket);
    ticket = &client->nouveauTicket("Apres avoir ecrit que j'avais un probleme avec mon disque dur, je ne vois que des pubs pour des disques durs... Il y aurait-il une fuite de donnees ??", Categorie::securite);
    gestionnaire->assignerTicket(ticket);

    ticket->ajouterMessage(*client, "Je trouve ça vraiment étrange...");

    client = gestionnaire->getClient("TESTMartin");
    ticket = &client->nouveauTicket("Votre logiciel a crash suite a un click sur le bouton 'ajout'.", Categorie::logiciel);
    gestionnaire->assignerTicket(ticket);

    client = gestionnaire->getClient("TESTAlexia");
    ticket = &client->nouveauTicket("Je n'arrive pas a installer votre logiciel sur windows, pouvez vous m'aider ?", Categorie::assistance);
    gestionnaire->assignerTicket(ticket);

    ticket = &client->nouveauTicket("Pouvez vous m'aider a installer votre logiciel svp", Categorie::assistance);
    gestionnaire->assignerTicket(ticket);

    client = gestionnaire->getClient("TESTGoogle");
    ticket = &client->nouveauTicket("Pouvez vous répéter votre question ?", Categorie::materiel);
    gestionnaire->assignerTicket(ticket);

    Technicien *technicien = gestionnaire->getTechnicien("TESTMichel");
    technicien->addCategorie(Categorie::materiel);
    gestionnaire->assignerTicket(technicien);

    technicien = gestionnaire->getTechnicien("TESTAntoine");
    technicien->addCategorie(Categorie::assistance);
    technicien->addCategorie(Categorie::securite);
    gestionnaire->assignerTicket(technicien);

    technicien = gestionnaire->getTechnicien("TESTLea");
    technicien->addCategorie(Categorie::assistance);
    technicien->addCategorie(Categorie::securite);
    technicien->addCategorie(Categorie::materiel);
    technicien->addCategorie(Categorie::logiciel);
    gestionnaire->assignerTicket(technicien);

    w.setGestionnaire(gestionnaire);



    return a.exec();
}
