#include "ppmload.h"
#include<stdio.h>

struct CMYKColor {
	unsigned char C, M, Y, K;
};

struct CMYKColor RGB2CMYK(struct RGBColor);
void setPnmPixelCMYK(struct ppmimg* simg,int x,int y,struct CMYKColor _cmyk);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
//	struct CMYKColor tcmyk;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("Lenna.ppm",image1);
	cloneppmimage(image1,image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);
	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(image1,i,j);
			struct CMYKColor tcmyk;
			if(image1->cmode == 1){
				printf("ファイルタイプが違います。");
				//trgb.dens = 255 - trgb.dens;
			}else{
				/*
				trgb.R = 255 - trgb.R;
				trgb.G = 255 - trgb.G;
				trgb.B = 255 - trgb.B;
				//*/

				tcmyk = RGB2CMYK(trgb);
			}
			setPnmPixelCMYK(image3,i,j,tcmyk);
		}
	}
	saveppmimage(image3,"RGB2CMYK.ppm");
	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}

struct CMYKColor RGB2CMYK(struct RGBColor rgbTmp)
{
	struct CMYKColor cmyk;
	cmyk.K = 255 - min(255 - rgbTmp.R, 255 - rgbTmp.G, 255 - rgbTmp.B);
	cmyk.C = 255 - rgbTmp.R - cmyk.K;
	cmyk.M = 255 - rgbTmp.G - cmyk.K;
	cmyk.Y = 255 - rgbTmp.B - cmyk.K;

	return cmyk;
}

void setPnmPixelCMYK(struct ppmimg* simg,int x,int y,struct CMYKColor _cmyk){
	if(simg->cmode==3){
		unsigned long cindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode;
		unsigned long mindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode+1;
		unsigned long yindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode+2;
		simg->dat[cindex] = _cmyk.C;
		simg->dat[mindex] = _cmyk.M;
		simg->dat[yindex] = _cmyk.Y;
	}else{
		printf("エラー\n");
	}
}

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
