#include "ppmload.h"
#include<stdio.h>

//参考　教科書p154

void sizeCvtNearestNeighbor(struct ppmimg *src, struct ppmimg *dst, double scale);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);
unsigned char max(unsigned char a, unsigned char b, unsigned char c);
unsigned char roundAngle(unsigned char angle);

char dstName[256] = {0};


int main(void){
	int i;
	unsigned char ave = 0;
	char inputTxt[256] = {0};
	double scale = 1;
	struct ppmimg *image1=NULL, *image2=NULL;

//	inputScale(&scale);

	puts("何倍に拡大しますか?");
    printf("倍率: ");
	fflush(stdin);
    scanf("%lf", &scale);
	
	sprintf(dstName, "sizeCvtNearestNeighbor");

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("Lenna.ppm",image1);
	image2 = createppmimage(image2, (int)(image1->iwidth*scale), (int)(image1->iheight*scale),image1->cmode);
	sizeCvtNearestNeighbor(image1, image2, scale);

	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
}
/*
void inputScale(double &scale){
	puts("何倍に拡大しますか?");
    printf("倍率: ");
	fflush(stdin);
    scanf("%s", scale);
	
	sprintf(dstName, "sizeCvtNearestNeighbor");
}
*/
void sizeCvtNearestNeighbor(struct ppmimg *src, struct ppmimg *dst, double scale){
	int x, y;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
	//		struct RGBColor trgb = getPnmPixel(src,x,y);
			if(src->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
                // 四捨五入して最近傍を求める
                // scaleは拡大率
                int xp = (int)(x / scale);
                int yp = (int)(y / scale);
                
                if (xp < src->iwidth && yp < src->iheight) {
                    struct RGBColor trgb = getPnmPixel(src, xp, yp);
                    setPnmPixel(dst, x, y, trgb);
				}
			}
		//	setPnmPixel(dst,x,y,trgb);
		}
	}
	sprintf(dstName, "%s.ppm", _dstName);
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

unsigned char roundAngle(unsigned char angle)
{
	if(angle < 0)
		return angle + 360;
	else if(angle >= 360)
		return angle - 360;
}
