#include "ppmload.h"
#include<stdio.h>

//参考　教科書p154

void thresholding(struct ppmimg *src, struct ppmimg *dst, unsigned char threshold);
unsigned char roundAngle(unsigned char angle);

char dstName[256] = {0};


int main(void){
	int i;
	char inputTxt[256] = {0};
	unsigned char threshold = 0;
	struct ppmimg *image1=NULL, *image2=NULL;

	sprintf(dstName, "thresholding");

	do{
		fflush(stdin);
		printf("閾値(0~255): ");
		scanf("%d", &threshold);
	}while(threshold < 0 && threshold >= 256);

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("LENNA.pgm",image1);
	image2 = createppmimage(image2, image1->iwidth, image1->iheight, image1->cmode);
	thresholding(image1, image2, threshold);

	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
}

void thresholding(struct ppmimg *src, struct ppmimg *dst, unsigned char threshold){
	int x, y;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
			struct RGBColor trgb = getPnmPixel(src, x, y);
			struct RGBColor dstrgb; 
			if(src->cmode == 1){
				if(trgb.dens > threshold){
					dstrgb.dens = 255;
				}
				else{
					dstrgb.dens = 0;
				}
			}
			else{
				puts("入力画像はグレースケールにしてください。");
				continue;
			}
			setPnmPixel(dst,x,y,dstrgb);
		}
	}
	sprintf(dstName, "%s%d.pgm", _dstName, threshold);
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
