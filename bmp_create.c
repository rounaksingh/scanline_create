/*************************************************************************

*************************************************************************/

#include<stdio.h>
#include <malloc.h>
#include "bmp.h"
#include "bmp_create.h"

IR_RX * ir_rx_init(int no_of_rx)
{
	IR_RX *nu_ir_rx;
	IR_RX *nu_ir_rx_local;
	int rx_counter=0;
	
	nu_ir_rx=(IR_RX *)malloc(sizeof(IR_RX)*no_of_rx);
	if(nu_ir_rx==NULL)
	return NULL;

	//memset (nu, 0, sizeof (BMP));
	nu_ir_rx_local=nu_ir_rx;
	

	while(rx_counter<(no_of_rx/2))
	{
		nu_ir_rx_local->pos_x=(gap_bet_rx/2)+(gap_bet_rx * rx_counter);
		nu_ir_rx_local->pos_y=0;
		nu_ir_rx_local++;
		rx_counter++;
	}

	rx_counter=0;

	while(rx_counter<(no_of_rx/2))
	{
		nu_ir_rx_local->pos_x=(gap_bet_rx/2)+(gap_bet_rx * rx_counter);
		nu_ir_rx_local->pos_y=height;
		nu_ir_rx_local++;
		rx_counter++;
	}
	return nu_ir_rx;
}	
		
IR_TX * ir_tx_init(int no_of_tx)
{
	IR_TX *nu_ir_tx;
	IR_TX *nu_ir_tx_local;
	int tx_counter=0;
	
	nu_ir_tx=(IR_TX *)malloc(sizeof(IR_TX)*no_of_tx);
	if(nu_ir_tx==NULL)
	return NULL;

	//memset (nu, 0, sizeof (BMP));
	nu_ir_tx_local=nu_ir_tx;
//////////////////////////////////////////////////////////////////////////	
	//first nu_ir_rx_local

	
	while(tx_counter<(no_of_tx/2))
	{
		nu_ir_tx_local->pos_x=(gap_bet_tx/2)+(gap_bet_tx * tx_counter);
		nu_ir_tx_local->pos_y=height;
		nu_ir_tx_local++;
		tx_counter++;
	}
	
	tx_counter=0;
	
	while(tx_counter<(no_of_tx/2))
	{
		nu_ir_tx_local->pos_x=(gap_bet_tx/2)+(gap_bet_tx * tx_counter);
		nu_ir_tx_local->pos_y=0;
		nu_ir_tx_local++;
		tx_counter++;
	}
	
	return nu_ir_tx;
}	

unsigned char *get_rx_data()
{
// USB Procedure
	unsigned char *rx_data_local;
	unsigned char *nu_rx_data;
	//NEED TO CHANGE WHEN NO OF RECEIVER CHANGES
	no_of_rx_data_bytes=12;

	nu_rx_data=malloc(sizeof(unsigned char)*no_of_rx_data_bytes);
	if(nu_rx_data==NULL)
	return NULL;

	rx_data_local=nu_rx_data;

	int i=0;
	while(i<no_of_rx_data_bytes)
	{
		//0 means tsop output zero
		//0xff means tsop output high for one module.
		*rx_data_local=0xff;
		//Testing one by one..
		if(i==3)
		*rx_data_local=0x7f;
		
		rx_data_local++;
		i++;
	}
	
	return nu_rx_data;

// USB Procedure

}


int line_create_per_tx_per_rx(BMP * bmp, IR_RX * ir_rx, IR_TX * ir_tx, unsigned char * rx_data, unsigned char mask)
{
	int counter=0;
	//Check TSOP OUTPUT=0 for line draw
	//i.e. ! is used
	if(!((*rx_data) & mask))
	{
		for(counter=-(mean_dis);counter<=mean_dis;counter++)
		{
			BMP_line(bmp,(ir_rx->pos_x)+counter,ir_rx->pos_y,ir_tx->pos_x,ir_tx->pos_y,RGB_BLACK);
		}
		return RET_LINE_CREATED;
	}
			
	return RET_LINE_NOT_CREATED;

}


int line_create_per_tx(BMP *bmp, IR_RX *ir_rx,int no_of_ir_rx, IR_TX *ir_tx, unsigned char *rx_data)
{
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

int scan_line_create(BMP *bmp, IR_RX *ir_rx,int no_of_ir_rx, IR_TX *ir_tx,int no_of_ir_tx,unsigned char *rx_data)
{
	int counter;
	for(counter=0;counter<no_of_ir_tx;counter++)
	{
		line_create_per_tx(bmp,ir_rx,no_of_ir_rx,ir_tx,rx_data);
		ir_tx++;
	}
	
	return 0;
}	 
int main(int argc,char *argv[],char *env[])
{
	//char *outfilename=malloc(sizeof(unsigned char)*30);
	//*outfilename="";
	char *outfilename="test_3.bmp";
	BMP *bmp;
	int ret_val;
	IR_RX *ir_rx_ptr;
	IR_TX *ir_tx_ptr;

	
	
	no_ir_rx=96;
	//no_ir_tx=5;
	no_ir_tx=12;
	//width must be divided by the no_of_rx & no_of tx.
	//It is recommended to take width as a multiple of both.
	width= 672;
	height=400;
	
	//Here we are talking to put rx & tx on the width
	//so we have calculated gap_bet_rx like this.
	gap_bet_rx=width*2/no_ir_rx;
	gap_bet_tx=width*2/no_ir_tx;
	
	mean_dis=gap_bet_rx/2;
	
	bmp=BMP_new(width,height);
	
	ir_rx_ptr=ir_rx_init(no_ir_rx);
	if(ir_rx_ptr==NULL)
	{
		printf("IR_RX_PTR: cannot allocate memory.");
		return 1;
	}

	ir_tx_ptr=ir_tx_init(no_ir_tx);
	if(ir_tx_ptr==NULL)
	{
		printf("IR_TX_PTR: cannot allocate memory.");
		return 1;
	}
	

	rx_data=get_rx_data();
	if(rx_data==NULL)
	{
		printf("get_rx_data: cannot allocate memory");
		return 1;
	}
	
	scan_line_create(bmp,ir_rx_ptr,no_ir_rx,ir_tx_ptr,no_ir_tx,rx_data);
	
	//line_create_per_tx_per_rx(bmp,ir_rx_ptr,ir_tx_ptr,rx_data,0x80);
	printf("%d %d\n",ir_rx_ptr->pos_x,ir_rx_ptr->pos_y);
	BMP_write (bmp, outfilename);
	
	return 0;
}
