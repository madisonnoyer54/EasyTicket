#include "mainwindow.h"

#include <QApplication>
#include "gestionnairedialogue.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    // Afin de tester nous allons simuler un monde
    // Avec des clients qui ont créé des tickets
    // Et nous les affichons sur la sortie standard
    GestionnaireDialogue* gestionnaire = new GestionnaireDialogue();

    Client* client = gestionnaire->getClient("Josephine");
    Ticket* ticket = &client->nouveauTicket("Mon disque dur prend feu apres avoir utilise votre logiciel. Je ne comprend pas....", Categorie::materiel);
    gestionnaire->assignerTicket(ticket);
    ticket = &client->nouveauTicket("Apres avoir ecrit que j'avais un probleme avec mon disque dur, je ne vois que des pubs pour des disques durs... Il y aurait-il une fuite de donnees ??", Categorie::securite);
    gestionnaire->assignerTicket(ticket);

    Technicien *technicien = gestionnaire->getTechnicien("Michel");
    technicien->addCategorie(Categorie::materiel);
    gestionnaire->assignerTicket(technicien);

    technicien = gestionnaire->getTechnicien("Antoine");
    technicien->addCategorie(Categorie::assistance);
    technicien->addCategorie(Categorie::securite);
    gestionnaire->assignerTicket(technicien);

    w.setGestionnaire(gestionnaire);



    return a.exec();
}
