#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "Camera.h"

class Hotel {
private:
    std::string nume;
    std::vector<std::shared_ptr<Camera>> camere;

public:
    explicit Hotel(const std::string& numeHotel);
    
    Hotel(const Hotel& altul);
    Hotel& operator=(Hotel altul);
    friend void swap(Hotel& primul, Hotel& al_doilea) noexcept;

    void adaugaCamera(const std::shared_ptr<Camera>& camera);
    void afiseazaToateCamerele() const;
    void rezervaCamera(int numar, const std::string& client, int nopti);
    
    void oferaPachetSpaVIP();

    friend std::ostream& operator<<(std::ostream& os, const Hotel& h);
};