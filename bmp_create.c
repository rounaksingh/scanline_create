/*************************************************************************
gcc Template
*************************************************************************/

#include<stdio.h>
#include "bmp.h"

int main(int argc,char *argv[],char *env[])
{
	
	BMP *bmp;
	int i;
	char *p="example_1.bmp";
	char *o="example_test.bmp";
	bmp=BMP_read (p);
	
	if(bmp!=NULL)
	{
		printf("%d\n",i);
		printf("%d %d \n",bmp->width,bmp->height);
	}
	
	i=BMP_write (bmp,o);
	printf("%d\n",i);

	return 0;
}
