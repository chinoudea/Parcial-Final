#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnPunto2_pressed()
{
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnPunto3_pressed()
{
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnPunto4_pressed()
{
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnPunto5_pressed()
{
    //Para iniciar simulacion se pasa a pagina correspondiente.
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnVolver_pressed()
{
    //Se regresa a pagina inicial
    ui->stackedWidget->setCurrentIndex(0);
}
