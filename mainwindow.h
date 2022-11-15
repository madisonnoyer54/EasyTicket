#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Permet à la classe d'hériter ce QMainWindow
#include <QMainWindow>
// Permet de lancer le widget de connexion
#include "connexionwidget.h"
// Permet d'inclure le modèle à l'interface
#include "gestionnairedialogue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief La classe MainWindow correspond a la classe
 * principale de l'interface graphique du logiciel
 *
 * @version 1c
 *
 * @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow *ui;
        ConnexionWidget *connexion;
        GestionnaireDialogue *gestionnaire;

    public:
        /// @brief Construction de la classe MainWindow
        ///
        /// @param parent Parent de la fenetre principale
        MainWindow(QWidget *parent = nullptr);

        /// @brief Destructeur de la classe MainWindow
        ~MainWindow();

        /// @brief Methode qui permet de définir le modele du logiciel
        ///
        /// @param gestionnaire Modele du logiciel
        void setGestionnaire(GestionnaireDialogue *gestionnaire);
};
#endif // MAINWINDOW_H
