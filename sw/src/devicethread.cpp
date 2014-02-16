#include "devicethread.h"

DeviceThread::DeviceThread()
{
  exit = false;
}

void DeviceThread::finish()
{
  exit = true;
}

DeviceThread::run()
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
        wait(3000);
        notConnected();
        continue;
      }
      else
        connected();
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
        //TODO:
      }
    }

    //Wait for some time period. Number chosen at random as prime.
    wait(635);
  }
}

void DeviceThread::enqueue(const Command_t & c)
{
  cmd.enqueue(c);
}
