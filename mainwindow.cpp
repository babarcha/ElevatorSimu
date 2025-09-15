#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QMessageBox>
#include <QPushButton>
#include <QCheckBox>
#include <QPlainTextEdit>
#include <QTextCursor>

static QString tsNow() {
    return QDateTime::currentDateTime().toString("HH:mm:ss");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ElevatorSimQt - v0.6.1 (Single-Select + Dual Logs + Hybrid)");

    // Connection buttons
    connect(ui->btnRefresh,    &QPushButton::clicked, this, &MainWindow::refreshPorts);
    connect(ui->btnConnect,    &QPushButton::clicked, this, &MainWindow::connectPort);
    connect(ui->btnDisconnect, &QPushButton::clicked, this, &MainWindow::disconnectPort);

    // Floor buttons (single-selection target)
    connect(ui->btnF1, &QPushButton::clicked, this, &MainWindow::callFloor1);
    connect(ui->btnF2, &QPushButton::clicked, this, &MainWindow::callFloor2);
    connect(ui->btnF3, &QPushButton::clicked, this, &MainWindow::callFloor3);
    connect(ui->btnF4, &QPushButton::clicked, this, &MainWindow::callFloor4);
    connect(ui->btnF5, &QPushButton::clicked, this, &MainWindow::callFloor5);

    // Door + status
    connect(ui->btnDoorOpen,  &QPushButton::clicked, this, &MainWindow::doorOpen);
    connect(ui->btnDoorClose, &QPushButton::clicked, this, &MainWindow::doorClose);
    connect(ui->btnStatus,    &QPushButton::clicked, this, &MainWindow::requestStatus);

    // Serial read
    connect(&serial_, &QSerialPort::readyRead, this, &MainWindow::onReadyRead);

    // Animation timer
    connect(&simTimer_, &QTimer::timeout, this, &MainWindow::onSimTick);
    simTimer_.setInterval(200);

    // Init UI
    setConnected(false);
    refreshPorts();
    setFloor(currentFloor_);
    setMoving("IDLE");
    setDoor("CLOSED");
    updateFloorLights();
}

MainWindow::~MainWindow() { delete ui; }

// ---------------- UI helpers ----------------
void MainWindow::logConn(const QString& line) {
    ui->textConnLog->appendPlainText(QString("[%1] %2").arg(tsNow(), line));
    scrollToEnd(ui->textConnLog);
}

void MainWindow::logFloorNumber(int n) {
    static int last = -9999;            // de-duplicate identical consecutive numbers
    if (last == n) return;
    last = n;
    ui->textFloorLog->appendPlainText(QString::number(n));
    scrollToEnd(ui->textFloorLog);
}

void MainWindow::scrollToEnd(QPlainTextEdit* pte) {
    auto c = pte->textCursor();
    c.movePosition(QTextCursor::End);
    pte->setTextCursor(c);
}

// ------------- Ports / connect -------------
void MainWindow::refreshPorts() {
    ui->cmbPorts->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const auto &p : ports) {
        ui->cmbPorts->addItem(QString("%1 (%2)").arg(p.portName(), p.description()), p.systemLocation());
    }
    logConn(QString("Found %1 port(s).").arg(ui->cmbPorts->count()));
}

void MainWindow::connectPort() {
    auto *chkSim = this->findChild<QCheckBox*>("chkSim");
    const bool simOnly = (chkSim && chkSim->isChecked());

    if (simOnly) {
        simTimer_.start();
        setConnected(true);
        logConn("Simulator mode: connected (virtual).");
        return;
    }

    if (serial_.isOpen()) return;
    if (ui->cmbPorts->count() == 0) {
        QMessageBox::warning(this, "No Ports", "No serial ports found. Plug in ESP32 and click Refresh.");
        return;
    }
    const QString sysLoc = ui->cmbPorts->currentData().toString();
    serial_.setPortName(sysLoc);
    serial_.setBaudRate(ui->spinBaud->value());
    serial_.setDataBits(QSerialPort::Data8);
    serial_.setParity(QSerialPort::NoParity);
    serial_.setStopBits(QSerialPort::OneStop);
    serial_.setFlowControl(QSerialPort::NoFlowControl);

    if (!serial_.open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Connect Failed", "Could not open port.");
        setConnected(false);
        return;
    }

    setConnected(true);
    logConn(QString("Connected -> %1 @ %2").arg(sysLoc).arg(ui->spinBaud->value()));

    // Always animate in hybrid mode when ESP32 is connected
    simTimer_.start();
    logConn("Hybrid animation: ON (simulator-style UI while ESP32 is connected).");
}

void MainWindow::disconnectPort() {
    auto *chkSim = this->findChild<QCheckBox*>("chkSim");
    const bool simOnly = (chkSim && chkSim->isChecked());

    if (simOnly) {
        simTimer_.stop();
        logConn("Simulator mode: disconnected.");
        setConnected(false);
        return;
    }

    if (serial_.isOpen()) {
        const auto name = serial_.portName();
        serial_.close();
        logConn(QString("Disconnected <- %1").arg(name));
    }
    simTimer_.stop();
    setConnected(false);
}

void MainWindow::setConnected(bool ok) {
    auto *chkSim = this->findChild<QCheckBox*>("chkSim");
    const bool simOnly = (chkSim && chkSim->isChecked());

    ui->btnConnect->setEnabled(!ok);
    ui->btnDisconnect->setEnabled(ok);
    ui->cmbPorts->setEnabled(!ok && !simOnly);
    ui->btnRefresh->setEnabled(!ok && !simOnly);
    ui->spinBaud->setEnabled(!ok && !simOnly);

    ui->grpControls->setEnabled(ok);
    ui->grpStatus->setEnabled(ok);
}

// ------------- Serial RX -------------
void MainWindow::onReadyRead() {
    rxBuffer_.append(serial_.readAll());
    processIncoming();
}

void MainWindow::processIncoming() {
    while (true) {
        int nl = rxBuffer_.indexOf('\n');
        if (nl < 0) break;
        QByteArray line = rxBuffer_.left(nl);
        rxBuffer_.remove(0, nl + 1);
        const QString s = QString::fromUtf8(line).trimmed();
        if (!s.isEmpty()) handleLine(s);
    }
}

void MainWindow::handleLine(const QString& s) {
    logConn(QString("<< %1").arg(s));
    const QStringList parts = s.split(' ', Qt::SkipEmptyParts);
    if (parts.isEmpty()) return;
    const QString head = parts[0].toUpper();

    if (head == "POS" && parts.size() >= 2) {
        bool ok=false; int n = parts[1].toInt(&ok);
        if (ok) {
            setFloor(n);
            logFloorNumber(n);
        }
    } else if (head == "DOOR" && parts.size() >= 2) {
        setDoor(parts[1].toUpper());
    } else if (head == "MOVING" && parts.size() >= 2) {
        setMoving(parts[1].toUpper());
    } else if (head == "ACK") {
        // optional: brief status
    } else if (head == "ERR") {
        statusBar()->showMessage(s, 4000);
    }
}

// ------------- Model setters -------------
void MainWindow::setFloor(int n) {
    currentFloor_ = n;
    ui->valCurFloor->setText(QString::number(n));
    updateFloorLights();      // current floor = highlighted (green)
}

void MainWindow::setMoving(const QString& s) {
    ui->valMoving->setText(s);
}

void MainWindow::setDoor(const QString& s) {
    ui->valDoor->setText(s);
}

// ------------- Send commands -------------
template<typename Logger>
void MainWindow::sendCmd(const QString& cmd, Logger logger) {
    auto *chkSim = this->findChild<QCheckBox*>("chkSim");
    const bool simOnly = (chkSim && chkSim->isChecked());

    logger(QString(">> %1").arg(cmd));

    // Always animate locally (hybrid), even with hardware
    simHandleCmd(cmd);
    simTimer_.start();

    if (!simOnly && serial_.isOpen()) {
        QByteArray line = cmd.toUtf8();
        if (!line.endsWith('\n')) line.append('\n');
        serial_.write(line);
    }
}

// ------------- Controls (single-selection target) -------------
void MainWindow::callFloor1() { targetFloor_ = 1; updateFloorLights(); sendCmd("CALL 1", [this](const QString& m){ logConn(m); }); }
void MainWindow::callFloor2() { targetFloor_ = 2; updateFloorLights(); sendCmd("CALL 2", [this](const QString& m){ logConn(m); }); }
void MainWindow::callFloor3() { targetFloor_ = 3; updateFloorLights(); sendCmd("CALL 3", [this](const QString& m){ logConn(m); }); }
void MainWindow::callFloor4() { targetFloor_ = 4; updateFloorLights(); sendCmd("CALL 4", [this](const QString& m){ logConn(m); }); }
void MainWindow::callFloor5() { targetFloor_ = 5; updateFloorLights(); sendCmd("CALL 5", [this](const QString& m){ logConn(m); }); }
void MainWindow::doorOpen()   { sendCmd("DOOR OPEN",  [this](const QString& m){ logConn(m); }); }
void MainWindow::doorClose()  { sendCmd("DOOR CLOSE", [this](const QString& m){ logConn(m); }); }
void MainWindow::requestStatus(){ sendCmd("STATUS?",  [this](const QString& m){ logConn(m); }); }

// ------------- Animation/Simulator engine -------------
void MainWindow::simSend(const QString& line) {
    // Reuse the same input path as hardware
    handleLine(line);
}

void MainWindow::simHandleCmd(const QString& cmd) {
    const auto up = cmd.toUpper();
    if (up.startsWith("CALL")) {
        const auto parts = up.split(' ', Qt::SkipEmptyParts);
        if (parts.size() >= 2) {
            bool ok=false; int n = parts[1].toInt(&ok);
            if (ok && n >= 1 && n <= 20) {
                targetFloor_ = n;        // single selection
                updateFloorLights();     // show target (amber), current (green)

                // close door if open; then move if needed
                if (door_ == Door::Open || door_ == Door::Opening) {
                    door_ = Door::Closing; doorTick_ = 0;
                    simSend("DOOR CLOSING");
                }
                Move desired = (n > currentFloor_) ? Move::Up : (n < currentFloor_ ? Move::Down : Move::Idle);
                if (desired == Move::Idle) {
                    // same floor: open door
                    simSend("ACK CALL");
                    door_ = Door::Opening; doorTick_ = 0;
                    simSend("DOOR OPENING");
                } else {
                    if (move_ == Move::Idle) {
                        move_ = desired;
                        simSend(QString("MOVING %1").arg(move_==Move::Up?"UP":"DOWN"));
                    }
                    simSend("ACK CALL");
                }
            }
        }
    } else if (up == "DOOR OPEN") {
        if (move_ != Move::Idle) { simSend("ERR 1 CANNOT_OPEN_WHILE_MOVING"); return; }
        if (door_ == Door::Closed || door_ == Door::Closing) {
            door_ = Door::Opening; doorTick_ = 0;
            simSend("DOOR OPENING");
        }
        simSend("ACK DOOR_OPEN");
    } else if (up == "DOOR CLOSE") {
        if (door_ == Door::Open || door_ == Door::Opening) {
            door_ = Door::Closing; doorTick_ = 0;
            simSend("DOOR CLOSING");
        }
        simSend("ACK DOOR_CLOSE");
    } else if (up == "STATUS?") {
        simSend(QString("POS %1").arg(currentFloor_));
        simSend(QString("MOVING %1").arg(move_==Move::Up?"UP":move_==Move::Down?"DOWN":"IDLE"));
        QString d = "CLOSED";
        if (door_==Door::Open) d="OPEN";
        else if (door_==Door::Opening) d="OPENING";
        else if (door_==Door::Closing) d="CLOSING";
        simSend(QString("DOOR %1").arg(d));
        simSend("ACK STATUS");
    }
}

void MainWindow::onSimTick() {
    // Door transitions
    if (door_ == Door::Opening) {
        doorTick_ += simTimer_.interval();
        if (doorTick_ >= doorStepMs_) { door_ = Door::Open; simSend("DOOR OPEN"); }
    } else if (door_ == Door::Closing) {
        doorTick_ += simTimer_.interval();
        if (doorTick_ >= doorStepMs_) { door_ = Door::Closed; simSend("DOOR CLOSED"); }
    }

    // Movement
    if (move_ != Move::Idle && door_ == Door::Closed) {
        static int acc = 0;
        acc += simTimer_.interval();
        if (acc >= simStepMs_) {
            acc = 0;
            currentFloor_ += (move_==Move::Up ? 1 : -1);
            simSend(QString("POS %1").arg(currentFloor_));
            logFloorNumber(currentFloor_);   // floor log updates here
            if ((move_==Move::Up  && currentFloor_ >= targetFloor_) ||
                (move_==Move::Down&& currentFloor_ <= targetFloor_)) {
                move_ = Move::Idle;
                simSend("MOVING IDLE");
                // open door on arrival
                door_ = Door::Opening; doorTick_ = 0;
                simSend("DOOR OPENING");
            }
        }
    }
}

// -------------------- Lights helpers --------------------
QPushButton* MainWindow::buttonForFloor(int floor) {
    switch (floor) {
    case 1: return ui->btnF1;
    case 2: return ui->btnF2;
    case 3: return ui->btnF3;
    case 4: return ui->btnF4;
    case 5: return ui->btnF5;
    default: return nullptr;
    }
}

void MainWindow::setFloorLight(int floor, Light st) {
    if (auto *btn = buttonForFloor(floor)) {
        switch (st) {
        case Light::Normal:
            btn->setStyleSheet("");
            break;
        case Light::Target:
            btn->setStyleSheet("QPushButton{ background-color:#ffd54f; }"); // amber
            break;
        case Light::Current:
            btn->setStyleSheet("QPushButton{ background-color:#81c784; }"); // green
            break;
        }
    }
}

void MainWindow::updateFloorLights() {
    // Reset all
    for (int f=1; f<=5; ++f) setFloorLight(f, Light::Normal);
    // Current floor green
    setFloorLight(currentFloor_, Light::Current);
    // Target amber (unless same as current)
    if (targetFloor_ != currentFloor_) setFloorLight(targetFloor_, Light::Target);
}
