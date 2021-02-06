#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <mortero.h>
#include <iostream>
#include <cmath>


using namespace std;

class Escenario
{
public:
    Escenario();
    Escenario(double);
    Escenario(double,double,double);
    Mortero c_ofensivo;
    Mortero c_defensivo;
    double distancia;
    double tiempo;
    double anguloToDefensivo;
    double anguloToOfensivo;
    void simularDefensivos(bool);
    void simularOfensivoEfectivo();
    void simular1();
    void simular2();
private:
    double g = 9.81;
    double pi = 2*acos(0.0);
};

#endif // ESCENARIO_H
