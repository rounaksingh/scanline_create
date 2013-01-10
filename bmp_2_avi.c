/*************************************************************************

	Program Name: Rewa
	Author: Rounak Singh Narde
	email: rounaksingh17@gmail.com
	
		This program is written for the purpose of converting bmp files 
	into avi video container without any compression. This program can 
	set the frame rate & other features.
	
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "bmp.h"
#include "avilib.h"
#include "bmp_2_avi.h"

/**********************************************************************************
 *
 *	Function to write a bmp file to the avi frame 
 *	It takes BMP struct, avi_t struct a frame_no & avi output filename
 *	(i.e bmp filename)
 *	
 *	frame_no can be considered as infile nunber (bmp file no)
 ***********************************************************************************/
int bmp_2_frame(BMP *bmp,avi_t *avi,long frame_no)
{
		unsigned char *buf;
		int width,height,x,y;
		unsigned long rgb;
		unsigned long frameSize;		//total data of one frame in bytes

		//Temporary pointer to deal with buffer manipulation
		unsigned char *temp_buf_pointer;
		
		//getting the width & height of the frame
		width=avi->width;
		height=avi->height;
		
		//we are considering bytes per pixels	 3		rbg
		frameSize=height*width*3;

		//allocate memory for temporary buffer
		buf=malloc(sizeof(unsigned char)*frameSize);
		if(buf==NULL)
		{
			fprintf(stderr,"Memory Not Allocated");
			return AVI_ERR_NO_MEM;
		}

		temp_buf_pointer=buf;
		
		/*
			This will read the whole bmp pixels ( size of long 4 bytes) into memory
			as avi frame buffer.( size of 1 bytes)
		*/
		for(int y=0;y<height;y++)
		{
			for(int x=0;x<width;x++)	
			{
				rgb=BMP_getpixel (bmp,x,y);
				//store blue byte at first in buffer
				*temp_buf_pointer=(unsigned char)(rgb & MASK);
				temp_buf_pointer++;
				//store green byte afterwards
				*temp_buf_pointer=(unsigned char)((rgb>>8) & MASK);
				temp_buf_pointer++;
				//At last store red byte
				*temp_buf_pointer=(unsigned char)((rgb>>16) & MASK);
				temp_buf_pointer++;
				
			}
		}
	
	//To write the frame of the video file.
	if(AVI_write_frame(avi,buf,frameSize))
	{
		return AVI_ERR_WRITE;
	}
		
	free (buf);
	return 0;
	
}
