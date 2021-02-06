#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cuerpo.h"
#include "escenario.h"
#include <QList>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Escenario * campoBatalla;
    QGraphicsScene * escena;
    QTimer * timeSimula;
    cuerpo * bala1;
    double deltaY = 500;
    double deltaX = 100;
    double factorConversion;

private slots:
    void mover1();
    void on_btnPunto1_pressed();

    void on_btnPunto2_pressed();

    void on_btnPunto3_pressed();

    void on_btnPunto4_pressed();

    void on_btnPunto5_pressed();

    void on_btnVolver_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
