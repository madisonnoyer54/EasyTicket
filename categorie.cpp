#include "categorie.h"

Categorie str_to_categorie(QString string) {
    Categorie res = logiciel;
    if(string == "Materiel") res = Categorie::materiel;
    if(string == "Securite") res = Categorie::securite;
    if(string == "Assistance") res = Categorie::assistance;

    return res;
}

QString categorie_to_str(Categorie categorie) {
    QString res;
    switch (categorie) {
        case logiciel:
            res = "Logiciel";
            break;
        case materiel:
            res = "Materiel";
            break;
        case assistance:
            res = "Assistance";
            break;
        case securite:
            res = "Securite";
            break;
    }

    return res;
}
