Scanline Create
===============

Written by :Rounak Singh
Working Environment: Linux
Compiler: Gnu C(gcc)

>Description
This Program creates 12 frames of scanlines connecting all IR_RX & IR_TX.
This program uses bmp picture format, but doesn't save it. But directly
makes frame for avi & saves it & increasing the speed of execution.
It doesn't receives data from USB now, but creates rx_data buffer by itself
using get_rx_data function.


no_of_rx=96
no_of_tx=12

>Must Take width as a multiple of no of rx. 
width= 672
height=400

>This variables decides the gap between rx & tx. gap must be integer.
gap_bet_rx=width*2/no_ir_rx;
gap_bet_tx=width*2/no_ir_tx;

>To change the thickness of the line on rx side.Note: divide it with even number
,so that mean_dis will alway remain integer. Note: Pixels can be integer only.
mean_dis=gap_bet_rx/4;

>To change the frame rate. vlc doesn't play video fps<3, so to view it on vlc use fps>=3.
fps=1.0;

>To change color of line change RGB_BLACK in function "line_create_per_tx_per_rx"
to RGB_* from bmp.h.

>To change data received, change rx_data in function "get_rx_data".Remember, line 
will draw when data is zero.

>To change video filename, change the "avi_outfilename" variable.

>Note to free the memory space that have been alloted to the pointer & variables.
execute bmp_delete, AVI_close, rx_data_free, IR_RX_free, IR_TX_free.

