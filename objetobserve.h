#ifndef OBJETOBSERVE_H
#define OBJETOBSERVE_H

// Permet de définir les objets qui devront reagir a chaque changement
#include "observeur.h"
// Permet de gérer une liste d'observeur
#include <QVector>

/**
 * @brief La classe abstraite
 */
class ObjetObserve
{
    private:
        QVector<Observeur*> observeurs;

    public:
        ObjetObserve();
        virtual ~ObjetObserve() = 0;
        void addObserveur(Observeur *observeur);
    protected:
        void notifier();
};

#endif // OBJETOBSERVE_H
