#include "ppmload.h"
#include "cvtGray.h"
#include<stdio.h>

#define ALPHA 0.2

void alphaBlending(struct ppmimg *forward, struct ppmimg *back, struct ppmimg *srcAlpha, struct ppmimg *dst);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);
unsigned char max(unsigned char a, unsigned char b, unsigned char c);

char dstName[256] = {0};


int main(void){
	int i;
	unsigned char ave = 0;
	double intxt = 0;
	char dstNameGray[256] = {0};
	struct ppmimg *image1=NULL, *image2=NULL, *image3 = NULL, *image4 = NULL;
	fflush(stdin);
	sprintf(dstName, "alphaBlending");
	sprintf(dstNameGray, dstName);

	image1 = makeimagestruct(image1);
	loadppmimage("Lenna.ppm",image1);
	image2 = makeimagestruct(image2);
	loadppmimage("milkdrop.ppm",image2);
	image3 = makeimagestruct(image3);
	image4 = makeimagestruct(image4);
	
	image3 = createppmimage(image3, image1->iwidth, image1->iheight,image1->cmode);
	image4 = createppmimage(image4, image1->iwidth, image1->iheight, 1);
	
	cvtGray(image2, image4, &dstNameGray[0]);
	alphaBlending(image2, image1, image4, image3);

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);
	deleteppmimg(image4);

	return 0;
}


void alphaBlending(struct ppmimg *forward, struct ppmimg *back, struct ppmimg *srcAlpha, struct ppmimg *dst){
	int x, y;
	double tmp = 1;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
			if(forward->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
				struct RGBColor forwardRGB = getPnmPixel(forward, x, y);
				struct RGBColor backRGB = getPnmPixel(back, x, y);
				struct RGBColor alpha = getPnmPixel(srcAlpha, x, y);
				struct RGBColor trgb3;
				trgb3.R = (unsigned char)((256-alpha.dens)/(double)256*backRGB.R + alpha.dens/(double)256*forwardRGB.R);
				trgb3.G = (unsigned char)((256-alpha.dens)/(double)256*backRGB.G + alpha.dens/(double)256*forwardRGB.G);
				trgb3.B = (unsigned char)((256-alpha.dens)/(double)256*backRGB.B + alpha.dens/(double)256*forwardRGB.B);
				setPnmPixel(dst, x, y, trgb3);
			}
		}
	}
	sprintf(dstName, "%s.ppm", _dstName);
	printf("%s\n", dstName);
	saveppmimage(dst, dstName);
}

//*/
unsigned char min(unsigned char a, unsigned char b, unsigned char c)
{
	if(a < b){
		if(a < c) return a;
	}
	else{
		if(b < c) return b;
	}
	return c;
}

unsigned char max(unsigned char a, unsigned char b, unsigned char c)
{
	if(a > b){
		if(a > c) return a;
	}
	else{
		if(b > c) return b;
	}
	return c;
}
