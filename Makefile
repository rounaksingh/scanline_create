
#
#
#Makefile for the test_avi_header.c
#

GCC = gcc

SOURCE = scanline_create
SOURCE_EXT = c

EXT_SOURCE = bmp.c bmp_2_avi.c avilib.c

all   :   compile

compile : 
	$(GCC) $(SOURCE).$(SOURCE_EXT) $(EXT_SOURCE) -o $(SOURCE) -std=c99 \
	-L/usr/local/lib -lusb-1.0
	#-Wall 

clean :
	rm -f $(SOURCE)
