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
    client->nouveauTicket("Mon disque dur prend feu apres avoir utilise votre logiciel. Je ne comprend pas....", Categorie::materiel);
    client->nouveauTicket("Apres avoir ecrit que j'avais un probleme avec mon disque dur, je ne vois que des pubs pour des disques durs... Il y aurait-il une fuite de donnees ??", Categorie::securite);

    Technicien* technicien = gestionnaire->getTechnicien("Joseph");
    technicien->getId();

    // On vérifie si ça ne créer pas un nouveau client à la place de nous rendre Josephine
    client = gestionnaire->getClient("Josephine");
    client->nouveauTicket("Je n'arrive pas a utiliser votre logiciel suite a sa mise a jour, j'ai besoins d'aide !", Categorie::assistance);

    std::cout << *gestionnaire << std::endl;

    return a.exec();
}
