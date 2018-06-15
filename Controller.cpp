#include "Controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
     settingupTTY();
     m_uarmLib = new Uarm();
}

void Controller::registerMetaTypes()
{

}

void Controller::setContextProperty(QQmlContext context)
{

}


void Controller::settingupTTY()
{
    m_ttyUsbThread = new QThread;
    m_ttyUsb = new TTYUSB();
    m_ttyUsb->moveToThread(m_ttyUsbThread);

    connect(m_ttyUsbThread, SIGNAL(started()), m_ttyUsb, SLOT(TTYUSB_THREAD()));
    connect(m_ttyUsb, SIGNAL(finished()), m_ttyUsbThread, SLOT(quit()));
    connect(m_ttyUsb, SIGNAL(finished()), m_ttyUsb, SLOT(deleteLater()));
    connect(m_ttyUsbThread, SIGNAL(finished()), m_ttyUsbThread, SLOT(deleteLater()));

    //QObject::connect(m_ttyUsb,SIGNAL(makeErrorSignal(ERRORCODE, QString)),this,SLOT(HandleErrors(ERRORCODE, QString)),Qt::QueuedConnection);
    //Connect setPixmap Signal from Business Class to MainWindows signal

    //QObject::connect(m_ttyUsb,SIGNAL(responseNmea(QString)),this,SLOT(HandleNmea(QString)),Qt::QueuedConnection);
    //Connect PixmapButton Signal from MainWindow to Business Class signal

    /*QObject::connect(this,
                 SIGNAL(readttyUSB()),
                 m_ttyUsb,
                 SLOT(TTYUSB_INIT()),
                 Qt::QueuedConnection);*/

    m_ttyUsbThread->start();

}


