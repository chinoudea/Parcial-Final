#include "cuerpo.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnPunto1_pressed()
{
    QList<QList<double>> result;
    QList<double> simulacion;
    QString angulo, velocidad, posicionX, posicionY, tiempo;
    //Para iniciar simulacion se inicializa campo de batalla
    campoBatalla = new Escenario(ui->inputDistancia->value(), ui->inputHo->value(), ui->inputHd->value());
    //Se llama metodo de simular punto 1
    result = campoBatalla->simular1();
    //Se recorre resultado para mostrar las respuestas
    for (int i=0; i< result.size(); i++) {
        simulacion = result[i];
        angulo = QString::number(simulacion[0]);
        velocidad = QString::number(simulacion[1]);
        posicionX = QString::number(simulacion[2]);
        posicionY = QString::number(simulacion[3]);
        tiempo = QString::number(simulacion[4]);
        angulo = "Para un disparo con angulo " +angulo+" y velocidad "+velocidad+" se logra generar danio en X="+posicionX+" y Y="+posicionY+" en tiempo "+tiempo+" segundos.";
        switch (i) {
        case 0:
            ui->lblSimula1->setText(angulo);
            break;
        case 1:
            ui->lblSimula2->setText(angulo);
            break;
        case 2:
            ui->lblSimula3->setText(angulo);
            break;
        }
    }
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
    //Pintar simulacion
    escena = new QGraphicsScene();
    escena->setSceneRect(0,0,800,580);
    factorConversion = 600/campoBatalla->distancia;
    cuerpo * mortero1 = new cuerpo(10,deltaX,deltaY-(campoBatalla->c_ofensivo.posicionY*factorConversion),"morteroO");
    cuerpo * mortero2 = new cuerpo(10,700,deltaY-(campoBatalla->c_defensivo.posicionY*factorConversion),"morteroD");
    bala1 = new cuerpo(5,deltaX,deltaY-(campoBatalla->c_ofensivo.posicionY*factorConversion),"balaO");
    escena->addItem(mortero1);
    escena->addItem(mortero2);
    timeSimula = new QTimer;
    connect(timeSimula,SIGNAL(timeout()), this, SLOT(mover1()));
    ui->gvSimulacion->setScene(escena);


}

void MainWindow::on_btnPunto2_pressed()
{
    QList<QList<double>> result;
    QList<double> simulacion;
    QString angulo, velocidad, posicionX, posicionY, tiempo;
    //Para iniciar simulacion se inicializa campo de batalla
    campoBatalla = new Escenario(ui->inputDistancia->value(), ui->inputHo->value(), ui->inputHd->value());
    //Se llama metodo de simular punto 2
    result = campoBatalla->simular2();
    //Se recorre resultado para mostrar las respuestas
    for (int i=0; i< result.size(); i++) {
        simulacion = result[i];
        angulo = QString::number(simulacion[0]);
        velocidad = QString::number(simulacion[1]);
        posicionX = QString::number(simulacion[2]);
        posicionY = QString::number(simulacion[3]);
        tiempo = QString::number(simulacion[4]);
        angulo = "Para un disparo con angulo " +angulo+" y velocidad "+velocidad+" se logra generar danio en X="+posicionX+" y Y="+posicionY+" en tiempo "+tiempo+" segundos.";
        switch (i) {
        case 0:
            ui->lblSimula1->setText(angulo);
            break;
        case 1:
            ui->lblSimula2->setText(angulo);
            break;
        case 2:
            ui->lblSimula3->setText(angulo);
            break;
        }
    }
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
    //Pintar simulacion
    escena = new QGraphicsScene();
    escena->setSceneRect(0,0,800,580);
    factorConversion = 600/campoBatalla->distancia;
    cuerpo * mortero1 = new cuerpo(10,deltaX,deltaY-(campoBatalla->c_ofensivo.posicionY*factorConversion),"morteroO");
    cuerpo * mortero2 = new cuerpo(10,700,deltaY-(campoBatalla->c_defensivo.posicionY*factorConversion),"morteroD");
    escena->addItem(mortero1);
    escena->addItem(mortero2);

    ui->gvSimulacion->setScene(escena);
}

void MainWindow::on_btnPunto3_pressed()
{
    QList<QList<double>> result;
    QList<double> simulacion;
    QString angulo, velocidad, posicionX, posicionY, tiempo;
    //Para iniciar simulacion se inicializa campo de batalla
    campoBatalla = new Escenario(ui->inputDistancia->value(), ui->inputHo->value(), ui->inputHd->value());
    //Se llama metodo de simular punto 2
    result = campoBatalla->simular34(false, ui->inputVelocidadOfe->value(), ui->inputAnguloOfe->value());
    //Se recorre resultado para mostrar las respuestas
    for (int i=0; i< result.size(); i++) {
        simulacion = result[i];
        if (simulacion[0]==-99) {
            ui->lblSimula1->setText("No es posible defenderse de un ataque con esos parametros, la informacion de inteligencia no llega a tiempo.");
            break;
        }
        angulo = QString::number(simulacion[0]);
        velocidad = QString::number(simulacion[1]);
        posicionX = QString::number(simulacion[2]);
        posicionY = QString::number(simulacion[3]);
        tiempo = QString::number(simulacion[4]);
        angulo = "Disparo defensivo con angulo " +angulo+" grados y velocidad "+velocidad+"  m/s se logra generar danio en X="+posicionX+" y Y="+posicionY+" en tiempo "+tiempo+" segundos.";
        switch (i) {
            case 0:
                ui->lblSimula2->setText(angulo);
                break;
            case 1:
                ui->lblSimula3->setText(angulo);
                break;
            case 2:
                ui->lblSimula4->setText(angulo);
                break;
        }
    }
    ui->lblSimula1->setText("Para un disparo de ataque con angulo "+QString::number(ui->inputAnguloOfe->value())+" y velocidad "+QString::number(ui->inputVelocidadOfe->value())+" se puede evitar el ataque con las siguientes opciones:");
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
    //Pintar simulacion
    escena = new QGraphicsScene();
    escena->setSceneRect(0,0,800,580);
    factorConversion = 600/campoBatalla->distancia;
    cuerpo * mortero1 = new cuerpo(10,deltaX,deltaY-(campoBatalla->c_ofensivo.posicionY*factorConversion),"morteroO");
    cuerpo * mortero2 = new cuerpo(10,700,deltaY-(campoBatalla->c_defensivo.posicionY*factorConversion),"morteroD");
    escena->addItem(mortero1);
    escena->addItem(mortero2);

    ui->gvSimulacion->setScene(escena);
}

void MainWindow::on_btnPunto4_pressed()
{
    QList<QList<double>> result;
    QList<double> simulacion;
    QString angulo, velocidad, posicionX, posicionY, tiempo;
    //Para iniciar simulacion se inicializa campo de batalla
    campoBatalla = new Escenario(ui->inputDistancia->value(), ui->inputHo->value(), ui->inputHd->value());
    //Se llama metodo de simular punto 2
    result = campoBatalla->simular34(true, ui->inputVelocidadOfe->value(), ui->inputAnguloOfe->value());
    //Se recorre resultado para mostrar las respuestas
    for (int i=0; i< result.size(); i++) {
        simulacion = result[i];
        if (simulacion[0]==-99) {
            ui->lblSimula1->setText("No es posible defenderse de un ataque con esos parametros, la informacion de inteligencia no llega a tiempo.");
            break;
        }
        angulo = QString::number(simulacion[0]);
        velocidad = QString::number(simulacion[1]);
        posicionX = QString::number(simulacion[2]);
        posicionY = QString::number(simulacion[3]);
        tiempo = QString::number(simulacion[4]);
        angulo = "Disparo defensivo con angulo " +angulo+" grados y velocidad "+velocidad+"  m/s se logra generar danio en X="+posicionX+" y Y="+posicionY+" en tiempo "+tiempo+" segundos.";
        switch (i) {
            case 0:
                ui->lblSimula2->setText(angulo);
                break;
            case 1:
                ui->lblSimula3->setText(angulo);
                break;
            case 2:
                ui->lblSimula4->setText(angulo);
                break;
        }
    }
    ui->lblSimula1->setText("Para un disparo de ataque con angulo "+QString::number(ui->inputAnguloOfe->value())+" y velocidad "+QString::number(ui->inputVelocidadOfe->value())+" se puede evitar el ataque con las siguientes opciones:");
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
    //Pintar simulacion
    escena = new QGraphicsScene();
    escena->setSceneRect(0,0,800,580);
    factorConversion = 600/campoBatalla->distancia;
    cuerpo * mortero1 = new cuerpo(10,deltaX,deltaY-(campoBatalla->c_ofensivo.posicionY*factorConversion),"morteroO");
    cuerpo * mortero2 = new cuerpo(10,700,deltaY-(campoBatalla->c_defensivo.posicionY*factorConversion),"morteroD");
    escena->addItem(mortero1);
    escena->addItem(mortero2);

    ui->gvSimulacion->setScene(escena);
}

void MainWindow::on_btnPunto5_pressed()
{
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnVolver_pressed()
{
    ui->lblSimula1->setText("");
    ui->lblSimula2->setText("");
    ui->lblSimula3->setText("");
    ui->lblSimula4->setText("");
    //Se regresa a pagina inicial
    ui->stackedWidget->setCurrentIndex(0);
}
