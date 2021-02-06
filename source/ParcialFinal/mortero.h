#ifndef MORTERO_H
#define MORTERO_H
#include <iostream>
#include <cmath>
#include <bala.h>

using namespace std;

class Mortero
{
public:
    double posicionX;
    double posicionY;
    Bala proyectil;
    Mortero();
    Mortero(double posX, double posY);
    void armarMortero(double rangoDanio);
    void setAnguloDisparo(double angulo);
    void setVelocidadDisparo(double velocidad);
    void simularDisparo(Mortero *objetivo);
private:
    double pi = 2*acos(0.0);
    double g = 9.81;
};

#endif // MORTERO_H
