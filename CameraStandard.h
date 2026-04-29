#pragma once
#include "Camera.h"

class CameraStandard : public Camera {
protected:
    double calculeazaPretSpecific(int nopti) const override;

public:
    CameraStandard(int numar, double pret);
    
    Camera* clone() const override;
    void afisare(std::ostream& os) const override;
};