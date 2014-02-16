#ifndef BOARDV1_H
#define BOARDV1_H

#include <libusb.h>

#define VID 0xaaaa
#define PID 0x1234
#define EP_LEN 64
#define EP_IN 0x81
#define EP_OUT 0x02
#define USB_TIMEOUT 500

#define uint8_t unsigned char

class BoardV1
{
  public:
    BoardV1();
    ~BoardV1();

    //Attempts to attach to the device
    //Returns <0 on failure, 0 on success
    int attachDevice();
    bool isConnected();

    //Sends the command with arguments and waits for an ACK
    //Buf is required to be EP_LEN in size
    int sendCmd(uint8_t cmd);
    int sendCmd(uint8_t cmd, uint8_t* buf);
    int sendCmd(uint8_t cmd, uint8_t arg1);
    int sendCmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3);
    int sendCmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t* buf);

  private:
    libusb_device_handle *dev;
    bool libusb_is_init;
};

#endif
