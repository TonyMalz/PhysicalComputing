/*******************************************************
 *            Serial Communication                     *
 *                                                     *
 *                                                     *
 * this code allows communication with a serial device *
 * according to POSIX, i.e., it should work at least   *
 * on Linux, Mac, and many other Unix/BSD systems      *
 * around. For Windows, you may want to consult the    *
 * source code of "avrdude" and look into the files    *
 * serial.h and ser_win32.c                            *
 * see: http://www.nongnu.org/avrdude/                 *
 *                                                     *
 * The only function of interest is:                   *
 *                                                     *
 * int configureSerial(int fd, int baudrate);          *
 * fd       : file handle as returned by open          *
 * baudrate : desired baudrate                         *
 * RETURN   : fd if sucessfull, negative number in     *
 *            case of error (- errno)                  *
 *                                                     *
 ******************************************************/

#ifndef __SERIAL_H__
#define __SERIAL_H__

int configureSerial(int fd, long baudrate); // set baudrate 


#endif