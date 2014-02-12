#ifndef DEVICETHREAD_H
#define DEVICETHREAD_H

#include <QThread>

class DeviceThread : public QThread
{
  Q_OBJECT

  public:
    DeviceThread();

  protected:
    void run();
};

#endif
