#pragma once
#include "Camera.h"

class Penthouse : public Camera {
private:
    bool areMiniBarGratuit;

protected:
    double calculeazaPretSpecific(int nopti) const override;

public:
    Penthouse(int numar, double pret, bool miniBar);
    
    void activeazaPachetVip();
    
    Camera* clone() const override;
    void afisare(std::ostream& os) const override;
};