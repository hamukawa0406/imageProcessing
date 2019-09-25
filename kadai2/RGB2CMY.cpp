#include "ppmload.h"
#include<stdio.h>

struct CMYColor {
	unsigned char C, M, Y;
};

struct CMYColor RGB2CMY(struct RGBColor);
void setPnmPixelCMY(struct ppmimg* simg,int x,int y,struct CMYColor _cmy);

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
//	struct CMYColor tcmy;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("Lenna.ppm",image1);
	cloneppmimage(image1,image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);
	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(image1,i,j);
			struct CMYColor tcmy;
			if(image1->cmode == 1){
				printf("ファイルタイプが違います。");
				//trgb.dens = 255 - trgb.dens;
			}else{
				/*
				trgb.R = 255 - trgb.R;
				trgb.G = 255 - trgb.G;
				trgb.B = 255 - trgb.B;
				//*/

				tcmy = RGB2CMY(trgb);
			}
			setPnmPixelCMY(image3,i,j,tcmy);
		}
	}
	saveppmimage(image3,"RGB2CMY.ppm");
	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}

struct CMYColor RGB2CMY(struct RGBColor rgbTmp)
{
	struct CMYColor cmy;
	cmy.C = 255 - rgbTmp.R;
	cmy.M = 255 - rgbTmp.G;
	cmy.Y = 255 - rgbTmp.B;

	return cmy;
}

void setPnmPixelCMY(struct ppmimg* simg,int x,int y,struct CMYColor _cmy){
	if(simg->cmode==3){
		unsigned long cindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode;
		unsigned long mindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode+1;
		unsigned long yindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode+2;
		simg->dat[cindex] = _cmy.C;
		simg->dat[mindex] = _cmy.M;
		simg->dat[yindex] = _cmy.Y;
	}else{
		printf("エラー\n");
	}
}