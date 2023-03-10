#ifndef TECHNICIEN_H
#define TECHNICIEN_H

// Pour que la classe Technicien puisse hériter de utilisateur
#include "utilisateur.h"
// Pour que le technicien puisse connaitre un ticket
#include "ticket.h"
// Pour la liste de categorie
#include <QVector>
// Pour la suppression d'element dans la liste de categorie
#include <QtAlgorithms>

// Un Technicien connait un ticket, il faut donc déclarer
// cette classe (Mais il est inutile de la définir)
class Ticket;


/** @brief La classe Technicien est la classe qui permet de créer un technicien
 ** Le tecnicien connait un Ticket et une ou plusieur catégorie(s) de ticket
 ** La classe Technicien hérite de la class Utilisateur
 **
 ** @version 2b
 **
 ** @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 **/
class Technicien : public Utilisateur
{
    private:
        /// @brief Variable qui contient le ticket utiliser par le technicien
        Ticket* ticket = nullptr;

        /// @brief Variable qui contient la/les catégorie(s) du Technicien
        /// Une catégorie définie les differentes action que le technicien peut effectuer sur le ticket
        QVector<Categorie> categories;

    public:
        /// @brief Le constructeur
        ///
        /// @param identifiant L'identifiant du technicien
        Technicien(QString identifiant);

        /// @brief Le constructeur
        ///
        /// @param identifiant L'identifiant du technicien
        ///
        /// @param categories Les categories du technicien
        Technicien(QString identifiant, QVector<Categorie> categories);

        /// @brief le destructeur ne fait rien
        ~Technicien();

        /// @brief La méthode qui permet de retourner le ticket du technicien
        ///
        /// @return Le ticket que possede le technicien
        Ticket *getTicket() const;

        /// @brief La méthode qui permet d'assigner un ticket à un technicien
        ///
        /// @param ticket Le ticket que va traiter le technicien
        void setTicket(Ticket* ticket);

        /// @brief La méthode qui permet de connaitre les catégories gérées par
        /// le technicien
        ///
        /// @return une constante contenant les Categories que peut gérer le technicien
        const QVector<Categorie> getCategories() const;

        ///@brief La méthode qui permet d'ajouter une catégorie à un technicien
        ///
        /// @param categorie La categorie à rajouter
        void addCategorie(Categorie categorie);

        ///@brief La méthode qui permet d'enlever une catégorie à un technicien
        ///
        /// @param categorie La categorie à enlever
        void removeCategorie(Categorie categorie);

        /// @brief La méthode qui permet de fermer le ticket que gère le technicien
        void fermerTicket();

        /// @brief La méthode qui permet de savoir si l'utilisateur est un client
        ///
        /// @return false
        bool estUnClient() override;

        /// @brief La méthode qui permet de savoir si un technicien peut gérer
        /// un ticket ou non
        ///
        /// @return true si le technicien ne traite pas déjà un ticket
        /// et que le ticket correspond à ses catégories
        bool peutTraiter(Ticket& ticket);
};

#endif // TECHNICIEN_H
