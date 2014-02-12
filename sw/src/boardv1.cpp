#include "boardv1.h"

BoardV1::BoardV1()
{
  dev = NULL;
  libusb_init = false;
}

BoardV1::~BoardV1()
{
  if(dev != NULL)
  {
    libusb_release_interface(dev, 0);
    libusb_close(dev);
  }
  libusb_exit(NULL);
}

int BoardV1::attachDevice()
{
  int ret;

  if(!libusb_init)
  {
    ret = libusb_init(NULL);
    if(ret != 0)
      return -1;
    libusb_init = true;
  }

  dev = libusb_open_device_with_vid_pid(NULL, VID, PID);
  if(dev == NULL)
    return -2;

  ret = libusb_kernel_driver_active(dev, 0);
  if(ret == 1)
  {
    ret = libusb_kernel_driver_detach(dev, 0);
    if(ret != 0)
      return -3;
  }

  ret = libusb_claim_interface(dev, 0);
  if(ret != 0)
    return -4;

  return 0;
}

int BoardV1::sendCmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
  if(!dev)
    return;

  //Send the command
  uint8_t buf[EP_LEN];
  buf[0] = cmd;
  buf[1] = arg1;
  buf[2] = arg2;
  buf[3] = arg3;
  int actual, ret;
  ret = libusb_bulk_transfer(EP_OUT, buf, EP_LEN, &actual, USB_TIMEOUT);
  if(ret != 0)
    return -1;
  if(actual < 4)
    return -2;

  //Read the acknowledgment
  ret = libusb_bulk_transfer(EP_IN, buf, EP_LEN, &actual, USB_TIMEOUT);
  if(ret != 0)
    return -3;
  if(buf[0] != CMD_ACK)
    return -4;
  if(buf[1] != cmd)
    return -5

  return 0;
}
