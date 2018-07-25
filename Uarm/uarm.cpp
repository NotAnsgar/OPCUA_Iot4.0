#include "uarm.h"

Uarm::Uarm(QObject *parent) : QObject(parent)
{
    m_CmdNr = 0;
    QString la = MoveToXYZ(100,100,100);
    sleep(10);
}

void Uarm::initUarm()
{
    qDebug() << "init!:";

    qDebug() << "GetSoftwareVersion!:";
    emit TTYUSB_WRITE("#2 P203\r\n");

    emit TTYUSB_WRITE("#3 P203\r\n");
    emit TTYUSB_WRITE("#4 P203\r\n");

    qDebug() << "GetHardwareVersion!:";
    emit TTYUSB_WRITE("#5 P202\r\n");
    sleep(2);
    qDebug() << "Drive to home!:";
    emit TTYUSB_WRITE("#1 G0 X0 Y0 Z0 F100\r\n");

}

QString Uarm::CommandSkeleton(QString cmd)
{
    return "#"+QString::number(m_CmdNr)+" "+cmd+"\r\n";
}


QString Uarm::MoveToXYZ(uint16_t X, uint16_t Y, uint16_t Z,uint16_t F)
{
    QString cmd = QString("G") + QString::number(MoveCmdXYZ) +" "+"X" +QString::number(X)+" "+"Y" +QString::number(Y)+" "+"Z" +QString::number(Z)+" "+"F" +QString::number(F);
    QString skelleton = CommandSkeleton(cmd);
    return skelleton;
}

QString Uarm::MoveToSRH(uint16_t S, uint16_t R, uint16_t H)
{

}

QString Uarm::MoveServo(uint8_t ID, uint16_t Angle)
{

}

QString Uarm::relativeDisplacement()
{

}

QString Uarm::stopMotor(uint16_t X, uint16_t Y, uint16_t Z)
{

}

void Uarm::sendCmd(QString Fullcmd)
{
     qDebug() << Fullcmd;
     emit TTYUSB_WRITE(Fullcmd);
}
