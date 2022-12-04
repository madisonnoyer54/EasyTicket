#ifndef CATEGORIE_H
#define CATEGORIE_H

/// Permet de gérer la transformation de la categorie en string ou inverse
#include <QString>

/** @brief L'enum Categorie permet de d'attribuer une catégorie à un Ticket et d'attriduer une ou plusieurs catégorie à un Technicien
 *
 *  Elle gère les différents types d'incident/retour qui peuvent avoir lieu par
 *  rapport à l'entreprise
 **
 ** @version 3b
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
enum Categorie {logiciel, materiel, assistance, securite};

/// @brief Fonction qui permet de transformer une chaine de caractères en une categorie
///
/// @param string La chaine de caractères
///
/// @return La catégorie correspondant a la chaine de caractères
Categorie str_to_categorie(QString string);

/// @brief Fonction qui permet de transformer une categorie en chaine
/// de caractères
///
/// @param categorie La categorie a transformer
///
/// @return La chaine de caractère correspondante
QString categorie_to_str(Categorie categorie);

#endif // CATEGORIE_H
