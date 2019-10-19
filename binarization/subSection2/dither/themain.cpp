#include "ppmload.h"
#include<stdio.h>

//参考　教科書p154

void pixelize(struct ppmimg *src, struct ppmimg *dst, int minBlock);
unsigned char roundAngle(unsigned char angle);

char dstName[256] = {0};


int main(void){
	int i;
	unsigned char ave = 0;
	char inputTxt[256] = {0};
	int minBlock8 = 8;
	int minBlock16 = 16;
	struct ppmimg *image1=NULL, *image2=NULL, *image3=NULL;

	sprintf(dstName, "pixelize");

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("Lenna.ppm",image1);
	image2 = createppmimage(image2, image1->iwidth, image1->iheight, image1->cmode);
	image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);
	pixelize(image1, image2, minBlock8);
	pixelize(image1, image3, minBlock16);

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}

void pixelize(struct ppmimg *src, struct ppmimg *dst, int minBlock){
	int x, y;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
			struct RGBColor trgb = getPnmPixel(src, x, y);
			if(src->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{

			}
			setPnmPixel(dst,x,y,trgb);
		}
	}
	sprintf(dstName, "%sMinBlock%d.ppm", _dstName, minBlock);
	saveppmimage(dst, dstName);
}


unsigned char roundAngle(unsigned char angle)
{
    while(angle < 0 && angle >= 256){
	    if(angle < 0)
		    angle = angle + 256;
	    else if(angle >= 256)
		    angle =  angle - 256;
    }
    return angle;
}
