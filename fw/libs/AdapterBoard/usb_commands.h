/* USB commands use the first byte as the 'type' variable.
 * Subsequent bytes are generally the 'arguments'.
 * So host->device usb packets usually look like:
 * [command, arg1, arg2, 0, 0, ... , 0, 0]
 * to which the device will respond with
 * [CMD_ACK, command, 0, 0, 0 ..., 0, 0]
 *
 * The exception to this, are the commands which 'GET'
 * For them host->device generally looks like:
 * [command, 0, ..., 0, 0]
 * to which the device responds
 * [CMD_RESP, command, arg1, arg2, 0, ..., 0, 0]
 * */

#ifndef USB_COMMANDS_H
#define USB_COMMANDS_H

#define CMD_ACK          0xAF
#define CMD_RESP         0xBF

#define CMD_BL_ON        0x10
#define CMD_BL_OFF       0x11
#define CMD_BL_LEVEL     0x12
#define CMD_BL_UP        0x13
#define CMD_BL_DOWN      0x14
#define CMD_BL_GET_STATE 0x1F

#define CMD_RGB_SET      0x20
#define CMD_RGB_GET      0x2F

#define IS_GET(x) (x == CMD_RGB_GET || x == CMD_BL_GET_STATE)

#endif
