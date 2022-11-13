#ifndef OBSERVEUR_H
#define OBSERVEUR_H

/** @brief Interface de la classe observeur du pattern observeur
 *  Cette interface permet de définir la méthode reagir de chaque observeur
 *
 *  @version 1d
 *
 *  @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */

class Observeur
{
    public:
        /// @brief Methode reagir qui fait
        /// reagir un objet lorsqu'elle est appelée
        virtual void reagir() = 0;
};

#endif // OBSERVEUR_H
