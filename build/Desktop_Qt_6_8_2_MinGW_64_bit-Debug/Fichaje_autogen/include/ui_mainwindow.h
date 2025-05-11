/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QDateEdit *dateSelector;
    QTimeEdit *timeEdit;
    QPushButton *ficharButton;
    QPushButton *exportButton;
    QLabel *dayLabelCaption;
    QLabel *weekLabelCaption;
    QLabel *dayLabel;
    QLabel *weekLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(372, 297);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        dateSelector = new QDateEdit(centralwidget);
        dateSelector->setObjectName("dateSelector");
        dateSelector->setGeometry(QRect(30, 10, 110, 26));
        timeEdit = new QTimeEdit(centralwidget);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setGeometry(QRect(140, 10, 118, 26));
        ficharButton = new QPushButton(centralwidget);
        ficharButton->setObjectName("ficharButton");
        ficharButton->setGeometry(QRect(100, 40, 93, 29));
        exportButton = new QPushButton(centralwidget);
        exportButton->setObjectName("exportButton");
        exportButton->setGeometry(QRect(100, 160, 93, 29));
        dayLabelCaption = new QLabel(centralwidget);
        dayLabelCaption->setObjectName("dayLabelCaption");
        dayLabelCaption->setGeometry(QRect(30, 90, 161, 20));
        weekLabelCaption = new QLabel(centralwidget);
        weekLabelCaption->setObjectName("weekLabelCaption");
        weekLabelCaption->setGeometry(QRect(30, 120, 221, 20));
        dayLabel = new QLabel(centralwidget);
        dayLabel->setObjectName("dayLabel");
        dayLabel->setGeometry(QRect(230, 90, 63, 20));
        weekLabel = new QLabel(centralwidget);
        weekLabel->setObjectName("weekLabel");
        weekLabel->setGeometry(QRect(230, 120, 63, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 372, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Fichaje", nullptr));
        ficharButton->setText(QCoreApplication::translate("MainWindow", "Fichar", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Exportar", nullptr));
        dayLabelCaption->setText(QCoreApplication::translate("MainWindow", "Tiempo trabajado hoy:", nullptr));
        weekLabelCaption->setText(QCoreApplication::translate("MainWindow", "Tiempo trabajado esta semana:", nullptr));
        dayLabel->setText(QCoreApplication::translate("MainWindow", "00:00", nullptr));
        weekLabel->setText(QCoreApplication::translate("MainWindow", "00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
