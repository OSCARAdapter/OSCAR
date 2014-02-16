#include "boardv1.h"
#include "usb_commands.h"
#include <string.h>

BoardV1::BoardV1()
{
  dev = NULL;
  libusb_is_init = false;
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

  if(!libusb_is_init)
  {
    ret = libusb_init(NULL);
    if(ret != 0)
      return -1;
    libusb_is_init = true;
  }

  dev = libusb_open_device_with_vid_pid(NULL, VID, PID);
  if(dev == NULL)
    return -2;

  ret = libusb_kernel_driver_active(dev, 0);
  if(ret == 1)
  {
    ret = libusb_detach_kernel_driver(dev, 0);
    if(ret != 0)
      return -3;
  }

  ret = libusb_claim_interface(dev, 0);
  if(ret != 0)
    return -4;

  return 0;
}

int BoardV1::sendCmd(uint8_t cmd)
{
  return sendCmd(cmd, 0, 0, 0, NULL);
}

int BoardV1::sendCmd(uint8_t cmd, uint8_t* buf)
{
  return sendCmd(cmd, 0, 0, 0, buf);
}

int BoardV1::sendCmd(uint8_t cmd, uint8_t arg1)
{
  return sendCmd(cmd, arg1, 0, 0, NULL);
}


int BoardV1::sendCmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
  return sendCmd(cmd, arg1, arg2, arg3, NULL);
}

int BoardV1::sendCmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t* readBuf)
{
  if(!dev)
    return -6;

  //Send the command
  uint8_t buf[EP_LEN];
  buf[0] = cmd;
  buf[1] = arg1;
  buf[2] = arg2;
  buf[3] = arg3;
  int actual, ret;
  ret = libusb_bulk_transfer(dev, EP_OUT, buf, EP_LEN, &actual, USB_TIMEOUT);
  if(ret != 0)
    return -1;
  if(actual < 4)
    return -2;

  //Read the acknowledgment/response
  ret = libusb_bulk_transfer(dev, EP_IN, buf, EP_LEN, &actual, USB_TIMEOUT);
  if(ret != 0)
    return -3;
  if(!(buf[1] == cmd && (buf[0] == CMD_ACK || buf[0] == CMD_RESP)))
    return -4;

  if(readBuf != NULL)
    memcpy(&readBuf, buf, EP_LEN);

  return 0;
}

bool BoardV1::isConnected()
{
  if(!dev)
    goto fail;

  uint8_t buf[EP_LEN];
  buf[0] = CMD_BL_GET_STATE;
  int actual, ret;
  ret = libusb_bulk_transfer(dev, EP_OUT, buf, EP_LEN, &actual, USB_TIMEOUT);
  if(ret != 0)
    goto fail;

  //Get ACK
  ret = libusb_bulk_transfer(dev, EP_IN, buf, EP_LEN, &actual, USB_TIMEOUT);
  if(ret != 0)
    goto fail;
  if(buf[0] != CMD_RESP && buf[1] != CMD_BL_GET_STATE)
    goto fail;

  return true;

fail:
  dev = NULL;
  return false;
}
