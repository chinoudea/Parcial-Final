#include "bala.h"



Bala::Bala()
{

}

Bala::Bala(double posIniX, double posIniY, double rango)
{
    posicionX = posIniX;
    posicionY = posIniY;
    posInicialX = posIniX;
    posInicialY = posIniY;
    rangoDetonacion = rango;
}

Bala::Bala(double posIniX, double posIniY, double rango, double velIni, double angIni)
{
    posicionX = posIniX;
    posicionY = posIniY;
    posInicialX = posIniX;
    posInicialY = posIniY;
    rangoDetonacion = rango;
    velocidadInicial = velIni;
    anguloInicial = angIni;
}

bool Bala::sensarCercania(double X, double Y)
{
        double deltaX = posicionX - X;
        double deltaY = posicionY - Y;
        if (abs(sqrt(pow(deltaX,2)+pow(deltaY,2))) <= rangoDetonacion) {
            return true;
        } else {
            return false;
        }
    }

void Bala::calcularPosicion(double* t) {
    posicionX = posInicialX + (velocidadInicial * cos(anguloInicial*pi/180)) * (*t);
    posicionY = posInicialY + (velocidadInicial * sin(anguloInicial*pi/180)) * (*t) - (g*pow((*t),2))/2;
}


