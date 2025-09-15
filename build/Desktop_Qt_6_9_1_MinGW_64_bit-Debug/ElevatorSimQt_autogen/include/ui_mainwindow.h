/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *grpConn;
    QGridLayout *gridConn;
    QLabel *lblPort;
    QComboBox *cmbPorts;
    QPushButton *btnRefresh;
    QLabel *lblBaud;
    QSpinBox *spinBaud;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QCheckBox *chkAnimate;
    QCheckBox *chkSim;
    QGroupBox *grpControls;
    QGridLayout *gridControls;
    QLabel *lblFloors;
    QHBoxLayout *hboxFloors;
    QPushButton *btnF1;
    QPushButton *btnF2;
    QPushButton *btnF3;
    QPushButton *btnF4;
    QPushButton *btnF5;
    QLabel *lblDoorCtl;
    QPushButton *btnDoorOpen;
    QPushButton *btnDoorClose;
    QPushButton *btnStatus;
    QGroupBox *grpStatus;
    QGridLayout *gridStatus;
    QLabel *lblCurFloor;
    QLabel *valCurFloor;
    QLabel *lblMoving;
    QLabel *valMoving;
    QLabel *lblDoor;
    QLabel *valDoor;
    QGroupBox *grpLog;
    QGridLayout *gridLogs;
    QLabel *lblConnLog;
    QPlainTextEdit *textConnLog;
    QLabel *lblFloorLog;
    QPlainTextEdit *textFloorLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        grpConn = new QGroupBox(centralwidget);
        grpConn->setObjectName("grpConn");
        gridConn = new QGridLayout(grpConn);
        gridConn->setObjectName("gridConn");
        lblPort = new QLabel(grpConn);
        lblPort->setObjectName("lblPort");

        gridConn->addWidget(lblPort, 0, 0, 1, 1);

        cmbPorts = new QComboBox(grpConn);
        cmbPorts->setObjectName("cmbPorts");

        gridConn->addWidget(cmbPorts, 0, 1, 1, 2);

        btnRefresh = new QPushButton(grpConn);
        btnRefresh->setObjectName("btnRefresh");

        gridConn->addWidget(btnRefresh, 0, 3, 1, 1);

        lblBaud = new QLabel(grpConn);
        lblBaud->setObjectName("lblBaud");

        gridConn->addWidget(lblBaud, 1, 0, 1, 1);

        spinBaud = new QSpinBox(grpConn);
        spinBaud->setObjectName("spinBaud");
        spinBaud->setMinimum(1200);
        spinBaud->setMaximum(10000000);
        spinBaud->setValue(115200);
        spinBaud->setSingleStep(1200);

        gridConn->addWidget(spinBaud, 1, 1, 1, 1);

        btnConnect = new QPushButton(grpConn);
        btnConnect->setObjectName("btnConnect");

        gridConn->addWidget(btnConnect, 1, 2, 1, 1);

        btnDisconnect = new QPushButton(grpConn);
        btnDisconnect->setObjectName("btnDisconnect");
        btnDisconnect->setEnabled(false);

        gridConn->addWidget(btnDisconnect, 1, 3, 1, 1);

        chkAnimate = new QCheckBox(grpConn);
        chkAnimate->setObjectName("chkAnimate");

        gridConn->addWidget(chkAnimate, 1, 4, 1, 1);

        chkSim = new QCheckBox(grpConn);
        chkSim->setObjectName("chkSim");

        gridConn->addWidget(chkSim, 1, 5, 1, 1);


        verticalLayout->addWidget(grpConn);

        grpControls = new QGroupBox(centralwidget);
        grpControls->setObjectName("grpControls");
        gridControls = new QGridLayout(grpControls);
        gridControls->setObjectName("gridControls");
        lblFloors = new QLabel(grpControls);
        lblFloors->setObjectName("lblFloors");

        gridControls->addWidget(lblFloors, 0, 0, 1, 1);

        hboxFloors = new QHBoxLayout();
        hboxFloors->setObjectName("hboxFloors");
        btnF1 = new QPushButton(grpControls);
        btnF1->setObjectName("btnF1");

        hboxFloors->addWidget(btnF1);

        btnF2 = new QPushButton(grpControls);
        btnF2->setObjectName("btnF2");

        hboxFloors->addWidget(btnF2);

        btnF3 = new QPushButton(grpControls);
        btnF3->setObjectName("btnF3");

        hboxFloors->addWidget(btnF3);

        btnF4 = new QPushButton(grpControls);
        btnF4->setObjectName("btnF4");

        hboxFloors->addWidget(btnF4);

        btnF5 = new QPushButton(grpControls);
        btnF5->setObjectName("btnF5");

        hboxFloors->addWidget(btnF5);


        gridControls->addLayout(hboxFloors, 0, 1, 1, 5);

        lblDoorCtl = new QLabel(grpControls);
        lblDoorCtl->setObjectName("lblDoorCtl");

        gridControls->addWidget(lblDoorCtl, 1, 0, 1, 1);

        btnDoorOpen = new QPushButton(grpControls);
        btnDoorOpen->setObjectName("btnDoorOpen");

        gridControls->addWidget(btnDoorOpen, 1, 1, 1, 1);

        btnDoorClose = new QPushButton(grpControls);
        btnDoorClose->setObjectName("btnDoorClose");

        gridControls->addWidget(btnDoorClose, 1, 2, 1, 1);

        btnStatus = new QPushButton(grpControls);
        btnStatus->setObjectName("btnStatus");

        gridControls->addWidget(btnStatus, 1, 3, 1, 1);


        verticalLayout->addWidget(grpControls);

        grpStatus = new QGroupBox(centralwidget);
        grpStatus->setObjectName("grpStatus");
        gridStatus = new QGridLayout(grpStatus);
        gridStatus->setObjectName("gridStatus");
        lblCurFloor = new QLabel(grpStatus);
        lblCurFloor->setObjectName("lblCurFloor");

        gridStatus->addWidget(lblCurFloor, 0, 0, 1, 1);

        valCurFloor = new QLabel(grpStatus);
        valCurFloor->setObjectName("valCurFloor");

        gridStatus->addWidget(valCurFloor, 0, 1, 1, 1);

        lblMoving = new QLabel(grpStatus);
        lblMoving->setObjectName("lblMoving");

        gridStatus->addWidget(lblMoving, 0, 2, 1, 1);

        valMoving = new QLabel(grpStatus);
        valMoving->setObjectName("valMoving");

        gridStatus->addWidget(valMoving, 0, 3, 1, 1);

        lblDoor = new QLabel(grpStatus);
        lblDoor->setObjectName("lblDoor");

        gridStatus->addWidget(lblDoor, 1, 0, 1, 1);

        valDoor = new QLabel(grpStatus);
        valDoor->setObjectName("valDoor");

        gridStatus->addWidget(valDoor, 1, 1, 1, 1);


        verticalLayout->addWidget(grpStatus);

        grpLog = new QGroupBox(centralwidget);
        grpLog->setObjectName("grpLog");
        gridLogs = new QGridLayout(grpLog);
        gridLogs->setObjectName("gridLogs");
        lblConnLog = new QLabel(grpLog);
        lblConnLog->setObjectName("lblConnLog");

        gridLogs->addWidget(lblConnLog, 0, 0, 1, 1);

        textConnLog = new QPlainTextEdit(grpLog);
        textConnLog->setObjectName("textConnLog");
        textConnLog->setReadOnly(true);
        textConnLog->setMinimumHeight(90);

        gridLogs->addWidget(textConnLog, 1, 0, 1, 1);

        lblFloorLog = new QLabel(grpLog);
        lblFloorLog->setObjectName("lblFloorLog");

        gridLogs->addWidget(lblFloorLog, 2, 0, 1, 1);

        textFloorLog = new QPlainTextEdit(grpLog);
        textFloorLog->setObjectName("textFloorLog");
        textFloorLog->setReadOnly(true);
        textFloorLog->setMinimumHeight(70);

        gridLogs->addWidget(textFloorLog, 3, 0, 1, 1);


        verticalLayout->addWidget(grpLog);

        verticalLayout->setStretch(3, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ElevatorSimQt - v0.6.1 (Single-Select + Dual Logs + Hybrid)", nullptr));
        grpConn->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        lblPort->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        lblBaud->setText(QCoreApplication::translate("MainWindow", "Baud", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        btnDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        chkAnimate->setText(QCoreApplication::translate("MainWindow", "Animate UI", nullptr));
        chkSim->setText(QCoreApplication::translate("MainWindow", "Simulator mode", nullptr));
        grpControls->setTitle(QCoreApplication::translate("MainWindow", "Controls", nullptr));
        lblFloors->setText(QCoreApplication::translate("MainWindow", "Floors", nullptr));
        btnF1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnF2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btnF3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btnF4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btnF5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        lblDoorCtl->setText(QCoreApplication::translate("MainWindow", "Door", nullptr));
        btnDoorOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        btnDoorClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        btnStatus->setText(QCoreApplication::translate("MainWindow", "Status?", nullptr));
        grpStatus->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        lblCurFloor->setText(QCoreApplication::translate("MainWindow", "Floor:", nullptr));
        valCurFloor->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lblMoving->setText(QCoreApplication::translate("MainWindow", "Moving:", nullptr));
        valMoving->setText(QCoreApplication::translate("MainWindow", "IDLE", nullptr));
        lblDoor->setText(QCoreApplication::translate("MainWindow", "Door:", nullptr));
        valDoor->setText(QCoreApplication::translate("MainWindow", "CLOSED", nullptr));
        grpLog->setTitle(QCoreApplication::translate("MainWindow", "Logs", nullptr));
        lblConnLog->setText(QCoreApplication::translate("MainWindow", "Device Log", nullptr));
        lblFloorLog->setText(QCoreApplication::translate("MainWindow", "Floor Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
