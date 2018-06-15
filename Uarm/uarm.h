#ifndef UARM_H
#define UARM_H

#include <QObject>
#include <QDebug>
#include <QString>

#define MoveCmdS  ((const char *)"G")

enum MoveCmd
{
    MoveCmdXYZ=0,
    MoveCmdPOL=201,
    MoveCmdServo=202,
    MoveCmdStop=203,
    MoveCmdRelativeDis=204
};

#define SetCmdS ((const char *)"M")

enum SetCmd
{
    SetCmdFeedbackCycle=120,
    SetCmdArmIsMoving=200,
    SetCmdAttachServo=201,
    SetCmdDetachServo=202,
    SetCmdBuzzer=210,
    SetCmdReadEEPROM=211,
    SetCmdWriteEEPROM=212,
    SetCmdConvCoortoAngle=220,
    SetCmdConvAngletoCoor=221,
    SetCmdCheckReach=222,
    SetCmdPumpWorking=231,
    SetCmdGripperClose=232,
    SetCmdSetGPIO=240
};

#define QueryCmdS ((const char *)"P")

enum QueryCmd
{
    QueryCmdCurrAngle=200,
    QueryCmdDeviceName=201,
    QueryCmdHardwareVersion=202,
    QueryCmdSoftwareVersion=203,
    QueryCmdAPIVersion=204,
    QueryCmdUID=205,
    QueryCmdCurrCartCoordinates=220,
    QueryCmdCurrPolarCoordinates=221,
    QueryCmdStatusOfPump=231,
    QueryCmdStatusOfGripper=232,
    QueryCmdStatusOfLimitedSwitch=233,
    QueryCmdStatusGPIO=240,
    QueryCmdStatusADC=241
};

enum ErrorNumber
{
    ErrorNumberUnexistCommand=20,
    ErrorNumberParameterError=20,
    ErrorNumberAddressOutOfRange=20
};

class Uarm : public QObject
{
    Q_OBJECT
public:
    explicit Uarm(QObject *parent = 0);  
    QString CommandSkeleton(QString cmd);
    QString MoveToXYZ(uint16_t X, uint16_t Y, uint16_t Z, uint16_t F = 100);
    QString MoveToSRH(uint16_t S,uint16_t R,uint16_t H);
    QString MoveServo(uint8_t ID,uint16_t Angle);
    QString relativeDisplacement();
    QString stopMotor(uint16_t X,uint16_t Y,uint16_t Z);

    void sendCmd(QString Fullcmd);
signals:

public slots:

private:
    void initUarm();
    quint32 m_CmdNr;
};

#endif // UARM_H
