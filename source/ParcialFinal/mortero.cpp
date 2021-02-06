#include "mortero.h"


Mortero::Mortero()
{
    posicionX = 0;
    posicionY = 0;
    tiempoInformante = 1;
}

Mortero::Mortero(double posX, double posY, double time)
{
    posicionX = posX;
    posicionY = posY;
    tiempoInformante = time;
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

QList<QList<double>> Mortero::simularDisparo(Mortero *objetivo)
{
    QList<QList<double>> respuesta;
    QList<double> simulacion;
    double anguloSemilla, count=0;
    bool flag;
    double velSemilla;
    double deltaVel;
    double deltaAngulo;
    double anguloToObjetivo = atan((objetivo->posicionY-posicionY)/abs(objetivo->posicionX-posicionX))*(180/pi);
    double lineaVista = pow((pow((objetivo->posicionY-posicionY),2))+(pow((objetivo->posicionX-posicionX),2)),0.5);

    // Se valida el angulo al objetivo
    if (anguloToObjetivo>=45) {
        anguloSemilla=ceil(anguloToObjetivo);
        deltaAngulo = 1;
    } else if (anguloToObjetivo>=0 && anguloToObjetivo < 45) {
        anguloSemilla=45;
        deltaAngulo = -(45-anguloToObjetivo)/10;
    } else {
        anguloSemilla = 0;
        deltaAngulo = -anguloToObjetivo/10;
    }
    // Se imprimen resultados        system("CLS");
    //cout << lineaVista << endl ;
    //cout << anguloSemilla << endl ;
    //system("PAUSE");
    //cout << "Angulo objetivo: " << anguloToObjetivo << endl;
    //cout << "Angulo semilla: " << anguloSemilla << endl;
    //cout << "Delta angulo: " << deltaAngulo << endl;
    //system("PAUSE");
    //cout << "\t********************* RESULTADOS ********************* " << endl << endl;
    //Se itera en 3 angulos a partir de la semilla
    for (double i=anguloSemilla; count < 3; i+=deltaAngulo) {
        simulacion.clear();
        flag = false;
        proyectil.anguloInicial = (objetivo->posicionX-posicionX)>=0 ? i : 180 - i;
        // Para el angulo definido se obtiene la velocidad para el alcance maximo en X.
        if (anguloToObjetivo<0) {
            velSemilla=lineaVista/(tiempoInformante);
            deltaVel = -0.1;
            deltaAngulo = -1;
        } else {
            velSemilla = lineaVista/(tiempoInformante*2);
            deltaVel = velSemilla/10;
        }
        //cout << velSemilla << endl ;
        //cout << deltaVel << endl ;
        //system("PAUSE");
        //Se itera en velocidad inicial
        for (double v=velSemilla; ; v+=deltaVel) {
            //Si la velocidad ya supera el doble de la velocidad requerida en linea recta se aborta
            if (v > lineaVista*10) break;
            if (v<0) break;
            proyectil.velocidadInicial = v;
            //cout << v<< endl;
            //cout << i << endl;
            //system("PAUSE");
            //return;
            //Se itera en tiempo
            for (double tiempo=0.1; ; tiempo+=0.01) {
                proyectil.calcularPosicion(&tiempo);
                // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                if (proyectil.posicionY<0) break;
                // Se limita a tiempo minimo de impacto
                if (tiempo > tiempoInformante) break;
                // Se valida la cercania al objetivo
                if (proyectil.sensarCercania(objetivo->posicionX, objetivo->posicionY)) {
                    flag = true;
                    simulacion.append(i);//Angulo
                    simulacion.append(proyectil.velocidadInicial); //Velocidad Inicial
                    simulacion.append(proyectil.posicionX);
                    simulacion.append(proyectil.posicionY);
                    simulacion.append(tiempo);
                    //cout << "Para un disparo con angulo " << i << " y velocidad " << proyectil.velocidadInicial << endl;
                    //cout << "se logra generar danio en X=" << proyectil.posicionX << " y Y=" << proyectil.posicionY << " en tiempo " << tiempo << " segundos."<<endl<<endl;
                    count++;
                    respuesta.append(simulacion);
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
    //cout << endl;
    return respuesta;
    //system("PAUSE");
}

double Mortero::validarDisparo(Mortero *objetivo)
{
    // Lo primero saber si el disparo con esos parametros puede hacer daño, se itera en tiempo para averiguarlo.
    for (double tiempo=0.1; ; tiempo+=0.01) {
        proyectil.calcularPosicion(&tiempo);
        // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
        if (proyectil.posicionY<0) return -1;
        // Se valida la cercania al objetivo
        if (proyectil.sensarCercania(objetivo->posicionX, objetivo->posicionY)) {
            return tiempo;
        }
        // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
        if ((objetivo->posicionX-posicionX)>=0) {
            if (proyectil.posicionX > (objetivo->posicionX + proyectil.rangoDetonacion)) return -1;
        } else {
            if (proyectil.posicionX < (objetivo->posicionX - proyectil.rangoDetonacion)) return -1;
        }
    }
}

void Mortero::validarInterseccionTime(Mortero *objetivo, double delay, double timeLimit, bool proteger)
{
    int anguloSemilla, count=0;
    bool flag;
    double tiempoObjetivo, tiempoInterseccion;
    double anguloToObjetivo = atan((objetivo->posicionY-posicionY)/(objetivo->posicionX-posicionX))*(180/pi);
    // Se valida el angulo al objetivo, se compara con 45 por ser el angulo de mayor alcance.
    if (anguloToObjetivo>45) anguloSemilla=int(ceil(anguloToObjetivo));
    else anguloSemilla=45;
    // Se imprimen resultados
    //system("CLS");
    //cout << "\t********************* RESULTADOS ********************* " << endl << endl;
    //cout << "Para un disparo de ataque con angulo " << objetivo->proyectil.anguloInicial << " y velocidad " << objetivo->proyectil.velocidadInicial << endl;
    //cout << "se puede evitar el ataque con las siguientes opciones:" << endl << endl;
    //Se itera en 3 angulos a partir de la semilla
    for (int i=anguloSemilla; count<3; i+=5) {
        flag = false;
        proyectil.anguloInicial = (objetivo->posicionX-posicionX)>=0 ? i : 180 - i;
        //Se itera en velocidad inicial
        for (double v=0.1; ; v+=0.1) {
            proyectil.velocidadInicial = v;
            //Se itera en tiempo
            for (double tiempo=0.1; ; tiempo+=0.01) {
                tiempoObjetivo = tiempo + delay;
                proyectil.calcularPosicion(&tiempo);
                objetivo->proyectil.calcularPosicion(&tiempoObjetivo);
                // Se valida la cercania al objetivo
                if (proyectil.sensarCercania(objetivo->proyectil.posicionX, objetivo->proyectil.posicionY)) {
                    // Si el tiempo logrado es mayor al tiempo en el que el cañon ofensivo logra hacer daño, no sirven estos parametros.
                    if (timeLimit>0) if ((tiempo + delay) >= timeLimit ) break;
                    // Se guarda el tiempo y posicion en el que la defensa seria efectiva
                    tiempoInterseccion = tiempo;
                    // Se analiza si este disparo de defensa no hara daño al cañon ofensivo.
                    if (proteger) {
                        //se sigue iterando en el tiempo para validar si hara daño al cañon ofensivo
                        for (;;tiempo+=0.01) {
                            proyectil.calcularPosicion(&tiempo);
                            if (proyectil.sensarCercania(objetivo->posicionX,objetivo->posicionY)) {
                                break;
                            }
                            // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                            if (proyectil.posicionY<0) {
                                flag=true;
                                break;
                            }
                            // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
                            if ((objetivo->posicionX-posicionX)>=0) {
                                if (proyectil.posicionX > (objetivo->posicionX + proyectil.rangoDetonacion)) {
                                    flag = true;
                                    break;
                                }
                            } else {
                                if (proyectil.posicionX < (objetivo->posicionX - proyectil.rangoDetonacion)) {
                                    flag = true;
                                    break;
                                }
                            }
                        }
                    } else {
                        flag = true;
                        break;
                    }
                }
                // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                if (proyectil.posicionY<0) break;
                // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
                if (proyectil.posicionX < objetivo->posicionX) break;
            }
            // Si ya se encontro resultado se deja de iterar en velocidad.
            if (flag) {
                proyectil.calcularPosicion(&tiempoInterseccion);
                //cout << "\tDisparo defensivo con angulo " << i << " grados y velocidad " << v << " m/s" << endl;
                //cout << "\tse logra generar danio en X=" << proyectil.posicionX << " y Y=" << proyectil.posicionY << " en tiempo " << tiempoInterseccion+delay << " segundos." << endl << endl;
                count++;
                break;
            }
        }
    }
// Se da tiempo al usuario para que lea los resultados
//cout << endl;
//system("PAUSE");
}

QList<QList<double>> Mortero::validarInterseccion(Mortero *objetivo, double delay, double timeLimit, bool proteger)
{
    QList<QList<double>> respuesta;
    QList<double> simulacion;
    int anguloSemilla, count=0;
    bool flag;
    double tiempoObjetivo, tiempoInterseccion;
    double anguloToObjetivo = atan((objetivo->posicionY-posicionY)/(objetivo->posicionX-posicionX))*(180/pi);
    // Se valida el angulo al objetivo, se compara con 45 por ser el angulo de mayor alcance.
    if (anguloToObjetivo>45) anguloSemilla=int(ceil(anguloToObjetivo));
    else anguloSemilla=45;
    // Se imprimen resultados
    //system("CLS");
    //cout << "\t********************* RESULTADOS ********************* " << endl << endl;
    //cout << "Para un disparo de ataque con angulo " << objetivo->proyectil.anguloInicial << " y velocidad " << objetivo->proyectil.velocidadInicial << endl;
    //cout << "se puede evitar el ataque con las siguientes opciones:" << endl << endl;
    //Se itera en 3 angulos a partir de la semilla
    for (int i=anguloSemilla; count<3; i+=5) {
        simulacion.clear();
        flag = false;
        proyectil.anguloInicial = (objetivo->posicionX-posicionX)>=0 ? i : 180 - i;
        //Se itera en velocidad inicial
        for (double v=0.1; ; v+=0.1) {
            proyectil.velocidadInicial = v;
            //Se itera en tiempo
            for (double tiempo=0.1; ; tiempo+=0.01) {
                tiempoObjetivo = tiempo + delay;
                proyectil.calcularPosicion(&tiempo);
                objetivo->proyectil.calcularPosicion(&tiempoObjetivo);
                // Se valida la cercania al objetivo
                if (proyectil.sensarCercania(objetivo->proyectil.posicionX, objetivo->proyectil.posicionY)) {
                    // Si el tiempo logrado es mayor al tiempo en el que el cañon ofensivo logra hacer daño, no sirven estos parametros.
                    if (timeLimit>0) if ((tiempo + delay) >= timeLimit ) break;
                    // Se guarda el tiempo y posicion en el que la defensa seria efectiva
                    tiempoInterseccion = tiempo;
                    // Se analiza si este disparo de defensa no hara daño al cañon ofensivo.
                    if (proteger) {
                        //se sigue iterando en el tiempo para validar si hara daño al cañon ofensivo
                        for (;;tiempo+=0.01) {
                            proyectil.calcularPosicion(&tiempo);
                            if (proyectil.sensarCercania(objetivo->posicionX,objetivo->posicionY)) {
                                break;
                            }
                            // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                            if (proyectil.posicionY<0) {
                                flag=true;
                                break;
                            }
                            // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
                            if ((objetivo->posicionX-posicionX)>=0) {
                                if (proyectil.posicionX > (objetivo->posicionX + proyectil.rangoDetonacion)) {
                                    flag = true;
                                    break;
                                }
                            } else {
                                if (proyectil.posicionX < (objetivo->posicionX - proyectil.rangoDetonacion)) {
                                    flag = true;
                                    break;
                                }
                            }
                        }
                    } else {
                        flag = true;
                        break;
                    }
                }
                // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                if (proyectil.posicionY<0) break;
                // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
                if (proyectil.posicionX < objetivo->posicionX) break;
            }
            // Si ya se encontro resultado se deja de iterar en velocidad.
            if (flag) {
                proyectil.calcularPosicion(&tiempoInterseccion);
                simulacion.append(i);//Angulo
                simulacion.append(v); //Velocidad Inicial
                simulacion.append(proyectil.posicionX);
                simulacion.append(proyectil.posicionY);
                simulacion.append(tiempoInterseccion+delay);
                //cout << "\tDisparo defensivo con angulo " << i << " grados y velocidad " << v << " m/s" << endl;
                //cout << "\tse logra generar danio en X=" << proyectil.posicionX << " y Y=" << proyectil.posicionY << " en tiempo " << tiempoInterseccion+delay << " segundos." << endl << endl;
                count++;
                respuesta.append(simulacion);
                break;
            }
        }
    }
// Se da tiempo al usuario para que lea los resultados
//cout << endl;
//system("PAUSE");
}




