#include "escenario.h"


Escenario::Escenario()
{

}

Escenario::Escenario(double dist)
{
    distancia = dist;
    c_ofensivo =  Mortero();
    c_defensivo = Mortero(distancia, 0);
    anguloToDefensivo = 0;
    anguloToOfensivo = 0;
}

Escenario::Escenario(double dist, double alt_ofensivo, double alt_defensivo) {
    distancia = dist;
    c_ofensivo = Mortero(0, alt_ofensivo);
    c_defensivo = Mortero(distancia, alt_defensivo);
    anguloToDefensivo = atan((c_defensivo.posicionY-c_ofensivo.posicionY)/distancia)*(180/pi);
    anguloToOfensivo = atan((c_ofensivo.posicionY-c_defensivo.posicionY)/distancia)*(180/pi);
}

void Escenario::simular1()
{
    c_ofensivo.armarMortero(0.05*distancia);
    c_ofensivo.simularDisparo(&c_defensivo);
}

void Escenario::simular2()
{
    c_defensivo.armarMortero(0.025*distancia);
    c_defensivo.simularDisparo(&c_ofensivo);
}

void Escenario::simularDefensivos(bool protegerOfensivo)
{
    double Voo, angO, tiempoOfensivo, tiempoOfensivoEfectivo;
    double posicionXDefensivo, posicionYDefensivo, tiempoDefensivo;
    bool flag = false;
    int count=0, anguloSemilla;
    cout << endl << "Por favor ingrese los parametros de configuracion de disparo ofensivo" << endl;
    cout << "Indique la velocidad inicial (m/s) del disparo: ";
    cin >> Voo;
    cout << "Indique el angulo en grados del disparo: ";
    cin >> angO;
    Bala ofensiva = Bala(c_ofensivo.posicionX, c_ofensivo.posicionY, 0.05*distancia, Voo, angO);
    // Lo primero es saber si el disparo ofensivo con esos parametros puede hacer daño, se itera en tiempo para averiguarlo.
    for (tiempo=0.1; ; tiempo+=0.01) {
        ofensiva.calcularPosicion(&tiempo);
        // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
        if (ofensiva.posicionY<0) break;
        // Se valida la cercania al objetivo
        if (ofensiva.sensarCercania(c_defensivo.posicionX, c_defensivo.posicionY)) {
            tiempoOfensivoEfectivo = tiempo;
            flag = true;
            break;
        }
        // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
        if (ofensiva.posicionX > (c_defensivo.posicionX + ofensiva.rangoDetonacion)) break;
    }
    if (flag) { // Si puede hacer daño
        //Se verifica si hay tiempo de reaccionar al ataque
        if (tiempo<=2) {
            cout << "No es posible defenderse de un ataque con esos parametros, la informacion de inteligencia no llega a tiempo." << endl;
        } else {
            // Se crea la bala defensiva
            Bala defensiva = Bala(c_defensivo.posicionX, c_defensivo.posicionY, (0.025 * distancia));
            // Se valida el angulo al objetivo, se compara con 45 por ser el angulo de mayor alcance.
            if (anguloToOfensivo>45) anguloSemilla=int(ceil(anguloToOfensivo));
            else anguloSemilla=45;
            // Se imprimen resultados
            system("CLS");
            cout << "\t********************* RESULTADOS ********************* " << endl << endl;
            cout << "Para un disparo ofensivo con angulo " << ofensiva.anguloInicial << " y velocidad " << ofensiva.velocidadInicial << endl;
            cout << "se puede evitar el ataque con las siguientes opciones:" << endl << endl;
            //Se itera en 3 angulos a partir de la semilla
            for (int i=anguloSemilla; count<3; i+=5) {
                flag = false;
                defensiva.anguloInicial = 180 - i;
                //Se itera en velocidad inicial
                for (double v=0.1; ; v+=0.1) {
                    defensiva.velocidadInicial = v;
                    //Se itera en tiempo
                    for (tiempo=0.1; ; tiempo+=0.01) {
                        tiempoOfensivo = tiempo + 2;
                        defensiva.calcularPosicion(&tiempo);
                        ofensiva.calcularPosicion(&tiempoOfensivo);
                        // Se valida la cercania al objetivo
                        if (defensiva.sensarCercania(ofensiva.posicionX, ofensiva.posicionY)) {
                            // Si el tiempo logrado es mayor al tiempo en el que el cañon ofensivo logra hacer daño, no sirven estos parametros.
                            if ((tiempo + 2) >= tiempoOfensivoEfectivo ) break;
                            // Se guarda el tiempo y posicion en el que la defensa seria efectiva
                            tiempoDefensivo = tiempo;
                            posicionXDefensivo = defensiva.posicionX;
                            posicionYDefensivo = defensiva.posicionY;
                            // Se analiza si este disparo de defensa no hara daño al cañon ofensivo.
                            if (protegerOfensivo) {
                                //se sigue iterando en el tiempo para validar si hara daño al cañon ofensivo
                                for (;;tiempo+=0.01) {
                                    defensiva.calcularPosicion(&tiempo);
                                    if (defensiva.sensarCercania(c_ofensivo.posicionX,c_ofensivo.posicionY)) {
                                        break;
                                    }
                                    // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                                    if (defensiva.posicionY<0) {
                                        flag=true;
                                        break;
                                    }
                                    // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
                                    if (defensiva.posicionX < (c_ofensivo.posicionX - defensiva.rangoDetonacion)) {
                                        flag=true;
                                        break;
                                    }
                                }
                            } else {
                                flag = true;
                                break;
                            }
                        }
                        // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                        if (defensiva.posicionY<0) break;
                        // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
                        if (defensiva.posicionX < c_ofensivo.posicionX) break;
                    }
                    // Si ya se encontro resultado se deja de iterar en velocidad.
                    if (flag) {
                        cout << "\tDisparo defensivo con angulo " << i << " grados y velocidad " << v << " m/s" << endl;
                        cout << "\tse logra generar danio en X=" << posicionXDefensivo << " y Y=" << posicionYDefensivo << " en tiempo " << tiempoDefensivo+2 << " segundos." << endl << endl;
                        count++;
                        break;
                    }
                }
            }
            // Se da tiempo al usuario para que lea los resultados
            cout << endl;
        }

    } else {
        cout << "Los parametros indicados no pueden hacer danio al canion defensivo" << endl;
    }
    system("PAUSE");
}

void Escenario::simularOfensivoEfectivo()
{
    double inputVelocidad, inputAngulo;
    double tiempoOfensivo, tiempoOfensivoEfectivo, tiempoDefensivo, tiempoDefensivoEfectivo,velMinInterseccion;
    int anguloIntersectado;
    int count = 0;
    bool ofensivoEfectivo = false;
    bool defensivoEfectivo = false;
    bool neutralizadorEfectivo = false;
    cout << endl << "Por favor ingrese los parametros de configuracion de disparo ofensivo" << endl;
    cout << "Indique la velocidad inicial (m/s) del disparo: ";
    cin >> inputVelocidad;
    cout << "Indique el angulo en grados del disparo: ";
    cin >> inputAngulo;
    Bala ofensiva = Bala(c_ofensivo.posicionX, c_ofensivo.posicionY, 0.05*distancia, inputVelocidad, inputAngulo);
    // Lo primero es saber si el disparo ofensivo con esos parametros puede hacer daño, se itera en tiempo para averiguarlo.
    for (tiempo=0.1; ; tiempo+=0.01) {
        ofensiva.calcularPosicion(&tiempo);
        // Se valida la cercania al objetivo
        if (ofensiva.sensarCercania(c_defensivo.posicionX, c_defensivo.posicionY)) {
            tiempoOfensivoEfectivo = tiempo;
            ofensivoEfectivo = true;
            break;
        }
        // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
        if (ofensiva.posicionY<0) break;
        // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
        if (ofensiva.posicionX > (c_defensivo.posicionX + ofensiva.rangoDetonacion)) break;
    }
    if (!ofensivoEfectivo) {
        system("CLS");
        cout << "\t********************* RESULTADOS ********************* " << endl << endl;
        cout << "Los parametros indicados no pueden hacer danio al canion defensivo" << endl << endl;
    } else { // Si puede hacer daño al cañon defensivo
        //Se verifica si hay tiempo de reaccionar al ataque, ya que la informacion llega con 2 segundos de retraso.
        if (tiempoOfensivoEfectivo<=2) {
            cout << endl << "No es posible defenderse de un ataque con esos parametros." << endl;
        } else {
            cout << endl << "Por favor ingrese los parametros de configuracion de disparo defensivo" << endl;
            cout << "Indique la velocidad inicial (m/s) del disparo: ";
            cin >> inputVelocidad;
            cout << "Indique el angulo en grados del disparo: ";
            cin >> inputAngulo;
            // Se crea la bala defensiva
            Bala defensiva = Bala(c_defensivo.posicionX, c_defensivo.posicionY, (0.025 * distancia), inputVelocidad, (180 - inputAngulo));
            //Se valida si los parametros defensivos si evitarian ataque.
            for (tiempo=0.1; ; tiempo+=0.01) {
                tiempoOfensivo = tiempo + 2; // La bala ofensiva ya lleva 2 segundos en vuelo
                defensiva.calcularPosicion(&tiempo);
                ofensiva.calcularPosicion(&tiempoOfensivo);
                // Se valida la cercania al objetivo
                if (defensiva.sensarCercania(ofensiva.posicionX, ofensiva.posicionY)) {
                    // Si el tiempo logrado es mayor al tiempo en el que el cañon ofensivo logra hacer daño, no sirven estos parametros.
                    if ((tiempo + 2) >= tiempoOfensivoEfectivo ) break;
                    defensivoEfectivo = true;
                    // Se guarda el tiempo en el que la defensa seria efectiva
                    tiempoDefensivoEfectivo = tiempo;
                    // Se calcula el angulo donde la defensa es efectiva segun cañon ofensivo.
                    anguloIntersectado = int(atan((defensiva.posicionY-c_ofensivo.posicionY)/(defensiva.posicionX-c_ofensivo.posicionX)) * (180/pi));
                    if (anguloIntersectado>0) anguloIntersectado-=5;
                    velMinInterseccion = (abs(sqrt(pow((defensiva.posicionY-c_ofensivo.posicionY),2)+pow((defensiva.posicionX-c_ofensivo.posicionX),2))) / (tiempoDefensivoEfectivo-1));
                    break;
                }
                // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                if (defensiva.posicionY<0) break;
                // Si la posicion en X ya supera la posicion del cañon ofensivo mas el rango de daño, no habria forma de evitar la bala ofensiva
                if (defensiva.posicionX < (c_ofensivo.posicionX - defensiva.rangoDetonacion)) break;
            }
            if (!defensivoEfectivo) {
                // Se da informacion sobre recorrido de bala ofensiva.
                ofensiva.calcularPosicion(&tiempoOfensivoEfectivo);
                system("CLS");
                cout << "\t********************* RESULTADOS ********************* " << endl << endl;
                cout << "Los parametros indicados no pueden evitar el ataque del canion ofensivo." << endl;
                cout << "La bala ofensiva seguira su curso y hara danio al canion defensivo." << endl;
                cout << "Tras recorrer " << ofensiva.posicionX << " m en el eje X y a una altura de " << ofensiva.posicionY << " m en un tiempo de "  << tiempoOfensivoEfectivo << " s." << endl;
            } else { // Si puede evitar el ataque ofensivo
                //Se verifica si hay tiempo de reaccionar con una bala q neutralice la defensa, ya que la informacion llega con un segundo de retraso.
                if (tiempoDefensivoEfectivo<=1) {
                    cout << endl << "No es posible neutralizar la defensa con esos parametros." << endl;
                } else {
                    // Se imprimen resultados
                    system("CLS");
                    cout << "\t********************* RESULTADOS ********************* " << endl << endl;
                    cout << "Para un disparo ofensivo con angulo " << ofensiva.anguloInicial << " y velocidad " << ofensiva.velocidadInicial << endl;
                    cout << "Se activo un disparo defensivo con angulo " << 180 - defensiva.anguloInicial << " y velocidad " << defensiva.velocidadInicial << endl;
                    cout << "Para lograr neutralizar la defensa se presentan las siguientes opciones:" << endl;
                    // Se crea bala para neutralizar defensa.
                    Bala neutralizadora = Bala ( c_ofensivo.posicionX, c_ofensivo.posicionY, (0.005*distancia));
                    // Se iterara en varios angulos para ofrecer varias opciones de neutralizacion
                    for (int i=anguloIntersectado; count<3; i++) {
                        neutralizadorEfectivo = false;
                        neutralizadora.anguloInicial = i;
                        //Se itera en velocidad inicial
                        for (double v=velMinInterseccion; v<(10*velMinInterseccion); v+=0.1) {
                            neutralizadora.velocidadInicial = v;
                            //Se itera en tiempo
                            for (tiempo=0.1; ; tiempo+=0.01) {
                                tiempoDefensivo = tiempo + 1; // La bala defensiva ya lleva 1 segundo en vuelo.
                                // Si el tiempo logrado es mayor al tiempo en el que el cañon defensivo logra hacer daño, no sirven estos parametros.
                                if (tiempoDefensivo >= tiempoDefensivoEfectivo ) break;
                                neutralizadora.calcularPosicion(&tiempo);
                                defensiva.calcularPosicion(&tiempoDefensivo);
                                // Se limita para que el escenario tenga piso en 0, asi que si se dan valores negativos no se tienen en cuenta.
                                if (neutralizadora.posicionY<0) break;
                                // Se valida la cercania al objetivo
                                if (neutralizadora.sensarCercania(defensiva.posicionX, defensiva.posicionY)) {
                                    neutralizadorEfectivo = true;
                                    count++;
                                    cout << endl;
                                    cout << "\tDisparo con un angulo de " << neutralizadora.anguloInicial << " grados y velocidad inicial de " << neutralizadora.velocidadInicial << " m/s" << endl;
                                    cout << "\tque logra evitar el disparo defensivo en las coordenas X= " << neutralizadora.posicionX << " y Y= " << neutralizadora.posicionY << endl;
                                    cout << "\ten un tiempo de " << tiempo + 3 << " s despues de disparada la bala ofensiva inicial." <<endl;
                                    cout << "\tLa bala defensiva logra recorrer " << (distancia-defensiva.posicionX) << " m  en el eje X y estaba a una altura de " << defensiva.posicionY << " m" << endl;
                                    if (c_ofensivo.posicionY < c_ofensivo.posicionX) continue;
                                    else break;
                                }
                                // Si la posicion en X ya supera la distancia mas el rango de daño, se aborta la iteracion
                                if (neutralizadora.posicionX > (c_defensivo.posicionX + neutralizadora.rangoDetonacion)) break;
                            }
                            // Si ya se encontro resultado se deja de iterar en velocidad.
                            if (neutralizadorEfectivo) break;
                        }
                    }
                    // Se da informacion sobre recorrido de bala ofensiva.
                    ofensiva.calcularPosicion(&tiempoOfensivoEfectivo);
                    cout << endl;
                    cout << "Con cualqiera de las opciones anteriores la bala ofensiva puede seguir su curso y hara danio al canion defensivo." << endl;
                    cout << "Tras recorrer " << ofensiva.posicionX << " m en el eje X y a una altura de " << ofensiva.posicionY << " m en un tiempo de "  << tiempoOfensivoEfectivo << " s." << endl;
                    cout << endl;
                }
            }
        }
    }
    system("PAUSE");
}
