#include "categorie.h"

std::ostream& operator<<(std::ostream& os, Categorie const& categorie) {
    switch (categorie) {
        case materiel:
            os << "Materiel";
        break;
        case securite:
            os << "Securite";
        break;
        case logiciel:
            os << "Logiciel";
        break;
        case assistance:
            os << "Assistance";
        break;
    }

    return os;
}
