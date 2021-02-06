#include "mortero.h"

void Mortero::simularDisparo(Mortero *objetivo)
{
    int anguloSemilla, count=0;
    bool flag;
    double velSemilla;
    double anguloToObjetivo = atan((objetivo->posicionY-posicionY)/(objetivo->posicionX-posicionX))*(180/pi);
    // Se valida el angulo al objetivo, se compara con 45 por ser el angulo de mayor alcance.
    if (anguloToObjetivo>45) anguloSemilla=int(ceil(anguloToObjetivo));
    else anguloSemilla=45;
    // Se imprimen resultados
    system("CLS");
    cout << "\t********************* RESULTADOS ********************* " << endl << endl;
    //Se itera en 3 angulos a partir de la semilla
    for (int i=anguloSemilla; count < 3; i+=5) {
        flag = false;
        proyectil.anguloInicial = (objetivo->posicionX-posicionX)>=0 ? i : 180 - i;
        // Para el angulo definido se obtiene la velocidad para el alcance maximo en X.
        if (anguloToObjetivo<0) velSemilla=0.1;
        else velSemilla = sqrt(((abs(objetivo->posicionX-posicionX)/2)*g)/sin(i*pi/180));
        //Se itera en velocidad inicial
        for (double v=velSemilla; ; v+=0.1) {
            proyectil.velocidadInicial = v;
            //Se itera en tiempo
            for (double tiempo=0.1; ; tiempo+=0.01) {
                proyectil.calcularPosicion(&tiempo);
                // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                if (proyectil.posicionY<0) break;
                // Se valida la cercania al objetivo
                if (proyectil.sensarCercania(objetivo->posicionX, objetivo->posicionY)) {
                    flag = true;
                    cout << "Para un disparo con angulo " << i << " y velocidad " << proyectil.velocidadInicial << endl;
                    cout << "se logra generar danio en X=" << proyectil.posicionX << " y Y=" << proyectil.posicionY << " en tiempo " << tiempo << " segundos."<<endl<<endl;
                    count++;
                    break;
                }
                // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
                if ((objetivo->posicionX-posicionX)>=0) {
                    if (proyectil.posicionX > (objetivo->posicionX + proyectil.rangoDetonacion)) break;
                } else {
                    if (proyectil.posicionX < (objetivo->posicionX - proyectil.rangoDetonacion)) break;
                }
            }
            // Si ya se encontro resultado se deja de iterar en velocidad.
            if (flag) break;
        }
    }
    // Se da tiempo al usuario para que lea los resultados
    cout << endl;
    system("PAUSE");
}

Mortero::Mortero()
{
    posicionX = 0;
    posicionY = 0;
}

Mortero::Mortero(double posX, double posY)
{
    posicionX = posX;
    posicionY = posY;
}

void Mortero::armarMortero(double rangoDanio)
{
    proyectil = Bala(posicionX,posicionY,rangoDanio);
}

void Mortero::setAnguloDisparo(double angulo)
{
    proyectil.anguloInicial = angulo;
}

void Mortero::setVelocidadDisparo(double velocidad)
{
    proyectil.velocidadInicial = velocidad;
}



