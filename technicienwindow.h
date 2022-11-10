#ifndef TECHNICIENWINDOW_H
#define TECHNICIENWINDOW_H

#include <QWidget>

namespace Ui {
class technicienwindow;
}

class Technicienwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Technicienwindow(QWidget *parent = nullptr);
    ~Technicienwindow();

private:
    Ui::technicienwindow *ui;
};

#endif // TECHNICIENWINDOW_H
