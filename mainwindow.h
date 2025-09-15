#pragma once
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

class QPushButton;
class QCheckBox;
class QPlainTextEdit;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Connection
    void refreshPorts();
    void connectPort();
    void disconnectPort();

    // Serial RX
    void onReadyRead();

    // Controls (single-selection target)
    void callFloor1();
    void callFloor2();
    void callFloor3();
    void callFloor4();
    void callFloor5();
    void doorOpen();
    void doorClose();
    void requestStatus();

    // Animation tick (also used with ESP32 connected)
    void onSimTick();

private:
    // UI helpers
    void setConnected(bool ok);
    void logConn(const QString& line);
    void logFloorNumber(int n);
    void scrollToEnd(QPlainTextEdit* pte);

    // Parser + state
    void processIncoming();
    void handleLine(const QString& s);
    void setFloor(int n);
    void setMoving(const QString& s);
    void setDoor(const QString& s);

    template<typename Logger>
    void sendCmd(const QString& cmd, Logger logger);

    // Animation engine (same as simulator logic)
    void simSend(const QString& line);
    void simHandleCmd(const QString& cmd);

    // Floor button highlighting
    enum class Light { Normal, Target, Current };
    void setFloorLight(int floor, Light st);
    void updateFloorLights();
    QPushButton* buttonForFloor(int floor);

    Ui::MainWindow *ui{};
    QSerialPort serial_;
    QByteArray rxBuffer_;

    // Animated model
    QTimer simTimer_;
    int currentFloor_ = 1;
    int targetFloor_  = 1;     // single selection target
    enum class Move { Idle, Up, Down } move_ = Move::Idle;
    enum class Door { Closed, Opening, Open, Closing } door_ = Door::Closed;
    int simStepMs_ = 800;      // per-floor
    int doorStepMs_ = 600;     // open/close transition
    int doorTick_ = 0;
};
