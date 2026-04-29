#pragma once
#include "Camera.h"

class Apartament : public Camera {
private:
    double taxaCuratenie;

protected:
    double calculeazaPretSpecific(int nopti) const override;

public:
    Apartament(int numar, double pret, double taxaCuratenie);
    
    Camera* clone() const override;
    void afisare(std::ostream& os) const override;
};