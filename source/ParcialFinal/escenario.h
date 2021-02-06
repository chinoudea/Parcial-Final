#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <mortero.h>
#include <iostream>
#include <cmath>
#include <QList>


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
    QList<QList<double>> simularDefensivos(double , double ,bool);
    QList<QList<double>> simularOfensivoEfectivo(double , double, double, double);
    QList<QList<double>> simular1();
    QList<QList<double>> simular2();
    QList<QList<double>> simular34(bool , double , double);
private:
    double g = 9.81;
    double pi = 2*acos(0.0);
};

#endif // ESCENARIO_H
