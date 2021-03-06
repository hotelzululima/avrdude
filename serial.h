/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Copyright (C) 2003-2004  Theodore A. Roth  <troth@openavr.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* $Id: serial.h,v 1.13 2007/01/24 22:43:46 joerg_wunsch Exp $ */

/* This is the API for the generic serial interface. The implementations are
   actually provided by the target dependant files:

   ser_posix.c : posix serial interface.
   ser_win32.c : native win32 serial interface.

   The target file will be selected at configure time. */

#ifndef serial_h
#define serial_h

extern long serial_recv_timeout;
union filedescriptor
{
  int ifd;
  void *pfd;
};

struct serial_device
{
  void (*open)(char * port, long baud, union filedescriptor *fd);
  int (*setspeed)(union filedescriptor *fd, long baud);
  void (*close)(union filedescriptor *fd);

  int (*send)(union filedescriptor *fd, unsigned char * buf, size_t buflen);
  int (*recv)(union filedescriptor *fd, unsigned char * buf, size_t buflen);
  int (*drain)(union filedescriptor *fd, int display);

  int flags;
#define SERDEV_FL_NONE         0x0000 /* no flags */
#define SERDEV_FL_CANSETSPEED  0x0001 /* device can change speed */
};

extern struct serial_device *serdev;
extern struct serial_device serial_serdev;
extern struct serial_device usb_serdev;
extern struct serial_device usb_serdev_frame;
extern struct serial_device avrdoper_serdev;

#define serial_open (serdev->open)
#define serial_setspeed (serdev->setspeed)
#define serial_close (serdev->close)
#define serial_send (serdev->send)
#define serial_recv (serdev->recv)
#define serial_drain (serdev->drain)

#endif /* serial_h */
