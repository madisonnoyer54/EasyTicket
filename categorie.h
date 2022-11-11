#ifndef CATEGORIE_H
#define CATEGORIE_H
#include <iostream>

/** @brief L'enum Categorie permet de d'attribuer une catégorie à un Ticket et d'attriduer une ou plusieurs catégorie à un Technicien
 *
 *  Elle gère les différents types d'incident/retour qui peuvent avoir lieu par
 *  rapport à l'entreprise
 **
 ** @version 1a
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
enum Categorie {logiciel, materiel, assistance, securite};


/// @brief Fonction qui permet d'afficher une categorie sur la sortie standard
///
/// @param os Flux de la sortie standard
///
/// @param ticket Constante de la categorie
///
/// @return Flux de la sortie standard
std::ostream& operator<<(std::ostream& os, Categorie const& categorie);

#endif // CATEGORIE_H
