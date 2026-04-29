#include "Camera.h"
#include "ExceptiiHotel.h"

Camera::Camera(int numar, double pret)
    : numarCamera(numar), pretDeBaza(pret), esteOcupata(false), numeClient("") {}

double Camera::calculeazaPretTotal(int nopti) const {
    if (nopti <= 0) { throw EroareDateInvalide("Zile invalide."); }
    return calculeazaPretSpecific(nopti);
}

void Camera::realizeazaRezervare(const std::string& nume, int nopti) {
    if (esteOcupata) { throw EroareCameraOcupata("Camera ocupata."); }
    if (nopti <= 0) { throw EroareDateInvalide("Zile invalide."); }
    esteOcupata = true;
    numeClient = nume;
}

void Camera::elibereazaCamera() {
    esteOcupata = false;
    numeClient = "";
}

int Camera::getNumar() const { return numarCamera; }
bool Camera::getStatusOcupat() const { return esteOcupata; }

void Camera::afisare(std::ostream& os) const {
    os << "Camera " << numarCamera << " | Pret: " << pretDeBaza 
       << " RON | Status: " << (esteOcupata ? "Ocupata de " + numeClient : "Libera");
}

std::ostream& operator<<(std::ostream& os, const Camera& c) {
    c.afisare(os);
    return os;
}