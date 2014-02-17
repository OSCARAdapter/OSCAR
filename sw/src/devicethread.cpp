#include "devicethread.h"
#include "usb_commands.h"

DeviceThread::DeviceThread()
{
  exit = false;
}

void DeviceThread::finish()
{
  exit = true;
}

void DeviceThread::run()
{
  int ret;
  while(!exit)
  {
    if(!board.isConnected())
    {
      ret = board.attachDevice();
      if(ret < 0)
      {
        //Failed to attach
        sleep(3000);
        emit notConnected();
        continue;
      }
      else
        emit connected();
    }

    //Connected, do actual work in this thread...

    //Update status
    getBacklightState();

    //Process command queue
    while(!cmd.isEmpty())
    {
      Command_t c = cmd.dequeue();
      if(!IS_GET(c.cmd))
        board.sendCmd(c.cmd, c.arg1, c.arg2, c.arg3);
      else
      {
        uint8_t buf[EP_LEN];
        board.sendCmd(c.cmd, c.arg1, c.arg2, c.arg3, buf);
        if(buf[0] == CMD_RESP && buf[1] == CMD_BL_GET_STATE)
          emit(backlightResponse(buf[2], buf[3]));
      }
    }

    //Wait for some time period. Number chosen at random as prime.
    sleep(635);
  }
}

void DeviceThread::enqueue(const Command_t & c)
{
  cmd.enqueue(c);
}

void DeviceThread::getBacklightState()
{
  Command_t c;
  c.cmd = CMD_BL_GET_STATE;
  enqueue(c);
}

void DeviceThread::setBacklightPower(bool on)
{
  Command_t c;
  if(on)
    c.cmd = CMD_BL_ON;
  else
    c.cmd = CMD_BL_OFF;
  enqueue(c);
}

void DeviceThread::setBacklightLevel(int level)
{
  Command_t c;
  c.cmd = CMD_BL_LEVEL;
  c.arg1 = level;
  enqueue(c);
}
