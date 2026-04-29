#include "CameraStandard.h"

CameraStandard::CameraStandard(int numar, double pret) 
    : Camera(numar, pret) {}

double CameraStandard::calculeazaPretSpecific(int nopti) const {
    return pretDeBaza * nopti;
}

Camera* CameraStandard::clone() const {
    return new CameraStandard(*this);
}

void CameraStandard::afisare(std::ostream& os) const {
    os << "[Standard] ";
    Camera::afisare(os);
}