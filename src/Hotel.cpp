#include "Hotel.h"
#include "Penthouse.h"
#include "ExceptiiHotel.h"
#include <algorithm>

Hotel::Hotel(const std::string& numeHotel) : nume(numeHotel) {}

void swap(Hotel& primul, Hotel& al_doilea) noexcept {
    using std::swap;
    swap(primul.nume, al_doilea.nume);
    swap(primul.camere, al_doilea.camere);
}

Hotel::Hotel(const Hotel& altul) : nume(altul.nume) {
    for (const auto& c : altul.camere) {
        camere.push_back(std::shared_ptr<Camera>(c->clone()));
    }
}

Hotel& Hotel::operator=(Hotel altul) {
    swap(*this, altul);
    return *this;
}

void Hotel::adaugaCamera(const std::shared_ptr<Camera>& camera) {
    camere.push_back(camera);
}

void Hotel::afiseazaToateCamerele() const {
    std::cout << "--- " << nume << " ---" << std::endl;
    for (const auto& c : camere) {
        std::cout << *c << std::endl;
    }
}

void Hotel::rezervaCamera(int numar, const std::string& client, int nopti) {
    for (auto& c : camere) {
        if (c->getNumar() == numar) {
            c->realizeazaRezervare(client, nopti);
            std::cout << "Rezervare confirmata pentru camera " << numar << std::endl;
            return;
        }
    }
    throw EroareDateInvalide("Camera cu numarul respectiv nu a fost gasita.");
}

void Hotel::oferaPachetSpaVIP() {
    for (auto& c : camere) {
        auto p = std::dynamic_pointer_cast<Penthouse>(c);
        if (p) {
            p->activeazaPachetVip();
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Hotel& h) {
    os << "Hotel: " << h.nume << " | Camere: " << h.camere.size();
    return os;
}