#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// Permet d'afficher un dialog pour la connexion
#include "dialogconnexion.h"
#include "connexionwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        ConnexionWidget *connexion;

};
#endif // MAINWINDOW_H
