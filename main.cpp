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

    w.setGestionnaire(gestionnaire);



    return a.exec();
}
