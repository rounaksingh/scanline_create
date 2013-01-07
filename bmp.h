
/*=============================================================================
  bmplib, a simple library to create, modify, and write BMP image files.
  Copyright (C) 2009 by Zack T Smith.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  The author may be reached at fbui@comcast.net.
 *============================================================================*/

#ifndef _BMP_H
#define _BMP_H

typedef struct {
	int width, height;
	unsigned long *pixels;
} BMP;

#define MINIFONT_HEIGHT (8)

extern BMP* BMP_new (int, int);
extern void BMP_delete (BMP*);
extern void BMP_clear (BMP*, unsigned long);
extern int BMP_write (BMP*, char *path);
extern BMP *BMP_read (char *path);
extern void BMP_point (BMP*, int, int, unsigned long);
extern void BMP_line (BMP *, int x0, int y0, int x1, int y1, unsigned long);
extern void BMP_hline (BMP *, int x0, int x1, int y, unsigned long);
extern void BMP_vline (BMP *, int x, int y0, int y1, unsigned long);
extern void BMP_rect (BMP *, int x, int y, int w, int h, unsigned long);
extern void BMP_fillrect (BMP *, int x, int y, int w, int h, unsigned long);
extern unsigned long BMP_getpixel (BMP*, int, int);

#define RGB_BLACK (0)
#define RGB_GRAY (0xc0c0c0)
#define RGB_RED (0xff0000)
#define RGB_MAGENTA (0xff00ff)
#define RGB_GREEN (0xff00)
#define RGB_DARKGREEN (0x6400)
#define RGB_BLUE (0xff)
#define RGB_WHITE (0xffffff)
#define RGB_YELLOW (0xffff00)
#define RGB_CYAN (0xffff)
#define RGB_NAVYBLUE (0x80)
#define RGB_DARKORANGE (0xff8c00)
#define RGB_PURPLE (0xa020f0)

//File Handling Error
#define ERROR_HEADER_LEN_INVALID 2
#define ERROR_BMP_FILE_OPEN 3

//Header Details
#define HDR_START 0

//#define 


#endif

