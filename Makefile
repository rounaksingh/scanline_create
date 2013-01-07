
#
#
#Makefile for the test_avi_header.c
#

GCC = gcc

SOURCE = bmp_create
SOURCE_EXT = c

EXT_SOURCE = bmp.c

all   :   compile

compile : 
	$(GCC) $(SOURCE).$(SOURCE_EXT) $(EXT_SOURCE) -o $(SOURCE) -lm   #-Wall

clean :
	rm -f $(SOURCE)
