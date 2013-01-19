/*************************************************************************

	Program Name: create_scanline
	Author: Rounak Singh Narde
	email: rounaksingh17@gmail.com
	
		This program is written for the purpose of creating scanline video(avi file)
		using the data from the TSOP receiver.This program can set the frame rate 
		width & height of video. No of Receiver & transmitter can be set here.
		It is important to note that USB device VID & PID is set using the macros 
		provided in "create_scanline.h".
	
*************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "libusb.h"
#include "avilib.h"
#include "bmp.h"
#include "scanline_create.h"
#include "bmp_2_avi.h"

/***********************************************************

	Function Name: ir_rx_init
	Parameters: no_of_rx(int)
	Description: This function initizlizes the 
				struct IR_RX. It allocates memory space
				to struct depending upon the no_of_rx.
				It also sets the position of the rx on
				image depending upon no_of_rx, width & 
				height of image.
	Return Value: It returns the pointer to initiazed struct
				IR_RX.
***********************************************************/
IR_RX * ir_rx_init(int no_of_rx)
{
	//temporary pointers
	IR_RX *nu_ir_rx;
	IR_RX *nu_ir_rx_temp;
	//receiver counter
	int rx_counter=0;

	//Allocating memory for nu_ir_rx	
	nu_ir_rx=(IR_RX *)malloc(sizeof(IR_RX)*no_of_rx);
	//check if allocated or not
	if(nu_ir_rx==NULL)
	return NULL;
	
	//a temp ptr for Initialization Purpose
	nu_ir_rx_temp=nu_ir_rx;
	
	//Providing value to IR_RX *
	//x changes depending upon gap_bet_rx & rx_counter
	//y=0
	//Means TOP line of sensors.
	while(rx_counter<(no_of_rx/2))
	{
		nu_ir_rx_temp->pos_x=(gap_bet_rx/2)+(gap_bet_rx * rx_counter);
		nu_ir_rx_temp->pos_y=0;
		nu_ir_rx_temp++;
		rx_counter++;
	}

	//Again, initializes counter for bottom line.
	rx_counter=0;
	
	//Providing value to IR_RX *
	//x changes depending upon gap_bet_rx & rx_counter
	//y=height
	//Means BOTTOM line of sensors.
	while(rx_counter<(no_of_rx/2))
	{
		nu_ir_rx_temp->pos_x=(gap_bet_rx/2)+(gap_bet_rx * rx_counter);
		nu_ir_rx_temp->pos_y=height;
		nu_ir_rx_temp++;
		rx_counter++;
	}
	
	return nu_ir_rx;
}

/************************************************************

	Function Name: IR_RX_free
	Parameter: IR_RX *
	Description: It dellocates the memory space.
	Return Value:void
	
************************************************************/
void IR_RX_free(IR_RX *ir_rx)
{
	if (ir_rx==NULL)
	return;
	//deallocates the memory space.
	free(ir_rx);	
}

/***********************************************************

	Function Name: ir_tx_init
	Parameters: no_of_tx(int)
	Description: This function initizlizes the 
				struct IR_TX. It allocates memory space
				to struct depending upon the no_of_tx.
				It also sets the position of the rx on
				image depending upon no_of_tx, width & 
				height of image.
	Return Value: It returns the pointer to initiazed struct
				IR_TX.
***********************************************************/
IR_TX * ir_tx_init(int no_of_tx)
{
	//temporary pointers
	IR_TX *nu_ir_tx;
	IR_TX *nu_ir_tx_local;
	//counter for transmitter
	int tx_counter=0;
	
	//allocating memory space for nu_ir_tx
	nu_ir_tx=(IR_TX *)malloc(sizeof(IR_TX)*no_of_tx);
	//check whether memory space is provided or not
	if(nu_ir_tx==NULL)
	return NULL;

	//a temp ptr for Initialization Purpose
	nu_ir_tx_local=nu_ir_tx;

	//Providing value to IR_TX *
	//x changes depending upon gap_bet_tx & tx_counter
	//y=0
	//Means TOP line of transmitters.
	while(tx_counter<(no_of_tx/2))
	{
		nu_ir_tx_local->pos_x=(gap_bet_tx/2)+(gap_bet_tx * tx_counter);
		nu_ir_tx_local->pos_y=0;
		nu_ir_tx_local++;
		tx_counter++;
	}
	
	//Again, initializes counter for bottom line.
	tx_counter=0;
	
	//Providing value to IR_TX *
	//x changes depending upon gap_bet_tx & tx_counter
	//y=height
	//Means BOTTOM line of transmitters.
	while(tx_counter<(no_of_tx/2))
	{
		nu_ir_tx_local->pos_x=(gap_bet_tx/2)+(gap_bet_tx * tx_counter);
		nu_ir_tx_local->pos_y=height;
		nu_ir_tx_local++;
		tx_counter++;
	}
	
	return nu_ir_tx;
}	

/************************************************************

	Function Name: IR_TX_free
	Parameter: IR_TX *
	Description: It dellocates the memory space.
	Return Value:void
	
************************************************************/
void IR_TX_free(IR_TX *ir_tx)
{
	if (ir_tx==NULL)
	return;
	
	//deallocates memory space.
	free(ir_tx);	
}

/*************************************************************
	Function Name: rx_data_init
	Parameters: void
	Description: This function initializes the memory space 
			for the rx_data.
	Return Value: It returns the pointer to the rx_data.
			The pointer is of unsigned char type.
			
**************************************************************/
unsigned char *rx_data_init()
{

	unsigned char *nu_rx_data;

	//NEED TO CHANGE WHEN NO OF RECEIVER CHANGES
	//no_of_rx_data_bytes=12;
	nu_rx_data=malloc(sizeof(unsigned char)*RX_BUFFER_LENGTH);
	if(nu_rx_data==NULL)
	return NULL;

	return nu_rx_data;

}

/************************************************************

	Function Name: rx_data_free
	Parameter: rx_data pointer
	Description: It dellocates the memory space.
	Return Value:void
	
************************************************************/
void rx_data_free(unsigned char *rx_data_ptr)
{
	if (rx_data_ptr==NULL)
	return;
	
	//deallocates memory space.
	free(rx_data_ptr);	
}

/************************************************************

	Function Name: get_rx_data
	Parameter: rx_data pointer
	Description: It transfers the data via USB & put it in buffer
				provided.
	Return Value: SUCCESS or FAIL.
	
************************************************************/
int get_rx_data(unsigned char *rx_data_ptr)
{
	int ret_val;
	int transfer_retry=0;
	while(1)
	{
		ret_val=libusb_bulk_transfer(devh,RX_EP,rx_data_ptr,RX_BUFFER_LENGTH,actual_length,TRANSFER_TIMEOUT);
		
		if(ret_val==LIBUSB_SUCCESS)
		{
			//break while loop
			break;
		}
		
		//Check for ret_val from function "libusb_bulk_transfer"
		switch(ret_val)
		{
			case LIBUSB_ERROR_IO:
			{
				printf("libusb_bulk_transfer: Error Input/Output.\n");
				break;
			}
			case LIBUSB_ERROR_INVALID_PARAM:
			{
				printf("libusb_bulk_transfer: Error-Invalid \
				Parameter.\n");
				break;
			}
			case LIBUSB_ERROR_ACCESS:
			{
				printf("libusb_bulk_transfer: Error-Access Denied\n.");
				break;
			}
			case LIBUSB_ERROR_NO_DEVICE:
			{
				printf("libusb_bulk_transfer: Error-No Device with \
				VID: %d & PID: %d Connected.\n",VID,PID);
				break;
			}
			case LIBUSB_ERROR_NOT_FOUND:
			{
				printf("libusb_bulk_transfer: Error-Entity Not \
				Found.\n");
				break;
			}
			case LIBUSB_ERROR_BUSY:
			{
				printf("libusb_bulk_transfer: Error-Resource Busy.\n");
				break;
			}
			case LIBUSB_ERROR_TIMEOUT:
			{
				printf("libusb_bulk_transfer: Error-Transfer \
				Timeout.\n");
				break;
			}
			case LIBUSB_ERROR_OVERFLOW:
			{
				printf("libusb_bulk_transfer: Error-Buffer Overflow.\n");
				break;
			}
			case LIBUSB_ERROR_PIPE:
			{
				printf("libusb_bulk_transfer: Error-USB Pipe.\n");
				break;
			}
			case LIBUSB_ERROR_INTERRUPTED:
			{
				printf("libusb_bulk_transfer: Error-System call \
				interrupted.\n");
				break;
			}
			case LIBUSB_ERROR_NO_MEM:
			{
				printf("libusb_bulk_transfer: Error-No Memory.\n");
				break;
			}
			case LIBUSB_ERROR_NOT_SUPPORTED:
			{
				printf("libusb_bulk_transfer: Error-Operation not \
				supported or unimplemented on this platform.\n");
				break;
			}
			default:
			{
				printf("libusb_bulk_transfer: Error-Others.\n");
				break;
			}
		
		}
		
		//retry increases whenever transfer fails
		transfer_retry++;
		//if retry fails for MAX_TRANSFER_RETRY times than return to calling function.
		if(transfer_retry>=MAX_TRANSFER_RETRY)
		{
			printf("No of Retry = %d.\n",MAX_TRANSFER_RETRY);
			return TRANSFER_FAIL;
		}

	}

	return TRANSFER_SUCCESS;
}

/************************************************************
	Function Name: line_create_per_tx_per_rx
	Parameter: BMP *, IR_RX *, IR_TX *, rx_data & mask.
	Description: This function creates a line between one IR_RX
			& IR_TX using the rx_data bytes & mask provided. 
	Return Value: it returns Success & Failure value.		
	
*************************************************************/
int line_create_per_tx_per_rx(BMP * bmp, IR_RX * ir_rx, IR_TX * ir_tx, unsigned char * rx_data, unsigned char mask)
{
	int counter=0;
	//Check TSOP OUTPUT=0 for line draw
	//i.e. ! is used
	if(!((*rx_data) & mask))
	{
		//This is done for creating widthen line on receiver side.
		for(counter=-(mean_dis);counter<=mean_dis;counter++)
		{
			//draw line from rx to tx
			BMP_line(bmp,(ir_rx->pos_x)+counter,ir_rx->pos_y,ir_tx->pos_x,ir_tx->pos_y,RGB_BLACK);
		}
		return RET_LINE_CREATED;
	}
			
	return RET_LINE_NOT_CREATED;

}

/************************************************************
	Function Name: line_create_per_tx
	Parameter: BMP *, IR_RX *,no_of_rx, IR_TX *, rx_data & mask.
	Description: This function creates scanline between all IR_RX
			& an IR_TX using the rx_data bytes & mask provided.
			It calls line_create_per_tx_per_rx.
	Return Value: it returns Success & Failure value.		
	
*************************************************************/
int line_create_per_tx(BMP *bmp, IR_RX *ir_rx,int no_of_ir_rx, IR_TX *ir_tx, unsigned char *rx_data)
{
	//mask is to get one bit
	unsigned char mask=0x80;
	int ret_val;
	int counter=0;
	
	while(counter<no_of_ir_rx)
	{
		ret_val=line_create_per_tx_per_rx(bmp,ir_rx,ir_tx,rx_data,mask);
		
		//ret_val can be checked.
		//increase the IR_RX pointer 
		//to point to next receiver
		ir_rx++;
		
		//Shift right the mask for next receiver output.
		mask=mask>>1;
		
		//if mask=0 means 8 IR_RX are processed.
		//so do mask=0x80 & increase rx_data by one.
		if(mask==0)
		{
			mask=0x80;
			rx_data++;
		}
		//The counter for receiver or bits in rx_data increases
		//till no_of_ir_rx
		counter++;
		
	}
	
	return 0;
}

/************************************************************
	Function Name: scan_line_create
	Parameter: BMP *, IR_RX *,no_of_rx, IR_TX *, no_of_tx, rx_data & mask.
	Description: This function creates scanlines between all IR_RXs
			& IR_TXs using the rx_data bytes by get_rx_data provided. 
	Return Value: it returns 0.		
	
*************************************************************/
int scan_line_create(BMP *bmp, IR_RX *ir_rx,int no_of_ir_rx, IR_TX *ir_tx,\
int no_of_ir_tx,unsigned char *rx_data)
{
	int counter;
	int ret_val;
	for(counter=0;counter<no_of_ir_tx;counter++)
	{
		//GET RX DATA for one ir_tx through USB
		//it returns only two val SUCCESS or FAIL
		ret_val=get_rx_data(rx_data);
		if(ret_val==TRANSFER_FAIL)
		{
			printf("get_rx_data: Transfer Failed.\n");
			return TRANSFER_FAIL;
		}

		line_create_per_tx(bmp,ir_rx,no_of_ir_rx,ir_tx,rx_data);
		ir_tx++;
	}
	
	return 0;
}

/************************************************************
	Function Name: program_exit
	Parameter: return_value,BMP *, IR_RX *,IR_TX *, *rx_data,bmp *, avi*,\
			*compressor,*actual_length .
	Description: This function free all memory space acquired by program.
	Return Value: it returns return_value.
	
*************************************************************/
int program_exit(int return_value, IR_RX *ir_rx,IR_TX *ir_tx,unsigned char *rx_data,\
BMP *bmp,avi_t *avi,char *compressor,int *actual_length)
{
	//call memory deallocation functions for safe exit
	libusb_exit(NULL);
	IR_RX_free(ir_rx);
	IR_TX_free(ir_tx);
	rx_data_free(rx_data);	
	BMP_delete (bmp);
	AVI_close(avi);
	free(compressor);
	free(actual_length);
	
	return return_value;	
	
}

/************************************************************
	Function Name: main
	Parameter: argc, * argv[].
	Description: This function is main, responsible for 
			initialization & calling other function to 
			complete create_scanline task. 
	Return Value: it returns Success & Failur value.		
	
*************************************************************/
int main(int argc,char *argv[],char *env[])
{
	//char *outfilename=malloc(sizeof(unsigned char)*30);
	//*outfilename="";
	//char *outfilename="test_3.bmp";
	
	
	BMP *bmp;
	int ret_val;
	IR_RX *ir_rx_ptr;
	IR_TX *ir_tx_ptr;
	
	//////////////////////////////////////////////////////////////////////////////
	//Declaration & Initialization of the AVI video variables
	avi_t *avi = NULL;						//points to opened avi file
	char *avi_outfilename="test.avi";			//avi outfilename
	double fps;							//frame rate
	//Frames per second
	//fps=3.0;
	fps=20.0;
	
	//Compression is important for init of avi header
	//Compression needs 4 bytes of NULL So,,
	char *compressor=malloc(4); 		//4 bytes for type of compressor
	char *c;
	c=compressor;
	for(int i=0;i<4;i++)
	{
		*c=0;
		c++;
	}
	/////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////
	//Initialization about numbers of transmitters & receivers.
	//Most of the values, that are needed to provide, are set here.
	/////////////////////////////////////////////////////////////////////////////
	no_ir_rx=96;
	//no_ir_rx=8;
	//no_ir_tx=5;
	no_ir_tx=12;
	//no_ir_tx=1;
	
	//width & height of the bmp image
	//width must be divided by the no_of_rx & no_of tx.
	//It is recommended to take width as a multiple of both.
	width= 672;
	height=400;
	
	//Here we are talking to put rx & tx on the width
	//so we have calculated gap_bet_rx like this.
	gap_bet_rx=width*2/no_ir_rx;
	gap_bet_tx=width*2/no_ir_tx;
	
	//need to make the rx side scanline bold 
	//so this mean distance is calculated from rx.
	//It should be less than gap_bet_rx/2, otherwise 
	//overlapping of scanline with eachother starts.
	mean_dis=gap_bet_rx/4;
	///////////////////////////////////////////////////////////////////////////////////
	//For libusb.. actual size defines the size of datatype for rx_data
	actual_length=malloc(sizeof(int));
	*actual_length=1;
	/////////////////////////////////////////////////////////////////////////
	
	//initialization of the bmp pointer using width & height.
	bmp=BMP_new(width,height);
	
	
	
	//IR RX & TX Initialization
	ir_rx_ptr=ir_rx_init(no_ir_rx);
	if(ir_rx_ptr==NULL)
	{
		printf("IR_RX_PTR: cannot allocate memory.\n");
		program_exit(ERR_NOT_MALLOC,ir_rx_ptr,ir_tx_ptr,rx_data,bmp,avi,compressor,actual_length);
	}
	
	ir_tx_ptr=ir_tx_init(no_ir_tx);
	if(ir_tx_ptr==NULL)
	{
		printf("IR_TX_PTR: cannot allocate memory.\n");
		program_exit(ERR_NOT_MALLOC,ir_rx_ptr,ir_tx_ptr,rx_data,bmp,avi,compressor,actual_length);
	}
	
	//Initialize the rx_data
	rx_data=rx_data_init();
	if(rx_data==NULL)
	{
		printf("rx_data: cannot allocate memory.\n");
		program_exit(ERR_NOT_MALLOC,ir_rx_ptr,ir_tx_ptr,rx_data,bmp,avi,compressor,actual_length);
 	}
	
	//Intialization of libusb
	ret_val = libusb_init(NULL);
	if (ret_val < 0)
	{
		printf("libusb_init: Error initializing.\n");
		program_exit(ERR_NOT_INIT_LIBUSB,ir_rx_ptr,ir_tx_ptr,rx_data,bmp,avi,compressor,actual_length);
	}
	
	//Now waiting for the device to connect
	//device with VID & PID (defined in scanline_create.h) 
	printf("\nWaiting for device to connect...\n");
	while(1)
	{
		//This is added to reduce CPU usage.
		//This will create 2 second delay for connecting to device
		sleep(2);
		//
		//open device with VID & PID 
		devh = libusb_open_device_with_vid_pid(NULL,VID,PID);
		
		//continue looping if device not found.
		if (devh == NULL)
		{
			//printf("libusb_open_device: Error opening the device.");
			//return ERR_NOT_INIT_LIBUSB;
			continue;
		}
		else
		{	
			//if device found, break the loop
			printf("libusb_open_device: Device with VID:%d & \
			PID:%d opened.\n",VID,PID);
			break;
		}
		
		
	}
	
		
///////////////////////////////////////////////////////////////////////////////////////
	
	printf("\nInitializing Receiver...\n");
	
	//create frame for avi
	//one frame means forming image for all IR_RX & IR_TX for all rx_data
	while(1)
	{
		//To create output file with name=avi_outfilename
	avi = AVI_open_output_file(avi_outfilename);
	if (avi == 0) {
	     fprintf(stderr, "error %s: %s\n", avi_outfilename, AVI_strerror());
		program_exit(ERROR_AVI_FILE_OPEN,ir_rx_ptr,ir_tx_ptr,rx_data,bmp,avi,compressor,actual_length);
	}
	
	//To set the property of the avi video
	AVI_set_video(avi,width,height,fps,compressor);
	
		for(frame_no=1;frame_no<=MAX_FRAME_NO;frame_no++)
		{
		
			//CREATE A bmp pointer of scanlines using the rx_data
			scan_line_create(bmp,ir_rx_ptr,no_ir_rx,ir_tx_ptr,no_ir_tx,rx_data);
	
			//line_create_per_tx_per_rx(bmp,ir_rx_ptr,ir_tx_ptr,rx_data,0x80);
		//	printf("%d %d\n",ir_rx_ptr->pos_x,ir_rx_ptr->pos_y);
		//	BMP_write (bmp, outfilename);
	
			//convert bmp to frame & write to avi outfile
		 	int ret_val=bmp_2_frame(bmp,avi,frame_no);
		 	if(ret_val==AVI_ERR_WRITE)
		 	{
		 		printf("\nAVI Error:Frame Write\n");
		 		break;
		 	}
		 	if(ret_val==AVI_ERR_NO_MEM )
		 	{
		 		printf("\nAVI Error:No memory for Temporary Buffer\n");
		 		break;
		 	}
		 	
		 	//after one frame is created do clear the bmp for next frame
		 	BMP_clear (bmp, RGB_WHITE);
		}
		
	//print no_of_frame processed or formed.
	printf("\nNo of frames in avi outfile: %ld\n",AVI_video_frames(avi));
		AVI_close(avi);
		}	
		
		
	program_exit(0,ir_rx_ptr,ir_tx_ptr,rx_data,bmp,avi,compressor,actual_length);	
	
	
}
