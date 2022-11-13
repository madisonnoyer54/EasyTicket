#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connexionwidget.h"
#include "gestionnairedialogue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void setGestionnaire(GestionnaireDialogue *gestionnaire);

    private:
        Ui::MainWindow *ui;
        ConnexionWidget *connexion;
        GestionnaireDialogue *gestionnaire;

};
#endif // MAINWINDOW_H
