/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *pageMenu;
    QSplitter *splitter;
    QPushButton *btnPunto1;
    QPushButton *btnPunto2;
    QPushButton *btnPunto3;
    QPushButton *btnPunto4;
    QPushButton *btnPunto5;
    QSplitter *splitter_2;
    QLabel *label;
    QDoubleSpinBox *inputDistancia;
    QSplitter *splitter_3;
    QLabel *label_2;
    QDoubleSpinBox *inputHo;
    QSplitter *splitter_4;
    QLabel *label_3;
    QDoubleSpinBox *inputHd;
    QLabel *label_4;
    QDoubleSpinBox *inputVelocidadOfe;
    QLabel *label_5;
    QDoubleSpinBox *inputAnguloOfe;
    QDoubleSpinBox *inputAnguloDef;
    QLabel *label_6;
    QLabel *label_7;
    QDoubleSpinBox *inputVelocidadDef;
    QWidget *pageSimulator;
    QGraphicsView *gvSimulacion;
    QPushButton *btnVolver;
    QLabel *lblSimula1;
    QLabel *lblSimula2;
    QLabel *lblSimula3;
    QLabel *lblSimula4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 800, 580));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        pageMenu = new QWidget();
        pageMenu->setObjectName(QString::fromUtf8("pageMenu"));
        pageMenu->setStyleSheet(QString::fromUtf8(""));
        splitter = new QSplitter(pageMenu);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(250, 210, 301, 311));
        splitter->setOrientation(Qt::Vertical);
        btnPunto1 = new QPushButton(splitter);
        btnPunto1->setObjectName(QString::fromUtf8("btnPunto1"));
        splitter->addWidget(btnPunto1);
        btnPunto2 = new QPushButton(splitter);
        btnPunto2->setObjectName(QString::fromUtf8("btnPunto2"));
        splitter->addWidget(btnPunto2);
        btnPunto3 = new QPushButton(splitter);
        btnPunto3->setObjectName(QString::fromUtf8("btnPunto3"));
        splitter->addWidget(btnPunto3);
        btnPunto4 = new QPushButton(splitter);
        btnPunto4->setObjectName(QString::fromUtf8("btnPunto4"));
        splitter->addWidget(btnPunto4);
        btnPunto5 = new QPushButton(splitter);
        btnPunto5->setObjectName(QString::fromUtf8("btnPunto5"));
        splitter->addWidget(btnPunto5);
        splitter_2 = new QSplitter(pageMenu);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(20, 30, 241, 31));
        splitter_2->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter_2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        splitter_2->addWidget(label);
        inputDistancia = new QDoubleSpinBox(splitter_2);
        inputDistancia->setObjectName(QString::fromUtf8("inputDistancia"));
        inputDistancia->setDecimals(1);
        inputDistancia->setMaximum(50.000000000000000);
        splitter_2->addWidget(inputDistancia);
        splitter_3 = new QSplitter(pageMenu);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(280, 30, 221, 31));
        splitter_3->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        splitter_3->addWidget(label_2);
        inputHo = new QDoubleSpinBox(splitter_3);
        inputHo->setObjectName(QString::fromUtf8("inputHo"));
        inputHo->setDecimals(1);
        inputHo->setMaximum(50.000000000000000);
        splitter_3->addWidget(inputHo);
        splitter_4 = new QSplitter(pageMenu);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setGeometry(QRect(524, 30, 231, 31));
        splitter_4->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        splitter_4->addWidget(label_3);
        inputHd = new QDoubleSpinBox(splitter_4);
        inputHd->setObjectName(QString::fromUtf8("inputHd"));
        inputHd->setDecimals(1);
        inputHd->setMaximum(50.000000000000000);
        splitter_4->addWidget(inputHd);
        label_4 = new QLabel(pageMenu);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 90, 251, 31));
        label_4->setFont(font);
        inputVelocidadOfe = new QDoubleSpinBox(pageMenu);
        inputVelocidadOfe->setObjectName(QString::fromUtf8("inputVelocidadOfe"));
        inputVelocidadOfe->setGeometry(QRect(280, 90, 49, 31));
        inputVelocidadOfe->setDecimals(1);
        inputVelocidadOfe->setMaximum(2000.000000000000000);
        label_5 = new QLabel(pageMenu);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(360, 90, 231, 31));
        label_5->setFont(font);
        inputAnguloOfe = new QDoubleSpinBox(pageMenu);
        inputAnguloOfe->setObjectName(QString::fromUtf8("inputAnguloOfe"));
        inputAnguloOfe->setGeometry(QRect(610, 90, 49, 31));
        inputAnguloOfe->setDecimals(1);
        inputAnguloOfe->setMaximum(90.000000000000000);
        inputAnguloDef = new QDoubleSpinBox(pageMenu);
        inputAnguloDef->setObjectName(QString::fromUtf8("inputAnguloDef"));
        inputAnguloDef->setGeometry(QRect(610, 140, 49, 31));
        inputAnguloDef->setDecimals(1);
        inputAnguloDef->setMaximum(90.000000000000000);
        label_6 = new QLabel(pageMenu);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(360, 140, 231, 31));
        label_6->setFont(font);
        label_7 = new QLabel(pageMenu);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 140, 251, 31));
        label_7->setFont(font);
        inputVelocidadDef = new QDoubleSpinBox(pageMenu);
        inputVelocidadDef->setObjectName(QString::fromUtf8("inputVelocidadDef"));
        inputVelocidadDef->setGeometry(QRect(280, 140, 49, 31));
        inputVelocidadDef->setDecimals(1);
        inputVelocidadDef->setMaximum(2000.000000000000000);
        stackedWidget->addWidget(pageMenu);
        pageSimulator = new QWidget();
        pageSimulator->setObjectName(QString::fromUtf8("pageSimulator"));
        gvSimulacion = new QGraphicsView(pageSimulator);
        gvSimulacion->setObjectName(QString::fromUtf8("gvSimulacion"));
        gvSimulacion->setGeometry(QRect(0, 0, 800, 580));
        btnVolver = new QPushButton(pageSimulator);
        btnVolver->setObjectName(QString::fromUtf8("btnVolver"));
        btnVolver->setGeometry(QRect(710, 540, 75, 23));
        lblSimula1 = new QLabel(pageSimulator);
        lblSimula1->setObjectName(QString::fromUtf8("lblSimula1"));
        lblSimula1->setGeometry(QRect(30, 30, 751, 20));
        lblSimula2 = new QLabel(pageSimulator);
        lblSimula2->setObjectName(QString::fromUtf8("lblSimula2"));
        lblSimula2->setGeometry(QRect(30, 50, 751, 20));
        lblSimula3 = new QLabel(pageSimulator);
        lblSimula3->setObjectName(QString::fromUtf8("lblSimula3"));
        lblSimula3->setGeometry(QRect(30, 70, 751, 20));
        lblSimula4 = new QLabel(pageSimulator);
        lblSimula4->setObjectName(QString::fromUtf8("lblSimula4"));
        lblSimula4->setGeometry(QRect(30, 90, 751, 20));
        stackedWidget->addWidget(pageSimulator);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btnPunto1->setText(QApplication::translate("MainWindow", "Generar disparos ofensivos", nullptr));
        btnPunto2->setText(QApplication::translate("MainWindow", "Generar disparos defensivos", nullptr));
        btnPunto3->setText(QApplication::translate("MainWindow", "Simular defensa protegiendo posicion ofensiva", nullptr));
        btnPunto4->setText(QApplication::translate("MainWindow", "Simular defensa sin proteger posicion ofensiva", nullptr));
        btnPunto5->setText(QApplication::translate("MainWindow", "Simular neutralizacion de defensa", nullptr));
        label->setText(QApplication::translate("MainWindow", "Distancia entre ca\303\261ones", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Altura ca\303\261on ofensivo", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Altura ca\303\261on defensivo", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Velocidad Inicial Disparo Ofensivo", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Angulo Inicial Disparo Ofensivo", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Angulo Inicial Disparo Defensivo", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Velocidad Inicial Disparo Defensivo", nullptr));
        btnVolver->setText(QApplication::translate("MainWindow", "Volver", nullptr));
        lblSimula1->setText(QString());
        lblSimula2->setText(QString());
        lblSimula3->setText(QString());
        lblSimula4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
