#include "objetobserve.h"

ObjetObserve::ObjetObserve()
{

}

void ObjetObserve::notifier() {
    for(int i = 0; i < observeurs.size(); i++) {
        observeurs[i]->reagir();
    }
}

void ObjetObserve::addObserveur(Observeur &observeur) {
    observeurs.push_back(&observeur);
    observeur.reagir();
}

ObjetObserve::~ObjetObserve() {}
