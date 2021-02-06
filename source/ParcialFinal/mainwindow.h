#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "escenario.h"
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

private slots:
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
