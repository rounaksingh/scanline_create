/*****************************************************************
	bmp_create.h

******************************************************************/

//Macros
#define GAP_BETWEEN_RX 16
#define GAP_BETWEEN_TX 20

//
#define RET_LINE_CREATED 0
#define RET_LINE_NOT_CREATED 1
#define ERR_NOT_MALLOC 1
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

