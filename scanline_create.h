/*****************************************************************
	bmp_create.h

******************************************************************/

#ifndef SCANLINE_CREATE_H
#define SCANLINE_CREATE_H

//Macros
//#define GAP_BETWEEN_RX	16
//#define GAP_BETWEEN_TX 	20
#define RX_BUFFER_LENGTH	12
#define MAX_FRAME_NO		10

//
#define RET_LINE_CREATED		0
#define RET_LINE_NOT_CREATED 	1
#define ERR_NOT_MALLOC 		1
#define ERR_NOT_INIT_LIBUSB 	2

#define TRANSFER_FAIL			3
#define TRANSFER_SUCCESS		4

//Macros for libusb
#define EP_INTR			(1 | LIBUSB_ENDPOINT_IN)
#define EP_DATA			(2 | LIBUSB_ENDPOINT_IN)
#define CTRL_IN			(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN)
#define CTRL_OUT		(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT)
#define USB_RQ			0x04
#define INTR_LENGTH		64

#define VID 		0x1cbe
#define PID 		0x0003
#define TX_EP 	0x01				// transmit bullk endpoint
#define RX_EP 	0x81				// receive bulk endpoint
#define TRANSFER_TIMEOUT 		10000 // timeout is in msec
#define MAX_TRANSFER_RETRY		5	


//variables
int width;
int height;
int no_ir_rx;
int no_ir_tx;
unsigned char *rx_data;			//per byte : 8 receiver output
int no_of_rx_data_bytes;
int gap_bet_tx;
int gap_bet_rx;
int mean_dis;
static struct libusb_device_handle *devh = NULL;
int *actual_length;

//GLOBAL for TESTING
long frame_no;

//Struct defination
//structure for IR transmitter (LED)
typedef struct
{
	int pos_x;
	int pos_y;
}
IR_TX;

//structure for IR receiver (TSOP)
typedef struct
{
	int pos_x;
	int pos_y;
}
IR_RX;


//function prototypes
IR_RX * ir_rx_init(int no_of_rx);
void IR_RX_free(IR_RX *ir_rx);
IR_TX * ir_tx_init(int no_of_tx);
void IR_TX_free(IR_TX *ir_tx);
unsigned char *rx_data_init();
void rx_data_free(unsigned char *rx_data_ptr);
int get_rx_data(unsigned char *rx_data_ptr);
int line_create_per_tx_per_rx(BMP * bmp, IR_RX * ir_rx, IR_TX * ir_tx,\
 unsigned char * rx_data, unsigned char mask);
int line_create_per_tx(BMP *bmp, IR_RX *ir_rx,int no_of_ir_rx, IR_TX *ir_tx, unsigned char *rx_data);
int scan_line_create(BMP *bmp, IR_RX *ir_rx,int no_of_ir_rx, IR_TX *ir_tx,\
int no_of_ir_tx,unsigned char *rx_data);
int program_exit(int return_value, IR_RX *ir_rx,IR_TX *ir_tx,unsigned char *rx_data,\
BMP *bmp,avi_t *avi,char *compressor,int *actual_length);

//end of .h file
#endif

