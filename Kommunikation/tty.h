#pragma once
#include <list>
#include <QString>
#include <QTimer>
#include <QDir>
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <QMutex>
#include <QWaitCondition>

///
/// \brief The TTYUSB class
/// reads the TTY device and sends the GPS information to the BusinessClass
class TTYUSB final : public QObject {
Q_OBJECT
public :
     ///
     /// \brief TTYUSB
     ///
    TTYUSB();
    virtual ~TTYUSB();
public slots:
    void TTYUSB_WRITE(QString message);


protected slots:
    ///
    /// \brief TTYUSB_READ
    ///
    void TTYUSB_READ();
    ///
    /// \brief TTYUSB_THREAD
    ///
    void TTYUSB_THREAD();

Q_SIGNALS:
    ///
    /// \brief makeErrorSignal
    /// \param error
    /// \param extraerror
    ///
    void responseNmea(QString response);
    ///
    /// \brief finished
    ///
    void finished();
    ///
    /// \brief error
    /// \param err
    ///
    void error(QString err);

private:
    ///
    /// \brief TTYUSB_INIT
    /// \return
    ///
    bool TTYUSB_INIT();
    ///
    /// \brief makeError
    /// \param error
    /// \param extraerror
    ///
    std::string getfirstTTYUSB(std::string dir, std::string find);//TODO: Why dont you use QString
    bool m_cancelRequested;
    struct termios m_tty;
    struct termios m_tty_old;
    int m_USB;
    QString m_devicepath;
    QObject* m_obj;
    bool m_windowshown;
    bool m_iserror;
    QString m_Device;
    QString m_Device_Path;
 };
