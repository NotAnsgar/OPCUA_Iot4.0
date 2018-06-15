#include "tty.h"
#include <stdio.h>   // standard input / output functions
#include <stdlib.h>
#include <string.h>  // string function definitions
#include <unistd.h>  // UNIX standard function definitions
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions
#include <termios.h> // POSIX terminal control definitions
#include <iostream>
#include <dirent.h>
#include <pthread.h>
#include <mutex>
#include <QThread>
#include <QDebug>

TTYUSB::TTYUSB()
  : QObject(nullptr)
{
  m_obj         = this;
  m_windowshown = false;
  m_Device      = "ttyUSB";
  m_Device_Path = "/dev/";
  m_USB = 0;
  m_devicepath = "empty";
}

void TTYUSB::TTYUSB_THREAD()
{
  QTimer::singleShot(0, this, SLOT(TTYUSB_READ()));
}


TTYUSB::~TTYUSB(){}


bool TTYUSB::TTYUSB_INIT()
{
  m_devicepath = QString::fromStdString(getfirstTTYUSB(m_Device_Path.toStdString(), m_Device.toStdString()));

  if (m_devicepath != "empty")
  {
    qDebug() << m_devicepath;
    m_USB = open(m_devicepath.toUtf8(), O_RDWR | O_NOCTTY);
    memset(&m_tty, 0, sizeof m_tty);

    /* Error Handling */
    if (tcgetattr(m_USB, &m_tty) != 0) {
      std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
    }

    /* Save old tty parameters */
    m_tty_old = m_tty;

    /* Set Baud Rate */
    cfsetospeed(&m_tty, (speed_t)B115200);
    cfsetispeed(&m_tty, (speed_t)B115200);

    /* Setting other Port Stuff */
    m_tty.c_cflag &=  ~PARENB; // Make 8n1
    m_tty.c_cflag &=  ~CSTOPB;
    m_tty.c_cflag &=  ~CSIZE;
    m_tty.c_cflag |=  CS8;

    m_tty.c_cflag    &=  ~CRTSCTS;       // no flow control
    m_tty.c_cc[VMIN]  =  1;              // read doesn't block
    m_tty.c_cc[VTIME] =  2;              // 2.0 seconds read timeout
    m_tty.c_cflag    |=  CREAD | CLOCAL; // turn on READ & ignore ctrl lines

    /* Make raw */
    cfmakeraw(&m_tty);

    /* Flush Port, then applies attributes */
    tcflush(m_USB, TCIFLUSH);

    if (tcsetattr(m_USB, TCSANOW, &m_tty) != 0)
    {
      std::cout << "Error " << errno << " from tcsetattr" << std::endl;
    }
    return true;
  }
  else
  {
    return false;
  }
}

void TTYUSB::TTYUSB_READ()
{
  //make sure usb serial adapter is initialised
  if (m_USB == 0)
  {
   while (!TTYUSB_INIT())
    {
      usleep(500 * 1000);
    }
  }

  //init temp. var
  int pos = 0;
  char buffer[1024];

  //read until we got a linefeed
  do
  {
    //check buffer size
    if (pos >= sizeof(buffer))
    {
      std::cout << "Error reading from USB: No linefeed since " <<  sizeof(buffer) << " characters\n";
      pos = 0;
    }

    //read one char
    read(m_USB, &buffer[pos], 1);
  }
  while (buffer[pos++] != '\n');

  //make sure string is terminated
  buffer[pos] = '\0';

  //call nmea parser function
  QString result = QString(buffer);
  //emit responseNmea(result);

  qDebug() << result;

  //restart function call
  QTimer::singleShot(1, this, SLOT(TTYUSB_READ()));
}

void TTYUSB::TTYUSB_WRITE(QString message)
{
    if (m_USB == 0)
    {
        return;
    }
    write(m_USB, message.toUtf8(), message.length());
}

std::string TTYUSB::getfirstTTYUSB(std::string dir, std::string find)
{
  DIR *dpdf;
  struct dirent *epdf;

  std::string out = "empty"; // ,dir = "/dev/";
  // TODO: better handle this with an error enum like success, failed, ...
  dpdf = opendir(dir.c_str());

  // std::cout <<"Tried to open sth TTY"<< std::endl;
  if (dpdf != NULL) {
    while ((epdf = (readdir(dpdf)))) {
      std::string str(epdf->d_name);

      if (str.find(find.c_str()) != std::string::npos) {
        std::cout << epdf->d_name << '\n';
        out = dir + str;
      }
    }
  }
  closedir(dpdf);
  //std::cout << out;
  return out;
}
