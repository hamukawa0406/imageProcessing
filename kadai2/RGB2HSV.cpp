#include "ppmload.h"
#include<stdio.h>

#define EQUAL_NUM -1

struct HSVColor {
	unsigned char H, S, V;
};

struct HSVColor RGB2HSV(struct RGBColor);
void setPnmPixelHSV(struct ppmimg* simg,int x,int y,struct HSVColor _hsv);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);
unsigned char max(unsigned char a, unsigned char b, unsigned char c);
unsigned char roundAngle(unsigned char angle);

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
//	struct HSVColor thsv;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("Lenna.ppm",image1);
	cloneppmimage(image1,image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);
	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(image1,i,j);
			struct HSVColor thsv;
			if(image1->cmode == 1){
				printf("ファイルタイプが違います。");
				//trgb.dens = 255 - trgb.dens;
			}else{
				/*
				trgb.R = 255 - trgb.R;
				trgb.G = 255 - trgb.G;
				trgb.B = 255 - trgb.B;
				//*/

				thsv = RGB2HSV(trgb);
			}
			setPnmPixelHSV(image3,i,j,thsv);
		}
	}
	saveppmimage(image3,"RGB2HSV.ppm");
	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}

struct HSVColor RGB2HSV(struct RGBColor rgbTmp)
{
	struct HSVColor hsv;
	unsigned char maxColor = max(rgbTmp.R, rgbTmp.G, rgbTmp.B);
	unsigned char minColor = min(rgbTmp.R, rgbTmp.G, rgbTmp.B);

	if(rgbTmp.R == rgbTmp.G && rgbTmp.G == rgbTmp.B){
		hsv.H = 0;
	}
	else{
		if(maxColor == rgbTmp.R){
			hsv.H = 60 * ((rgbTmp.G - rgbTmp.B) / (maxColor - minColor));
		}
		else if(maxColor == rgbTmp.G){
			hsv.H = 60 * ((rgbTmp.B - rgbTmp.R) / (maxColor - minColor)) + 120;
		}
		else if(maxColor == rgbTmp.B){
			hsv.H = 60 * ((rgbTmp.R - rgbTmp.G) / (maxColor - minColor)) + 240;
		}
		else{
			printf("エラー\n");
		}

		if(hsv.H < 0 || hsv.H >= 360)
			hsv.H = roundAngle(hsv.H);
	}
	//後で0~360から外れる値を丸める処理書いとけよ俺 <- 書いたぞ、俺

	hsv.S = (maxColor - minColor) / maxColor * 255;
	hsv.V = maxColor;

	return hsv;
}

void setPnmPixelHSV(struct ppmimg* simg,int x,int y,struct HSVColor _hsv){
	if(simg->cmode==3){
		unsigned long cindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode;
		unsigned long mindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode+1;
		unsigned long yindex = (simg->iwidth)*y*simg->cmode+x*simg->cmode+2;
		simg->dat[cindex] = _hsv.H;
		simg->dat[mindex] = _hsv.S;
		simg->dat[yindex] = _hsv.V;
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

unsigned char roundAngle(unsigned char angle)
{
	if(angle < 0)
		return angle + 360;
	else if(angle >= 360)
		return angle - 360;
}
