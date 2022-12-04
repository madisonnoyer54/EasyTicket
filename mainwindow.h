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
 * @version 2b
 *
 * @author Madison NOYER, Julien POINCET, Erwan DIEBOLD
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        /// @brief interface graphique de la fenètre
        Ui::MainWindow *ui;
        /// @brief Affichage de connexion
        ConnexionWidget *connexion;
        /// @brief Modele du programme
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
        void setGestionnaire(GestionnaireDialogue &gestionnaire);

    private slots:
        void on_MainWindow_destroyed();

    private:
        /// @brief La méthode qui permet de gérer la destruction du modèle
        /// a la fermeture de la fenetre
        void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
