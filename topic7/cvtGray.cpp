#include "ppmload.h"
#include<stdio.h>

#define ALPHA 0.2

void alphaBlending(struct ppmimg *src1, struct ppmimg *src2, struct ppmimg *dst, double alpha);

unsigned char Lut[256] = {0};
char dstName[256] = {0};

int main(void){
	unsigned char Lut[256] = {0};
	int i, channel;
	struct ppmimg *image1=NULL, *image2=NULL, *image3=NULL;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("Lenna.ppm",image1);
	loadppmimage("Sailboat.ppm", image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);
	alphaBlending(image1, image2, image3, ALPHA);

	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
}


void alphaBlending(struct ppmimg *src1, struct ppmimg *src2, struct ppmimg *dst, double alpha){
	int x, y;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
			if(src1->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
				struct RGBColor trgb1 = getPnmPixel(src1, dst->iwidth, dst->iheight);
				struct RGBColor trgb2 = getPnmPixel(src2, dst->iwidth, dst->iheight);
				struct RGBColor trgb3;
				trgb3.R = (unsigned char)((1-alpha)*trgb1.R + alpha*trgb2.R);
				trgb3.G = (unsigned char)((1-alpha)*trgb1.G + alpha*trgb2.G);
				trgb3.B = (unsigned char)((1-alpha)*trgb1.B + alpha*trgb2.B);
				setPnmPixel(dst, dst->iwidth, dst->iheight, trgb3);
			}
		}
		printf("どうしよ\n");
	}
	sprintf(dstName, "%s.ppm", _dstName);
	printf("%s\n", dstName);
	saveppmimage(dst, dstName);
}

