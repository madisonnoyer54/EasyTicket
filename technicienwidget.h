#ifndef TECHNICIENWIDGET_H
#define TECHNICIENWIDGET_H

#include <QWidget>

namespace Ui {
class TechnicienWidget;
}

class TechnicienWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TechnicienWidget(QWidget *parent = nullptr);
    ~TechnicienWidget();

private:
    Ui::TechnicienWidget *ui;
};

#endif // TECHNICIENWIDGET_H
