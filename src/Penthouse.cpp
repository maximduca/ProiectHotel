#include "Penthouse.h"

Penthouse::Penthouse(int numar, double pret, bool miniBar) 
    : Camera(numar, pret), areMiniBarGratuit(miniBar) {}

double Penthouse::calculeazaPretSpecific(int nopti) const {
    double total = pretDeBaza * nopti;
    if (nopti >= 3) {
        total = total * 0.9;
    }
    return total;
}

void Penthouse::activeazaPachetVip() {
    areMiniBarGratuit = true;
}

Camera* Penthouse::clone() const {
    return new Penthouse(*this);
}

void Penthouse::afisare(std::ostream& os) const {
    os << "[Penthouse VIP] ";
    Camera::afisare(os);
    if (areMiniBarGratuit) {
        os << " - MiniBar Gratuit Inclus";
    }
}