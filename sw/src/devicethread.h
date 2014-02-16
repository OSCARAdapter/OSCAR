#ifndef DEVICETHREAD_H
#define DEVICETHREAD_H

#include <QThread>
#include <QQueue>
#include "boardv1.h"

typedef struct Command
{
  uint8_t cmd;
  uint8_t arg1;
  uint8_t arg2;
  uint8_t arg3;
} Command_t;

class DeviceThread : public QThread
{
  Q_OBJECT

  public:
    DeviceThread();

    void setBacklightPower(bool on);
    void setBacklightLevel(int level);
    void getBacklightState();

    void finish();
    void enqueue(const Command_t & c);

  signals:
    //Called whenever a change in connection state is noticed
    void connected();
    void notConnected();

    //Called as a response to 'GET' commands
    void backlightResponse(bool on, int level);

  protected:
    void run();

  private:
    BoardV1 board;
    bool exit;
    QQueue<Command_t> cmd;
};

#endif
