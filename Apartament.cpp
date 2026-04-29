#include "Apartament.h"

Apartament::Apartament(int numar, double pret, double taxa) 
    : Camera(numar, pret), taxaCuratenie(taxa) {}

double Apartament::calculeazaPretSpecific(int nopti) const {
    return (pretDeBaza * nopti) + taxaCuratenie;
}

Camera* Apartament::clone() const {
    return new Apartament(*this);
}

void Apartament::afisare(std::ostream& os) const {
    os << "[Apartament] ";
    Camera::afisare(os);
    os << " (+ " << taxaCuratenie << " RON taxa curatenie)";
}