#ifndef DIALOGNOUVEAUTICKET_H
#define DIALOGNOUVEAUTICKET_H

#include <QDialog>

namespace Ui {
class DialogNouveauTicket;
}

class DialogNouveauTicket : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNouveauTicket(QWidget *parent = nullptr);
    ~DialogNouveauTicket();

private:
    Ui::DialogNouveauTicket *ui;
};

#endif // DIALOGNOUVEAUTICKET_H
