#include "ppmload.h"
#include<stdio.h>

//参考　教科書p154

void pixelize(struct ppmimg *src, struct ppmimg *dst, int minBlock);
void averaging(struct ppmimg *src, int i, int j, int minBlock, struct RGBColor *aveRGB);
void setAveRGB(struct ppmimg *dst, int i, int j, int minBlock, struct RGBColor trgb);
unsigned char roundAngle(int angle);

char dstName[256] = {0};


int main(void){
	int i;
	unsigned char ave = 0;
	char inputTxt[256] = {0};
	int minBlock8 = 8;
	int minBlock16 = 16;
	struct ppmimg *image1=NULL, *image2=NULL, *image3=NULL;

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
	int i = 0;
	char _dstName[256];
	sprintf(_dstName, "pixelize");
	for(y=0; y < dst->iheight; y += minBlock){
		for(x=0; x<dst->iwidth; x += minBlock){
			struct RGBColor trgb;
			averaging(src, x, y, minBlock, &trgb);
			setAveRGB(dst, x, y, minBlock, trgb);
			i++;
		}
	}
	sprintf(dstName, "%sMinBlock%d.ppm", _dstName, minBlock);
	saveppmimage(dst, dstName);
}

void averaging(struct ppmimg *src, int i, int j, int minBlock, struct RGBColor *aveRGB){
	int x, y;
	int R = 0;
	int G = 0;
	int B = 0;
	for(y = j; y < j+minBlock; y++){
		for(x = i; x < i+minBlock; x++){
			struct RGBColor trgb = getPnmPixel(src, x, y);
			if(src->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
				R += trgb.R;
				G += trgb.G;
				B += trgb.B;
			}
		}
	}
	aveRGB->R = roundAngle(R/(minBlock*minBlock));
	aveRGB->G = roundAngle(G/(minBlock*minBlock));
	aveRGB->B = roundAngle(B/(minBlock*minBlock));
	
}

void setAveRGB(struct ppmimg *dst, int i, int j, int minBlock, struct RGBColor aveRGB){
	int x, y;
	for(y = j; y < j+minBlock; y++){
		for(x = i; x < i+minBlock; x++){
			if(dst->cmode == 1){
				puts("出力画像です");
				continue;
			}
			else{
				setPnmPixel(dst, x, y, aveRGB);
			}
		}
	}
}



unsigned char roundAngle(int angle)
{
    while(angle < 0 && angle >= 256){
	    if(angle < 0)
		    angle = angle + 256;
	    else if(angle >= 256)
		    angle =  angle - 256;
    }
    return angle;
}
