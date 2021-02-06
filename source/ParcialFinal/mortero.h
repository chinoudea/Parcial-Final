#ifndef MORTERO_H
#define MORTERO_H
#include <iostream>
#include <cmath>
#include <bala.h>
#include <QList>

using namespace std;

class Mortero
{
public:
    double posicionX;
    double posicionY;
    double tiempoInformante;
    Bala proyectil;
    Mortero();
    Mortero(double posX, double posY, double time);
    void armarMortero(double rangoDanio);
    void setAnguloDisparo(double angulo);
    void setVelocidadDisparo(double velocidad);
    QList<QList<double>> simularDisparo(Mortero *objetivo);
    double validarDisparo(Mortero *objetivo);
    //QList<QList<double>> validarInterseccion(bool respuesta);
    QList<QList<double>> validarInterseccion(Mortero *objetivo, double delay, double timeLimit, bool proteger);
    void validarInterseccionTime(Mortero *objetivo, double delay, double timeLimit, bool proteger);
private:
    double pi = 2*acos(0.0);
    double g = 9.81;
};

#endif // MORTERO_H
