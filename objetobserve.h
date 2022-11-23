#ifndef OBJETOBSERVE_H
#define OBJETOBSERVE_H

// Permet de définir les objets qui devront reagir a chaque changement
#include "observeur.h"
// Permet de gérer une liste d'observeur
#include <QVector>

/**
 * @brief La classe abstraite d'un objet observer
 *
 * @version 1d
 *
 * @author Diebold Erwan, Noyer Madison, Poincet Julien
 */
class ObjetObserve
{
    private:
        /// @brief Variable contenant les observeurs de l'objet
        QVector<Observeur*> observeurs;

    public:
        /// @brief Constructeur de l'objet observé
        ObjetObserve();

        /// @brief Destructeur de l'objet observé
        /// virtuel pour rendre la classe abstraite
        virtual ~ObjetObserve() = 0;

        /// @brief Méthode qui permet d'ajouter un observeur
        ///
        /// @param observeur Référence d'un observeur
        void addObserveur(Observeur &observeur);
    protected:

        /// @brief Méthode qui permet de notifier tout les observeurs
        void notifier();
};

#endif // OBJETOBSERVE_H
