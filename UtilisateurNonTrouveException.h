#ifndef UTILISATEURNONTROUVEEXCEPTION_H
#define UTILISATEURNONTROUVEEXCEPTION_H

#include <iostream>
#include <QString>

class UtilisateurNonTrouveException : public std::exception {
    private:
        QString message;
    public:
        UtilisateurNonTrouveException(QString message) {
            this->message = "Impossible de trouver " + message;
        }

        const QString getMessage() {
            return message;
        }

};

#endif // UTILISATEURNONTROUVEEXCEPTION_H
