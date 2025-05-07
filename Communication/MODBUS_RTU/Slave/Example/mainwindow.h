#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../MODBUS_RTU_Slave.h"
#include <QDebug>
#include <QRegularExpression>
#include <QDateTime>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    MODBUS_RTU_Slave* _MODBUS_RTU_Slave;
    QByteArray _Frame;

    void ShowRegisterArea(int index);

#define LED_TOTAL_COUNT 36

#define MODBUS_COILEDREGISTERS 3

#define MODBUS_REGISTERS_DEVICE_AMOUNT 10
#define MODBUS_REGISTERS_DEVICE_FIRSTADDRESS 0
    MODBUS_RTU_Register_UINT16 _Registers_Device[MODBUS_REGISTERS_DEVICE_AMOUNT];
    MODBUS_RTU_Register_Attribute _RegistersAttribute_Device[MODBUS_REGISTERS_DEVICE_AMOUNT];
#define MODBUS_REGISTERS_GRADIENT_AMOUNT 63
#define MODBUS_REGISTERS_GRADIENT_FIRSTADDRESS 100
#ifdef USE_COIL
    MODBUS_RTU_Register_BIT
#else
    MODBUS_RTU_Register_UINT16
#endif
        _Registers_Gradient[MODBUS_REGISTERS_GRADIENT_AMOUNT];
    MODBUS_RTU_Register_Attribute _RegistersAttribute_Gradient[MODBUS_REGISTERS_GRADIENT_AMOUNT];
#define MODBUS_REGISTERS_DIRECTCOLOR_AMOUNT (LED_TOTAL_COUNT << 1) + 1
#define MODBUS_REGISTERS_DIRECTCOLOR_FIRSTADDRESS 1000
    MODBUS_RTU_Register_UINT16 _Registers_DirectColor[MODBUS_REGISTERS_DIRECTCOLOR_AMOUNT];
    MODBUS_RTU_Register_Attribute _RegistersAttribute_DirectColor[MODBUS_REGISTERS_DIRECTCOLOR_AMOUNT];

    MODBUS_RTU_CoiledRegistersArea _CoiledRegistersArray[MODBUS_COILEDREGISTERS];

private slots:
    void SLOT_PushButton_Prase_Clicked();
    void SLOT_UpdateFrame();
    void SLOT_LineEdit_Data_TextChanged(const QString &arg1);
    void SLOT_TableWidget_RegisterAreas_CurrentCellChanged(int newRow, int newColumn, int oldRow, int oldColumn);
};
#endif // MAINWINDOW_H
