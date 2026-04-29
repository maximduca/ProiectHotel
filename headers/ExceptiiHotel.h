#pragma once

#include <stdexcept>
#include <string>

class EroareHotel : public std::runtime_error {
public:
    explicit EroareHotel(const std::string& mesaj)
        : std::runtime_error(mesaj) {}
};

class EroareDateInvalide : public EroareHotel {
public:
    explicit EroareDateInvalide(const std::string& mesaj = "Numar de nopti invalid!")
        : EroareHotel("Eroare Validare: " + mesaj) {}
};

class EroareCameraOcupata : public EroareHotel {
public:
    explicit EroareCameraOcupata(const std::string& mesaj = "Camera selectata este luata!")
        : EroareHotel("Eroare Rezervare: " + mesaj) {}
};

class EroareFisierLipsa : public EroareHotel {
public:
    explicit EroareFisierLipsa(const std::string& mesaj = "Baza de date nu poate fi deschisa!")
        : EroareHotel("Eroare Sistem: " + mesaj) {}
};