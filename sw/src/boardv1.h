#ifndef BOARDV1_H
#define BOARDV1_H

#define VID 0xaaaa
#define PID 0x1234
#define EP_LEN 64
#define EP_IN 0x81
#define EP_OUT 0x02
#define USB_TIMEOUT 500

class BoardV1
{
  public:
    BoardV1();
    ~BoardV1();

    //Attempts to attach to the device
    //Returns <0 on failure, 0 on success
    int attachDevice();

    //Convenience methods
    int blOn();
    int blOff();
    int blLevel(int level);

  private:
    //Sends the command with arguments and waits for an ACK
    //Must NOT be used with a 'GET' command
    int sendCmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3);

    libusb_device_handle *dev;
    bool libusb_init;
};

#endif
