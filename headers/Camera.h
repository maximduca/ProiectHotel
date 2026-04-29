#pragma once
#include <string>
#include <iostream>

class Camera {
protected:
    int numarCamera;
    double pretDeBaza;
    bool esteOcupata;
    std::string numeClient;

    virtual double calculeazaPretSpecific(int nopti) const = 0;

public:
    Camera(int numar, double pret);
    virtual ~Camera() = default;

    double calculeazaPretTotal(int nopti) const;
    void realizeazaRezervare(const std::string& nume, int nopti);
    void elibereazaCamera();

    int getNumar() const;
    bool getStatusOcupat() const;

    virtual Camera* clone() const = 0;
    virtual void afisare(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Camera& c);
};