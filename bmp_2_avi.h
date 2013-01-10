/***************************************************************



****************************************************************/
#define ERROR_AVI_FILE_OPEN 1
#define ERROR_LESS_ARGUMENT 2

#define OUTFILENAME_LEN 30
#define INFILENAME_LEN 30

#define MASK 0x000000ff

int bmp_2_frame(BMP *bmp,avi_t *avi,long frame_no);
