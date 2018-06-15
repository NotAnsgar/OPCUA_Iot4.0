#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QQmlContext>

#include "Kommunikation/tty.h"
#include "Uarm/uarm.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    void settingupTTY();
    void setContextProperty(QQmlContext context);
signals:

public slots:

private:
     void registerMetaTypes();
     TTYUSB* m_ttyUsb;
     QThread* m_ttyUsbThread;
     Uarm* m_uarmLib;

};

#endif // CONTROLLER_H
